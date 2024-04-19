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
  prometheus:
    image: 'prom/prometheus:v2.48.0'
    container_name: 'prometheus'
    ports: 
      - '9090:9090'
    volumes:
      - ./prometheus.yml:/etc/prometheus/prometheus.yml		# prometheus.yml 파일 mount

# docker-compose -f docker_compose.yml up -d
```

