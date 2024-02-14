# Grafana

grafana구성 방법



`prometheus.yml`

```
global:
  scrape_interval: 15s        # metrics를 수집하는 매 시간(defaul: 60s) 
  # evaluation_interval: 60s    # 알람 규칙을 평가하는 간격

scrape_configs:
  - job_name: 'prometheus' # 작업 이름
    static_configs:
      - targets: ['localhost:9090'] # Prometheus 자체를 스크레이핑 대상으로 추가

  - job_name: 'flask_app' # Flask 애플리케이션 scraping 작업
    static_configs:
      - targets: ['192.168.110.18:5004'] # Flask 애플리케이션이 실행 중인 호스트와 포트
      # prometheus를 docker로 실행할것이기 때문에 local IP(192.168.110.18)를 기입  (localhost로 표현하면 안된다.)

```



`docker-compose.yml`

```
version: '3'
services:
  prometheus:
    image: 'prom/prometheus:v2.48.0'
    container_name: 'prometheus'
    ports: 
      - '9090:9090'
    volumes:
      - ./prometheus.yml:/etc/prometheus/prometheus.yml
    networks:
      - prometheus_grafana    # grafana와 통신하기 위한 docker network 설정

  grafana:
    image: 'grafana/grafana:10.0.10-ubuntu'
    container_name: 'grafana'
    ports: 
      - '3000:3000'
    networks:
      - prometheus_grafana  # prometheus와 통신하기 위한 docker network 설정


networks:
  kakaortb:
    name: prometheus_grafana
    driver: bridge

# docker-compose -f docker_compose.yml up -d
```



## Data Source(sync prometheus)

### local

`localhost:3000` 으로 접속

최초 ID/PW : `admin`/`admin`



**Data Source 선택** (prometheus연동)

1. 중앙 상단의 `Search or jump tp...` 의 칸에 `Add new connection` 라고 검색

2. Data source 에서 prometheus 검색하여 선택 > 우측 상단 `Create a Prometheus data source` 클릭

3. - Name의 dashboard 이름 입력(연동 한 prometheus 의 dashboard의 이름을 결정한다.)

   - HTTP의 `Prometheus server URL` 부분에 `http://192.168.110.18:9090`입력

      prometheus와 grafana를 모두 docker container로 실행했기 때문에 IP를 명시해야 한다.

4. 페이지 가장 및 `Save & test` 선택



### ssh

