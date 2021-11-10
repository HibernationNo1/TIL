# Docker 입문

## install

#### WSL

docker를 설치하기 전 WSL설치

> windows 사용시 설치 



#### DOCKER

https://docs.docker.com/

- Docker Desktop for window 

  실제 Docker server를 운영하기 보다는 Docker appilcation 개발자들이 사용하는 platform

- ['Docker for linux'](https://docs.docker.com/engine/install/ubuntu/)

  실제 Docker server를 운영



**Download 후 직접설치**

외부 network가 불가능할 때 또는 windows



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



**Uninstall old versions**

```
$ sudo apt-get remove docker docker-engine docker.io containerd runc
```





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

  



### linux setting

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

### **container란?**

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

  





#### **container image**

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

1.  container를 download받아 run해주고

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

   port number : 위에서 5000을 사용했다고 기재되어있음

4. push 해준다.

   ```
   $ docker push localhost:5000/ubuntu
   ```

   

