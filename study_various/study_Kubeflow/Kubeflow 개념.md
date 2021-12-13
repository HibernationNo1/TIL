# Kubeflow

### Kubeflow Features

1. 조합가능성 Composability
   
   kubeflow의 핵심 구성 요소는 이미 머신러닝 실무자들에게 익숙한 데이터 과학 도구를 사용한다.
   
   이들은 기계 학습의 특정 단계를 용이하게 하기 위해 독립적으로 사용되거나, end to end pipeline을 형성하기 위해 함께 구성될 수 있다.

2. 이식성 Portability
   
   container 기반 설계를 갖추고 kubernetes 및 cloud 네이티브 아키텍처를 활용함으로써 kubeflow는 특정 개발환경에 종속될 필요가 없다.
   
   labtop에서 실험 및 프로토타입 작업을 수행할 수 있으며, 프로덕션 환경에 손쉽게 배포할 수 있다.

3. 확장성 Scalability
   
   kubenetes를 사용하면 기본 컨테이너와 기계의 수와 크기를 변경하여 클러스터의 요구에 따라 동적으로 확장할 수 있다.

### kubeflow moduel

#### pipeline

pipeline은 각 component를 이어서 만든 것으로, 여러 component(preprocessing, training 등)을 구성하여 만드는 것이다.

component는 특정 function에 `@kfp.das.python_componenet`라는 decorator를 적어주면 된다.

이를 'component로 추상화한다.' 라고 한다. 

component로 추상화한다는 말은, docker image로 만든다는 의미이다.

이러한 여러가지 component를 조합하여 pipeline을 구성한다.

이렇게 구성된 pipeline을 build하게 되면 yaml file이 만들어지게 되는데, 이를 pipeline을 compile한다고 한다. 이러한 yaml file을 kubeflow 대시보드에서 업로드하거나 kfctl명령으로 업로드 할 수 있다.

#### Katlib

kubeflow에서 model tuning(Auto ML)을 담당하는 모듈을 kubeflow katlib이라고 한다.

#### TFJops

비동기로 학습을 하거나 offline inference를 할 때 사용하는 모듈을 TFJops라고 한다.

#### KFserving

online inference server를 배포하는 모듈이다.

#### MinIO

kubeflow pipeline간의 저장소 기능을 수행하는 솔루션으로, MinIO에 pipeline 중간에 생기는 부산물들을 저장할 수 있다.
