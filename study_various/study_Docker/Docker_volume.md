# Docker volume



### create volume

1. create

   ```
   $ docker volume create test-vol
   ```

2. confirm

   ```
   $ docker volume ls
   ```

   ```
   DRIVER    VOLUME NAME
   local     test-vol
   ```

3. check mount point

   ```
   $ docker volume inspect test-vol
   ```

   ```
   [
       {
           "CreatedAt": "2022-11-17T11:49:50+09:00",
           "Driver": "local",
           "Labels": {},
           "Mountpoint": "/var/lib/docker/volumes/test-vol/_data",
           "Name": "test-vol",
           "Options": {},
           "Scope": "local"
       }
   ]
   ```

   

### apply

#### Dockerfile

pytorch image에서 test

```
ARG PYTORCH="1.11.0"
ARG CUDA="11.3"
ARG CUDNN="8"  

FROM pytorch/pytorch:${PYTORCH}-cuda${CUDA}-cudnn${CUDNN}-devel	


ENV TORCH_CUDA_ARCH_LIST="7.5"
ENV TORCH_NVCC_FLAGS="-Xfatbin -compress-all"
ENV CMAKE_PREFIX_PATH="$(dirname $(which conda))/../"	
```



```
docker build . -t hibernation4958/volume_test:0.1
```



#### docker run

1. container에 접속

   ```
   docker run -v $(pwd):/test-vol -it hibernation4958/volume_test:0.1
   ```

   > - `-v` option을 통해 volume사용
   >
   > - `$(pwd):/test-vol` 현재 host위치와 container안의 `test-vol` dir을mount

2. `test-vol` 이름의 dir이 있는것을 확인

   ```
   root@17c754212a85:/workspace# cd ..
   root@17c754212a85:/# ls
   ```

   ```
   NGC-DL-CONTAINER-LICENSE  bin  boot  dev  etc  home  lib  lib64  media  mnt  opt  proc  root  run  sbin  srv  sys  test-vol  tmp  usr  var  workspace
   ```

3. confirm mount

   ```
   root@17c754212a85:/# cd test-vol/
   root@17c754212a85:/test-vol# ls
   ```

   host에서 `docker run` 을 실행한 path의 모든 file이 mount됨을 확인할 수 있다.

   여기서 code의 수정이 이루어지면 바로 참조되어 적용된다.

