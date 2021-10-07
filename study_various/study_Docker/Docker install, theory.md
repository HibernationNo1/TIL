# Docker 입문

## install

https://docs.docker.com/

- Docker Desktop for window 

  실제 Docker server를 운영하기 보다는 Docker appilcation 개발자들이 사용하는 platform

- ['Docker for linux'](https://docs.docker.com/engine/install/ubuntu/)

  실제 Docker server를 운영



**Download 후 직접설치**

외부 network가 불가능할 때



#### Repository를 이용해서 설치

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



### setting

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



#### 

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



**container image와 contrainer의 차이 **

Docker가 설치된 OS를 Docker host하고 하고, Docker Host에는 Docker를 실행하는 Dockerd가 있다.

그리고 container image는 하드디스크에 하나의 file형태로 저장이 되어있다.

container image를 실행시키면 메모리에 container image가 할당되는데,  이 때 container image는 하나의 process로 running이 된다. 이 동작되는 container image를 **contrainer**라고 한다.



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



#### distribution(배포)

docker file을 `docker build` command로 container image로 만들어 하드디스크에 저장했다면,

docker hub에 올리면 된다.

어떻게?

```
$ docker login
$ docker push <image_name>
```

