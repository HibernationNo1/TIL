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
	--requirements-file requirements.txt
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

  `config.properties`file에 `install_py_dep_per_model=true`를 포함시켜야 한다.

  **사용하는 경우**

  **kserve를 통해 배포**할 때 pod의 환경에 library를 install하는 경우 사용된다.

  `requirements.txt`는  kserve의 환경이 될 docker container내부에서 install이 가능한 library만 포함해야 한다.

  > kserve의 container image의 환경이 python3.7인데 python3.8에서만 install가능한 library가 있다면 requirements.txt의 모든 lib이 설치되지 않는다

- `--export-path`: 생성된 model archive file(`.mar`)이 저장될 directory를 지정한다. 

  default는 `.` 이다.

  > `hendler.py`에서 import할 modul 및 python file을 포함한다.

- `--force`: 해당 option을 사용하면 이미 존재하는 archive file이 있을 경우 덮어씌운다.





#### config.properties

properties는 지정할 수 있는 사용자가 torchserve에 대한 설정을 결정한다.

```
inference_address=http://0.0.0.0:8095
management_address=http://0.0.0.0:8091
metrics_address=http://0.0.0.0:8092
grpc_inference_port=7070
grpc_management_port=7071
enable_envvars_config=true	
enable_metrics_api=true
metrics_format=prometheus
NUM_WORKERS=4
number_of_netty_threads=4
job_queue_size=10
load_models=all
number_of_gpu=1
gpu_id=0
install_py_dep_per_model=true
model_store=/mnt/models/model-store	
model_snapshot={"name": "startup.cfg", "modelCount": 1, "models": {"pipeline": {"1.0": {"defaultVersion": true, "marName": "pipeline.mar", "minWorkers": 1, "maxWorkers": 3, "batchSize": 4, "maxBatchDelay": 100, "responseTimeout": 120}}}}
```

- `enable_envvars_config=true`: TorchServe가 환경 변수를 사용하여 구성 설정을 오버라이드할 수 있도록 설정한다.

-  `enable_metrics_api=true`: TorchServe가 지표(metrics) API를 사용할 것인지를 정의한다.

- `metrics_format=prometheus`: TorchServe가 어떤 유형의 메트릭 시스템을 사용하는지를 정의한다.

- `NUM_WORKERS=`: orchServe에서 사용하는 워커(worker) 프로세스의 수를 지정한다.

- `number_of_netty_threads=`: Netty를 사용하여 비동기 네트워킹을 처리하는 데 사용되는 스레드 수를 지정한다. torchserve의 network처리 성능에 영향을 미친다

- `job_queue_size=`: TorchServe의 작업 큐 크기를 지정한다.

- `load_models=all`: TorchServe가 시작될 때 로드할 모델을 지정한다.

   `all` 값은 모든 사용 가능한 모델을 로드하도록 TorchServe에 지시한다.

- `number_of_gpu=1`: TorchService에서 사용할 GPU의 갯수를 지정한다.

- `gpu_id=0`: 사용할 gpu 의 id를 지정한다.

-  `install_py_dep_per_model=true`: kserve에 의한 배포를 진행할 때 inference를 진행할 pod에 설치할 module을 적어놓은 requirements.txt를 전달한 경우 추가한다.

- `model_store=` kserve의  `storageUri`로부더 download한 model(`.mar`)을 위치할 path를 지정한다



torchserve가 정상적으로 구동됨을 확인했다는 가정 하에 다음 step진행



## gs

`.mar`과 `config.prosperties`를 공개 storage에 upload한다.

> `gsutil` 설치 필요

upload하려는 storageUri은 `gs://bucket_name/dir`과 같이 bucket하위 최소 1층의 dir의 위치에 있어야 한다.

1. upload하고자 하는 path를 공개 access로 변경

   https://cloud.google.com/storage/docs/access-control/making-data-public?hl=ko

   버킷의 모든 객체를 읽을 수 있도록 공개

   

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
      $ gsutil cp -r gs gs://bucket_name/dir
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
  name: "test-01"
spec:
  predictor:
    pytorch:
      storageUri: "gs://bucket_name/dir/dir_name"
      resources:
        limits:
          nvidia.com/gpu: 1
          cpu: "4" 
          memory: "4Gi"
        requests:
          cpu: "1"
          memory: "2Gi" 
      image: "192.168.219.100:5000/kserve:0.1"
```

- `storageUri`:  `gs://bucket_name/dir`과 같이 bucket하위 최소 1층의 dir의 위치에 있어야 한다.

