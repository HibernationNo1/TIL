# Docker command

id에 docker 권한이 부여되어 있다고 가정

##### version

`docker version` : version확인



##### info

`docker info` : docker가 저장된 path등을 확인할 수 있다.



##### search

`docker search` : docker hub에서  container image를 검색

```
$ docker search nginx
```

docker hub에서 nginx라는 container image를 찾는다.





##### pull

`docker pull` :  docker hub에서  container image를 가져온다.

```
$ docker pull nginx:latest
```

```
07aded7c29c6: Pull complete
bbe0b7acc89c: Pull complete
44ac32b0bba8: Pull complete
91d6e3e593db: Pull complete
8700267f2376: Pull complete
4ce73aa6e9b0: Pull complete
```

총 5개의 layer로 구성된 image(nginx의 마지막 version)를 다운받음을 알 수 있다.



##### images

`docker images` : 하드웨어에 저장된 container image 확인

```
$ docker images
```

```
# cd /var/lib/docker/overlay2
```

container image가 layer형식으로 저장되는 forder



##### inspect 

`docker inspect` : 하드웨어에 저장된 container image를 상세보기

```
$ docker inspect _name
```

_name 을 container name을 사용하거나 image name을 사용하는지에 따라서 출력이 달라진다.



##### create

`docker create` : 하드웨어에 저장된 container image를 container로 만들어준다.

```
$ docker pull python
```

python의 latest version의 image를 가져왔다고 하면

```
$ docker create --name container_name python
```

해당 image를 container_name이라는 이름의 container로 만들어준다.

아직 runing중이진 않다.



##### start

`docker start` : `docker create` 로 인해 하드웨어상에 running중이지 않은 container를 running상태로 실행한다.(application으로써 실행)

```
$ docker start container_name
```



##### image ls

```
$ docker image ls
```

local에 존재하는 image에 대한 목록과 information을 알 수 있다.





#### run

`docker run` : container image를 docker hub로부터 가져다가 application으로써 실행한다.

(pull + create + start 동작)

```
$ docker run (<옵션>) <이미지 식별자> (<명령어>) (<인자>)
```

```
$ docker run -d --name web  -p 80:80 nginx:latest
```

`--name web` : web이라는 이름으로 container실행`

`-d` : background mode로 실행

`-p80:80` : 80번 port로 실행



docker hub에 잇는 image를 사용하고자 한다면 해당 page에서 알려주는 run명령어를 찾아서 실행

> 예시 : Registry 사용
>
> ```
> $ docker run -d -p 5000:5000 --restart always --name registry registry:2
> ```



- `--shm-size` : 메모리 부족을 방지하기 위해 container에 메모리 공유

  > `--shm-size = 8G`



**volume mount option**

- `-v` : 원하는 경로의 directory를 container의 특정 경로에 공유

  실수로 `docker -rm` 을 사용해 중요한 data가 담겨있는 container를 삭제했을 때를 대비해 공유된 path에도 data를 저장하는 option

  > 공유하고자 하는 path : `C:\docker_result`
  >
  > 공유되는 path : `/home/workspace`라고 할 때
  >
  > `-v C:\docker_result:/home/workspace` : `C:\docker_result`  에 저장된 data는 container의 ` /home/workspace` 에도 저장된다.
  >
  > 또는 
  >
  > 공유하고자 하는 path : `/home/workspace`
  >
  > 공유되는 path : `C:\docker_result`라고 할 때
  >
  > `-v /home/workspace:C:\docker_result` : container의  `/home/workspace`  에 저장된 data는 host의 ` C:\docker_result` 에도 저장된다.

  - `:ro` read only 

    보안 issue가 있는 경우를 대비해 read only file만 저장되도록 하는 option

  예시

  ```
  $ docker run --shm-size=8G -v C:\docker_result:/home/workspace:ro python
  ```



**resource option**

- `-m` : container가 사용할 최대 memory양을 지정

  ```
  $ docker run -d -m 200m python:latest	# 200MB
  ```

- `-oom-kill-disable` : OOM Killer가 process kill을 하지 못하도록 보호 

- `--cpus` : container에 할당할 CPU core수를 지정

  ```
  $ docker run -d --cpus="1.5" python # container가 최대 1.5개의 CPU power사용
  ```

  



##### ps

`docker ps` : 현재 container 들의 상태를 확인

running중인, stop되어있는 container를 확인할 수 있다.

```
$ docker ps
```

```
CONTAINER ID   IMAGE          COMMAND                  CREATED          STATUS          PORTS                               NAMES
4fa8d4276c5e   nginx:latest   "/docker-entrypoint.…"   17 minutes ago   Up 17 minutes   0.0.0.0:80->80/tcp, :::80->80/tcp   web

