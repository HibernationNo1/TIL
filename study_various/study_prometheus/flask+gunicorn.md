# prometheus

prometheus 환경 구축 (with docker)



### `prometheus.yml`

```yaml
global:
  scrape_interval: 15s        # metrics를 수집하는 매 시간(defaul: 60s) 
  # evaluation_interval: 15s    # 알람 규칙을 평가하는 간격

scrape_configs:
  # 필수
  - job_name: 'prometheus' # 작업 이름
    static_configs:
      - targets: ['localhost:9090'] # Prometheus 자체를 scraping 대상으로 추가

  # TODO: docker사용시 어떻게 설정 방법 공부하기
  - job_name: 'node_exporter' # Node Exporter scraping 작업
    # CPU 사용량, 메모리 사용량, 디스크 I/O,네트워크 통계, 시스템 로드와 같은 중요한 서버 수준의 정보를 모니터링
    static_configs:
      - targets: ['localhost:9100'] # Node Exporter가 실행 중인 호스트와 포트

  - job_name: 'flask_application' # Flask 애플리케이션 scraping 작업
    static_configs:
      - targets: ['localhost:5004'] # Flask 애플리케이션이 실행 중인 호스트와 포트
      # prometheus를 docker로 설치하고,
      # 	1. metrics를 수집할 flask_application 또한 container에서 동작한다면
      # 		두 container로 docker network를 연결하고 
      # 		localhost -> container name으로 수정 필요
      # 	2. metrics를 수집할 flask_application은 local에서 동작한다면
      # 		localhost -> local의 IP(192.168.110.18) 로 명시

```



### `docker-compose.yml`

```yaml
version: '3'
services:
  exam_container:
    image: 'exam_image:0.1'
    container_name: 'exam_container'
    ports:
      - '5004:5004'		# 예시 port
    volumes:
      - /etc/localtime:/etc/localtime:ro    # docker외부와 내부의 시간을 동일하게 맞추기 위한 설정
      - ../:/workspace
    ipc: 'host'                             # container 내부의 process가 host의 process와 통신하기 위해 설정.
    shm_size: 8G
    command: /bin/bash                      # container실행 시 /bin/bash 를 실행하기 위해 설정.  docker image의 base image가 `python`인 경우 사용.

    # 개발 중이거나 디버깅을 이유로 container 내부와 상호작용할 경우 필요
    stdin_open: true                        # container가 실행 중일 때 외부에서 user가 container와 상호 작용하기 위해 설정.
    tty: true                               # container 내부에서 terminal을 사용하기 위해 설정.
    networks:
      - exam_network    
    
  prometheus:
    image: 'prom/prometheus:v2.48.0'		# version은 docker hub에서 선택
    container_name: 'prometheus'
    ports: 
      - '9090:9090'	
    volumes:
      - ./prometheus.yml:/etc/prometheus/prometheus.yml			# prometheus.yml 구성 파일을 적절히 위치시켜야 한다.
    networks:
      - exam_network

networks:
  exam_network:
    name: exam_network
    driver: bridge

```









## flask + gunicorn



- requirements.txt

  ```
  prometheus_client==0.19.0
  prometheus_flask_exporter==0.23.0
  ```

  

###  `gunicorn.py`

config 파일 

guicorn의 multi instance processing의 모든 metrics를 통합하여 수집하기 위해선 `GunicornPrometheusMetrics`를 사용해야 한다.

```python
"""gunicorn WSGI server configuration."""
from multiprocessing import cpu_count
import os, os.path as osp

BASE_LOG_DIR = os.getcwd()


def max_workers():
    return cpu_count()

def half_workers():
    return round(cpu_count()/2)


from prometheus_flask_exporter.multiprocess import GunicornPrometheusMetrics
def when_ready(server):
    # master process가 모든 설정을 완료하고 worker process를 스폰하기 직전에 호출
    GunicornPrometheusMetrics.start_http_server_when_ready(8080)

def child_exit(server, worker):
    # worker process가 종료될 때 호출. 
    # 해당 프로세스에 대한 메트릭 데이터를 정리해야 할 필요가 있을 수 있기 때문
    GunicornPrometheusMetrics.mark_process_dead_on_child_exit(worker.pid)

# GunicornPrometheusMetrics를 사용하기 위해 환경변수 `PROMETHEUS_MULTIPROC_DIR` 설정 필요
prometheus_path = '/tmp/prometheus_multiproc_dir_5'
os.environ['PROMETHEUS_MULTIPROC_DIR'] = prometheus_path
os.makedirs(prometheus_path, exist_ok=True)

bind = '0.0.0.0:5004'
max_requests = 1000
worker_class = 'gevent'		# 적정한 worker class사용
workers = half_workers()
timeout = 60
accesslog = osp.join(BASE_LOG_DIR, 'gunicorn.access.log')
access_log_format = '%(h)s %(l)s %(t)s "%(r)s" %(s)s %(b)s "%(a)s" "%(M)s ms"'
errorlog = osp.join(BASE_LOG_DIR, 'gunicorn.error.log') 
pidfile = osp.join(BASE_LOG_DIR, 'gunicorn.pid')
daemon = False

reload = False

```



### `prometheus.py`

prometheus를 활용하여 metrics를 수집하기 위해 각 `metrix`을 정의하여  `PROMETHEUS_REGISTRY`에 할당한다.

```python
from prometheus_client import Gauge, Histogram

PROMETHEUS_REGISTRY = dict()

PROMETHEUS_REGISTRY['memory_usage'] = Gauge('system_memory_usage_bytes', 'System memory usage in bytes')
"""
- apply to code
    PROMETHEUS_REGISTRY['memory_usage_gauge'].set(저장할 값.float)
- PromQL
    - 값 확인
        system_memory_usage_bytes
"""

PROMETHEUS_REGISTRY['request_latency'] = Histogram('request_latency_seconds', 'Description of histogram')
"""
- apply to code
    request_latency = PROMETHEUS_REGISTRY['request_latency']
    @request_latency.time()
- PromQL
    - 값 확인
        request_latency_seconds
    - 5분간의 요청 횟수
        rate(request_latency_seconds_count[5m])/5
    - 5분간의 요청 평균 수행 시간
        rate(request_latency_seconds_sum[5m])/5
"""
```



### `flask_app.py`

```python
import psutil
from flask import Flask
from flask import Flask, request, jsonify

app = Flask(__name__)

from prometheus_flask_exporter import PrometheusMetrics
from handlers.prometheus import PROMETHEUS_REGISTRY
PROMETHEUS_REGISTRY['metrics'] = PrometheusMetrics(app)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5004)
```



```python
from handlers.prometheus import PROMETHEUS_REGISTRY
request_latency = PROMETHEUS_REGISTRY['request_latency']
memory_usage = PROMETHEUS_REGISTRY['memory_usage']

@app.route('/add', methods=['post'])
@request_latency.time()			# prometheus를 사용해서 request latency 측정 및 기록
def add():
    # 요청으로부터 a와 b 파라미터를 받음
    data = request.json  # JSON 본문을 파싱
    a = data['a']
    b = data['b']
        
    # prometheus를 사용해서 메모리 사용량 기록
    memory_usage.set((psutil.virtual_memory().used/psutil.virtual_memory().total))
   
    # 결과 반환
    result = a + b
    return jsonify(result=result)
```

