# Docker Registry

docker registry는 Docker image를 저장하고 배포할 수 있는 server측 application이다.

> ```
> $ docker run -d -p 5000:5000 --name registry registry
> ```
>
> registry application을 담은 image run



#### image push to registry

1. create dockerfile and build

   ```
   $ touch Dockerfile
   ```

   ```
   FROM ubuntu:18.04
   
   RUN apt-get updatecd
   
   CMD ["echo", "Hellow world"]
   ```

   ```
   $ docker build -t test:v1.0.0 .
   ```

2. run registry

   ```
   $ docker run -d -p 5000:5000 --name registry registry
   ```

   > registry image가 registry라는 이름으로 생성되었으며, local host 5000으로 registry와 통신 가능 

3. tag to image

   ```
   $ docker tag test:v1.0.0 localhost:5000/test:v1.0.0
   ```

   > test로 `localhost:5000`를 달아준다

4. push

   ```
   $ docker push localhost:5000/test:v1.0.0
   ```

5. check

   ```
   $ curl -X GET http://localhost:5000/v2/_catalog
   ```

   > `localhost:5000 이라는 registry에 어떤 image가 저장되어 있는지 list를 출력`
   >
   > ```
   > {"repositories":["test"]}
   > ```
   >
   > 

   ```
   $ curl -X GET http://localhost:5000/v2/test/tags/list
   ```

   > test라는 image name에 어떤 tag가 저장되어 있는지 list출력
   >
   > ```
   > {"name":"test","tags":["v1.0.0"]}
   > ```



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