# Install Kubernetes

## prerequisite

### port

**Master node**

- **6443**: Kubernetes API 서버 (모든 인바운드 트래픽 허용)
- **2379-2380**: etcd 서버 클라이언트 API (클러스터 내에서만 접근 가능해야 함)
- **10250**: Kubelet API (모든 인바운드 트래픽 허용) Master와 worker 간의 관리 트래픽에 사용
- **10251**: kube-scheduler (로컬 트래픽만 허용)
- **10252**: kube-controller-manager (로컬 트래픽만 허용)

**Worker node**

- **10250**: Kubelet API (모든 인바운드 트래픽 허용)
- **30000-32767**: NodePort 서비스들을 위한 포트 범위 (선택적으로 열기)

6443과 10250은 반드시 open상태인지 확인해야 한다.

- 해당 port들이 이미 사용되는 port인지 확인

  ```
  $ sudo lsof -i:6443
  $ sudo netstat -tulnp | grep 6443
  ```

  아무것도 출력되지 않으면 사용하고 있는 port가 아님.

- firewalld를 사용하여 port open (Ubuntu 20.04)

  ```
  $ sudo firewall-cmd --permanent --add-port=6443/tcp
  $ sudo firewall-cmd --permanent --add-port=10250/tcp
  $ sudo firewall-cmd --reload
  ```

  또는

  ufw를 사용하여 port open (Ubuntu 18.04)

  ```
  $ sudo ufw allow 6443/tcp
  $ sudo ufw allow 10250/tcp
  $ sudo ufw reload
  ```

  





### Swap

Kubernetes는  시스템의 성능 예측 가능성과 프로세스 스케줄링의 정확성을 높이기 위해서 **기본적으로 swap 메모리 사용을 지원하지 않는다**. 

- swap off 명령어

  ```
  $ sudo swapoff -a && sudo sed -i '/swap/s/^/#/' /etc/fstab
  ```

  제대로 적용되었는지 확인

  ```
  $ sudo cat /etc/fstab
  ```

  아래의 출력이 포함되어 나와야 함

  ```
  /swapfile                                 none            swap    sw              0       0
  ```

  



### br_netfilter

Kubernetes에서 네트워킹을 위해서 필요.

브리지된 네트워크 트래픽에 대한 iptables 규칙을 적용하는 데 사용된다.

```
$ lsmod | grep br_netfilter
```

아래와 같이 출력되어야 한다.

```
br_netfilter           28672  0
bridge                176128  1 br_netfilter
```

- `br_netfilter` kernel module이 존재하고 있으나 아무도 사용을 하고 있지 않아서 `0`
- `br_netfilter`가 이 `bridge` module에 의존해서 동작함을 **확인**



### Hostname

hostname을 변경하면 kubeadm init, join 실행 시 `[WARNING Hostname] ` 가 발생한다. 

`[WARNING Hostname] ` 발생 시 node를 정상적으로 join 불가능.

그러니 hostname변경 금지

> 클러스터 내에서 노드를 쉽게 식별하기 위해 Hostname 설정
>
> 시스템 재부팅이 가능한 경우에만 설정
>
> 1. hostname 설정
>
>    ```
>    $ hostnamectl set-hostname MasterNode
>    ```
>
>    > `_`를 포함하여 hostname을 설정해도 `_`가 누락되어 설정된다.
>
>    확인
>
>    ```
>    $ hostname
>    ```
>
> 2. `/etc/hosts` 파일에 mapping
>
>    ```
>    $ sudo vi /etc/hosts
>    ```
>
>    ```
>    127.0.1.1       MasterNode
>    ```









### docker

1. docker설치 필요(GPU 사용 시 **NVIDIA DOCKER** 까지 설치 필수)

