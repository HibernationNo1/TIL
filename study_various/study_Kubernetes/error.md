error



### node STATUS NotReady

```
$ kubectl get nodes
```

```
NAME                 STATUS     ROLES                  AGE   VERSION
master.example.com   NotReady   control-plane,master   30s   v1.22.13
```



kubelet 상태 확인

```
$ systemctl status kubelet
```

Active :`activating` 확인



kubelet 에러 로그 확인

```
$ journalctl -xeu kubelet
```





#### no networks found in /etc/cni/net.d

```
Sep 21 10:10:45 master.example.com kubelet[74043]: I0921 10:10:45.253800   74043 cni.go:239] "Unable to update cni config" err="no networks found in /etc/cni/net.d"
Sep 21 10:10:45 master.example.com kubelet[74043]: E0921 10:10:45.879933   74043 kubelet.go:2381] "Container runtime network not ready" networkReady="NetworkReady=false reason:NetworkPluginNotReady message:d>
```

와 같은 에러 발생: 네트쿼트 플러그인이 없다는 의미

`/etc/cni/net.d`에 `10-flannel.conflist` 가 있는지 확인한다. 

없다면 

```
$ vim 10-flannel.conflist
```

```
{
  "name": "cbr0",
  "plugins": [
  {
    "type": "flannel",
    "delegate": {
      "hairpinMode": true,
      "isDefaultGateway": true
      }
  },
  {
    "type": "portmap",
    "capabilities": {
      "portMappings": true
      }
  }
  ]
}
```

추가



#### "Error getting node" err="node \"{hostname}\" not found"

```
Sep 21 10:27:16 master.example.com kubelet[86015]: E0921 10:27:16.222895   86015 kubelet.go:2456] "Error getting node" err="node \"master.example.com\" not found"
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
  
  
  
  
