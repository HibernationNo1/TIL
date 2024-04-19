# hwmon

리눅스에서 하드웨어 센서(예: 온도, 전압, 팬 속도)의 정보를 읽기 위한 인터페이스를 제공하는 도구

`hwmon` 인터페이스는 `/sys/class/hwmon/` 디렉토리 아래에서 찾을 수 있으며, 여러 하드웨어 모니터링 도구나 프로그램이 이 인터페이스를 사용하여 시스템 정보를 사용자에게 제공한다.

- `prometheus.yml`

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
        - targets: ['192.168.110.18:9100'] # Node Exporter가 실행 중인 호스트와 포트
  ```

  - `192.168.110.18` 가 localhost의 IP와 일치하더라도, `localhost`가 아닌 IP를 입력해야 한다.

- `docker-compose.yml`

  node-exporter를 설치하지 않아도 동작하는경우가 있고, 아닌경우가 있다.

  아닌 경우는 docker로 설치

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
  
    node-exporter:
      image: 'prom/node-exporter:v1.7.0'
      container_name: 'node-exporter'
      command:
        - '--collector.hwmon'
      volumes:
        - '/sys:/host/sys:ro'   # data를 수집하기 위해 `/sys` 위치를 읽기 전용으로 mount(변경 불가능)
      extra_hosts:            
        - 'host.docker.internal:host-gateway'   # container에서 host의 network에 접근하기 위한 설정 (network resource나 service에 접근이 필요시)
      ports:
      - '9100:9100'
      pid: host                 # host의 namespace를 사용
      restart: unless-stopped   # container가 중단되지 않는 한 자동으로 재시작
  
  # docker-compose -f docker_compose.yml up -d
  ```

  



제대로 적용되었는지 확인하는 방법

http://192.168.110.18:9100/metrics 접속



### Load Node Exporter dashboard

Node Exporter를grafana의 dashboard에 추가하는 방법 (이미 구현된 dashboard를 가져오는 방법이다.)

1. connection 추가 

2. https://grafana.com/grafana/dashboards/12950-hwmon/ 으로 접속 후 `Dashboard ID copy` 버튼 클릭

3. Grafana에서 `Search or jump to...` 창에 `import dashboard` 입력

4. Import via grafana.com 부분에 copy한 dashboard id 복붙 후 `Load`

5. Options 결정

   - Name

     Dashboard이름 결정

   - Folder

     Dashboard를 저장할 Folder이름 결정

   - Unique identifier (UID)

     UID(고유 식별자)는 여러 Grafana 설치 간에 대시보드를 고유하게 식별하는 데 사용.

     UID를 사용하면 대시보드에 액세스하기 위한 일관된 URL을 가질 수 있으므로 대시보드 제목을 변경해도 해당 대시보드에 대한 북마크 링크가 끊어지지 않는다.

   - Prometheus

     connection 결정

   Import 클릭

6. 탐색 시간 결정

   (일반적인 운영 서버 기준)

   - 탐색 범위:`Last 15 minutes`
   - refresh 시간: `5s`

