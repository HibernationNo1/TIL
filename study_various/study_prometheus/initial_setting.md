# exporter



### `prometheus.yml`

```
global:
  scrape_interval: 15s        # metrics를 수집하는 매 시간(defaul: 60s) 
  # evaluation_interval: 60s    # 알람 규칙을 평가하는 간격

scrape_configs:
  - job_name: 'prometheus' # 작업 이름
    static_configs:
      - targets: ['192.168.110.18:9090'] # Prometheus 자체를 스크레이핑 대상으로 추가

  - job_name: 'node_exporter' # Node Exporter scraping 작업
    static_configs:
      - targets: ['192.168.110.18:9100'] 
      
  - job_name: 'dcgm_exporter' 
    static_configs:
      - targets: ['192.168.110.18:9400']
```



### `docker-compose.yml`

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
      - monitering    

  node-exporter:
    image: 'prom/node-exporter:v1.7.0'
    container_name: 'node-exporter'
    ports: 
      - '9100:9100'
    networks:
      - monitering  

  grafana:
    image: 'grafana/grafana:10.0.10-ubuntu'
    container_name: 'grafana'
    ports: 
      - '3000:3000'
    networks:
      - monitering  # prometheus와 통신하기 위한 docker network 설정

  dcgm-exporter:
    image: 'nvidia/dcgm-exporter:3.1.8-3.2.0-b0-ubuntu20.04'
    container_name: 'dcgm-exporter'
    ports: 
      - '9400:9400'
    networks:
      - monitering  # prometheus와 통신하기 위한 docker network 설정

networks:
  monitering:
    name: monitering
# docker-compose -f docker_compose.yml up -d
```