2. **cri-dockerd 설치**

   Docker와 Kubernetes 간의 통신 인터페이스 역할을 하는 CRI 호환 브릿지

   **설치 과정**

   1. get the latest release version

      ```
      $ VER=$(curl -s https://api.github.com/repos/Mirantis/cri-dockerd/releases/latest|grep tag_name | cut -d '"' -f 4|sed 's/v//g')
      $ echo $VER
      ```

   2. download the archive file from [Github cri-dockerd releases](https://github.com/Mirantis/cri-dockerd/releases) page.

      ```
      $ wget https://github.com/Mirantis/cri-dockerd/releases/download/v${VER}/cri-dockerd-${VER}.amd64.tgz
      $ tar xvf cri-dockerd-${VER}.amd64.tgz
      ```

      Move `cri-dockerd` binary package to `/usr/local/bin` directory

      ```
      $ sudo mv cri-dockerd/cri-dockerd /usr/local/bin/
      ```

   3. Validate successful installation

      ```
      $ cri-dockerd --version
      ```

      ```
      cri-dockerd 0.3.13 (5aee623)
      ```

   4. Configure systemd

      ```
      $ wget https://raw.githubusercontent.com/Mirantis/cri-dockerd/master/packaging/systemd/cri-docker.service
      $ wget https://raw.githubusercontent.com/Mirantis/cri-dockerd/master/packaging/systemd/cri-docker.socket
      $ sudo mv cri-docker.socket cri-docker.service /etc/systemd/system/
      $ sudo sed -i -e 's,/usr/bin/cri-dockerd,/usr/local/bin/cri-dockerd,' /etc/systemd/system/cri-docker.service
      ```

   5. Start and enable the services

      ```
      $ sudo systemctl daemon-reload
      $ sudo systemctl enable cri-docker.service
      $ sudo systemctl enable --now cri-docker.socket
      ```

   6. Confirm the service is now running

      ```
      $ systemctl status cri-docker.socket
      ```

      ```
      ● cri-docker.socket - CRI Docker Socket for the API
           Loaded: loaded (/etc/systemd/system/cri-docker.socket; enabled; vendor preset: enabled)
           Active: active (listening) since Mon 2024-04-29 18:18:32 KST; 3s ago
         Triggers: ● cri-docker.service
           Listen: /run/cri-dockerd.sock (Stream)
            Tasks: 0 (limit: 38261)
           Memory: 4.0K
           CGroup: /system.slice/cri-docker.socket
      ```








## install Kubeadm, Kubelet, Kubeadm

```
$ sudo apt update && sudo apt -y full-upgrade
```



**ubuntu 18.04, 20.04**

1. Add required packages

   ```
   $ sudo apt-get install -y apt-transport-https ca-certificates curl
   ```

   

2. download google cloud public key

   ```
   $ sudo curl -fsSL https://pkgs.k8s.io/core:/stable:/v1.28/deb/Release.key | sudo gpg --dearmor -o /usr/share/keyrings/kubernetes-apt-keyring.gpg
   ```

   `ubuntu 18.04, 20.04` 는 1.28 version의 kubernetes를 사용해야 한다.

3. add Kubernetes repository 

   ```
   $ echo "deb [signed-by=/usr/share/keyrings/kubernetes-apt-keyring.gpg] https://pkgs.k8s.io/core:/stable:/v1.28/deb/ /" | sudo tee /etc/apt/sources.list.d/kubernetes.list
   ```

   

4. install kubelet, kubeadm, kubectl

   ```
   $ sudo apt-get update && sudo apt-get install -y kubelet kubeadm kubectl
   ```

   설치된 tool의 version확인 

   ```
   $ kubectl version --client && kubeadm version
   ```

   ```
   Client Version: v1.28.9
   Kustomize Version: v5.0.4-0.20230601165947-6ce0bf390ce3
   kubeadm version: &version.Info{Major:"1", Minor:"28", GitVersion:"v1.28.9", GitCommit:"587f5fe8a69b0d15b578eaf478f009247d1c5d47", GitTreeState:"clean", BuildDate:"2024-04-16T15:04:37Z", GoVersion:"go1.21.9", Compiler:"gc", Platform:"linux/amd64"}
   ```

   version 고정

   ```
   $ sudo apt-mark hold kubelet kubeadm kubectl
   ```

5. reload daemon, restart kubelet

   ```
   $ sudo systemctl daemon-reload
   $ sudo systemctl restart kubelet
   ```

6. check status

   ```
   $ systemctl status kubelet
   ```

   ```
   ● kubelet.service - kubelet: The Kubernetes Node Agent
        Loaded: loaded (/lib/systemd/system/kubelet.service; enabled; vendor preset: enabled)
       Drop-In: /usr/lib/systemd/system/kubelet.service.d
                └─10-kubeadm.conf
        Active: activating (auto-restart) (Result: exit-code) since Mon 2024-04-29 19:11:06 KST; 3s ago
          Docs: https://kubernetes.io/docs/
       Process: 963258 ExecStart=/usr/bin/kubelet $KUBELET_KUBECONFIG_ARGS $KUBELET_CONFIG_ARGS $KUBELET_KUBEADM_ARGS $KUBELET_EXTRA_ARGS (code=exited, status=1/FAILURE)
      Main PID: 963258 (code=exited, status=1/FAILURE)
   ```

   > Active :`activating` 확인





**ubuntu 22.04**

TODO



## Initialize node



### Master(Control-plane) Node

> 192.168.110.103 을 master node로 지정했을 경우

#### Initialize

```
$ sudo kubeadm init \
  --pod-network-cidr=10.244.0.0/16 \
  --cri-socket /run/cri-dockerd.sock
```

- `--pod-network-cidr`: 클러스터 내에서 사용할 Pod 네트워크의 IP 범위를 지정. (**필수**)

  Pod 간 통신을 올바르게 처리할 수 있도록 설정하는 데 필요하다.

  - `10.244.0.0/16`: 10.244.0.0에서 시작해 10.244.255.255까지의 IP 주소를 포드에 할당할 수 있는 범위를 의미

- `--apiserver-advertise-address`: 쿠버네티스 API 서버가 자신을 광고(advertise)할 IP 주소를 지정

  이 주소는 클러스터 내의 다른 컴포넌트들이 API 서버와 통신할 때 사용된다.

  ```
    --apiserver-advertise-address 192.168.219.100\
  ```

- `--cri-socket`:  Kubernetes 노드에서 사용할 컨테이너 런타임 인터페이스(CRI) 소켓의 경로를 지정 (**필수**)

  - cri-docker 를 설지했다면 socket위치는 아래 명령어로 확인

    ```
    $ systemctl status cri-docker.socket
    ```

- `--upload-certs`: `kubeadm init` 명령어를 사용할 때, 컨트롤 플레인의 중요한 인증서와 키를 클러스터 내에 안전하게 업로드하고 공유하는 옵션

  클러스터의 다른 노드에서 이러한 인증서를 사용하여 추가적인 Master Node를 쉽게 조인할 수 있다.

  인증서는 Secret resource로 저장된다.

- `-control-plane-endpoint`: 모든 컨트롤 플레인 노드에 대한 공통의 접근 지점을 설정하는 데 사용된다.

  ```
  	--control-plane-endpoint "my-cluster-control-plane.example.com:6443" --upload-certs
  ```

  하나의 Master Node에 장애가 발생해도 시스템의 가용성을 유지하기 위해 사용된다.

  이를 위해 여러 마스터 노드(컨트롤 플레인 노드) 사이의 트래픽을 균등하게 분산할 수 있도록 로드 밸런서를 구성해야 한다. 

  > 로드 밸런서는 6443 포트에서 들어오는 요청을 클러스터의 여러 마스터 노드에 분산시켜 주어야 함.

  주소는 클러스터 내외부에서 API 서버에 접근하는 데 사용되는 주소이며, 보통 로드 밸런서의 IP 주소나 DNS 이름을 지정한다.



**출력 확인**

```
Your Kubernetes control-plane has initialized successfully!

To start using your cluster, you need to run the following as a regular user:

  mkdir -p $HOME/.kube
  sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
  sudo chown $(id -u):$(id -g) $HOME/.kube/config

Alternatively, if you are the root user, you can run:

  export KUBECONFIG=/etc/kubernetes/admin.conf

You should now deploy a pod network to the cluster.
Run "kubectl apply -f [podnetwork].yaml" with one of the options listed at:
  https://kubernetes.io/docs/concepts/cluster-administration/addons/

Then you can join any number of worker nodes by running the following on each as root:

kubeadm join 192.168.110.103:6443 --token 86y64o.tcxhz7xlufrxf1hj \
	--discovery-token-ca-cert-hash sha256:8dd1a7a7a1f147879b4bc87ea90a12cd6fdcf622669e76f1b430c81665ea23a6 

```

위 출력 중 보이는 아래 세 줄을 실행해야됨

```
$ mkdir -p $HOME/.kube
$ sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
$ sudo chown $(id -u):$(id -g) $HOME/.kube/config
```

`admin.conf` 파일을 현재 사용자의 홈 디렉토리 아래 `.kube/config`로 복사하여, 해당 사용자가 `kubectl` 명령어를 사용할 때 쿠버네티스 클러스터와 통신할 수 있게 하는 설정.

이 설정을 통해 사용자는 별도의 인증 절차 없이 `kubectl` 명령어를 사용하여 클러스터를 관리할 수 있다. (sudo 없이 `kubectl` 명령을 사용할 수 있음)

- ```
  kubeadm join 192.168.110.103:6443 --token 86y64o.tcxhz7xlufrxf1hj \
  	--discovery-token-ca-cert-hash sha256:8dd1a7a7a1f147879b4bc87ea90a12cd6fdcf622669e76f1b430c81665ea23a6 
  ```

  새로운 노드를 쿠버네티스 클러스터에 추가할때 사용하는 명령어 예시를 출력해준 것이다.

  - `192.168.110.103:6443`: Master Node의 IP 주소 및 API Server port.

  - `--token`: kubernetes cluster에 join할 때 사용하는 보안 토큰. 이 토큰은 노드가 클러스터에 안전하게 조인하기 위해 필요.

  - `--discovery-token-ca-cert-hash `: API Server의 인증서 hash. 

    클러스터의 API Server 인증서가 올바른지 검증하는 데 사용되어 join 프로세스 중에 보안을 강화한다.



#### Install Network plugin 

클러스터 내에서 파드가 서로 통신할 수 있도록 네트워크 플러그인을 설치

**plugin type**

- **Calico**:

  - 보안과 네트워킹을 동시에 제공.
  - network policy를 통한 세밀한 트래픽 제어가 가능.
  - BGP를 사용하여 데이터센터 전반에 걸쳐 확장성 있는 네트워킹을 제공.
  - IP 주소를 효율적으로 관리하고, NAT 없이 POD 간의 통신이 가능하도록 환경 제공.

  ```
  $ kubectl apply -f https://docs.projectcalico.org/manifests/calico.yaml
  ```

- **Flannel**:

  - 간단하게 설정할 수 있어서 작은 규모의 네트워크에 적합.
  - 각 호스트에 POD 네트워크 서브넷을 할당.
  - VXLAN 또는 UDP를 통한 오버레이 네트워크를 제공.

  ```
  $ kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/master/Documentation/kube-flannel.yml
  ```

- **Weave Net**:

  - 호스트 간에 암호화된 네트워크를 제공.
  - 자체적인 방식으로 네트워크 분할(brain split) 문제를 해결.
  - 설치가 간편하고, 내부적으로 DNS 서비스를 제공하여 서비스 검색을 지원.

  ```
  $ kubectl apply -f "https://cloud.weave.works/k8s/net?k8s-version=$(kubectl version | base64 | tr -d '\n')"
  ```

- **Cilium**:

  - BPF (Berkeley Packet Filter) 기반으로 동작하여 보안성과 성능을 강화.
  - HTTP/API 기반의 Layer 7 network policy를 지원.
  - 멀티 클라우드 환경에 적합하며, 서비스 메시 구성 요소와 통합할 수 있다.

  ```
  $ kubectl create -f https://raw.githubusercontent.com/cilium/cilium/v1.9/install/kubernetes/quick-install.yaml
  ```





#### Check node status

```
$ kubectl get nodes
```

```
NAME               STATUS   ROLES           AGE   VERSION
masternode110103   Ready    control-plane   14m   v1.28.9
```



```
$ kubectl get pod -n kube-system
```

```
NAME                                       READY   STATUS    RESTARTS   AGE
calico-kube-controllers-658d97c59c-ghcgr   1/1     Running   0          2m12s
calico-node-qfhmq                          1/1     Running   0          2m12s
coredns-5dd5756b68-bkltk                   1/1     Running   0          15m
coredns-5dd5756b68-wzcpf                   1/1     Running   0          15m
etcd-masternode110103                      1/1     Running   0          15m
kube-apiserver-masternode                  1/1     Running   0          15m
kube-controller-manager-masternode         1/1     Running   0          15m
kube-proxy-nngbd                           1/1     Running   0          15m
kube-scheduler-masternode                  1/1     Running   0          15m
```

- `1.28.0calico-kube-controllers`: Calico 네트워크 컨트롤러 파드로, 네트워크 정책 및 IP 관리를 담당
- `calico-node-qfhmq`: Calico 노드 에이전트 파드로, 각 노드에서 네트워크 트래픽을 관리하고 필터링
- `coredns`: 쿠버네티스 클러스터의 DNS 서비스를 제공하는 CoreDNS 파드들. 이들은 클러스터 내 DNS 쿼리를 처리한다.
- `etcd`: 클러스터의 데이터를 저장하는 etcd 서버 파드. etcd는 쿠버네티스의 핵심 데이터 저장소로, 모든 클러스터 상태와 설정을 저장.
- `kube-apiserver`: 쿠버네티스 API 서버 파드로, 클러스터와의 모든 API 통신을 처리한다.
- `kube-controller-manager-masternode: 쿠버네티스 컨트롤러 매니저 파드로, 클러스터의 다양한 리소스(노드, 복제본 집합 등)의 상태를 관리
- `kube-proxy-nngbd`: 각 노드에서 실행되는 kube-proxy 파드로, 서비스의 네트워크 트래픽을 적절한 파드로 라우팅한다.
- `kube-scheduler-masternode`: 쿠버네티스 스케줄러 파드로, 새로 생성된 파드를 적절한 노드에 스케줄링하는 역할을 담당한다.



### Worker Node

#### join

Master Node에서 kubeadm init을 수행하고 나서 얻은 token값과 hash값을 기반으로 worker node의 join 명령어 실행

```
sudo kubeadm join 192.168.110.103:6443 \
    --token 1gx0kw.6je83m4sd1clrla0 \
    --discovery-token-ca-cert-hash sha256:823df36ad0cf5b3b5925bc0d5318c0c9acd177a5fa7370610d1a52327649a272 \
    --cri-socket unix:///var/run/cri-dockerd.sock
```

- `--token`: master node에서 발행하는 token. 시간이 지나면 휘발되기 때문에, master node에서 `sudo kubeadm token create` 라는 명령어로 생성해야 한다.

- `--cri-socket`:  Kubernetes 노드에서 사용할 컨테이너 런타임 인터페이스(CRI) 소켓의 경로를 지정 (**필수**)

  - cri-docker 를 설지했다면 socket위치는 아래 명령어로 확인

    ```
    $ systemctl status cri-docker.socket
    ```

- `--node-name`: 클러스터에 조인할 때 사용할 노드 이름을 지정. 이 이름은 Kubernetes 클러스터 내에서 고유해야 한다. (default: hostname)

- `--control-plane`: 해당 노드를 새로운 Master Node로써 join할때 사용

  두 번째 Master Node부터는 init이 아닌 join을 사용해서 추가한다.

- `--certificate-key`: `kubeadm init` 단계에서 생성된 키를 사용하여 추가 Master Node에서 필요한 인증서를 복호화한다.

   해당 노드를 새로운 Master Node로써 join할때 사용한다.



위 명령어로 Worker node와 Master Node가 연결된다.

**Master node에서 연결됨을 확인하는 방법**

```
$  kubectl get nodes
```

```
NAME               STATUS   ROLES           AGE   VERSION
masternode         Ready    control-plane   14h   v1.28.9
wokernode          Ready    <none>          12h   v1.28.9
```

- STATUS 가 Ready 이면 정상적으로 연결된 것









## Set Node

### Master Node

#### nvidia-device-plugin

GPU가 있는 클러스터에서 각 노드의 GPU 사용 가능 여부와 수량을 쉽게 파악할 수 있도록 plugin 생성

1. create plugin 

   ```
   $ kubectl create -f https://raw.githubusercontent.com/NVIDIA/k8s-device-plugin/v0.15.0/deployments/static/nvidia-device-plugin.yml
   ```

   > version은 [공식 doc](https://github.com/NVIDIA/k8s-device-plugin)에서 확인 후 결정

   - 관련 resource가 제대로 배포되었는지 확인

     ```
     $ kubectl get pods --namespace=kube-system | grep nvidia
     ```

     > 만일 제대로 배포되지 않아 resource를 삭제해야한다면 아래 명령어 수행
     >
     > ```
     > $ kubectl delete -f https://raw.githubusercontent.com/NVIDIA/k8s-device-plugin/v0.15.0/deployments/static/nvidia-device-plugin.yml
     > ```

   - 관련 pod가 ContainerCreating 상태로 고정이라면

     ```
     NAMESPACE     NAME                                       READY   STATUS              RESTARTS   AGE
     kube-system   nvidia-device-plugin-daemonset-pqtlp       0/1     ContainerCreating   0          69s
     ```

     상태 확인

     ```
     $  kubectl describe pod nvidia-device-plugin-daemonset-pqtlp -n kube-system
     ```

     

   

2. 각 node에서 GPU활용이 가능한지 확인

   ```
   $ kubectl get nodes "-o=custom-columns=NAME:.metadata.name,GPU:.status.allocatable.nvidia\.com/gpu"
   ```







---



#### using pod

 Master Node의  taint를 해제한 후 아래 배포 절차를 따라야 한다.

```
$ kubectl taint nodes {Master_Node_name} node-role.kubernetes.io/control-plane-
```

> 만일 다시 tiant를 적용하고 싶단면 아래 명령어 수행
>
> ```
> $ kubectl taint nodes masternode110103 node-role.kubernetes.io/control-plane=:NoSchedule
> ```



#### Calico plugin

Calico plugin을 사용 시, kube-system 네임스페이스에서 실행 중인 모든 Calico pods의 상세 정보를 확인해보자.

```
$ kubectl get pods -n kube-system -o wide | grep calico
```

- 아래와 같이 STATUS가 Init인 경우

  ```
  NAMESPACE     NAME                                       READY   STATUS              RESTARTS   AGE     
  kube-system   calico-node-gsnfc                          0/1     Init:0/3            0          4m28s   192.168.110.107   wokernode110107    <none>           <none>
  ```

  







#### set node role

각 node별로 role을 결정해준다.

```
$ kubectl label nodes {WorkerNode_name} node-role.kubernetes.io/worker={role}
```

- `node-role.kubernetes.io/`: 일반적으로 노드의 역할을 지정할 때 사용하는 공식적인 접두어

  더욱 자유롭게, `kubectl label nodes wokernode110107 example_node=true` 과 같이 명령어를 실행해도 된다.

  - `worker`: 접두어 뒤에 worker라 붙이면, worker에 대한 role을 결정한다.

- 예시로, `kubectl label nodes wokernode node-role.kubernetes.io/worker=tmp` 라는 명령어를 실행하고

  이후 node를 확인하면 아래와 같이 출력된다.

  ```
  $ kubectl get nodes
  ```

  ```
  NAME               STATUS   ROLES           AGE   VERSION
  masternode         Ready    control-plane   14h   v1.28.9
  wokernode          Ready    worker          12h   v1.28.9
  ```





### Worker Node

#### User kubectl

worker node에서 kubectl을 사용하는 방법

기본적으로 worker node에서는 kubectl 을 사용하지 않는다.

하지만 사용하고 싶다면, 아래 순서를 따라야 한다.

1. worker node에서 적절한 위치에 dir생성

   ```
   $ mkdir ~/.kube
   ```

2. master node에서 worker node로  `admin.conf` 파일 복사

   ```
   $ sudo scp /etc/kubernetes/admin.conf {worker_node_user}@{worker_node_IP}:~/.kube/config
   ```

3. 워커 노드에서 `KUBECONFIG` 설정

   ```
   $ export KUBECONFIG=~/.kube/config
   ```

4. 이제 worker node에서도 kubectl을 사용할 수 있다.

   전체 cluster의 상태 보기

   ```
   $ kubectl get nodes
   ```

   ```
   NAME                                STATUS   ROLES           AGE     VERSION
   ai-cls-api                          Ready    worker          7d14h   v1.28.9
   masternode110103                    Ready    control-plane   7d15h   v1.28.9
   showbotsearch-system-product-name   Ready    worker          7d14h   v1.28.9
   ```

   > config파일을 제대도 추적하지 못하면 아래와 같이 출력됨
   >
   > ```
   > E0508 10:07:27.505869   12757 memcache.go:265] couldn't get current server API group list: Get "http://localhost:8080/api?timeout=32s": dial tcp 127.0.0.1:8080: connect: connection refused
   > ...
   > E0508 10:07:27.508858   12757 memcache.go:265] couldn't get current server API group list: Get "http://localhost:8080/api?timeout=32s": dial tcp 127.0.0.1:8080: connect: connection refused
   > The connection to the server localhost:8080 was refused - did you specify the right host or port?
   > ```





## uninstall

#### kubeadm reset

```
$ sudo systemctl restart docker
$ docker rm -f $(docker ps -aq)
$ docker rmi $(docker images -q)
```

```
$ sudo kubeadm reset
$ sudo rm -rf ~/.kube
```



- worker node에서 kubeadm reset을 수행했다면, master node에서 아래 명령어로 연결 제거

  ```
  $ kubectl delete node wokernode110107
  ```

  



#### uninstall kubeadm kubectl kubelet

```
$ sudo apt-get purge kubeadm kubectl kubelet
```



#### uninstall docker

```
$ docker rm -f $(docker ps -aq)
$ docker rmi $(docker images -q)
$ sudo apt-get remove docker-ce docker-ce-cli containerd.io 
```

