# Initial setting

linux기준임

**야간 모드**

1. redshift 패키지 설치
   
   ```
   $ sudo apt-get install redshift redshift-gtk
   ```

2. 야간모드 적용
   
   ```
   $ redshift -O 4200
   ```
   
   해제
   
   ```
   $ redshift -x
   ```

**command만 영문으로 바꾸기**

1. ```
   vi ~/.bachrc
   ```
   
   > bash 사용시

2. ```
   export LANG=en_US.UTF-8
   ```
   
   > 문구 추가 후 저장

3. bash 재시작

## chrom

1. 크롬 브라우저 패키지 설치용 인증 키 
   
   ```
   $ wget -q -O - https://dl-ssl.google.com/linux/linux_signing_key.pub | sudo apt-key add -
   ```

2. 웹 브라우저 패키지를 다운받을 PPA를 cources.list.d에 추가
   
   ```
   $ sudo sh -c 'echo "deb [arch=amd64] http://dl.google.com/linux/chrome/deb/ stable main" >> /etc/apt/sources.list.d/google.list'
   ```

3. ```
   $ sudo apt-get update
   ```

4. 크롬 install
   
   ```
   $ sudo apt-get install google-chrome-stable
   ```

5. 크롬 설치를 위해 생성했던 파일 제거
   
   ```
   $ ls /etc/apt/sources.list.d/google*
   $ sudo rm -rf /etc/apt/sources.list.d/google.list
   ```

## git

```
$ apt-get install git
```

또는 

