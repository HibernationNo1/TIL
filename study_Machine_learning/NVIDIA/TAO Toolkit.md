# TAO Toolkit

TAO(Train Adapt Optimize) Toolkit은 TensorFlow와 PyTorch를 기반으로 구축된 python 기반 AI Toolkit으로, neural network architecture와 backborn을 데이터에 맞게 조정하는 전이 학습 기능을 제공하여 엣지 배포를 위해 고도로 최적화되고 정확한 AI 모델을 training, fine-tune, prune, quantize 하여 배포할 수 있도록 도와준다.

- TAO Toolkit package 는 containers, python wheels, models 그리고 helm chart로 제공된다.



[docs](https://docs.nvidia.com/tao/tao-toolkit/text/tao_toolkit_quick_start_guide.html#launcher-cli)



**TAO를 사용하는 방법에는 4가지가 있다.**

- **Launcher CLI**: TAO를 실행하는 가벼운 Python 기반 CLI
- **Directly from Container**: Docker 컨테이너를 사용하여 TAO를 직접 실행할때 사용.
- **TAO Toolkit API**: TAO Toolkit API는 REST API를 사용하여 엔드투엔드 AI 모델을 구축할 수 있는 Kubernetes 서비스로, Helm 차트를 사용하여 Kubernetes 클러스터(로컬/AWS EKS)에 설치할 수 있다.
- **Python Wheel**: Docker 또는 K8s 없이 bare-metal 에서 직접 TAO를 실행할때 사용.





### Installing the Pre-requisites

1. Install `docker-ce` by following the [official instructions](https://docs.docker.com/engine/install).

   After you have installed docker-ce, follow the [post-installation steps](https://docs.docker.com/engine/install/linux-postinstall/) to ensure that the Docker can be run without `sudo`.

2. Install `nvidia-container-toolkit` by following the [install-guide](https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/install-guide.html).

3. docker client를 사용하여 NVIDIA의 container registry (nvcr.io)에 로그인

   ```
   $ docker login nvcr.io
   ```

   - `nvcr.io` : NVIDIA의 contianer registry 주소

   ```
   Username: $oauthtoken
   Password:  <Your Key>
   ```

   - Username 에는 반드시 `$oauthtoken` 를 입력

   - API key 생성 방법

     1. NVIDIA NGC 에 접속하여 로그인

     2. 우측 상단 개인메뉴 클릭 후 `Setup` 선택

     3. Generate API Key 선택 > `+ Generate API Key` 클릭

        API key는 1개만 존재할 수 있다.

   - 접속 성공 시 아래와 같은 출력 

     ```
     WARNING! Your password will be stored unencrypted in /home/sirs/.docker/config.json.
     Configure a credential helper to remove this warning. See
     https://docs.docker.com/engine/reference/commandline/login/#credentials-store
     
     Login Succeeded
     ```





## Launcher CLI

1. Download the TAO package (version: 5.3.0)

   ```
   $ wget --content-disposition https://api.ngc.nvidia.com/v2/resources/nvidia/tao/tao-getting-started/versions/5.3.0/zip -O getting_started_v5.3.0.zip
   $ unzip -u getting_started_v5.3.0.zip  -d ./getting_started_v5.3.0 && rm -rf getting_started_v5.3.0.zip && cd ./getting_started_v5.3.0
   ```

2. Install the CLI launcher using the quick start script downloaded

   ```
   bash setup/quickstart_launcher.sh --install
   ```

   



## Directly from Container

#### Run container

1. container 선택

   Nvidia NGC 에 접속 > 좌측 탭 중 Contianers 선택 > TAO 검색

   #### Tag

   - **pyt**: PyTorch(Pyt)를 기반으로 하는 TAO Toolkit container

     PyTorch를 사용하여 모델을 훈련, 검증, 최적화하고자 할 때 사용한다.

   - **deploy**: 모델을 배포(deploy)하기 위한 container

     훈련된 모델을 배포하는 환경을 구성할 때 사용한다.

   - **data-services**: 데이터 서비스(data services)를 위한 container

     데이터 전처리, 변환, 증강 및 데이터 파이프라인을 구성하는 데 사용

   - **api**: API를 통해 모델을 사용할 수 있게 하는 container (TAO Toolkit API 사용)

     RESTful API 또는 다른 형태의 API를 통해 모델을 호출하고 사용할 수 있는 환경을 제공

   - **tf**: TensorFlow(TF)를 기반으로 하는 TAO Toolkit container

2. docker 실행

   - docker run

     ```
     docker run --gpus all -it --rm nvcr.io/nvidia/tao/tao-toolkit:5.3.0-deploy
     ```

   - docker compose

     ```
     version: '3.8'
     
     services:
       tao_toolkit:
         image: nvcr.io/nvidia/tao/tao-toolkit:5.3.0-deploy
         runtime: nvidia
         environment:
           NVIDIA_VISIBLE_DEVICES: all
         volumes:
           - ./../ocr_api:/workspace
         working_dir: /workspace
         stdin_open: true
         tty: true
     
     # docker-compose -f docker-compose_tao.yml up -d 
     ```

     







