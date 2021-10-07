# Dockerfile

개발한 program과 execution environment을 모두 container로 만든다.

dockerfile은 text file로 Top-Down핵석 방식을 사용하며 container image를 create할 수 있는 고유의 지시어(instruction)를 가짐

> FROM
>
> COPY
>
> CMD와 같은 instruction이 존재함

dockerfile을 만든 후 dockerfile build 명령어를 실행해서 container를 build한다.



### grammar

- `#` : comment

- `FROM` : container의 BASE IMAGE(operating invironment)를 정의

  dockerfile에서 가장 먼저 나오는 단어

- `MAINTAINER` : name and information of user who create container

- `LABEL` : container image에 information of container을 저장

- `RUN` : container build할 때 `FROM`에서 정의한 base image에서 execution할 commands를 할당

  > ```
  > RUN apt-get updata\
  > 	apt-get install tensorflow
  > 	# 처럼
  > ```

- `COPY` : container build시 host file을 container로 copy

- `ADD` : container build시 host file(tar, url을 포함)을 container로 copy

- `WORKDIR` : container build시 commend가 execution될 작업 directory를 설정

- `ENV` : environment variable을 지정

- `USER` : commend 및 container를 excution시 apply할 user 설정

- `VOLUME` : container가 execution할 때 file or directory를 container의 directory로 mount

- `EXPOSE` : container 동작 시 외부에서 using할 port 지정

- `CMD` : container 동작 시 auto로 execution할 servise나 script지정

- `ENTRYPOINT` : `CMD`와 함께 사용하면서 command 지정 시 사용



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



#### write docker file

Docker Hub에서  python검색 후 원하는 version선택

```
$ vi dockerfile
```

```
# 
#		comment 표현
#

FROM python
COPY train.py
CMD 
```



file 확인

```
$ cat dockerfile
```



build

```
$ docker build -t model_train .
```

