# Docker command

id에 docker 권한이 부여되어 있다고 가정

- `docker version` : version확인

- `docker search` : docker hub에서  container image를 검색

  ```
  $ docker search nginx
  ```

  docker hub에서 nginx라는 container image를 찾는다.

  

- `docker pull` :  docker hub에서  container image를 가져온다.

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

  총 5개의 layer로 구성된 image를 다운받음을 알 수 있다.



- `docker images` : 하드웨어에 저장된 container image 확인

  ```
  $ docker images
  ```

  ```
  # cd /var/lib/docker/overlay2
  ```

  container image가 layer형식으로 저장되는 forder

  

- `docker run` : container image를 실행한다.

  ```
  $ docker run (<옵션>) <이미지 식별자> (<명령어>) (<인자>)
  ```

  ```
  $ docker run -d --name web  -p80:80 nginx:latest
  ```

  `--name web` : web이라는 이름으로 container실행`

  `-d` : background mode로 실행

  `-p80:80` : 80번 port로 실행

  

- `docker ps` : 현재 실행되고 있는 container 확인

  ```
  $ docker ps
  ```

  ```
  CONTAINER ID   IMAGE          COMMAND                  CREATED          STATUS          PORTS                               NAMES
  4fa8d4276c5e   nginx:latest   "/docker-entrypoint.…"   17 minutes ago   Up 17 minutes   0.0.0.0:80->80/tcp, :::80->80/tcp   web
  
  ```

  `web` 이라는 이름으로 container가 실행되고 있음을 알 수 있다.

  

  위에서 80번 port로 실행하고 있기 때문에

  ```
  $ curl localhost:80
  ```

  접속해보면 실행중인 contrainer(nginx의 web page)를 실행할 수 있다.

  다른 프로그램과 완전이 독립된 환경에서 실행됨



- `docker container` : container 과 images를 확인

  ```
  $ docker container ls -a
  ```

  

- `docker stop` : 실행중인 docker를 멈춘다.

  ```
  $ docker stop web
  ```

  `web` 이라는 이름으로 실행중인 container가 멈춤



- `docker rm` : container를 삭제한다.

  ```
  $ docker rm web
  ```

  `web` 이라는 이름의 container가 삭제됨

  container image가 삭제된게 아님!

- `docker rmi` : container image를 삭제한다.

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



- `docker build` : dockerfile을 build하는 command

  ```
  $ docker build -t hellojs:latest .
  ```

  `-t` :

  `hellojs:latest` : hellojs:latest라는 name의 container

  `.` : 현재 location 



- `docker login` : docker hub에 login

  ```
  $ docker login
  ```



- `docker push` : contrainer image를 docker hob에 push (distribution)

  ```
  $ docker push <image_name>
  ```

  