[여기](https://git-scm.com/downloads)에서 설치

install후

1. 이름과 이메일 설정
   
   ```
   $ git config --global user.name "Taeuk Noh"
   $ git config --global user.email taeuk4958@gmail.com
   ```

2. upstream 설정
   
   처음 branch를 만들고 push를 하면 upstream을 설정하라고 한다.
   
   우리는 local에서 branch를 만든 것이기 때문에 remote에 있는 git은 이 branch의 존재를 모르게 된다. upstream은 branch 자체를 git repository 서버인 origin으로 업로드 한다는 뜻이다.
   
   ```
   $ git push --set-upstream origin {branch name}
   ```
   
   > 이렇게 항상 upstream branch를 설정하라는 문구가 나오기 때문에 이러한 작업을 git의 config 설정으로 생략
   
   ```
   $ git config --global push.default current
   ```

3. git 편집 에디터 설정
   
   ```
   $ git config --global core.editor "vim"
   ```
   
   >  nano에서 vim으로 git 편집 에디터를 바꿀 수 있다. rebase 등의 과정 시 vim 에디터로 편집할 수 있다.
- **repository가져오기**
  
  - `$ git clone github_repository주소`:  
    - 로컬에서의 git init에 해당되는 명령어
    - `git remote add origin URL` 은 내가 직접 사용하는 내 계정의 URL을 관리할때 사용
    - `git clone Url` 은 남이 하는 프로젝트를 이어받거나 내가 잠시 사용할때(또는 다른 PC에서 내 URL을 사용할때) 사용
  - vscode사용

## Typora

```
$ wget -qO - https://typora.io/linux/public-key.asc | sudo apt-key add -
$ sudo add-apt-repository 'deb https://typora.io/linux ./'
$ sudo apt -y install typora
```



## Anaconda

**windows**

[여기](https://www.anaconda.com/products/individual) 에서 설치

- Install for : `All User` 선택

  >  내 PC내 설치를 할 경우 관리자 권한이 부여되기 때문

- 설치 경로 : 직접 설정 `D:Anaconda3`

  > 기본으로 할 경우 install 완료 후 해당 path를 확인하고자 할 때 path내 ProgramData가 보이지 않는 경우가 있기 때문

- Advaned Options : Register Anaconda3 as the system python 선택

- 설치 후 환경변수 추가

  1. 원도우 검색 > `고급 시스템 설정 보기` > 고급 > 환경 변수 > 시스템 변수 안의 `path` 더블클릭 
  2. 새로만들기 (아래 5개 추가)
     - `D:\Anaconda3\Library\bin`
     - `D:\Anaconda3\Library\mingw-w64\bin`
     - `D:\Anaconda3\Scripts`
     - `D:\Anaconda3`

- 설치 후 vs code와 anaconda연동하기

  1. vscode에서 Extensions를 통해 python extenstion(Python, Python for VSCode, Python Extension Pack)과 Code Runner를 설치 

  2. `ctrl + shift + p` 를 누른 후 `Python: Select Interpreter` 선택

  3. 목록 중 `'base : conda'` 선택

  4. vscode 좌측 상단 file>preferences>setting 에서 `shell window` 검색

     terminal, Integrated, defaul profile : windows 에서

     bash 선택





**linux**

1. `Anaconda3-2021.05-Linux-x86_64.sh` file다운로드 후, 해당 위치에서 무결성 확인
   
   ```
   $ sha256sum Anaconda3-2021.05-Linux-x86_64.sh
   ```

   > Anaconda3-2022.05-Linux-x86_64.sh 파일 명 확인
   
2. 설치
   
   ```
   $ bash Anaconda3-2021.05-Linux-x86_64.sh
   ```
   
   1. ```
      Please, press ENTER to continue
      >>> 
      뜨면 Enter하고 다 읽어내린 후 
      ```
   
   2. ```
      Do you accept the license terms? [yes|no]
      Please answer 'yes' or 'no':'
      >>> 
      뜨면 yes 입력 후 Enter
      ```
   
   3. ```
      Anaconda3 will now be installed into this location:
      /home/hibernation/anaconda3
      
        - Press ENTER to confirm the location
        - Press CTRL-C to abort the installation
        - Or specify a different location below
      
      [/home/hibernation/anaconda3] >>> 
      뜨면 새롭게 만들 directory의 name을 입력
      ```
   
   4. ```
      Do you wish the installer to initialize Anaconda3
      by running conda init? [yes|no]
      
      no를 입력하면 콘다는 쉘 스크립트를 수정하지 못한다. yes를 누른다
      ```
   
   5. path추가
      
      ```
      $ sudo vi ~/.bashrc
      ```
      
      text 편집기가 열리면 맨 아래줄에 추가
      
      ```
      $ export PATH="~/anaconda3/bin:~/anaconda3/condabin:$PATH"
      ```
      
      > 예시로, `home/hibernation/workspace/tmp` 의 위치에서 `$ bash Anaconda3-2021.05-Linux-x86_64.sh` 를 했어도 위 명령어 그대로 입력
      
      이후 terminer에서
      
      ```
      $ source ~/.bashrc
      ```
      
      >  (base)뜨는지 확인
      >
      > (base) 없애려면 ` $ conda deactivate`
      
      ```
      $ conda -V 
      ```
      
      version확인









## vscode

1. curl을 설치
   
   ```
   $ sudo apt-get install curl
   ```

2. 마이크로소프트 GPG 키를 다운로드하여 /etc/apt/trusted.gpg.d/ 경로에 복사
   
   ```
   $ sudo sh -c 'curl https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > /etc/apt/trusted.gpg.d/microsoft.gpg'
   ```

3. Visual Studio Code를 다운로드 받기 위한 저장소를 추가
   
   ```
   $ sudo sh -c 'echo "deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main" > /etc/apt/sources.list.d/vscode.list'
   ```

4. package가져오기
   
   ```
   $ sudo apt update
   ```

5. vscode설치
   
   ```
   $ sudo apt install code
   ```
   
   ```
   $ code
   ```
   
   실행되는지 확인

## Docker

['Docker for linux'](https://docs.docker.com/engine/install/ubuntu/)

실제 Docker server를 운영

**Repository를 이용해서 설치**

외부 network가 사용 가능할 때

1. 요구하는 program install
   
   ```
   $ sudo apt-get update
   ```
   
   ```
   $ sudo apt-get install \
       apt-transport-https \
       ca-certificates \
       curl \
       gnupg \
       lsb-release
   ```

2. Docker의 인증서 저장
   
   ```
   $ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg
   ```

3. URL등록
   
   ```
   $ echo \
     "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu \
     $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
   ```

4. install
   
   ```
   $ sudo apt-get update
   ```
   
   ```
   $ sudo apt-get install docker-ce docker-ce-cli containerd.io
   ```

5. check 
   
   ```
   $ sudo docker run hello-world
   ```
   
   tesk image를 다운로드
- **nvidia-dorker**
  
  GPU resource사용을 위해 필요
  
  ```
  $ release="ubuntu"$(lsb_release -sr | sed -e "s/\.//g")
  $ sudo apt install sudo gnupg
  $ sudo apt-key adv --fetch-keys "http://developer.download.nvidia.com/compute/cuda/repos/"$release"/x86_64/7fa2af80.pub"
  $ sudo sh -c 'echo "deb http://developer.download.nvidia.com/compute/cuda/repos/'$release'/x86_64 /" > /etc/apt/sources.list.d/nvidia-cuda.list'
  $ sudo sh -c 'echo "deb http://developer.download.nvidia.com/compute/machine-learning/repos/'$release'/x86_64 /" > /etc/apt/sources.list.d/nvidia-machine-learning.list'
  
  $ sudo apt update
  ```
  
  > 설치과정 중 sudo apt update에서 특정 file의 내용에 대한 에러가 나오면 
  > 
  > ```
  > sudo -H gedit /etc/apt/sources.list.d/nvidia-cuda.list
  > ```
  > 
  > 처럼 `sudo -H gedit`을 통해 파일 내용 확인 후 고쳐서 진행할것
  
  ```
  $ apt-cache search nvidia
  $ sudo apt-get install -y nvidia-driver-XXX # 
  $ sudo apt-get install -y dkms nvidia-modprobe
  ```
  
  > nvidia-XXX 는 알맞는 버전 확인 후 설치하면 된다. [여기](https://laondev12.tistory.com/11) 확인
  > 
  > > ```
  > > $ sudo apt-get install -y nvidia-driver-470
  > > ```
  > > 
  > > 리눅스 GeForce GTX 1650 SUPER 기준
  
  ```
  $ sudo reboot
  ```

```
$ sudo cat /proc/driver/nvidia/version | nvidia-smi
```

```
$ curl -s -L https://nvidia.github.io/nvidia-docker/gpgkey | sudo apt-key add -
$ distribution=$(. /etc/os-release;echo $ID$VERSION_ID)
$ curl -s -L https://nvidia.github.io/nvidia-docker/$distribution/nvidia-docker.list | sudo tee /etc/apt/sources.list.d/nvidia-docker.list
$ sudo apt-get update
$ sudo apt-get install -y nvidia-docker2
```

  demon.json에 추가

```
$ sudo vi /etc/docker/deamon.json
    "default-runtime" :"nvidia",
    "runtimes" :{
        "nvidia" :{
            "path:" "/usr/bin/nvidia-container-runtime",
            "runtimeArgs" : []
        }
    }
:wq
```

  **동작 확인**

  container에서 이용가능안 GPU정보를 얻는다.

```
$ sudo systemctl restart docker
$ sudo docker run --runtime=nvidia --rm nvidia/cuda:11.0-base nvidia-smi
```

> 11.0-base 부분은 
> 
> ```
> $ nvidia-smi
> ```
> 
> 의 명령어를 통해 `CUDA Version:`  을 확인 후 알맞는 version기입 (11.4 이면 `11.0-base` 기입)

- **Uninstall old versions**
  
  ```
  $ sudo apt-get remove docker docker-engine docker.io containerd runc
  ```

- **계정에 docker 권한 부여**
  
  ```
  root:~# usermod -a -G docker $USER
  ```
  
  재부팅 후 확인
  
  ```
  $ id
  ```
  
  `997(docker)` 가 포함되어 있다면 권한 부여된 것

- kubernetes사용 할 계획이면 미리 세팅할 것
  
  - Docker 데몬 드라이버 변경
    
    Docker 데몬이 사용하는 드라이버를 cgroupfs 대신 systemd를 사용하도록 설정
    
    1. ```
       $ sudo chown $USER:docker /etc/docker
       ```
    
    2. Setup daemon
       
       ```
       $ sudo cat > /etc/docker/daemon.json <<EOF
       {
         "exec-opts": ["native.cgroupdriver=systemd"],
         "log-driver": "json-file",
         "log-opts": {
           "max-size": "100m"
         },
         "storage-driver": "overlay2"
       }
       EOF
       ```
       
       ```
       $ sudo mkdir -p /etc/systemd/system/docker.service.d
       ```
    
    3. Restart docker
       
       ```
       $ sudo systemctl daemon-reload
       $ sudo systemctl restart docker
       ```

## Kubernetes

#### Kind, kubectl(windows)

**Kind**

```
$ curl -Lo ./kind https://kind.sigs.k8s.io/dl/v0.11.1/kind-linux-amd64
```

```
$ chmod +x ./kind
```

```
$ sudo mv ./kind /usr/bin/kind
```

설치 확인

```
$ kind version
```

**kubectl**

```
$ curl -O https://storage.googleapis.com/kubernetes-release/release/v${VERSION}/bin/${OS_TYPE}/amd64/kubectl
```

```
$ chmod +x kubectl
```

```
$ sudo mv ./kubectl /usr/bin/kubectl$ 
```

설치 확인

```
$ kubectl version
```

환경설정

1. shell 자동 완성 기능 (bash)
   
   ```
   $ source <(kubectl completion bash)
   ```
   
   > 다음 번 로그인할 떄 다른 shell을 기동했을 경우에도 자동 완성 기능을 활성화하려면 `~/.bashrc` 로 설정해야 한다.
   > 
   > ```
   > $ echo 'source <(kubectl completion bash)' >> ~/.bachrc
   > ```

#### kubelet, kubeadm, kubectl(linux)

kubelet, kubeadm, kubectl, docker 한 번에 설치

1. 필요한 의존 package 설치
   
   ```
   $ sudo apt update && sudo apt install -y apt-transport-https curl
   ```

2. 저장소 등록 및 업데이트
   
   ```
   $ curl -s http://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add -
   ```
   
   ```
   $ cat << E0F | sudo tee /etc/apt/sources.list.d/kubernetes.list
   > deb http://apt.kubernetes.io/ kubernetes-xenial main
   > E0F
   ```
   
   ```
   $ sudo apt update
   ```

3. kubernetes관련 package 설치
   
   ```
   $ sudo apt install -y kubelet=1.18.15-00 kubeadm=1.18.15-00 kubectl=1.18.15-00
   ```
   
   kubeadm 의 version이 곧 kubernetes 의 version이다.

4. 버전 고정
   
   ```
   $ sudo apt-mark hold kubelet kubeadm kubectl docker.io
   ```

## pip 설치

**windows**

[링크](https://github.com/HibernationNo1/TIL/raw/master/image/get-pip.py)를 저장 후 해당 위치에서 명령어

```
$ python get-pip.py
```

```
pip install tensorflow
pip install numpy
pip install opencv-python
```

```python
import tensorflow as tf
import tensorflow.keras as tk
import numpy as np
import pandas as pd
import cv2
import scipy

print(tf.__version__)
print(tk.__version__)
print(np.__version__)
print(pd.__version__)
print(cv2.__version__)
print(scipy.__version__)
```

## GPU_CUDA설치

### Ubuntu



### windows

#### graphic driver

**1. check GPU**

NVIDIA GTX-1060 3GB 기준

- 그래픽카드 확인
  
  장치관리자 > 디스플레이 어뎁터

- [여기](https://www.studio1productions.com/Articles/NVidia-GPU-Chart.htm)서 CUDA core 수 확인
  
  ![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2F49t3X%2FbtqyEA98R9n%2FxTxNRuRsrJeB8yW2UgHb10%2Fimg.png)
  
  NVIDIA GTX-1060 3GB는 코어 1152임을 확인
  
  CUDA Cores = **1152**

- 성능 확인
  
  [여기](https://www.wikiwand.com/en/CUDA) 서 ctrl + f로 `1060` 검색  (또는 [여기](https://en.wikipedia.org/wiki/CUDA))
  
  6.1임을 확인
  
  ![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2F0b42E%2FbtqyGmpmz1S%2FCoqplHiiDHOyphS9sBOVe0%2Fimg.png)
  
  CUDA Compute Capability = **6.1**

**2. graphic driver 설치**

 [여기](https://www.nvidia.co.kr/Download/index.aspx?lang=kr) 에서 graphic driver를 설치

> 제품유형 : GeForce
> 
> 시리즈 : GeForce 10 Series
> 
> 계열 : GeForce GTX 1060
> 
> windows 10 64-bit
> 
> 다운로드 타입 : Game -Ready 드라이버 : 일반 사용자용,  sutido 드라이버 : 작업툴에서 성능발휘

#### CUDA toolkit

**1. Download CUDA**

- 쿠다 version 확인
  
  ![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbeO6bC%2FbtqyGvNswxK%2FNDZCW4KvK2zKZp2ejkkuH0%2Fimg.png)
  
  CUDA Compute Capability = **6.1** 이기에 SDK = 10.0~10.1 임을 확인

- 자신의 version에 맞게 다운
  
  [여기](https://developer.nvidia.com/cuda-toolkit-archive)서 알맞는 version 선택![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fzq3zP%2FbtqyFZ2v0R5%2FpUShfkRCyKo3NvMuc8p2W0%2Fimg.png)
  
  - network는 internet을 통해 여러 번 다운받는 것
  - local은 한 번에 받는 것 (internet이 일정하게 문제 없다면 이걸로 받기)
  
  visual studio가 설치되어 있어야함
  
  [여기](https://visualstudio.microsoft.com/ko/thank-you-downloading-visual-studio/?sku=Community&rel=16) 에서 community 2019다운

- 경로 지정 후 설치 (default로 지정함)
  
  `C:\Users\마이노\AppData\Local\Temp\CUDA`

- 환경 변수 추가 및 확인
  
  경로를 default로 했으면 환경 변수 자동으로 추가됨
  
  시스템 환경 변수 > 환경 변수
  
  `cudart64_100.dll` 가 있는 path
  
  `C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v10.0\bin`



**2. conda install**

1. 가상환경 만들며 install

   ```
   $ conda create -n env_name python=3.8 pytorch torchvision cudatoolkit=11.7 -c pytorch -c conda-forge -y
   ```

2. 명령어

   ```
   $ conda install pytorch torchvision torchaudio cudatoolkit=11.3 -c pytorch
   ```

   > 또는 [여기](https://pytorch.org/get-started/locally/) 



cudatoolkit의 version에 따라 `torch.cuda.is_available()` 의 `False`, `True`여부가 달라지니 반드시 확인



#### cuDNN

**Download cuDNN**

> Tensorflow사용 시 필요

cuDNN는 회원가입을 해야 다운로드 가능

[여기](https://developer.nvidia.com/cudnn)에서 로그인 후 다운로드

다운받은 file(`bin`, `include`, `lib`)을 

`C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.4` 에 옮긴다.

