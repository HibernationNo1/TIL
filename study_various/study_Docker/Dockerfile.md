# Dockerfile

docker image를 만드는 file.

특정 execution environment을 packaging한다.









### How to create Image?

#### 1. create Dockerfile

```
$ touch Dockerfile
```

> 이름 반드시 Dockerfile 이여야 함





1. write base image

2. write command for download some file

3. write command to excute when start contianer



docker hub의 explore 에 보면 잘 만든 container image의  docker file 을 보고 어떻게 만들어졌는지 이해해보자



#### 2. bulid image

**build**

```
$ docker build ./
```

> 해당 dir(build)내에 dockerfile이라는 file을 맞아서 docker client에 전달



- `-t`

  build 에 성공하면 image ID를 출력한다.  (8723458cf6 처럼 복잡함)

  해당 image를 통해 container를 running한다면

  ```
  $ docker run -it 8723458cf6
  ```

  이 때 복잡한 ID대신 나만의 알기 쉬운 name을 붙여주고자 한다면

  `-t` option을 추가한다.

  ```
  -t {본인name/ID}/{project_name}:{version}
  ```

  

  ```
  $ docker build -t hibernation/segmentation:latest ./
  ```

  ```
  $ docker run -it hibernation/segmentation
  ```





## grammar

##### FROM

`FROM` : container의 BASE IMAGE(operating invironment)를 정의

dockerfile에서 가장 먼저 나오는 단어

- `AS` : FROM으로 할당한 image에 name을 지어줄 수 있다.



