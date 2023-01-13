# Docker Registry

docker registry는 Docker image를 저장하고 배포할 수 있는 server측 application이다.

### install, run registry

1. install

   ```
   $ docker pull registry:latest
   ```

   check 

   ```
   $ docker images 
   ```

   ```
   REPOSITORY                    TAG       IMAGE ID       CREATED       SIZE
   registry                      latest    d1fe2eaf6101   2 weeks ago   24.1MB
   ```

2. run

   ```
   $ docker run --name private-docker -dit -t -p 5000:5000 registry
   ```

   - `--name private-docker` : private-docker 이라는 이름으로 run
   
   - `-d` : background로 실행
   
   - `-t`: TTY mode사용 (bash를 사용하려면 설정)
   
   - `-i`: 표준 입력(STDIN)을 활성화하고, container와 연결되어 있지 않더라도 표준입력 유지
   
     > `-d`, `-t`, `-i`를 함께 쓰려면 `-dit`라고 명시
   
   - `-p 5000:5000` : 5000번 port로 사용
   
   - `registry` : run할 docker images이름
   
   check container

   ```
   $ docker ps -a | grep registry
   ```
   
   ```
   CONTAINER ID   IMAGE                                 COMMAND                  CREATED         STATUS         PORTS                                                                                                                                  NAMES
   5050f6b6e425   registry                              "/entrypoint.sh /etc…"   2 minutes ago   Up 2 minutes   0.0.0.0:5000->5000/tcp, :::5000->5000/tcp                                                                                              private-docker
   ```
   
   check port
   
   ```
   $ netstat -anp | grep 5000 | grep LIST
   ```
   
   > 공유기 통해서 들어가는거면 port forwarding필요



> remove
>
> ```
> docker stop CONTAINER ID
> docker rm CONTAINER ID
> ```
>
> 





#### image push to registry

regisitry가 run상태라고 가정

1. create dockerfile 

   ```
   $ touch Dockerfile
   ```

   ```
   FROM ubuntu:18.04
   
   RUN apt-get updatecd
   
   CMD ["echo", "Hellow world"]
   ```

2. build

   ```
   $ docker build -t [IP]:[registry port]/[container name]:[version] [dockerfile]
   ```

   

   1. local의 regisitry에 build할 때

      ```
      $ docker build -t localhost:5000/exam:0.0.1 .
      ```

   2. 외부 divice(ip : 192.168.56.102)의 regisitry에 local의 image를 build할 때

      ```
      $ docker build -t 192.168.56.102:5000/exam:0.0.1 .
      ```

   check 

   ```
   $ docker images
   ```

3. push

   ```
   $ docker push 192.168.56.102:5000/exam:0.0.1
   ```

   > 또는 
   >
   > ```
   > $ docker push localhost:5000/exam:0.0.1
   > ```
   >
   > - 만일 `server gave HTTP response to HTTPS client ` 가 출력되면
   >
   >   ```
   >   $ sudo systemctl deamon-reload
   >   $ sudo systemctl restart docker
   >   $ docker run --name private-docker -d -p 5000:5000 registry
   >   $ docker push 192.168.56.102:5000/exam:0.0.1
   >   ```

   check

   ```
   $ curl -X GET http://localhost:5000/v2/_catalog
   ```

   >localhost:5000 이라는 registry에 어떤 image가 저장되어 있는지 list를 출력

   ```
   $ curl -X GET http://localhost:5000/v2/exam/tags/list
   ```

   > `exam`이라는 image name에 어떤 tag가 저장되어 있는지 list출력

#### image pull(run) by load  from registry

```
$ docker run [regisitry IP]:[port]/[container name]:[version]
```



### command

image나 tags를 확인하려면 Docker Registry가 지원하는 REST API를 이용해야 한다.

[공식](https://docs.docker.com/registry/spec/api/)



#### images

해당 registry안에 있는 images의 이름 확인

```
$ curl http://localhost:5000/v2/_catalog
```

```
{"repositories":["docker","train"]}
```

`docker`, `train` 이라는 두 개의 image가 있는것을 확인할 수 있다.



#### tags

해당 registry안에 있는 images의 tag를 확인할 수 있다.

```
$ curl http://localhost:5000/v2/image_name/tags/list
```

```
{"name":"train","tags":["0.1"]}
```

> `train`이라는 image가 `0.1`의 tag 1개를 가진 것을 확인할 수 있다.



### uninstall

1. delete container

   ```
   $ docker run --name private-docker -dit -t -p 5000:5000 registry
   ```

   ```
   docker: Error response from daemon: Conflict. The container name "/private-docker" is already in use by container "476618bf9a89cc94a286b1f20bb86409197dfc76955bac3caf4145fce082b2bb". You have to remove (or rename) that container to be able to reuse that name.
   ```

   ```
   $ docker rm 476618bf9a89cc94a286b1f20bb86409197dfc76955bac3caf4145fce082b2bb
   ```

   

2. delete image

   ```
   $ docker images
   ```

   ```
   registry                                                                 latest                                            81c944c2288b   8 weeks ago     24.1MB
   ```

   ```
   docker rmi -f 81c944c2288b
   ```

   



## Docker Hub

public 또는 priebit 한 docker image를 push하고 pull하는데 사용



1. login

   ```
   $ docker login
   ```

   > username, password 입력

2. tag

   ```
   $ docker tag my-image:v1.0.0 hibernation/my-image:v1.0.0
   ```

   > docker tag <image_name>:<tag_name> <user_name>/<image_name>:<tag> 

3. push

   ```
   $ docker push hibernation/my-image:v1.0.0
   ```

   > docker push <user_name>/<image_name>:<tag> 