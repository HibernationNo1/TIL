# MLOps

MLOps는 모델을 만드는 것을 넘어서 데이터를 가져오는것부터 시작해 모델을 재배포, 재학습시키는 운영적 관점이 포함되어 있는 개념이다.

MLOps의 핵심은 머신러닝 학습 주기 관리의 표준화 및 간소화이다.



#### 사전 지식

Machine Learning system은 다음과 같은 상황에서 학습과 모델을 배포한다.

- **요청 시** : 요청이 있을 땐 pipeline을 임시로 수동 실행한다.
- **일정 기준** : label이 지정된 새 data는 매일, 매주 또는 매월 updata되기 때문에 일정 기준에 따라 model의 재학을 trigger 한다.
- **학습 data update** : 새로운 data가 들어오는 경우 model의 재학습을 trigger한다.
- **model performance 저하 시** : performance저하가 눈에 띄는 경우 모델을 재학습한다.
- **data distribution의 중요한 변화 시(concept Drift)** : 온라인 model의 전체 performance를 평가하기는 어렵지만 prediction을 수행하는 데 사용되는 feature의 data distribution에 큰 변화가 있으면, model이 오래되었다는 것을 뜻한다.



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