- python의 slim, alpine, windowsservercore의 차이점

  - `name:version-buster`  , `name:version-stretch ` 

    가장 기본이 되는 이미지로 보통 사람들이 뭘 사용해야하는지 잘 모를 때 해당 이미지를 사용한다. 해당 이미지는 배포 뿐 아니라 base 이미지로 사용되기 위해 설계되었다.

    Debian 계열 이미지를 베이스로 배포되었으며, 이미지가 어떤 릴리즈를 기반으로 배포되었는지를 알 수 있는 척도가 된다. 

  - `name:version-slim`

    이 이미지는 파이썬을 실행하는데 필요한 최소한의 패지키만 설치되어있다. 순수하게 파이썬만 실행할 수 있는 이미지를 말한다. 그렇기 때문에 배포 환경에 용량제한이 심하거나 순수하게 파이썬만 실행하는 환경이 아니라면 사용하지 않는 것이 좋다.

  - `name:version-alpine`

    해당 이미지는 [alpine linux](https://alpinelinux.org/)를 기반으로 제작된 이미지인데 이 alpine 은 os 자체 용량이 매우 작기로 유명하다. 그래서 alpine 은 minimalize의 끝판왕으로 평가받는다. 한가지 주의해야할 점은 alpine은 glibc 가 아니라 [musl libc](https://musl.libc.org/) 를 사용하기 때문에 가끔 C라이브러리 의존성에 이슈가 있을 수 있다는 단점이 있다.

  - `name:version-windowsservercore`

    windows server 이미지를 기반으로 배포되었다. 



##### MAINTAINER

`MAINTAINER` : name and information of user who create container



##### LABEL

`LABEL` : container image에 information of container을 저장



##### RUN

`RUN` : container build할 때 `FROM`에서 정의한 base image에서 execution할 commands를 할당

```
RUN pip install torch
	pip install -r requirements.txt
```





##### CMD

`CMD` : container 동작 시 auto로 execution할 servise나 script지정

- `RUN`과의 차이점 : `RUN`은 build될때 실행되고, `CMD`는 명령어가 실행될때 동작한다.

- `CMD`가 존재할 경우 가장 마지막 `CMD`만 실행 (하나의 CMD만 실행)

```
CMD python main.py

# 또는 
CMD ["echo", "Hellow world"]
```





##### COPY

`COPY` : container build시 host file을 container로 copy

```
COPY tmp_1/requirements.txt tmp_2/requirements.txt
# tmp_1/requirements.txt을 tmp_2에 requirements.txt라는 이름으로 container copy

RUN mkdir /code
COPY inference.py ./code
# inference.py을 이름 그대로 ./code의 위치에 copy
```



```
COPY ./ ./		# 현재 위치의 모든 파일을 copy
```





##### ADD

`ADD` : container build시 host file(tar, url을 포함)을 container로 copy



##### WORKDIR

`WORKDIR` : container build시 commend가 execution될 작업 directory를 설정

> RUN, CMD, ADD, COPY등이 이루어질 기본 디렉토리를 설정
>
> 해당 dir이 없다면 create

```
WORKDIR /usr/src/app
```

왜 정의하는가? 

container를 처음 create하게 되면 파일 스냅샷으로 인해 `home`, `bin`, `dev` 등과 같은 기본 dir이 전부 들어있게 된다. 그리고 WORKDIR의 정의 없이 COPY를 하게 되면 바로 이 최상단의 dir위치에 복사되게 된다.

이렇게 되면 원래 image에 있던 file과 name이 겹치는 경우에는 덮어씌우기가 발생할 수 있다.

그래서 모든 app을 위한 source들은 WORK dir를 따로 정의해서 저장한다.

WORKDIR를 정의 후

```
$ docker run -it container_name sh
# ls
```

를 입력하면 딱 COPY로 인해 copy된 file들만 있는 것을 볼 수 있다.

> ```
> COPY ./ ./
> ```
>
> 이여도 마찬가지.



##### **ENV**

`ENV` : environment variable을 지정



##### USER

`USER` : commend 및 container를 excution시 apply할 user 설정



##### VOLUME

`VOLUME` : container가 execution할 때 file or directory를 container의 directory로 mount

```
# dockerfile
VOLUMS ["container_directory_1", "container_directory_2"]
```

Dockerfile 에서 위와 같이 생성한 VOLUMS은 호스트OS의 /var/lib/docker/volumes에 생성되며, Docker 에서 자동 생성한 hash값으로 directory가 생긴다.

깔끔하게 data를 받고, 주려면 이후  `$ docker run` 을 실행할 때 `-v` 옵션으로 다시 mount해준다. 





##### EXPOSE

`EXPOSE` : container 동작 시 외부에서 using할 port 지정

```
EXPOSE <port> # 또는
EXPOSE <port>/<protocol>
```

```
EXPOSE 8080
```





##### ENTRYPOINT

`ENTRYPOINT` : `CMD`와 함께 사용하면서 command 지정 시 사용







### Multi Stage

docker multi stage build는 여러 container image를 사용하여 처리하고 결과물만 실행용 container image에 copy하는 구조다. 





## TIP

- source에 변경이 있는 경우

  source code에 변경점이 있을 때

  바뀐 code를 포함하여 다시 image를 빌드 후 container를 실행하면 너무 복잡하고 귀찮다.

  이런 경우 변경된 source의 변경된 부분을 바로 반영해주면 된다.

  이는 `-v` 옵션을 통해서 가능하다.

  > container가 실행될 때 docker container에서 host의 source code를 참조한다.(copy와는 다른 방식)

  ```
  $ docker run -v $(pwd):/usr/src/app hibernation/segmentation_inference
  ```

  > container의` /usr/src/app` 라는 위치에서 현재 명령어를 입력한 user의 위치에 있는 files를 mount한다.
  >
  > `hibernation/segmentation_inference` : container name
  >
  > 위 명령어는 변경점이 있는 source code가 위치한 곳에서 실행해야 한다.





## 예시

```
$ touch Dockerfile
```



```
FROM ubuntu:18.04

RUN apt-get update

CMD ["echo", "Hellow world"]
```



```
$ docker build -t test:v1.0.0 .
```



```
$ docker run test:v1.0.0
```



**결과**

`echo` 명령으로 인한 출력

```
Hellow world
```

