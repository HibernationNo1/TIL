# Docker 입문

{:toc}



## install



#### DOCKER

##### Ubuntu

[공식 문서](https://docs.docker.com/engine/install/ubuntu/)

**Install using the repository**

1. install docker의 prerequisite packge

   ```
   $ sudo apt-get update
   $ sudo apt-get install \
       ca-certificates \
       curl \
       gnupg \
       lsb-release
   ```

2. GPH key추가

   ```
   $ sudo apt-get update
   $ sudo install -m 0755 -d /etc/apt/keyrings
   $ sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
   $ sudo chmod a+r /etc/apt/keyrings/docker.asc
   ```

3. repository를 follow하도록 설정

   ```
   $ echo \
     "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
     $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
     sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
   $ sudo apt-get update
   ```

   > arm기반의 cpu인 경우 위 명령어 대신 다른 명령어 사용(검색하기)

4. install Docker Engine (최신 version)

   ```
   $ sudo apt-get install docker-ce docker-ce-cli containerd.io docker-compose-plugin
   ```

   > 특정 version의 docker engine을 install하고자 한다면 공식 문서 참고
   >
   > 1. 사용 가능한 verison확인
   >
   >    ```
   >    $ apt-cache madison docker-ce | awk '{ print $3 }'
   >    ```
   >
   > 2. version명시한 후 설치
   >
   >    ```
   >    $ VERSION_STRING=5:26.1.0-1~ubuntu.24.04~noble
   >    $ sudo apt-get install docker-ce=$VERSION_STRING docker-ce-cli=$VERSION_STRING containerd.io docker-buildx-plugin docker-compose-plugin
   >    ```

5. check

   ```
   $ sudo docker run hello-world
   ```

   `Hello from Docker!` 이 포함된 출력문이 나오면 된것

6. add user to docker group

   sudo 명령어 없이 docker를 실행하기 위한 조치

   ```
   $ sudo usermod -aG docker $USER
   ```

   바로 적용
   
   ```
   $ newgrp docker
   ```
   
   



**Uninstall old versions**

```
$ sudo apt-get remove docker docker-ce docker-ce-cli containerd.io docker-compose-plugin
```



##### windows

1. [공식 페이지](https://www.docker.com/products/docker-desktop/) 에서 다운 후 실행

   Use WSL 2 instead of Hyper-V 선택

   > Hyper-V 사용 시 문제발생

   설치 후 [여기](https://docs.microsoft.com/ko-kr/windows/wsl/install-manual#step-4---download-the-linux-kernel-update-package) 서 linux kernel(WSL2) updata package다운 후 설치 (PC 다시시작 필요)

2. setting가서 

   General > Use the WSL 2 based engine 체크 확인

   Resources > WSL integration > Enable integration with my default WSL distro 체크 확인

3. WSL2 VM resource limit

    WSL2 VM 가 점유하는 메모리가 상당함 > limit을 걸어준다.

   User폴더에서 .wslconfig file을 만들어준다. (powershell에서 vscode킴)

   ```
   $ PS C:\Users\ITC> code .wslconfig
   ```

   아래 내용 입력

   ```
   [wsl2]
   memory=4GB
   processors=2
   swap=0
   ```

   이후 

   docker desktop 종료 후 powershell을 관리자 권한으로 새롭게 open

   LxssManager를 다시 실행해야 함

   ```
   PS C:\WINDOWS\system32> Get-Service LxssManager | Restart-Service
   ```

   







#### NVIDIA DOCKER

##### Ubuntu

docker contianer안에서 GPU를 사용하기 위해선 필수

[공식문서](https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/latest/install-guide.html) 참고

1. Setting up NVIDIA Container Toolkit

   ```
   $ sudo apt-get update
   $ sudo apt-get install -y nvidia-container-toolkit
   ```
   
2. install nvidia-docker2

   ```
   $ sudo apt-get install -y nvidia-docker2
   ```

   - `sudo apt-get update`과정에서 아래 error발생 시

     ```
      Conflicting values set for option Signed-By regarding source https://nvidia.github.io/libnvidia-container/stable/ubuntu18.04/amd64/ /: /usr/share/keyrings/nvidia-container-toolkit-keyring.gpg != 
     
     ```

     1. PT 소스 리스트(`sources.list` 또는 `/etc/apt/sources.list.d/` 디렉토리 내의 파일들)에서 NVIDIA 관련 저장소를 추가할 때 `Signed-By` 옵션에 대해 충돌하는 값을 설정했기 때문에 발생

        어떤 파일에 의해 충돌했는지 확인

        ```
        $ grep -l "nvidia.github.io" /etc/apt/sources.list.d/* | grep -vE "/nvidia-container-toolkit.list\$"
        ```

        `/etc/apt/sources.list.d/nvidia-docker.list` 출력 시

     2. 충돌하는 파일 삭제

        ```
        $ sudo rm -rf /etc/apt/sources.list.d/nvidia-docker.list
        ```

   ```
   *** daemon.json (Y/I/N/O/D/Z) [default=N] ? y
   Installing new version of config file /etc/docker/daemon.json ...
   ```

3. Restart the Docker daemon 

   ```
   $ sudo systemctl restart docker
   ```

   

   check : 기본 CUDA container 실행

   ```
   $ docker run -it --rm --gpus all nvidia/cuda:11.4.3-devel-ubuntu20.04  
   ```

   ```
   container(container안에서)# nvidia-smi 
   ```

   

   > cuda와 ubuntu version에 대한tag는 [docker hub-nvidia](https://hub.docker.com/r/nvidia/cuda/tags)에서 검색 후 결정

4. edit daemon

   ```
   $ sudo vi /etc/docker/daemon.json
   ```

   아래처럼 변경

   ```
   {
       "default-runtime": "nvidia",
       "runtimes": {
           "nvidia": {
               "path": "nvidia-container-runtime",
               "runtimeArgs": []
           }
       }
   }
   ```

   

## Uninstall

1. docker container 를 모두 중지하고 삭제한다.

   ```
   $ docker stop $(docker ps -q)
   $ docker rm $(docker ps -a -q)
   ```

2. local 에 저장된 image 를 모두 삭제한다.

   ````
   $ docker rmi $(docker images -q)
   ````

3. check package

   ```
   $ dpkg -l | grep -i docker
   ```

   ```
   ii  docker-buildx-plugin                       0.10.5-1~ubuntu.18.04~bionic                    amd64        Docker Buildx cli plugin.
   ii  docker-ce                                  5:24.0.2-1~ubuntu.18.04~bionic                  amd64        Docker: the open-source application container engine
   ii  docker-ce-cli                              5:24.0.2-1~ubuntu.18.04~bionic                  amd64        Docker CLI: the open-source application container engine
   ii  docker-ce-rootless-extras                  5:24.0.2-1~ubuntu.18.04~bionic                  amd64        Rootless support for Docker.
   ii  docker-compose-plugin                      2.18.1-1~ubuntu.18.04~bionic                    amd64        Docker Compose (V2) plugin for the Docker CLI.
   
   ```
   
   위와 같이 출력된다면 아래 명령어로 delete
   
   
   
   ```
   $ sudo apt-get purge -y docker-engine docker docker.io docker-ce docker-ce-cli docker-ce-rootless-extras 
   $ sudo apt-get autoremove -y --purge docker-engine docker docker.io docker-ce  
   ```

   ```
   $ sudo rm -rf /var/lib/docker /etc/docker
   $ sudo rm /etc/apparmor.d/docker
   $ sudo groupdel docker
   $ sudo rm -rf /var/run/docker.sock
   ```
   
   
   
   
   
   

## linux setting

**계정에 docker 권한 부여**

```
root:~# usermod -a -G docker $USER
```

재부팅 후 확인

```
$ id
```

`997(docker)` 가 포함되어 있다면 권한 부여된 것

**부팅시 자동 실행**(Ubuntu는 자동으로 되어있음)

```
root:~# systemctl enable docker
```

## introduce

### container란?

호스트 OS상에 논리적인 구획(컨테이너)을 만들고, 어플리케이션을 작동시키기 위해 필요한 라이브러리나 어플리케이션 등을 하나로 모아, 마치 별도의 서버인 것처럼 사용할 수 있게 만든 것

> 보통 물리 서버 상에 설치한 호스트 OS의 경우 하나의 OS 상에서 움직이는 여러 어플리케이션은 똑같은 시스템 리소스를 사용한다.
> 
> 이때 작동하는 여러 어플리케이션은 데이터를 저장하는 디렉토리를 공유하고, 서버에 설정된 동일한 IP 주소로 통신을 한다. 그래서 여러 어플리케이션을 사용하고 있는 미들웨어나 라이브러리의 버전이 다른 경우에는 각 어플리케이션이 서로 영향을 받지 않도록 주의해야 함
> 
> 이에 반해 컨테이너 기술을 사용하면 OS나 디렉토리, IP 주소 등과 같은 시스템 자원을 마치 각 어플리케이션이 점유하고 있는 것처럼 보이게 할 수 있다.
> 
> 컨테이너는 virtuar environment와 마찬가지로 어플리케이션을 관련 라이브러리 및 종속항목과 함께 패키지로 묶어 소프트웨어 서비스 구동을 위한 격리 환경을 마련하기 때문에, 컨테이너를 사용하면 개발자와 IT운영팀이 훨씬 작은 단위로 업무를 수행할 수 있으므로 그에 따른 이점이 많다.

![](https://media.vlpt.us/images/dlfehd54/post/6903aa86-b663-4c4a-8228-19402c8a6e5a/docker-containerized-appliction-blue-border_2.png)

doker container는 virtual machine에 비해 가볍고 시작과 중지가 빠르다는 장점이 있다. 

**doker container를 생성할 때 주로 주의해야 할 점**

- 1 컨테이너당 1프로세스
  
  도커 컨테이너는 애플리케이션과 해당 애플리케이션을 실행하기 위한 실행 환경을 패키징함으로써 애플리케이션을 쉽게 실행하기 위한 도구로, 해플리케이션에서 중요한 역할을 한다. 주변의 에코시스템도 이 사상을 바탕으로 만들어진 것이므로 이를 무시하고 도커 컨테이너에 여러 프로세를 시동하도록 만들면 주변 에코시스템과 맞지 않거나 관리가 힘들어진다.

- 변경 불가능한 인프라 이미지로 생성한다.
  
  변경 불가능한 인프라는 '환경을 변경할 떄 오래된 환경은 없애고 새로운 환경을 만든다.', '한번 만들어진 환경은 절대 변경되지 않게 한다.'라는 개념이다.
  
  도커 컨테이너는 버전을 관리할 수 있으므로 컨테이너 이미지 안에 애플리케이션 실행 바이너리나 관련 리소스를 가능한 한 포함시켜 컨테이너 이미지를 변경 불가능한 상태로 만들어야 한다.

- 경량의 도커 이미지로 생성한다.
  
  컨테이너를 실행할 때 노드상에서 사용할 도커 이미지가 없다면 외부에서 이미지를 풀하여 가지고 와야 한다. 그러므로 도커 이미지는 가급적 경량인 상태로 만들어야 한다.

- 실행 계정은 root이외의 사용자로 한다.
  
  컨테이너 내부에서 프로세스를 기동하는 실행 계정 권한을 최소화한다. 특히 root사용자를 사용하면 큰 보안 사고로 이어질 수 있으므로 최대한 사용하지 않도록 한다.

#### container image

여러개의 layer로 구성된 container를 뜻한다.

layer란 하나의 역할을 가진 부품이라고 이해하면 된다.

> train.py 를 실행시키는 application을 하나의 container하고 했을 때
> 
> container에는 
> 
> python이라는 프로그램을 담은 layer와
> 
> train.py라는 source를 담은 layer와
> 
> train.py를 실행시키는 layer가 있다.

container image 안에는 또 layer별로 file이 따로따로 존재한다.

- container image는 readonly이다.

**container image와 container의 차이 **

Docker가 설치된 OS를 **Docker host**라고 하고, Docker Host에는 Docker를 실행하는 Docker demon이 있다.

그리고 container image는 하드디스크에 하나의 file형태로 저장이 되어있다.

**container image**를 실행시키면 메모리에 container image가 할당되는데,  이 때 container image는 하나의 process로 running이 된다. 이 동작되는 container image를 **running중인 container**라고 한다.

또는 container hub에서 run명령어를 통해 application으로써 image를 실행하게 되면 그것 또한 '**running중인 container**' 이라고 한다. 

 container image는 create를 통해 container가 될 때 container name을 가지게 된다.

(image name은 hub에 쓰여있는 그 이름임) 

- container를 통해 작업한 내용은 image에 반영되지 않는다.

[hub.docker.com](https://hub.docker.com/) 에는 수많은 container image가 저장되어있다.

### **Docker란?**

container engine으로써, 여러 container를 관리하는 프로그램

container program을 사용하면 개발자가 만든 그대로 어디서든 실행이 가능하기 때문에 확장/축소가 쉽고 배포에 용이하다.

**linux환경에서 사용**

linux kernel기능을 가지고 사용하기 때문에 linux환경에서 사용한다. 

> linux kernel기능
> 
> - chroot :독립된 공간을 형성한다.
> - namespace : isolate기능을 지원한다.
> - cgroup : 필요한 만큼 HW을 지원한다.

windows에는 kernel기능이 없기 때문에 virtualbox와 같은 Hypervisor를 활성화 후 virtual machine으로 linux를 활용하여 container를 사용한다.

**차이점**

1. 일반 program을 사용할 때
   
   train.py를 실행하려면 OS에 python을 설치 후 실행해야 한다.

2. container program을 사용할 때
   
   train.py를 실행하려면
   
   1. container를 build한다.
   2. python을 container에 설치한다.
   3. train.py을 container에 저장

**Docker의 한계**

서비스가 커지면 커질 수록 관리해야 하는 container의 양이 급격히 증가

kubernates를 사용해서 이러한 한계를 해결한다.

## how to use?

### docker hub

- official images : docker.com이 직접 관리하고 general하게 누구나 쓸 수 있도록 만들어짐
- verified pubilsher : mysql등의 사 기업이 제공하는 container

##### distribution(배포)

docker file을 `docker build` command로 container image로 만들어 하드디스크에 저장했다면,

docker hub에 올리면 된다.

어떻게?

```
$ docker login
$ docker push <image_name>
```

#### repository

docker hub의 나만의 repository를 이용할 수 있다.

공개 repository에 image를 push하면 누구든 접근할 수 있지만, 나만의 private repository는 나만 접근할 수 있다.(하나까지는 무료로 사용 가능)

repository 에 image를 push할 때는 `docker tag` 명령어를 통해 tag를 붙여준 후 push하도록 한다.

1. public repository로 push하는 경우 : tag를 통해 username/image_name 
   
   ```
   $ docker tag hello-world taeuk/hellow-world
   ```

2. private repository로 push하는 경우 : tag를 통해 host name과 port number을 붙여야 한다.
   
   ```
   $ docker tag ubuntu localhost:5000/ubuntu
   ```
   
   ```
   $ docker push localhost:5000/ubuntu
   ```

###### private Registry

사내의 container repository 라고 생각하면 된다. (외부 network가 안되는 공간에 사용하는 repository)

**[Registry](https://hub.docker.com/_/registry)** : `run`을 통해 execution을 하게 되면, cintainer image를 저장하고 관리하는 container (docker hub에서 검색) 즉, private registry를 만들어준다. 

이제 docker hub라는 container저장소 말고도, 내 PC안에 private한 container저장소가 만들어진 것.

예시 : private repository에  image 저장

1. container를 download받아 run해주고
   
   ```
   $ docker run -d -p 5000:5000 --restart always --name registry registry:2
   ```

2. private repository에 저장하고자 하는 image를 pull한다. (예시로 ubuntu라고 하겠음)
   
   ```
   $ docker pull ubuntu
   ```

3. tag를 통해 host name과 port number를 붙여준다.
   
   ```
   $ docker tag ubuntu localhost:5000/ubuntu
   ```
   
4. push 해준다.
   
   ```
   $ docker push localhost:5000/ubuntu
   ```
