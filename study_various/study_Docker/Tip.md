# Tip



## Shared Memory



```
$ docker build train --no-cache -t localhost:5000/exam:0.1
```

```
$ docker run --rm -it --name exam_1 localhost:5000/exam:0.1
```

- `--rm `: container가 종료될 때 container와 관련된 resource까지 제거된다.

  container를 일회성으로 실행할 때 주로 쓰인다.

- `--name` : 실행할 container의 별칭 설정



ShmSize 확인

```
$ docker inspect exam_1 | grep -i shm
```

```
"ShmSize": 67108864,
```



ShmSize 확인

```
$ docker run --rm -it --name exam_2 --shm-size=2gb localhost:5000/train:0.1
```

```
$ docker inspect exam_2 | grep -i shm
```

```
"ShmSize": 2147483648,
```



### docker data directory

기본 경로: `/var/lib/docker`

이 경로 하위에 컨테이너의 물리적 이미지를 저장하고, 또 컨테이너가 구동되었을 때 이미지 레이어 외의 컨테이너 레이어 정보를 저장하게 된다

docker를 자주 사용하다 보면 해당 path에 많은 양의 data가 저장되고, 용량을 차지하게 된다.

- 변경

  1. data 이동

     ```
     $ sudo systemctl stop docker
     ```

     ```
     $ sudo mv /var/lib/docker {변경하고자 하는 dir path}/docker
     ```

  2. docker 설정 변경

     1. deamon변경

        ```
        $ sudo vi /etc/docker/daemon.json
        ```

        ```
        {
          "data-root": "{변경하고자 하는 dir path}/docker"
        }
        ```

        위 내용 추가 후 저장

     2. ExecStart변경
     
        ```
        $ /usr/lib/systemd/system/docker.service
        ```

        ```
        ExecStart=/usr/bin/dockerd --data-root= {변경하고자 하는 dir path}/docker -H fd:// --containerd=/run/containerd/container
        ```

     3. reload deamon
     
        ```
        $ systemctl daemon-reload
        ```

     4. 확인
     
        ```
        $ sudo systemctl start docker
        $ sudo docker info | grep "Docker Root Dir"
        ```
     
        
     
     

  

  





### disk-pressure

volume에 너무 많은 용량을 할당하거나 용량이 큰 docker image를 너무 많이 build할 경우

disk-pressure issue로 인해 pod들이 제 기능을 못하게 된다.

이런 경우 `$ du -h` 명령어를 활용해서 불필요한 파일을 삭제하자.



- 직접 확인하며 삭제

  1. `/var/lib/docker/overlay2`의 용량 확인

     docker image를 build하면 해당 위치에 build한 docker에 대한 dir이 생성된다.

     이 dir은 `docker rmi -f <image_ID>`를 해도 남아있기 때문에, 용량을 잡아먹게된다.

     build한 docker image를 사용하지 않아 삭제를 하게 된다면 해당 path의 dir로 삭제해야 한다.

     ```
     # cd /var/lib/docker/overlay2
     # du -h --max-depth=1 .
     ```

     - `du -h --max-depth=1 .` : 해당 명령을 실행하는 path의 하위 첫 번째dir들의 용량을 출력한다.

       > `# du -h --max-depth=1 | awk '$1~/G/ {print}'` : G 이상의 용량만 출력

  2. `/var/lib/docker/volumes`의 용량 확인

     docker image를 local에 위치한 registry에 push한 경우 또는 pvc, volume등을 정의한 경우 `/var/lib/docker/volumes` path에 해당 volume에 들어간 images에 대한 layer를 저장하게 된다.

     registry같은 경우 push한 image가 많을수록 layer가 많아지고 용량 또한 쌓이기 때문에, registry를 삭제 시 해당 path에서 해당 dir를 삭제하자.

     ````
     # /var/lib/docker/volumes
     # du -h --max-depth=1 | awk '$1~/G/ {print}'
     ````

     각 dir마다 어떤 이름의 image가 push됐는지 확인

     ```
     # /var/lib/docker/volumes/<dir_name>/_data/docker/registry/v2/repositories
     # ls
     ```

     > push한 image의 이름을 가진 dir들이 존재한다.

     ```
     # /var/lib/docker/volumes/<dir_name>/_data/docker/registry/v2/repositories/<image_name>/_manifests/tags
     # ls
     ```

     > push한 tag의 이름을 가진 dir들이 존재한다.

- 명령어로 한번에 삭제

  ```
  $ sudo docker system prune -a
  ```

  - `prune`: 사용되지 않는 Docker 리소스를 제거한다. 컨테이너, 네트워크, 볼륨 및 이미지와 같은 Docker 리소스를 정리하는데 사용된다.

  - `-a` : 사용되지 않는 이미지뿐만 아니라, 현재 사용되고 있지 않은 모든 이미지를 제한다. 이는 빌드 캐시를 비롯한 모든 관련 리소스를 제거하므로 시스템에서 많은 공간을 확보할 수 있다.

  이후 안쓰는 pod삭제

  ```
  kubectl get pods --field-selector=status.phase=Failed --all-namespaces -o json | kubectl delete -f -
  ```

  

  
