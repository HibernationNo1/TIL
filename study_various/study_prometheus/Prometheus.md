# Prometheus

- 시계열 데이터를 수집하고 저장하는 오픈 소스 모니터링 시스템
- 멀티 차원 데이터 모델을 사용하여 시간에 따른 데이터 변화를 쿼리, 시각화하고, 경고를 설정할 수 있다.
- 주로 시스템과 서비스의 성능 모니터링에 사용된다.





# Install

docker를 사용해 설치한다.



### `prometheus.yml`

```
global:
  scrape_interval: 15s        # metrics를 수집하는 매 시간(defaul: 60s) 
  # evaluation_interval: 60s    # 알람 규칙을 평가하는 간격

scrape_configs:
  - job_name: 'prometheus' # 작업 이름
    static_configs:
      - targets: ['192.168.110.18:9090'] # Prometheus 자체를 스크레이핑 대상으로 추가
```



### `docker-compose.yml`

```
version: '3'
services:
  # 사전 준비 (Prometheus는 일반적으로 컨테이너 내부에서 nobody 사용자(UID 65534)로 실행되므로, 이 사용자가 이 디렉터리에 대한 쓰기 권한을 가지고 있어야 한다.)
    # mkdir -p ./prometheus_data
    # sudo chown 65534:65534 ./prometheus_data  
    image: 'prom/prometheus:v2.48.0'
    container_name: 'prometheus_pomission'
    ports: 
      - '9091:9090'   # pomission 만을 위한 prometheus
    volumes:
      - ./prometheus/prometheus.yml:/etc/prometheus/prometheus.yml
      - ./prometheus/prometheus_data:/prometheus/data                    # metrix 데이터를 저장할 DIR을 mount
      # sudo chown -R 65534:65534 prometheus_data
    command:  
      # retention.time 옵션 사용 시 --config.file 의 기본값이 /prometheus/prometheus.yml 로 변경됨
      # 때문에 다시 경로를 바로잡아준다.
      - '--config.file=/etc/prometheus/prometheus.yml'                    
      - '--storage.tsdb.retention.time=365d'			# 데이터 유지 기간
      
# docker-compose -f docker_compose.yml up -d
```





