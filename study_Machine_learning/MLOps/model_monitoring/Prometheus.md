# Prometheus

open source monitoring system

[github](https://github.com/prometheus/prometheus)

- kubernetes에 종속적이지 않고, binary혹은 docker container형태로도 사용하고 배포 가능

- kubernetes 생태계의 open source 중에서는 사실상 표준

- 수집하는 metric data는 multi dim의 시계열 data형태로 저장

- data 분석을 위한 자체 언어 PromQL지원

- 시계열 데이터 저장에 적합한 TimeSeries DB지원

- data수집하는 방식이 PULL방식

  > server가 직접 정보를 가져가는 방식



**Architecture**

![](https://prometheus.io/assets/architecture.png)

- **Prometheus Server**

  시계열 data를 수집하고 저장

- **Service Discovery**

  monitoring 대상 list를 조회

  user는 kubernetes에 등록하고, Prometheus server는 kubernetes api server에게 monitoring 대상을 물어보는 형태

- **Exporter**

  - Prometheus가 metrics을 수집해갈 수 있도록 정해진 HTTP Endpoint를 제공하여 정해진 형태로 metrics를 export

  - Prometheus Server가 이 Exporter의 endpoint로 HTTP GET request를 보내 metrics를 pull하여 저장한다

    > pull 방식은 수집 주기와 네트워크 단절 등의 이유로 모든 metrics데이터를 수집하는 것을 보장할 수 없기 때문에 push방식을 위한 Pushgateway도 제공

- **Pushgateway**

  prometheus server의 pull주기보다 짧은 lifecycle을 지닌 작업의 metrics수집 보장을 위함

- **Alertmanager**

  PromQL 을 사용해 특정 조건문을 만들고, 해당 조건무닝 만족되면 정해진 방식으로 정해민 message를 보낼 수 있다.

  > ex) service A가 5분 이상 응답이 없으면 관리자에게 slack DM과 e-mail을 보낸다.

- **Grafana**

  Prometheus 와 항상 함께 연동되는 시각화 tool

  Prometheus 자체 UI를 지원하고 API제공을 하기에 직접 시각화 대시보드를 구성할 수도 있다.

- **PromQL**

  Prometheus 가 저장한 data중 원하는 정보만 가져오기 위한 Query Language제공

  Time Series Data이며, Multi-Dimensional Data이기 때문에 복잡할 수 잇으니 Prometheus및 Grafana를 잘 사용하기 위해서는 중요



> **Thanos** : multi Prometheus server를 운영할때 사용하는 open source 



##### install

k8s환경, helm 필요

1. start kubernetes (minikube)

   ```
   $ minikube start --driver=docker --cpus="4" --memory='4g'
   ```

2. add helm repo

   ````
   $ helm repo add prometheus-community http://prometheus-community.github.io/helm-charts
   $ helm repo update
   ````

3. install kube-prometheus-stack

   ```
   $ helm install prom-stack prometheus-community/kube-prometheus-stack --set namespace=prometheus 
   ```

   > ```
   > Error: failed pre-install: timed out waiting for the condition
   > ```
   >
   > 위 메시지가 뜨면  `$ kubectl get events` 으로 문제 확인
   >
   > 특전 container에서 
   >
   > ```
   > No such container: 6b59..
   > ```
   >
   > 와 같은 에러가 떠서 설치 못함

   check

   ```
   $ kubectl get pod -w
   ```

   > uninstall 
   >
   > ```
   > $ helm uninstall prom-stack prometheus-community/kube-prometheus-stack
   > ```
   >
   > 

> 실무에서 admin password, storage class, resource, ingress등의 value를 수정한 뒤 적용하려면 github의 helm-charts를 clone한 뒤 [values.yaml](https://github.com/prometheus-community/helm-charts/blob/main/charts/kube-prometheus-stack/values.yaml)을 수정하여 git으로 환경별 history관리