# cluster 구축



- docker desktop for windows 와 kind사용 (windows)
- kubeadm 사용 (linux)



### kubeadm

```
$ kubectl version
$ kubeadm version
$ docker version
```

> 설치유무 확인





```
$ sudo sysctl net.bridge.bridge-nf-call-iptables=1
```

위 명령어는 master node와 worker node 공통으로 설치해야 하는 영역



- swap 끄기

  ```
  $ swapon -s 
  ```

  > 꺼지면 출력이 없어야 함

  

  1. 일시적인 끄기

     ```
     $ sudo swapoff -a
     ```

  2. 부팅시에도 자동으로 끄기

     ```
     $ sudo vi /etc/fstab
     ```

     입력 후 

     ```
     # /dev/mapper/centos-swap swap swap defaults 0 0
     ```

     위 줄을 추석처리 

     > 없으면



#### master node

```
$ sudo kubeadm init --pod-network-cidr=192.168.0.0/16
```

> `192.168.0.0/16`이 현재 사용하고 있는지 확인. 사용중이면 `172.16.0.0/16`으로 변경 
>
> (http://192.168.0.0 을 쳐서 사용하는지 확인)



- ```
  [WARNING IsDockerSystemdCheck]: detected "cgroupfs" as the Docker cgroup driver. The recommended driver is "systemd". Please follow the guide at https://kubernetes.io/docs/setup/cri/
  ```

  해결방법

  First Permission

  ```
  $ sudo chown $USER:docker /etc/docker
  ```

  Setup daemon

  ```
  $ sudo cat > /etc/docker/daemon.json <<EOF
  {
    "exec-opts": ["native.cgroupdriver=systemd"],
    "log-driver": "json-file",
    "log-opts": {
      "max-size": "100m"
    },
    "storage-driver": "overlay2"
  }
  EOF
  ```

  ```
  $ sudo mkdir -p /etc/systemd/system/docker.service.d
  ```

  Restart docker

  ```
  $ sudo systemctl daemon-reload
  $ sudo systemctl restart docker
  ```

  



```
Your Kubernetes control-plane has initialized successfully!
```

뜨면 

```
kubeadm join 192.168.0.85:6443 --token ea0x7r.o4vlp17enyd946tw \
    --discovery-token-ca-cert-hash sha256:176be416bd105bad5323257d247ca8c84a6bdbdac93c20ed25edaa688031a081 
```

도 이어서 뜰 거임

이 것이 master node에 조인 할 수 있는 토큰값을 포함한 kubeadm명령어.

이 명령어를 워커 노드에 그대로 복사하여 실행시키면 워커 노드가 정상적으로 마스터 노드에 join된다.

> ```
> $ sudo kubeadm join 192.168.0.85:6443 --token ea0x7r.o4vlp17enyd946tw \
>     --discovery-token-ca-cert-hash sha256:176be416bd105bad5323257d247ca8c84a6bdbdac93c20ed25edaa688031a081 
> ```



- master node 처음 만들때만 이어서 수행

  ```
  $ mkdir -p $HOME/.kube
  $ sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
  $ sudo chown $(id -u):$(id -g) $HOME/.kube/config
  ```

  enable master node scheduling

  ```
  $ kubectl taint nodes --all node-role.kubernetes.io/master-
  $ kubectl apply -f https://docs.projectcalico.org/v3.11/manifests/calico.yaml
  ```



정상적으로 cluster가 설치가 되었는지 확인

```
 $ kubectl get node
```

