# Dockerfile

개발한 program과 execution environment을 모두 container로 만든다.

dockerfile은 text file로 Top-Down해석 방식을 사용하며 container image를 create할 수 있는 고유의 지시어(instruction)를 가짐

> FROM
>
> COPY
>
> CMD와 같은 instruction이 존재함

dockerfile을 만든 후 dockerfile build 명령어를 실행해서 container를 build한다.



### grammar

##### FROM

`FROM` : container의 BASE IMAGE(operating invironment)를 정의

dockerfile에서 가장 먼저 나오는 단어

- `AS` : FROM으로 할당한 image에 name을 지어줄 수 있다.



##### MAINTAINER

`MAINTAINER` : name and information of user who create container



##### LABEL

`LABEL` : container image에 information of container을 저장



##### RUN

`RUN` : container build할 때 `FROM`에서 정의한 base image에서 execution할 commands를 할당

> ```
> RUN apt-get updata\
> 	apt-get install tensorflow
> 	# 처럼
> ```



##### COPY

`COPY` : container build시 host file을 container로 copy

```
COPY requirements.txt requirements.txt
# requirements.txt을 requirements.txt라는 이름으로 container 현재 위치에 copy

RUN mkdir /code
COPY inference.py /code
# inference.py을 이름 그대로 ./code의 위치에 copy
```





##### ADD

`ADD` : container build시 host file(tar, url을 포함)을 container로 copy



##### WORKDIR

`WORKDIR` : container build시 commend가 execution될 작업 directory를 설정



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



##### CMD

`CMD` : container 동작 시 auto로 execution할 servise나 script지정

- `RUN`과의 차이점 : `RUN`은 build될때 실행되고, `CMD`는 명령어가 실행될때 동작한다.



##### ENTRYPOINT

`ENTRYPOINT` : `CMD`와 함께 사용하면서 command 지정 시 사용



**예시**

```
$ mkdir build
$ cd build
$ vi dockerfile

FROM python		# train.py가 실행되기 위한 execution environment
COPY train.py
CMD ["python", "/train.py"]		# cmd에서 python train.py 라는 명령어가 실행됨

$ docker build -t train:latest .	# `.` 반드시 표기해야함
									# 현재 location의 directory에 위치한다는 뜻
```

> 현재 위치에서 train:latest라는 name의 container를 만드는 예시



docker hub의 explore 에 보면 잘 만든 container image의  docker file 을 보고 어떻게 만들어졌는지 이해해보자









