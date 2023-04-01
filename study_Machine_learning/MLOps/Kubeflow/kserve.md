# Kserve

## install

### [kubeflow](https://github.com/kubeflow/manifests)

kubeflow 설치를 통해 `knative`와 관련된 resource와 `istio-system`과 관련된 resource가 제대로 설치되어야 한다.



### [kserve](https://kserve.github.io/website/0.10/)

공식 link에서 install관련 정보를 얻을 수 있다.

version에 따라서 내용이 달라질 수 있으니 version확인을 잘 하자.

[공식](https://kserve.github.io/website/0.10/admin/serverless/serverless/)



**Install KServe**

```
$ kubectl apply -f https://github.com/kserve/kserve/releases/download/v0.10.0/kserve.yaml
```

check

```
$ kubectl get pod -n kserve
```

```
NAME                                         READY   STATUS    RESTARTS   AGE
kserve-controller-manager-5fc887875d-xl7sj   2/2     Running   0          7h3m
```



**Install KServe Built-in ClusterServingRuntimes**

```
kubectl apply -f https://github.com/kserve/kserve/releases/download/v0.10.0/kserve-runtimes.yaml
```

> InferenceService를 생성하는 데 필요



check

```
$ kubectl get clusterservingruntimes
```

```
NAME                        DISABLED   MODELTYPE    CONTAINERS         AGE
kserve-lgbserver                       lightgbm     kserve-container   7h13m
kserve-mlserver                        sklearn      kserve-container   7h13m
kserve-paddleserver                    paddle       kserve-container   7h13m
kserve-pmmlserver                      pmml         kserve-container   7h13m
kserve-sklearnserver                   sklearn      kserve-container   7h13m
kserve-tensorflow-serving              tensorflow   kserve-container   7h13m
kserve-torchserve                      pytorch      kserve-container   7h13m
kserve-tritonserver                    tensorrt     kserve-container   7h13m
kserve-xgbserver                       xgboost      kserve-container   7h13m
```







## example

### kubeflow Dashboard

kubeflow의 Tap menu중 하나은 Endpoint에 기본 예제의 resource를 배포

```
apiVersion: "serving.kserve.io/v1beta1"
kind: "InferenceService"
metadata:
  annotations:
    isdecar.istio.is/inject: "false"
  name: "sklearn-iris-python"
spec:
  predictor:
    sklearn:
      image: "kserve/sklearnserver:v0.9.0"
      storageUri: "gs://kfserving-examples/models/sklearn/1.0/model"
```

해당 계정이 속한 nemaspace에 자동으로 배포된다.



- `inferenceservices`확인

  ```
  $ kubectl get inferenceservices -n pipeline
  ```

  ```
  NAME            	sklearn-iris-python       
  URL                 http://sklearn-iris-python.pipeline.svc.cluster.local
  READY   			True
  PREV   				
  LATEST   			100
  PREVROLLEDOUTREVISION   
  LATESTREADYREVISION              sklearn-iris-python-predictor-default-00001               
  AGE					3m48s
                                                    
  ```

  

- `ksvc` 확인

  ```
  $ kubectl get ksvc -n pipeline
  ```

  ```
  NAME            sklearn-iris-python-predictor-default                         
  URL     		http://sklearn-iris-python-predictor-default.pipeline.svc.cluster.local     
  LATESTCREATED   sklearn-iris-python-predictor-default-00001                            
  LATESTREADY     sklearn-iris-python-predictor-default-00001
  READY      		True 
  ```

  

- model server가 운영되는 pod 확인

  ```
  $ kubectl get pods -n pipeline -l serving.kserve.io/inferenceservice=sklearn-iris-python
  ```

  ```
  NAME                                                              READY   STATUS    RESTARTS   AGE
  sklearn-iris-python-predictor-default-00001-deployment-84zrcd5    3/3     Running   0          32m
  ```

  

- model server가 운영되는 pod의 log확인

  ```
  $ kubectl logs -n pipeline -l serving.kserve.io/inferenceservice=sklearn-iris-python
  ```

  > 또는
  >
  > ```
  > $ kubectl get logs sklearn-iris-python2-predictor-default-00001-deployment-84zrcd5 -n pipeline
  > ```

  ```
  [I 230401 15:32:26 storage:63] Copying contents of /mnt/models to local
  [I 230401 15:32:26 model_server:150] Registering model: sklearn-iris-python
  [I 230401 15:32:26 model_server:123] Listening on port 8080
  [I 230401 15:32:26 model_server:125] Will fork 1 workers
  [I 230401 15:32:26 model_server:128] Setting max asyncio worker threads as 5
  ```

  1. `[I 230401 15:32:26 storage:63] Copying contents of /mnt/models to local`: 이 로그는 저장소에서 로컬 환경으로 모델 파일을 복사하는 과정을 나타낸다. 

  2. `[I 230401 15:32:26 model_server:150] Registering model: sklearn-iris-python`: 이 로그는 모델 서버에 `sklearn-iris-python` 모델을 등록하는 과정을 나타낸다. 

  3. `[I 230401 15:32:26 model_server:123] Listening on port 8080`: 이 로그는 모델 서버가 8080 포트에서 수신 대기 중임을 나타낸다.

     > **model server의 pod안의 8080 port가 수신 대기중임**

  4. `[I 230401 15:32:26 model_server:125] Will fork 1 workers`: 이 로그는 모델 서버가 1개의 워커 프로세스를 생성할 것임을 나타낸다.

  5. `[I 230401 15:32:26 model_server:128] Setting max asyncio worker threads as 5`: 이 로그는 최대 asyncio 워커 스레드를 5개로 설정하는 과정을 나타낸다.

  위 모든 작업은 정상적으로 완료되었음을 확인. (로그는 모델 서버가 정상적으로 실행 중이며, 모델이 올바르게 등록되었음을 나타냄)



이제 해당 service에 요청을 보내려면 port-forward를 해야 한다.



#### port-forward

```
kubectl port-forward -n pipeline sklearn-iris-python-predictor-default-00001-deployment-84zrcd5 8081:8080
```

- `sklearn-iris-python2-predictor-default-00001-deployment-84zrcd5`라는 pod에 port-foward
- local의 `8081` port와 연결







#### python SDK

##### with kfp client

```python
import kfp
import requests
import json

def connet_client(user_n, , name_space, host, pw,
                  return_session = False):   
    session = requests.Session()
    response = session.get(host)

    headers = {
        "Content-Type": "application/x-www-form-urlencoded",
    }

    data = {"login": user_n, "password": pw}
    session.post(response.url, headers=headers, data=data)                              
    session_cookie = session.cookies.get_dict()["authservice_session"]  
    
   
    # access kubeflow dashboard
    client = kfp.Client(
        host=f"{host}/pipeline",
        namespace=f"{name_space}",
        cookies=f"authservice_session={session_cookie}")
    if return_session:
        return client, session
    else:
        return client 
    
if __name__ == "__main__":
    dashboard_cfg = {'user_n': 'winter4958@gmail.com', 
                     'name_space': 'pipeline', 
                     'host': 'http://localhost:8080', 
                     'pw': '4958',
                    'return_session' = True}
    client, session = connet_client(**dashboard_cfg) 

    session_cookie = session.cookies.get_dict()
    sklear_iris_input = dict(instances = [
    [6.8, 2.8, 4.8, 1.4],
    [6.0, 3.4, 4.5, 1.6]
    ])

    HOST = "http://127.0.0.1:8081"		# port-forward한 port를 명시

    headers = {'Host': "sklearn-iris-python-predictor-default.pipeline.svc.cluster.local"}
    res = session.post(f"{HOST}/v1/models/sklearn-iris-python:predict", 
                        headers=headers, 
                        cookies=session_cookie,
                        data=json.dumps(sklear_iris_input))

    print(f"res.json : {res.json()}")
```

- heaser의 Host값에는 kserve의 URL에서 `http://`를 제외한 부분이 들어가야 한다.



출력

```
res.json : {'predictions': [1, 1]}
```





##### with KServeClient

TODO
