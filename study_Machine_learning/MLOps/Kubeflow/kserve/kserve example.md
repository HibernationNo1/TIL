# kserve example

````
namespace = pipeline
````







## sklearn

**InferenceService**

- old schema

- name: `sklearn-iris`

```
apiVersion: "serving.kserve.io/v1beta1"
kind: "InferenceService"
metadata:
  annotations:
    isdecar.istio.is/inject: "false"
  name: "sklearn-iris"
spec:
  predictor:
    sklearn:
      image: "kserve/sklearnserver:v0.9.0"
      storageUri: "gs://kfserving-examples/models/sklearn/1.0/model"
```



1. model server가 운영되는 pod 확인

   ```
   $ kubectl get pods -n pipeline -l serving.kserve.io/inferenceservice=sklearn-iris
   ```

   ```
   NAME                                                              READY   STATUS    RESTARTS   AGE
   sklearn-iris-predictor-default-00001-deployment-84zrcd5    3/3     Running   0          32m
   ```

   - init log 확인

     ```
     $ kubectl logs sklearn-iris-predictor-default-00001-deployment-84zrcd5 -c storage-initializer -n pipeline
     ```

   - pod log 확인

     ```
     $ kubectl logs sklearn-iris-predictor-default-00001-deployment-84zrcd5 -n pipeline
     ```

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

2. port-forward

   ```
   $ kubectl port-forward -n pipeline sklearn-iris-python-predictor-default-00001-deployment-84zrcd5 8081:8080
   ```

   - `sklearn-iris-python2-predictor-default-00001-deployment-84zrcd5`라는 pod에 port-foward
   - model server의 `8080` 과 local의 `8081` port와 연결

3. inference

   python SDK with kfp client

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

   





## pytorch

- new scheme

- name: `pytorch-mnist`

```
apiVersion: "serving.kserve.io/v1beta1"
kind: "InferenceService"
metadata:
  annotations:
    isdecar.istio.is/inject: "false"
  name: "pytorch-mnist"
spec:
  predictor:
    model:
      modelFormat:
        name: pytorch
      storageUri: "gs://kfserving-examples/models/torchserve/image_classifier/v1"
      resources:
        limits:
          memory: 4Gi
          nvidia.com/gpu: "1"
```

- gpu 개수 명시



1. model server가 운영되는 pod 확인

   ```
   $ kubectl get pods -n pipeline -l serving.kserve.io/inferenceservice=pytorch-mnist
   ```

   ```
   NAME                                                              READY   STATUS    RESTARTS   AGE
   pytorch-mnist-predictor-default-00001-deployment-5bcc7bb64ps7km   3/3     Running   0          37s
   ```

   - init log 확인

     ```
     $ kubectl logs pytorch-mnist-predictor-default-00001-deployment-5bcc7bb64ps7km -c storage-initializer -n pipeline
     ```

     ```
     2023-06-01 06:45:35.605 1 root INFO [<module>():13] Initializing, args: src_uri [gs://kfserving-examples/models/torchserve/image_classifier/v1] dest_path[ [/mnt/models]
     2023-06-01 06:45:35.605 1 root INFO [download():63] Copying contents of gs://kfserving-examples/models/torchserve/image_classifier/v1 to local
     2023-06-01 06:45:38.608 1 google.auth.compute_engine._metadata WARNING [ping():99] Compute Engine Metadata server unavailable on attempt 1 of 3. Reason: timed out
     2023-06-01 06:45:38.666 1 google.auth.compute_engine._metadata WARNING [ping():99] Compute Engine Metadata server unavailable on attempt 2 of 3. Reason: [Errno 113] No route to host
     2023-06-01 06:45:41.669 1 google.auth.compute_engine._metadata WARNING [ping():99] Compute Engine Metadata server unavailable on attempt 3 of 3. Reason: timed out
     2023-06-01 06:45:41.669 1 google.auth._default WARNING [_get_gce_credentials():301] Authentication failed using Compute Engine authentication due to unavailable metadata server.
     2023-06-01 06:45:42.000 1 root INFO [_download_gcs():232] Downloading: /mnt/models/config/config.properties
     2023-06-01 06:45:42.544 1 root INFO [_download_gcs():232] Downloading: /mnt/models/model-store/mnist.mar
     2023-06-01 06:45:43.340 1 root INFO [download():103] Successfully copied gs://kfserving-examples/models/torchserve/image_classifier/v1 to /mnt/models
     ```

     - `config.properties` 파일 다운로드 확인
     - `mnist.mar` 파일 다운로드 확인
     - `/mnt/models` 위치에 model 다운로드 확인

   - pod log 확인

     ```
     $ kubectl logs pytorch-mnist-predictor-default-00001-deployment-5bcc7bb64ps7km -n pipeline
     ```

     ```
     ...
     ...
     Torchserve version: 0.7.0									# torch server의 version 확인
     TS Home: /usr/local/lib/python3.8/dist-packages
     Current directory: /home/model-server						# dir path 확인
     Temp directory: /home/model-server/tmp
     Metrics config path: /usr/local/lib/python3.8/dist-packages/ts/configs/metrics.yaml
     Number of GPUs: 0											# 사용되는 GPU개수 확인
     Number of CPUs: 1											# 사용되는 CPU개수 확인
     Max heap size: 494 M
     Python executable: /usr/bin/python3.8
     Config file: /mnt/models/config/config.properties
     Inference address: http://0.0.0.0:8085						# inference server의 port 확인
     Management address: http://0.0.0.0:8085						# Management API의 port 확인
     Metrics address: http://0.0.0.0:8082						# Metrics API의 port 확인
     Model Store: /mnt/models/model-store						# model file의 path확인
     Initial Models: N/A
     Log dir: /home/model-server/logs
     Metrics dir: /home/model-server/logs
     ...
     ...
     Metrics report format: prometheus							# Metrics report의 format 확인 (prometheus 사용)
     ...
     ...
     [I 230601 06:45:47 model_server:150] Registering model: mnist		# model의 name 확인
     [I 230601 06:45:47 model_server:123] Listening on port 8080			# 연결 port확인 (port forward)
     ...
     
     ```

     그 외에도 batchsize 등 여러 정보 확인 가능