- `resources`: kserve/InferenceService에 의해 만들어진 pod에 할당된 resource의 최소, 최대 할당값을 지정한다

  - `nvidia.com/gpu: 1`: 사용할 GPU의 개수를 지정한다.

    GPU를 사용하기 위해 해당 문구는 반드시 포함되어야 한다.

- `image`: kserve/InferenceService에 의해 만들어진 pod의 환경을 구성할 docker image를 지정한다

  InferenceService가 GPU를 사용하는 경우 docker image pull할 때 `{image_name}-gpu`으로 pull을 하게 된다.

  > `hibernation4958/kserve:0.1`로 할당한 경우 `hibernation4958/kserve:0.1-gpu`를 pull하게 된다

  ```
  image: "192.168.219.100:5000/kserve:0.1"
  ```

  위 처럼 특정  IP의 registry로부터 pull을 하려면, 해당 InferenceService를 배포하는 device에서 docker의 demon에 아래 내용을 추가해야 한다.

  ```
  $ vi /etc/docker/daemon.json
  ```

  ```
  {
  
   "insecure-registries": ["192.168.219.100:5000"]
  
  }
  ```

  ```
  $ systemctl restart docker
  ```

  



**tip**

- kserve/InferenceService에 의해 만들어진 pod가 반복적으로 kill되는 경우

  해당 pod에 의해 torch-archrive명령어가 실행될 때 아래와 같이 실행할 수 없는 code가 포함된 경우가 있다.

  ```
  import subprocess
  
  command = "pip install mmcv-full==1.5.3 -f https://download.openmmlab.com/mmcv/dist/cu112/torch1.13.0/index.html"
  subprocess.call(command, shell=True)
  ```

  > pod의 환경에 설치가 불가능한 module을 설치하고자 하는 python code
  >

  

### docker image

