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







## resource

### InferenceService

kubeflow의 endpoint를 사용하여 `InferenceService` 를 배포할때 두 가지 경우가 있다.

1. 기본 

   ```
   apiVersion: "serving.kserve.io/v1beta1"
   kind: "InferenceService"
   metadata:
     annotations:
       isdecar.istio.is/inject: "false"
     name: "kserve-test"
   spec:
     predictor:
       pytorch:
         image: "hibernation4958/kserve_test:0.6"
         storageUri: "gs://pipeline_kserve_test_01"
   ```

   docker image를 통해 KServe의 내장된 PyTorch 서버를 사용하여 모델을 로드하고 실행한다.

   이 방법은 KServe에서 미리 정의된 모델 서버를 사용할 때 가장 효과적이다.

   - docker image의 Dockerfile 예시

     ```
     FROM ubuntu:20.04
     
     # 환경변수 설정으로 tzdata 패키지 설치 중에 나오는 대화식 질문을 회피
     ENV DEBIAN_FRONTEND=noninteractive
     
     # 패키지 업데이트 및 Python3와 pip 설치
     RUN apt-get update && apt-get install -y \
         python3.8 \
         python3-pip
     
     # 기본적으로 python3.8 버전을 사용하도록 설정
     RUN update-alternatives --install /usr/bin/python3 python3 /usr/bin/python3.8 1
     
     # 파이썬 버전 확인
     RUN python3 --version
     
     # 작업 디렉토리 설정
     WORKDIR /app
     
     COPY . .
     RUN pip3 install --no-cache-dir -r requirements.txt
     
     
     
     ENTRYPOINT ["python3", "-m", "server"]
     
     ```

     - `ENTRYPOINT ["python3", "-m", "server"]` : 해당 container가 실행될 때 server라는 module이 실행되도록 한다.

        

2. 사용자 포맷 정의

   ```
   apiVersion: "serving.kserve.io/v1beta1"
   kind: "InferenceService"
   metadata:
     annotations:
       isdecar.istio.is/inject: "false"
     name: "kserve-test"
   spec:
     predictor:
       model:
         modelFormat:
           name: pytorch
         storageUri: "gs://kfserving-examples/models/torchserve/image_classifier/v1"
   ```

   사용자가 모델 포맷을 직접 정의한다.

   모델은 PyTorch 포맷으로 정의되어 있지만, 실제 모델의 로딩과 실행에 대한 로직은 사용자가 정의하기 때문에 사용자 정의 모델 서버를 구성할 때 유용하다.



#### storageUri

storageUri은 aws, google storage등 다양한 storage를 지정할 수 있다.

- **google storage인 경우**

  1. 해당 객체가 저장된 bucket과, 해당 객체는 전체 공개(누구든지 접근 가능)이어야 한다.

     공개로 하는법 : https://cloud.google.com/storage/docs/access-control/making-data-public?hl=ko

     해당 객체가 공개 access인지 확인하는 방법

     > gsutil 설치 필요

     1. 특정 file인 경우

        ```
        gsutil cp gs://pipeline_kserve_test_01/model_36.pth .
        ```

     2. 특정 path인 경우(dir)

        ```
        gsutil cp -r gs://kfserving-examples/models/torchserve/image_classifier/v1 .
        ```


  2. gs의 bucket은 최소 1개의 dir path아래 target file을 가져야 한다.

     ```
     storageUri: "gs://bucket_name/dir"			# 특정 dir안의 file을 모두 참조
     ```

     > ```
     > storageUri: "gs://bucket_name"			 # bucket만 명시하면 pod가 init단계에서 멈춘다.
     > ```



### pod

`InferenceService`를 배포 후 아래 명령어로 해당 service를 관리하는 pod를 확인

```
kubectl get pods -n {namespace} -l serving.kserve.io/inferenceservice={service_name}
```

해당 pod의 STATUS가 `init:` 형태인 경우 log를 확인하려면 init container의 log를 확인해야 한다.

1. init container확인 

   ```
   kubectl describe pod <pod-name> -n <namespace>
   ```

   출력에서 `Init Containers` 부분에서 init container의 이름을 알 수 있다.

   ```
   Init Containers:
     storage-initializer:
       Container ID:  docker://3d7e883e67c41301f2bdbe2bb897f6de54bf235d3f216e5df5de7986edd77ead
       Image:         kserve/storage-initializer:v0.10.0
       Image ID:      
       ...
       ...
   ```

   위와 같은 경우 init container의 이름은 `storage-initializer`이다.

2. log확인

   ```
   kubectl logs <pod-name> -c <init-container-name> -n <namespace>
   ```

   
