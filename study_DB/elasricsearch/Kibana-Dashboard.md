# Kibana-Dashboard

Kibana란: elasticsearch 시각화 관리 service



## Analytics

Elasticsearch에 저장 data를 활용하는 여러 기능을 제공한다.



### Discover

Elasticsearch에 저장된 원시 data를 search하고 특정 field의 값을 볼 수 있게 해주는 기능이다.

특정 query나 filter를 사용하여 data를 search하고 결과를 table 또는 JSON 형식으로 볼 수 있게 해준다.



#### index management

Elasticsearch를 구성하는 index를 관리한다

특정 index를 선택하면 index의 `Settings`, `Mappings`을 결정할 수 있다.

- **Settings**

  index를 구성한 shard, replica 등의 resource개수를 결정할 수 있다.

  그 외에도 analyzer, tokenizer, filter 등도 사용자에 맞춰 구성할 수 있다.

- **Mappings**

  index에 추가될 document의 구조를 정의한다.

  Elasticsearch 는 동적 mapping을 지원하기 때문에 미리 정의하지 않아도 index에 document를 새로 추가하면 자동으로 mapping이 생성된다.

  이 때는 처음 추가된 document의 구조를 기준으로 mapping이 결정된다

   

  







### Dashboard

다양한 시각화(차트, 그래프, 지도 등)를 결합하여 custom dashboard를 생성하고 관리한다.



### Canvas

사용자 정의 인포그래픽 및 프레젠테이션을 생성할 수 있는 도구로, 실시간 Elasticsearch 데이터를 사용하여 동적으로 워크패드를 생성하고 스타일링할 수 있다.



### Maps

지리적 데이터를 시각화하는 도구



### Machine Learning

Elasticsearch 데이터에 대한 기계 학습 기능을 제공한다.

비정상적인 패턴, 이상 징후 등을 자동으로 탐지하기 위한 모델을 생성하고 관리할 수 있습니다.



### Visualize Libarary

Elasticsearch 데이터를 다양한 시각화 형태(예: 바 차트, 파이 차트, 지도, 지표 등)로 변환하는 데 사용된다.

각 시각화는 특정 쿼리 및 필터를 기반으로 데이터를 표시하며, 이러한 시각화는 대시보드에 추가될 수 있습니다



## Enterprise Search

### App Search

- 목적

  개발자가 웹사이트, 어플리케이션 또는 모바일 앱에 빠르게 검색 기능을 통합할 수 있게 해준다.

- 특징

  - 간단한 API를 사용하여 쉽게 데이터를 색인화할 수 있다.
  - 실시간 검색 분석, 결과 조정, 검색 UI 툴킷 및 타입헤드 지원과 같은 고급 기능을 제공한다.
  - 튜닝과 분석 도구를 제공하여 검색 경험을 최적화할 수 있다.
  - Kibana 대시보드를 통해 쉽게 관리하고 모니터링 할 수 있다.

### Workplace Search

- 목적

  Workplace Search는 조직 내의 다양한 데이터 소스 (예: Gmail, Google Drive, Slack, Salesforce, SharePoint 등)를 통합하여 직원들이 중앙에서 쉽게 찾을 수 있게 해준다.

- 특징

  - 다양한 데이터 소스와의 쉬운 연결을 제공하여 조직의 모든 정보에 대한 단일 검색 포털을 제공한다.
  - 개인화된 검색 결과를 제공하여 사용자마다 중요한 정보를 즉시 찾을 수 있다.
  - 관리자는 검색 성능을 높이고 데이터의 관련성을 향상시키기 위해 결과를 튜닝할 수 있다.
  - Kibana를 통해 설정, 관리 및 모니터링이 가능하다.



## Observability

운영 팀이 시스템 및 애플리케이션의 행동을 관찰하고 이해하기 위한 도구 및 기능을 제공한다.



### Logs

로그 모니터링을 통해 시스템과 애플리케이션의 활동을 추적한다

- 로그 데이터의 실시간 스트리밍과 분석
- 텍스트 기반의 로그 데이터를 쉽게 검색, 시각화 및 분석할 수 있다.
- 다양한 소스로부터 로그 데이터를 수집하고 집계할 수 있다.





### Metrics

시스템의 성능을 모니터링하고 metrix 데이터를 분석합니다.

- CPU 사용량, 메모리 사용량, 네트워크 활동 등의 핵심 시스템 메트릭을 수집 및 모니터링한다.
- 시각적 대시보드를 통해 성능 지표를 쉽게 확인할 수 있다.



### APM

Application Performance Monitoring, 애플리케이션 성능 모니터링

애플리케이션의 성능을 모니터링하고 문제점을 식별한다.



### Uptime

service와 endpoint의 가용성을 모니터링한다.



### User Experience

실제 사용자의 웹 사이트 및 애플리케이션에서의 경험을 모니터링하고 분석한다.



## Security

보안 정보 및 이벤트 관리 (SIEM) 기능을 제공한다.



### Detections

실시간으로 보안 위협과 유해한 활동을 탐지합니다.

사전 정의된 또는 사용자 지정 룰을 기반으로 위협을 탐지하며, 이상 행동 및 위협 패턴을 자동으로 식별하고 알림을 제공한다.





### Hosts

네트워크 내의 개별 호스트에 대한 보안 이벤트와 행동을 모니터링한다.

호스트의 로그, 프로세스, 네트워크 연결 등의 활동을 추적한다.

각 호스트에 대한 상세한 보안 정보와 관련 이벤트를 제공한다.





### Network

네트워크 트래픽과 연결에 대한 보안 이벤트를 모니터링한다.

- 네트워크 트래픽, 연결 시도, 데이터 전송 등의 활동을 분석한다.

- 네트워크에서의 위협 패턴 및 이상 행동을 탐지한다.



### Timelines

관련 보안 이벤트를 시간 순서대로 시각화하고 분석한다.

- 보안 이벤트의 타임라인을 생성하여 이벤트 간의 연관성 및 패턴을 파악한다.
- 사용자는 직접 타임라인에 이벤트를 드래그 앤 드롭할 수 있다.



### Cases



### Administration





## Management





### Dev Tools

#### Console

Elasticsearch에 RESTful query를 바로 전송할 수 있는 인터페이스를 제공한다.

사용자는 이를 통해 data를 직접 조회하거나 index 설정을 변경하는 등의 작업을 수행할 수 있다. 

>  자동완성 기능도 지원됨
>
> 

#### Search Profiler

 Elasticsearch의 검색 query 성능을 프로파일링하고 분석하는 도구



#### Grok Debugger

 Grok 패턴을 테스트하기 위한 도구입니다. 



### Fleet

### Stack Monitoring

### Stack Management





