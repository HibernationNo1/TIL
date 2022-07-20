# MLflow Tracking



## tracking server

MLflow tracking server를 띄우는 명령어는 두 가지가 있다.

**mlflow ui**

- deault로 `http://localhost:5000` 으로 접근할 수 있다.

  > 5000번 port가 열려있는지 확인 필요

- 사용자가 한 명일 경우 



**mlflow server**

- production server로 사용할 경우

- deault로 `http://localhost:5000` 으로 접근할 수 있다.

  > 5000번 port가 열려있는지 확인 필요

- worker를 여러 개 띄울 수 있다.

- prometheus가 metrics를 가져갈 수 있도록 end point를 제공



### mlflow ui

```
$ mlflow ui
```

> `http://127.0.0.1:5000`

`ctrl+c` 를 눌러 명령어를 멈추면 더 이상 접근 불가

> code실행 terminal따로, 위 명령어 입력하는 terminal따로 있어야 함 



**mlruns**

해당 명령어를 실행 한 위지에 `mlruns` 라는 이름의 dir이 생성되는데, 이는 실험관련 data를 save하게 되는 dir이다.

> `mlflow ui` 실행 시 `--backend-store-uri`, `--default-artifact-root ` option을 주지 않는 경우 자동
>
> 이 dir만 존재한다면 `mlflow ui`터미널을 종료한 뒤 다시 실행해도 동일한 화면을 확인 가능

mlruns 안에는 0부터 N(experiments의 개수)까지의 dir이 존재하는데, 이 숫자는 experiment ID로서 0번은 default라는 이름으로 자동 생성된다.

![](https://cran.r-project.org/web/packages/mlflow/readme/tools/readme/mlflow-user-interface.png)

experiment는 code의 version별 table로 이해하면 된다.

> experiment는 mlflow ui에서도 추가할 수 있다.









### function

```python
import mlflow
```

아래 mlflow function을 code에 추가하여 특정 값을 기록할 수 있으며, 해당 기록 값은 `$ mlflow ui` 명령어를 통해 ui형태로 확인할 수 있다.

또한 code에서 각 기록 정보들을 변형하여 code를 실행할 때 마다 **한 번** 기록이 진행되며(또한 랜덤한 run ID가 할당된다.), 이 또한 ui로 확인할 수 있다.  

![](https://miro.medium.com/max/1400/1*-BX3BpJxSZroJkSiwNRfGg.png)

> Default라는 experiment의 code가 언제 각각 어떤 정보를 log로 기록하며 실행이 되었는지 알 수 있다.
>
> 또한 각 시간마다(code를 실행할 때 마다) **RUN ID**가 새롭게 주어지는데 (63d1a9cde7f84190a5634648467be195 와 같은 긴 ramdom한 숫자+문자) 이는 model을 serving할때 사용된다.  (위 이미지의 Start Time부분을 클릭하면 상세 정보와 함께 볼 수 있다.)



#### log

log는 한 번 key값으로 저장한 정보는 해당 code가 진행되는동안 바뀔 수 없기 때문에 iterate한 training과정에서는 마지막 epche에만 사용하거나, test과정에서 image마다의 값을 모아서 metric형태로 저장하도록 사용한다.

##### log_param

parameter값을 key-value형태로 기록

```python
mlflow.log_param("{parameter_name}", parameter)
```



##### log_metric

metric를 key-value형태로 기록

```python
mlflow.log_metric("{metric}", metric)
```





##### log_artifact

image를 key-image형태로 기록

```python
mlflow.log_artifact("{image_name}", img)
```

> numpy형태의 image 도 저장 가능



#### sklearn

```python
import mlflow.sklearn
```



##### log_model

> .pkl format의 model을 저장

```python
mlflow.sklearn.log_model(model, "{model_name}")
```













### serving

```
$ mlflow models serve [OPTION]
```

model의 RUN ID가 필요함

model의 serving을 위해 위 명령어가 실행된 terminal은 항상 열려있어야 한다.



````
$ mlflow models serve -m ${pwd}/mlruns/0/63d1a9cde7f84190a5634648467be195/artifacts/model -p 5001
````

- `mlruns`

- `0` : experiment ID

- `63d1a9cde7f84190a5634648467be195` : RUN ID

  RUN ID : code가 정상적으로 RUN되는 pipeline의 RUN ID

- `{pwd}/mlruns/0/63d1a9cde7f84190a5634648467be195/artifacts/model` : model.pkl 이 저장된 경로

- `-p 5001` : port (5000을 제외한 열려있는 port )

> 해당 명령어가 성공적으로 입력되면 
>
> 1. RUN ID의 model에 관련된 code의 환경(python package, pip 등)을 새로운 codna 가상환경에 다운받는다
>
> 2. `http://127.0.0.1:5001` 에서 REST API형태로 .predict()함수를 사용할 수 있게 된다.
>
>    API를 보내기 위해서는 해당 code에 사용되는 API input 형식을 알아야 한다.

또 다른 terminal에서

```
$ curl -X POST {API input} http://127.0.0.1:5001/invocations
```

으로 API요청