pytorch를 사용하여 학습된 model인 경우 [`pytorch/torchserve-kfs`](https://hub.docker.com/r/pytorch/torchserve-kfs)  의 image를 기반으로 환경우 구성하는게 좋다

kserve의 example로 제공되는 InferenceService 또한 해당 image를 사용한다

> pod에 어떤 container가 사용되는지 확인하는 방법
>
> ```
> $ kubectl describe pod pod_name -n pipeline
> ```
>
> ```
> ...
>   kserve-container:
>     Container ID:  docker://443bdd2498a05531f9a0e336cd4d8225eef04aa2fb06e473dfb24e842e4731fd
>     Image:         index.docker.io/pytorch/torchserve-kfs@sha256:6daae3c54cf6b1785c4eb9849c4d1b88adf04625057c4026126b1b6a3cd27f5b
>     Image ID:      docker-pullable://pytorch/torchserve-kfs@sha256:6daae3c54cf6b1785c4eb9849c4d1b88adf04625057c4026126b1b6a3cd27f5b
> ...
> ```
>
> `pytorch/torchserve-kfs`라는 container임을 확인
>
> - DIGEST 확인: `kfs@sha256:6daae3c54cf6b1785c4eb9849c4d1b88adf04625057c4026126b1b6a3cd27f5b`
>
>   DIGEST는 docker가 push된 registry에서 tag를 확인하는데 사용된다
>
> 해당 image를 기반으로 새로운 docker image생성, 필요한 package를 install한다



**example**: 아래는 ubuntu 20.04에 python3.8의 환경을 제공하는 dockerfile이다.

> `pytorch/torchserve-kfs`를 분해하여 재조립한 docekrfile이다.
>
> pip를 통한 library 설치 시 해당 환경에 알맞는 version을 명시해야 한다.
>
> - requirements.txt
>
> ```
> kserve==0.10.2
> fastapi==0.88.0
> transformers==4.30.2
> captum==0.6.0
> 
> torchserve==0.8.1
> 
> pycocotools==2.0.6
> matplotlib==3.7.1
> terminaltables==3.1.0
> nvgpu==0.9.0
> pynvml==11.4.1
> Pillow==9.5.0
> addict==2.4.0
> tensorboard==2.13.0
> protobuf==3.19.6
> requests==2.28.2
> urllib3==1.26.14
> chardet==5.1.0
> ```
>
> - pynvml의 version은 2023년에 11.5.0이 새롭게 release되었다. 하지만 이는 470번대 nvidia version과 호환되지 않기 때문에 pynvml는 11.4.1을 사용해야 한다.

```
FROM ubuntu:20.04
LABEL org.opencontainers.image.ref.name=ubuntu
LABEL org.opencontainers.image.version=20.04

ARG TARGETARCH=amd64

# ADD file:d05d1c0936b046937bd5755876db2f8da3ed8ccbcf464bb56c312fbc7ed78589 in / 
CMD ["/bin/bash"]

# install package
RUN apt-get update && \
    apt-get install -y --no-install-recommends curl vim sudo wget
RUN useradd -m winter && echo "winter:4958" | chpasswd && adduser winter sudo

# set CUDA
ENV NVARCH=x86_64
ENV NVIDIA_REQUIRE_CUDA=cuda>=11.3 brand=nvidia,driver>=470,driver<471 
ENV NV_CUDA_COMPAT_PACKAGE=cuda-compat-11-3
ENV NV_CUDA_CUDART_PACKAGE=cuda-cudart-11-3
RUN apt-get update && \
    apt-get install -y --no-install-recommends gnupg2 ca-certificates && \
    curl -fsSL https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2004/${NVARCH}/3bf863cc.pub | apt-key add - && \
    echo "deb https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2004/${NVARCH} /" > /etc/apt/sources.list.d/cuda.list && \
    rm -rf /var/lib/apt/lists/* 
RUN apt-get update && \
    apt-get install -y --no-install-recommends ${NV_CUDA_CUDART_PACKAGE}\
    ${NV_CUDA_COMPAT_PACKAGE} && \
    rm -rf /var/lib/apt/lists/* 
RUN echo "/usr/local/nvidia/lib" >> /etc/ld.so.conf.d/nvidia.conf && \
    echo "/usr/local/nvidia/lib64" >> /etc/ld.so.conf.d/nvidia.conf 
ENV PATH=/usr/local/nvidia/bin:/usr/local/cuda/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
ENV LD_LIBRARY_PATH=/usr/local/nvidia/lib:/usr/local/nvidia/lib64
ENV NVIDIA_VISIBLE_DEVICES=all
ENV NVIDIA_DRIVER_CAPABILITIES=compute,utility
COPY ./copy/NGC-DL-CONTAINER-LICENSE /

# install python3, package-python, java
ENV PYTHONUNBUFFERED=TRUE
ARG PYTHON_VERSION=3.8
COPY ./copy/home/venv /home/venv 
RUN apt-get update --fix-missing && apt-get upgrade -y && \
    apt-get install -y software-properties-common && \
    add-apt-repository -y ppa:deadsnakes/ppa && \
    apt remove python-pip && \
	apt-get install -y python3-pip && \
    DEBIAN_FRONTEND=noninteractive apt-get install --no-install-recommends -y \
    python$PYTHON_VERSION \
    python3-distutils \
    python$PYTHON_VERSION-dev \
    python$PYTHON_VERSION-venv \
    openjdk-17-jdk \
    build-essential \
    && rm -rf /var/lib/apt/lists/* \
    && cd /tmp 
# create symbolic link for use `python` command for `python3`
RUN ln -s /usr/bin/python3 /usr/local/bin/python

ENV PATH=/home/venv/bin:/usr/local/nvidia/bin:/usr/local/cuda/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin

# COPY
RUN useradd -m model-server && \
    mkdir -p /home/model-server/tmp && \
    chown -R model-server /home/model-server && \
    mkdir /home/model-server/model-store && \
    chown -R model-server /home/model-server/model-store 
COPY ./copy/kserve_wrapper /home/model-server/kserve_wrapper
COPY ./copy/requirements.txt /home/model-server/requirements.txt
WORKDIR /home/model-server

# install requirements
RUN pip install -r requirements.txt
RUN pip install opencv-python-headless
RUN pip install torch==1.12.0+cu113  -f https://download.pytorch.org/whl/torch_stable.html

# set entryporint for kserve
COPY ./copy/dockerd-entrypoint.sh /usr/local/bin/dockerd-entrypoint.sh 
RUN chmod +x /usr/local/bin/dockerd-entrypoint.sh && \
    chmod +x /home/venv/bin

USER model-server
EXPOSE 7070/tcp 7071/tcp 8080/tcp 8081/tcp 8082/tcp
ENV TEMP=/home/model-server/tmp
ENTRYPOINT ["/usr/local/bin/dockerd-entrypoint.sh"]
CMD ["serve"]

# docker build docker --no-cache -t hibernation4958/kserve:0.1-gpu
# docker push hibernation4958/kserve:1.8-gpu

# docker build docker --no-cache -t localhost:5000/kserve:0.1-gpu
# docker push localhost:5000/kserve:0.1-gpu
```





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
   



**tip**

만일 pod는 Runinng인데 torchserve가 멈추거나 worker가 죽는 경우 해당 pod에 접속해서 여러 명령어를 통해 package또는 library version을 확인하자

```
kubectl exec -it pod_name -n pipeline -- /bin/bash
```







### ex

**resource**

```
apiVersion: "serving.kserve.io/v1beta1"
kind: "InferenceService"
metadata:
  annotations:
    isdecar.istio.is/inject: "false"
  name: "test-01"
spec:
  predictor:
    pytorch:
      storageUri: "gs://pipeline_kserve_test_01/dir/gs"
      resources:
        limits:
          nvidia.com/gpu: 1
          cpu: "4" 
          memory: "4Gi"
        requests:
          cpu: "1"
          memory: "2Gi" 
      image: "hibernation4958/kserve:0.1"
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



또는 , 특정 image를 request로 보내는 python code

```python
import base64
import json
import argparse
import os, os.path as osp
import cv2
import requests

URL = "http://localhost:8095/predictions/pipeline"
ACCEPT_MB = 5
class Kserve_cfg():
    URL = "http://127.0.0.1:8081/v1/models/pipeline:predict"
    headers = dict(Host = 'test-02.pipeline.svc.cluster.local')


# python request.py 20230219_102814_3.jpg --kserve
def parser_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("filename", help="converts image to bytes array",
                        type=str)
    parser.add_argument("--kserve", help="converts image to bytes array",
                        action='store_true')
    
    args = parser.parse_args()
    return args

def resize_image(file_name, scale):    
    file_path = osp.join(os.getcwd(), file_name)
    if not osp.isfile(file_path):
        raise OSError(f"The file does not exist! \n file path: {file_path}")
    
    org_img = cv2.imread(file_path)
    h, w, c = org_img.shape
    
    re_h, re_w = int(h*scale), int(w*scale)
    re_img = cv2.resize(org_img, (re_w, re_h))
    
    print(f"Resizing from [{h}, {w}, {c}] to [{re_h}, {re_w}, {c}]")
    
    return re_img


def send_request_get_response(request, kserve = False):    
    if kserve:
        response = requests.post(Kserve_cfg.URL, json=request, headers=Kserve_cfg.headers)
        print(f"\n    request: {Kserve_cfg.URL}\n    header: {Kserve_cfg.headers}")
    else:
        response = requests.post(URL, json=request)
        print(f"Send request to {URL}")
    
    # show response
    if not response.text == '':
        license_info = response.json() # ['response']
        print(f"license_info : {license_info}")
        exit()
        if license_info is None or license_info == 'None': 
            print(f"License plate detection failed.")
            exit()
        print(f"License plate information")
        for key, value in response.json()['response'][0].items():
            if key in ['width', 'height', 'board_center_p']: continue
            print(f"	{key}: {value}")
    else:
        print("Request has been denied.")
   

def endecode_image(image_bytes):
    image_64_encode = base64.b64encode(image_bytes)        # encode image to base64
    bytes_array = image_64_encode.decode('utf-8')    # decode base64 to UTF-8 string
    request = {"data": bytes_array}
    return request
    
def get_size_reque_mbytes(request):
    # check size of request
    json_string = json.dumps(request)
    json_bytes = json_string.encode('utf-8')
    size_in_bytes = len(json_bytes)
    size_in_mbytes = size_in_bytes/(1024*1024)
    return size_in_mbytes

if __name__ == '__main__':
    args = parser_args()
        
    file_path = osp.join(os.getcwd(), args.filename)
    if not osp.isfile(file_path):
        raise RuntimeError(f"File dose not exist: {file_path}")
    
    image_file = open(file_path, 'rb')          # open binary file in read mode
    image_bytes = image_file.read()             # <class 'bytes'>
    
    request = endecode_image(image_bytes)
    size_mbytes = get_size_reque_mbytes(request)
    if size_mbytes > ACCEPT_MB:
        image_np = resize_image(args.filename, 6/size_mbytes*1)       # load image and resizing
        _, buffer = cv2.imencode(".jpg", image_np)          # compression in memory
        image_bytes = buffer.tobytes()                      # convert to `bytes`
        request = endecode_image(image_bytes)
        
        size_mbytes_re = get_size_reque_mbytes(request)
        if size_mbytes_re > ACCEPT_MB:
            raise RuntimeError(f"The size of the request payload too large.\n"
                f"              Size of the request payload: {size_mbytes_re:.3f} MB")

    send_request_get_response(request, args.kserve)


```

