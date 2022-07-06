# Model Management

기록해두어야 하는 정보

- model source code
- evaluation metric 결과
- 사용한 parameters
- model.pkl 파일
- train dataset
- data preprocessing code



# MLflow

- mlflow tracking 

  - model source code의 hyper parameter나 그 외 code 변경점이 있는 경우 수정사항마다 각각의 model version별로 metric을 기록하는 중앙 저장소 제공

  - python 함수로 meta정보를 model과 함께 기록할 수 있는 API를 제공
  - 학습에 사용된 data 자체를 version별로 저장 관리 가능

- mlflow projects

  model의 의존성이 있는 모든 정보(conda, pytorch, cv2 version 등)와 code를 모두 packaging해준다.

- mlflow  models

  model이 어떤 환경에서 개발되는지 상관 없이 항상 통일된 상태로 배포에 사용할 수 있도록 format화 시켜준다.

- mlflow  model registry

  실행했던 model을 저장하고 관리하는 저장소



### install 

python환경과 conda만 갖추어져 있다면 mac, window, linux어디서든 사용 가능

[공식](https://www.mlflow.org/docs/latest/quickstart.html)



1. 가상환경

   ```
   $ conda acitvate -n mlflow python=3.8
   ```

2. install

   ```
   $ pip install mlflow
   ```

3. check

   ```
   $ mlflow --version
   ```

   