2. port-forward

   ```
   $ kubectl port-forward -n pipeline pytorch-mnist-predictor-default-00001-deployment-5bcc7bb64ps7km 8081:8080
   ```

   - `pytorch-mnist-predictor-default-00001-deployment-5bcc7bb64ps7km`라는 pod에 port-foward
   - model server의 `8080` 과 local의 `8081` port와 연결

3. inference

   새 terminal에서

   1. image를 json으로 변환한 파일 download

      ```
      $ curl https://raw.githubusercontent.com/kserve/kserve/c5f8984d3151769698664c33f94412b55a12d210/docs/samples/v1beta1/torchserve/v1/imgconv/input.json -o input.json
      ```

      > 숫자 2의 이미지를 json으로 변환한 것이다.
      >
      > [이곳](https://github.com/kserve/kserve/tree/master/docs/samples/v1beta1/torchserve/v1/imgconv)의 code를 사용하면 image file을 json으로 변환할 수 있다.

   2. `MODEL_NAME`, `SERVICE_HOSTNAME` 할당

      ```
      MODEL_NAME=mnist
      SERVICE_HOSTNAME=$(kubectl get inferenceservice pytorch-mnist -n pipeline -o jsonpath='{.status.url}' | cut -d "/" -f 3)
      ```

   3. request보내기

      ````
      curl -v -H "Host: ${SERVICE_HOSTNAME}" http://127.0.0.1:8081/v1/models/${MODEL_NAME}:predict -d @./input.json
      ````

      ```
      *   Trying 127.0.0.1:8081...
      * Connected to 127.0.0.1 (127.0.0.1) port 8081 (#0)
      > POST /v1/models/mnist:predict HTTP/1.1
      > Host: pytorch-mnist.pipeline.svc.cluster.local
      > User-Agent: curl/7.71.1
      > Accept: */*
      > Content-Length: 401
      > Content-Type: application/x-www-form-urlencoded
      > 
      * upload completely sent off: 401 out of 401 bytes
      * Mark bundle as not supporting multiuse
      < HTTP/1.1 200 OK
      < Server: TornadoServer/6.2
      < Content-Type: application/json; charset=UTF-8
      < Date: Thu, 01 Jun 2023 07:53:58 GMT
      < Content-Length: 20
      < 
      * Connection #0 to host 127.0.0.1 left intact
      {"predictions": [2]}
      ```

      - `{"predictions": [2]}` 확인

