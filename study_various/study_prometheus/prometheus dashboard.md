# prometheus dashboard

정상적으로 prometheus에 연결을 성공했을 시

`localhost:9090` 으로 접속하면 prometheus dashboard 를 사용할 수 있다.

## Alerts



## Graph

PromQL(prometheus query)을 사용하여 수집된 metrics의 정보를 확인할 수 있다.  



## Status

### Targets

`prometheus.yml`를 구성할 때 포함한 metrics 수집 app들을 확인할 수 있다



```
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
      # prometheus를 docker로 설치하고,
      # 	1. metrics를 수집할 flask_application 또한 container에서 동작한다면
      # 		두 container로 docker network를 연결하고 
      # 		localhost -> container name으로 수정 필요
      # 	2. metrics를 수집할 flask_application은 local에서 동작한다면
      # 		localhost -> local의 IP(192.168.110.18) 로 명시
      
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

위 처럼 구성한 경우 아래와 같이 flask_application 에 대한 status를 확인할 수 있다.

| Endpoint                      | State  | Labels                                                   | Last Scrape | Scrape Duration | Error |
| ----------------------------- | ------ | -------------------------------------------------------- | ----------- | --------------- | ----- |
| http://localhost:5004/metrics | **UP** | **instance="localhost:5004"****job="flask_application"** | 3.408s ago  | 1.963ms         |       |

- `http://localhost:5004/metrics` : 해당 url로 curl 요청을 보내거나 주소로 접속하면 app 에 대한 수집된 metrics 들을 확인할 수 있다. 