```

`web` 이라는 이름으로 container가 실행되고 있음을 알 수 있다.



```
$ docker ps -a
```





위에서 80번 port로 실행하고 있기 때문에

```
$ curl localhost:80
```

접속해보면 실행중인 contrainer(nginx의 web page)를 실행할 수 있다.

다른 프로그램과 완전이 독립된 환경에서 실행됨



##### top

`docker top` : 특정 container에서 어떤 것이 동작중인지를 출력

```
$ docker top container_name
```



##### logs

`docker logs` : 특정 container의 log확인

```
$ docker log container_name
```



##### exec

`docker exec`  : running중인 container에 추가 명령어 실행을 할 수 있도록 한다.

```
$ docker exec container_name /bin/bash
```

> bash를 추가 실행하여 사용자가 접근할 수 있도록 한다.





##### container

`docker container` : container 과 images를 확인

```
$ docker container ls -a
```



##### stop

`docker stop` : running중인 container를 멈춘다.

```
$ docker stop web
```

`web` 이라는 이름으로 실행중인 container가 멈춤



##### rm, rmi

`docker rm` : container를 삭제한다.

```
$ docker rm container_name
```

`container_name` 이라는 이름의 container가 삭제됨

container image가 삭제된게 아님!



`docker rmi` : container image를 삭제한다.

```
$ docker rmi nginx
```

> Error response from daemon: conflict: unable to remove repository reference "nginx" (must force) - container 78b5b2ef16e9 is using its referenced image f8f4ffc8092c
>
> 위 문구처럼 78b5b2ef16e9가 해당 image를 참조하고 있어서 삭제가 안된다면
>
> ```
> $ docker container ls -a		# 으로 확인 후
> $ docker rm 78b5b2ef16e9		# container_id를 가리키며 참조하고 있는 image를 삭제한다.
> $ docker rmi <image_id> 		# image_id로도 삭제 가능
> 
> $ docker rmi nginx				# 이후 다시 삭제
> ```



#####  build

`docker build` : dockerfile을 build하는 command

```
$ docker build -t hellojs:latest .
```

`-t` :

`hellojs:latest` : hellojs:latest라는 name의 container

`.` : 현재 location 



##### login

`docker login` : docker hub에 login

```
$ docker login


Username: hibernation4958
Password:  # 입력하면
WARNING : ~~~
Login Succeeded
```



##### push

`docker push` : contrainer image를 docker hob에 push (distribution)

```
$ docker push <tag>/<image_name>
```



##### tag

`docker tag` : image에 나만의 tag를 붙여주는 command

```
$ docker images		# 어떤 image가 있는지 check
$ docker tag hello-world taeuk/hellow-world		# hello-world 라는 image가 있고, 여기세 taeuk이라는 tag를 달아준다.
$ docker images		# taeuk/hellow-world 라는  image가 추가된걸 확인할 수 있음
```

docker tag로 인해 tag가 붙여진 image는 docker hub의 내 repository에 push할 수 있다.

```
$ docker push taeuk/hellow-world
```



 

#### monitoring

##### events

`docker events` : docker 가 동작하면서 내부적으로 발생하는 event를 수집해서 출력

```
$ docker events -f container=<container_name>
```



**cAdvisor** 

github.com/google/cadivisor

docker의 resource에 관한 information을 monitoring할 수 있다.
