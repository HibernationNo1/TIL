## prometheus

![](https://github.com/HibernationNo1/TIL/blob/master/seminar/images/prometheus/prometheus.png?raw=true)

- 오픈 소스 시스템 모니터링 도구

- 클라우드 기반의 인프라에서 시간에 따른 데이터의 추적을 위해 설계되었다.
- 데이터를 시계열 형태로 기록하며, PromQL 이라는 독자적인 query를 사용하여 데이터를 다양한 방식으로 활용할 수 있다.



#### 설치 방법

docker image를 가져와서 docker build-run을 통해 간단히 설치할 수 있다.

![](https://github.com/HibernationNo1/TIL/blob/master/seminar/images/prometheus/prometheus_docker.png?raw=true)



#### 특징

- **타겟으로 삼은 시스템(또는 APP)으로부터 주기적으로 데이터를 수집한다.**

  수집하는 데이터는 metrics라 불리며, 그 구성 요소는 아래와 같다.

  - **Metrix Name**: Metric의 이름

  - **Labels**: 메트릭스에 추가 정보를 제공하는 키-값 쌍

    라벨을 통해 동일한 메트릭스 이름을 공유하지만 서로 다른 속성(예: API 엔드포인트, HTTP 메소드, 서버 이름 등)을 가진 데이터를 구분할 수 있다.

  - **Sample Value**: 메트릭스의 실제 숫자 값. 이 값은 시간에 따라 변할 수 있으며, Prometheus는 이 시계열 데이터를 주기적으로 수집한다.

  - **Timestamp**: 메트릭스가 수집된 시간. Prometheus는 주로 풀 모델(pull model)을 사용하여 정해진 간격으로 메트릭스를 스크레이핑(scraping)한다.

  그럼 prometheus에서 사용하는 metrics는 어떤 type이 있나?

  - **Counter**: 값이 오직 증가할 수만 있는 메트릭스. 

    예: 처리된 요청 수, 완료된 작업 수 등.

  - **Gauge**: 값이 증가하거나 감소할 수 있는 메트릭스. 

    예: 메모리 사용량, 현재 온도 등.

  - **Histogram**: 수치 데이터를 분포로 나타내며, 특정 구간(bucket)에 데이터가 얼마나 속해 있는지 측정.

    예: 소요시간

  - **Summary**: 히스토그램과 비슷하지만, 특정 퍼센타일의 관측값을 계산할 수 있다.

    수집된 데이터에 대한 세부적인 이해를 얻을 수 있으며, 평균 또는 최대 값만으로는 파악하기 어려운 세밀한 값을 확보할 수 있다.

    예: 소요시간에 대한 퍼센타일

    - Percentiles

      통계에서 사용되는 용어로, 데이터 세트를 백분위 수로 나눈 값.

      - **50번째 퍼센타일 (중앙값)**: 데이터 세트의 정확히 중간에 위치하는 값
      - **90번째 퍼센타일** : 데이터 세트의 상위 90% 의 index에 위치한 값
      - **99번째 퍼센타일** : 데이터 세트의 상위 1% 의 index에 위치한 값

  metrics 데이터를 수집하는 방법은 사용자가 정의할 수 있고, 또는 다른 개발자들이 개발해놓은 수집 tool을 통합하여 사용할 수 있다.

  - 예시

    - node_exporter

      다른 개발자들이 개발해놓은 **node exporter** 라는 exporter

       `/proc/stat `위치에서 CPU관련 데이터를 가져오는데, prometheus 는 이 node exporter와 통신하면서 이 데이터들을 받아낸다.

      ![](https://github.com/HibernationNo1/TIL/blob/master/seminar/images/prometheus/node_exproter_1.png?raw=true)

    - python code에서 데이터 받기

      prometheus python SDK를 활용해 데이터를 수집할 수 있다.

      python에서 특정 함수의 소요시간을 측정하고자 할 때, 아래와 같이 데코레이터 기능을 사용할 수 있다.

      ![](https://github.com/HibernationNo1/TIL/blob/master/seminar/images/prometheus/python_exam.png?raw=true)

    > **exporter란?**
    >
    > 데이터를 수집하는 프로세스를 정의한 하나의 tool
    >
    > - CPU 데이터를 수집하는 exporter: `node_exporter`
    > - GPU 데이터를 수집하는 tool: `NVIDIA DCGM Exporter`

  - **시계열 데이터**: 수집한 데이터를 시간에 따라 기록한다.

  - **자체 저장소**: Prometheus는 시계열 데이터를 자체 내장된 시계열 데이터베이스에 저장하기 때문에, 스토리지를 따로 구성하지 않아도 된다.

    - **다양한 옵션 구성 가능**

      - 클라우드 환경에서 동적으로 타겟을 자동으로 찾을 수 있다.

      - **Thanos**라는 tool과 연동하여 데이터를 따로 저장하는 외부 스토리지(google drive, AWS S3 등)를 데이터베이스로 구성이 가능하다.

        grafana-thanos-prometheus 그림 삽입

        외부 스토리지를 사용하는 이유?

        Prometheus의 기본 데이터 보존 기간은 일반적으로 15일이다.

        `storage.tsdb.retention.time` option을 사용해 기간을 늘릴 수 있지만, 안정적인 해결법은 아니다.

  - **강력한 확장성**: 수집하고자 하는 데이터를 추가하는것이 쉽고, 여러 데이터를 수집하는 방법을 제공하는 exporter 가 다양하다.

    예를 들어

    - `node exporter`: CPU, RAM memory, Disk의 상태에 대한 데이터를 저장하는 path를 자동으로 잡아 데이터를 수집한다.

    - `NVIDIA DCGM Exporter`:  GPU의 사용량, 온도 등에 대한 데이터를 저장하는 path를 자동으로 잡아 데이터를 수집한다.

      ![](https://github.com/HibernationNo1/TIL/blob/master/seminar/images/prometheus/node_dcgm.png?raw=true)

    이를 활용해 규모의 분산 시스템이나 많은 수의 프로젝트를 효율적으로 모니터링 할 수 있다. 

  - **유연성**: 자동으로 제공하는 metrics 수집 외에도, 사용자가 필요에 따라 수집하는 metrics를 정의할 수 있다. (python)

  - **그래프 제공**: 기본적으로 metrics를 모두 시계열 데이터로 수집하기 때문에, 데이터를 시계열 그래프로 볼 수 있다.

    ![](https://github.com/HibernationNo1/TIL/blob/master/seminar/images/prometheus/graph_2.png?raw=true)

  - **query 언어(PromQL) 제공**: 같은 데이터라도 다양하게 활용할 수 있는 query언어를 제공한다.

    예를 들어

    특정 함수가 호출될 때마다 함수의 수행 시간을 `elapsed_time`이라는 이름의 metrics로 수집한다면, 아래와 같이 활용할 수 있다.

    - 특정 시점에서 함수가 호출되었을때 수행 시간 확인: 그래프로 바로 확인 가능
    - 최근 5분동안 해당 함수가 호출된 횟수:  `count_over_time(elapsed_time[5m])`
    - 최근 3분동안 해당 함수가 호출되었을 때 수행 시간
      - 총합: `sum_over_time(elapsed_time[3m])`
      - 평균: `avg_over_time(elapsed_time[3m])`

    이 모든 데이터를 시계열 데이터로 확인할 수 있다.

  - **Cluster 구성**: 다른 서버의 IP와 데이터 수집 타겟의 port만 알고 있다면, 다른 device의 데이터도 수집할 수 있다.

    ![](https://github.com/HibernationNo1/TIL/blob/master/seminar/images/prometheus/prometheus_map.png?raw=true)



prometheus는 데이터를 수집하는데 주요 기능이 집중되어있다.

그렇기에 화면에 멋있고 효율성있게 시각적으로 제공하는 기능은 많이 제공되지 않는다.

때문에, 많은 사람들은 Grafana를 사용하여 해당 데이터를 확인하고 모니터링한다.



## Grafana

![](https://github.com/HibernationNo1/TIL/blob/master/seminar/images/prometheus/grafana.png?raw=true)

- 오픈 소스 데이터 분석 및 시각화 플랫폼

- 데이터 모니터링과 분석을 위해 널리 사용된다.
- 주로 인프라 모니터링, 애플리케이션 성능 모니터링, 그리고 IoT 기기 데이터 등을 시각적으로 표현하는 데 사용된다.



#### 설치 방법

docker image를 가져와서 docker build-run을 통해 간단히 설치할 수 있다.

![](https://github.com/HibernationNo1/TIL/blob/master/seminar/images/prometheus/grafana_docker.png?raw=true)

#### 특징

- **다양한 데이터 소스 지원**

  Mysql, MongoDB, Elasticsearch, Redis, CSV, JSON, GitLab, GitHub, Prometheus, AWS S3, Kafka 등 거의 모든 데이터 관리 툴이나 플랫폼과 연동하여 분석 및 시각화 할 수 있다.  

  ![](https://github.com/HibernationNo1/TIL/blob/master/seminar/images/prometheus/data_source.png?raw=true)

- **강력한 시각화 기능**: 다양한 차트, 그래프, 맵, 그리고 게이지를 제공하여 사용자가 데이터를 다양한 형태로 시각화할 수 있게 도와준다.

  차트, 그래프, 맵, 그리고 게이지 그림 삽입

- **경고 및 알림**: 데이터 값이 특정 임계값을 초과할 경우 경고를 생성하고, 이를 telegram, slack 등으로 메시지를 보내는 알림 서비스를 제공한다.

- **보안 기능**: 사용자 인증 및 권한 부여를 통해 대시보드 접근을 제어할 수 있다.

- **Dashboard import지원**: 다른 개발자들이 만들어둔 모니터링 대쉬보드를 쉽게 가져와 사용할 수 있다.

  - `node exporter` 

    node exporter 그림 삽입

  - `NVIDIA DCGM Exporter`

    NVIDIA DCGM Exporter 그림 삽입

- **Cluster 구성**: 다른 서버에서 동작중인 데이터 소스에 연결할 수 있다.

  예를 들어. `192.168.110.103`서버에 grafana를 설치하고, 

  `10.251.1.164` , `192.168.110.107`, `192.168.0.101` 각각의 서버에 prometheus가 설치되어있다면

  `192.168.110.103:3000`(grafana web UI)에서 모든 서버를 모니터링 할 수 있다.

  ![](https://github.com/HibernationNo1/TIL/blob/master/seminar/images/prometheus/grafana_map.png?raw=true)



---



**prometheus를 사용하면 app, device로부터 여러 정보를 수집할 수 있다.**

**grafana를 사용해서 여러 device로부터 데이터를 가져와 시각화하여 실시간 모니터링을 할 수 있다.**

