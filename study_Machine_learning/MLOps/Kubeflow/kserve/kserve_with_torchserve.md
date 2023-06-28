# Kserve

순서

1. TorchServe로 model을 배포한다.

   1. hendler.py를 정의한다.
   2. TorchServe archrive를 통해 `.mar` file을 만들고 `config.prosperties` file을 작성한다.
   3. `TorchServe --start`로 해당 model이 정상적으로 배포되었는지 확인한다.

2. `.mar` file과 `config.prosperties`를 google storage에 upload한다.

3. Kserve로 TorceServe를 배포한다.

   1. kubeflow endpoint를 통해 InferenceService를 생성한다.
   2. request를 통해 해당 InferenceService가 정상적으로 동작중인지 확인한다.

   



## TorchServe

[github](https://github.com/pytorch/serve)

serving하고자 하는 model을 TorchServe에서 요구하는 방식으로 변환하고, 이를 기반으로 server를 실행하면 model과 user간의 API소통이 이루어지도록 하는 기술이다.

> runtime에서 모델을 manage하기 위한 다양한 기능의 API를 제공한다. 즉 torchserve를 실행시켜놓으면 모델 파라미터 외에 배포 관련 기본적인 설정은 실시간 api call을 통해 가능하다.



### .mar

#### archiver

아래의 dir map인 경우

```
v1
	extra
		sub_module(dir)
		config.py	
		requirements.txt
	handler.py
	model.pth
```



```
$ torch-model-archiver \
	--model-name pipeline \
	--version 0.1 \
	--serialized-file pipeline.pth \
	--extra-files extra \
	--handler handler.py \
	--runtime python \
	--requirements-file extra/requirements.txt
```

> `--model-name`에 할당한 이름에 `.mar`라는 format으로 file이 만들어진다.

- `--model-name`: model의 이름을 지정. 지정된 이름은 추후 TorchServe에서 model을 참조할 때 사용된다.

- `--version`: model의 version을 지정.  지정된 version은 추후 model 관리에 사용된다.

- `--model-file`: model을 정의하는 python file의 path를 지정한다. 해당 file은 model이 정의된 class를 포함해야 한다.

  만일 model이 여러 file에 나뉘어 정의되어 있다면 해당 model을 하나의 module로 정의하여 dir에 보관하고 `--extra-files`에 해당 module을 포함하자.

  `--model-file`은 단일 file만 지정할 수 있다.

- `--serialized-file`: 직렬화된 model file(일반적으로 `.pth` or `.pt` format)의 경로를 지정한다. 

- `--extra-files`: 추가 file의 경로를 지정한다. config file이나 infomation 또는 보조 code file등을 포함할 수 있다. 

- `--handler`: model serving handler를 지정한다. (`hendler.py`와 같은)

- `--runtime`: runtime version을 지정한다. (`python` or `python3`)

- `--requirements-file`: inference과정에서 추가로 install해야 할 module을 적어놓은 txt file의 path를 지정한다. 

  해당 option은 **kserve를 통해 배포**할 때 pod의 환경에 modules를 install하는 경우 사용된다.

  해당 option을 사용하려면 아래의 조건이 만족되어야 한다.

  - `config.properties`file에 `install_py_dep_per_model=true`를 포함시켜야 한다.
  - 해당 option에 지정할 requirements.txt의 path는 `--export-path`에 지정될 dir에 포함되어야 한다.

  > 예시
  >
  > **requirements.txt**
  >
  > ```
  > opencv-python
  > pycocotools
  > matplotlib
  > terminaltables
  > nvgpu==0.9.0
  > pynvml==11.4.1
  > Pillow
  > addict
  > mmcv
  > ```
  >
  > 해당 package는 `torchserve --start`명령을 실행한 환경의 library를 참조한다.
  >
  > - GTX3060기준, Nvidia driver version : `470.182.03` 일 때 pynvml의 최신 `11.5.0` version은 호환되지 않는다. 
  >
  >   `11.4.1`은 2021년에, `11.5.0`는 2023년 release된 version임
  >
  > kserve를 통해 배포하는 것이 아니라면, Torchserve의 package는 `torchserve --start`명령이 실행되는 환경속에서 작동된다.

- `--export-path`: 생성된 model archive file(`.mar`)이 저장될 directory를 지정한다. 

  default는 `.` 이다.

  > `hendler.py`에서 import할 modul 및 python file을 포함한다.

- `--force`: 해당 option을 사용하면 이미 존재하는 archive file이 있을 경우 덮어씌운다.





#### config.properties

properties는 지정할 수 있는 사용자가 torchserve에 대한 설정을 결정한다.

```
inference_address=http://0.0.0.0:8085
management_address=http://0.0.0.0:8085
metrics_address=http://0.0.0.0:8082
grpc_inference_port=7070
grpc_management_port=7071
enable_metrics_api=true
metrics_format=prometheus
config_path=extra/config
gpu_id=0
model_store=/mnt/models/model-store	# torchserve구동 시 model file의 저장 위치 지정
install_py_dep_per_model=true		# requriements.txt를 설치하기 위해
model_snapshot={"name": "startup.cfg", "modelCount": 1, "models": {"my_model": {"1.0": {"defaultVersion": true, "marName": "my_model.mar", "minWorkers": 1, "maxWorkers": 3, "batchSize": 4, "maxBatchDelay": 100, "responseTimeout": 120}}}}
```

- `install_py_dep_per_model`: kserve에 의한 배포를 진행할 때 inference를 진행할 pod에 설치할 module을 적어놓은 requirements.txt를 전달한 경우 추가



torchserve가 정상적으로 구동됨을 확인했다는 가정 하에 다음 step진행



## gs

`.mar`과 `config.prosperties`를 공개 storage에 upload한다.

> `gsutil` 설치 필요

upload하려는 storageUri은 `gs://bucket_name/dir`과 같이 bucket하위 최소 1층의 dir의 위치에 있어야 한다.

1. upload하고자 하는 path를 공개 access로 변경

   https://cloud.google.com/storage/docs/access-control/making-data-public?hl=ko

   > 특정 examples를 download하는 명령어
   >
   > ```
   > $ gsutil cp -r gs://kfserving-examples/models/torchserve/image_classifier/v1 .
   > ```

2. google stoage에 upload

   > 접근하려는 device에서 google storage접근 권한 설정 (최초 1번)
   >
   > 1. google cloud login
   >
   >    ```
   >    $ gcloud auth login 
   >    ```
   >
   >    ```
   >    Go to the following link in your browser:
   >    
   >        https://accounts.google.com/o/oauth2/auth?response_type=code&.... 
   >        
   >    Enter authorization code: 
   >    ```
   >
   >    해당 link접속 후 authorization code를 copy하여 입력
   >
   > 2. cloud가 속한 project지정
   >
   >    ```
   >    $ gcloud config set project PROJECT_ID
   >    ```

   1. dir map을 아래와 같이 구성한다.

      ```
      gs
      	config
              config.properties
          model-store
              model_name.mar
      ```

   2. upload

      ```
      $ gsutil cp -r gs gs://pipeline_kserve_test_01/dir
      ```

      `pipeline_kserve_test_01`라는 bucket의 `dir`이라는 path로 upload



## kserve

###  resource

```
apiVersion: "serving.kserve.io/v1beta1"
kind: "InferenceService"
metadata:
  annotations:
    isdecar.istio.is/inject: "false"
  name: "{InferenceService_name}"
spec:
  predictor:
    model:
      modelFormat:
        name: pytorch
      storageUri: "{google storage path}"
```

> - storageUri은 `gs://bucket_name/dir`과 같이 bucket하위 최소 1층의 dir의 위치에 있어야 한다.
>



### check InferenceService

1. check InferenceService pod

   ```
   $ kubectl get pods -n {namespace} -l serving.kserve.io/inferenceservice={InferenceService_name}
   ```

   > show initializer log
   >
   > 특정 pod의 상태가 `init:`에서 멈춘 경우, 해당 pod의 log를 확인하려면 init container의 log를 확인해야 한다.
   >
   > 1. init container확인 
   >
   >    ```
   >    $ kubectl describe pod <pod-name> -n <namespace>
   >    ```
   >
   >    출력에서 `Init Containers` 부분에서 init container의 이름을 알 수 있다.
   >
   >    ```
   >    Init Containers:
   >      storage-initializer:
   >        Container ID:  docker://3d7e883e67c41301f2bdbe2bb897f6de54bf235d3f216e5df5de7986edd77ead
   >        Image:         kserve/storage-initializer:v0.10.0
   >        Image ID:      
   >        ...
   >        ...
   >    ```
   >
   >    위와 같은 경우 init container의 이름은 `storage-initializer`이다.
   >
   > 2. log확인
   >
   >    ```
   >    $ kubectl logs {Pod_name} -c {init container} -n {namespace}
   >    ```
   >
   >

   - show log

     ```
     $ kubectl logs {Pod_name} -n {namespace}
     ```

   > InferenceService 구동 확인
   >
   > ```
   > $ kubectl get inferenceservice {InferenceService_name} -n {namespace}
   > ```

2. port-forward

   ```
   $ kubectl port-forward -n {namespace} {Pod_name} {local_port}:8080
   ```

   inference service에 의해 만들어진 pod의 8080port에 port-forwarding을 한다.
   
   

3. send request

   1. set variable

      ```
      $ MODEL_NAME={model_name}
      $ SERVICE_HOSTNAME=$(kubectl get inferenceservice {InferenceService_name} -n {namespace} -o jsonpath='{.status.url}' | cut -d "/" -f 3)
      ```

      - `MODEL_NAME`:  Torchserve를 통해 `.mar` file을 만들 때 지정한 model name

        > `torch-model-archiver`명령어의 `--model-name`에 명시한 것과 같아야 한다.

   2. get example file

      sample file을 download

      ```
      $ curl https://raw.githubusercontent.com/kserve/kserve/c5f8984d3151769698664c33f94412b55a12d210/docs/samples/v1beta1/torchserve/v1/imgconv/input.json -o input.json
      ```

      > 또는 request를 보내는 code작성
      >
      
   3. send request
   
      ```
      $ curl -v -H "Host: ${SERVICE_HOSTNAME}" http://127.0.0.1:{local_port}/v1/models/${MODEL_NAME}:predict -d @./input.json
      ```
   





### ex

**resource**

```
apiVersion: "serving.kserve.io/v1beta1"
kind: "InferenceService"
metadata:
  annotations:
    isdecar.istio.is/inject: "false"
  name: "pipeline-test"
spec:
  predictor:
    model:
      modelFormat:
        name: pytorch
      storageUri: "gs://pipeline_kserve_test_01/dir/gs"
```



**check inferenceservice**

```
$ kubectl get pods -n pipeline -l serving.kserve.io/inferenceservice=pipeline-test
```

```
NAME                                                              READY   STATUS    RESTARTS       AGE
pipeline-test01-predictor-default-00001-deployment-7dbf4b6rb8vl   3/3     Running   3 (2d3h ago)   2d3h
```

> check initialize log
>
> ```
> $ kubectl logs pipeline-test01-predictor-default-00001-deployment-7dbf4b6rb8vl -c storage-initializer -n pipeline
> ```



**port-forward**

```
kubectl port-forward -n pipeline pipeline-test01-predictor-default-00001-deployment-7dbf4b6rb8vl 8081:8080
```



**send request**

```
$ MODEL_NAME=pipeline
$ SERVICE_HOSTNAME=$(kubectl get inferenceservice pipeline-test -n pipeine -o jsonpath='{.status.url}' | cut -d "/" -f 3)
```

```
$ curl -v -H "Host: ${SERVICE_HOSTNAME}" http://127.0.0.1:{local_port}/v1/models/${MODEL_NAME}:predict -d @./input.json
```

