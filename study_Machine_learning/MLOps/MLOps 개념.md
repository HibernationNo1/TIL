# MLOps

MLOps는 모델을 만드는 것을 넘어서 데이터를 가져오는것부터 시작해 모델을 재배포, 재학습시키는 운영적 관점이 포함되어 있는 개념이다.

MLOps의 핵심은 머신러닝 학습 주기 관리의 표준화 및 간소화이다.



### MLOps구성 요소

#### data

1. 데이터 수집 파이프라인 

   관련 기술 : `Sqoop`, `Flume`, `Kafka`, `Flink`, `Spark Streaming`, `Airflow`

2. 데이터 저장

   관련 기술 : `MySQL`, `Hadoop`, `Amazon S3`, `MinlO`

3. 데이터 관리

   관련 기술 : `TFDV`, `DVC`, `Feast`, `Amundsen`

#### model

1. 모델 개발

   관련 기술 : `Jupyter Hub`, `Docker`, `Kubeflow`, `Optuna`, `Ray`, `Katib`

2. 모델 버전 관리

   관련 기술 : `Git`, `MLflow`, `Github Action`, `Jenkins`

3. 모델 학습 스케줄링 관리

   관련 기술 : `Grafana`, `Kubernetes`

#### serving

1. 모델 패키징

   관련 기술: `Docker`, `Flask`, `FaskAPI`, `BentoML`, `Kubeflow`, `TFServing`, `seldon-core`

2. 서빙 모니터링

   관련 기술 : `Prometheus`, `Grafana`, `Thanos`

3. 파이프라인 매니징

   관련 기술 : `Kubeflow`, `argo workflows`, `Airflow`





### MLOps의 성숙도

MLOps의 성숙도는 Level 0부터 1, 2까지 있다.

#### Lv 0

- 수동, script 중심, interactive process

  > 주피터 노트북으로 만들어서 배포하는 경우

- ML과 운영이 분리됨

  > SW팀이 model을 만든 후 engineering 팀에게 전달하는 정도

- 드문 release 반복

  > model deplotment가 거의 없거나 1년에 한, 두번 있을까 말까

- CI(Continuous Integration)없음

- CD(Continuous Deployment)없음 

- 배포는 예측 서비스를 의미

- Active성능 모니터링 부족

  > 성능 모니터링 잘 안함

![](https://cloud.google.com/architecture/images/mlops-continuous-delivery-and-automation-pipelines-in-machine-learning-2-manual-ml.svg)



#### Lv 1

- 빠른 실험

- 프로덕션 모델의 CT(Continuous training)

  > 자동으로 data가 정리되서 학습이 된다.

- 실험 운영 환경의 조화

- 구성 요소 및 pipeline을 위한 Module화 된 code

- 지속적인 model 제공

- pipeline deployment

![](https://blog.kakaocdn.net/dn/bT46HB/btq4TAEaP0f/u1L9EQWQQZlQTKIB9jXIN1/img.png)



#### Lv 2

- Production에서 pipeline을 빠르고 안정적으로 updata하려면 자동화된 CI/CD system이 필요하다.
- 이 자동화된 CI/ID system을 통해 data scientist는 Feature Engineering, model 아키텍쳐 및 하이퍼 파라미터에 대한 새로운 아이디어를 신속하게 탐색할 수 있다.

- VL 1에서 쿠베플로우 CI/CD가 있는 구조를 Lv 2라고 한다.

