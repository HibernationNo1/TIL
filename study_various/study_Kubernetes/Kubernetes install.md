# Kubernetes install

## Install

`Ubuntu 20.04` , [doc](https://computingforgeeks.com/deploy-kubernetes-cluster-on-ubuntu-with-kubeadm/)



### check before installation

1. ```
   $ sudo apt update
   ```

2. ```
   $ sudo apt -y full-upgrade
   ```

3. swap off

   ```
   $ sudo -i
   # swapoff -a && sed -i '/swap/s/^/#/' /etc/fstab
   ```

   confirm

   ```
   $ sudo vi /etc/fstab
   ```

   ```
   #/swapfile                                 none            swap    sw              0       0
   ```

4. Firewall off

   ```
   $ sudo ufw disable
   ```

   > 방화벽을 끄는것이 아닌, 특정 port만 허용하고 싶으면 아래 명령어
   >
   > ```
   > # Master
   > sudo ufw enable
   > sudo ufw allow 6443/tcp
   > sudo ufw allow 2379:2380/tcp
   > sudo ufw allow 10250/tcp
   > sudo ufw allow 10251/tcp
   > sudo ufw allow 10252/tcp
   > sudo ufw status
   > 
   > # Worker
   > sudo ufw enable
   > sudo ufw allow 10250/tcp
   > sudo ufw allow 30000:32767/tcp
   > sudo ufw status
   > ```

5. **open port 6443**

   ```
   $ echo > /dev/tcp/127.0.0.1/6443
   또는
   $ telnet 127.0.0.1 6443
   ```

   - port가 열려있는 경우 아무 메시지 안뜸

   - port가 닫혀있는 경우 아래처럼 뜸

     ```
     bash: connect: Connection refused
     또는 
     telnet: Unable to connect to remote host: Connection refused
     ```

   6443은 `kubeadm init` 을 사용하여 클러스터를 초기화한 후 생성되는 "kube-apiserver"에서 수신하기 때문에, 클러스터를 아직 초기화하지 않았으므로 **6443 port 에서 수신 대기하는 프로세스가 없기 때문에** `connect: Connection refused` 가 뜨는 것이 당연하다.

   때문에 kubernetes 클러스터를 설치하지 않고 포트 6443에서 트래픽을 허용하기 위해 방화벽/ufw 설정이 제대로 수행되었는지 확인하려는 경우 아래 명령어 실행

   1. ```
      $ ls | nc -l -p 6443
      ```

   2. 다른 terminal에서

      ```
      $ telnet localhost 6443
      ```

      출력

      ```
      Trying ::1...
      Trying 127.0.0.1...
      Connected to localhost.
      Escape character is '^]'.
      ```

      

      > 또는 다른 PC에서 
      >
      > ```
      > $ telnet 192.168.0.107 6443   
      > ```
      >
      > - `192.168.0.107` kubernetes를 설치하려는 PC의 IP
      >
      > 출력
      >
      > ```
      > 아무것도 안뜸. Ctrl+] 을 눌러 Telnet terminal로 전환
      > Microsoft Telnet>
      > Microsoft Telnet> q		# exit 키
      > ```

   > port자체가 닫혀있는 경우 방화벽 `ufw`를 통해 open
   >
   > ```
   > $ sudo ufw allow 6443
   > $ sudo ufw disable 		# 혹시 모르니 방화벽도 끄기
   > ```





### install docker

[공식 문서](https://docs.docker.com/engine/install/ubuntu/)

**Install using the repository**

1. install docker의 prerequisite packge

   ```
   $ sudo apt-get install \
       ca-certificates \
       curl \
       gnupg \
       lsb-release
   ```

   

2. GPH key추가

   ```
   $ sudo mkdir -p /etc/apt/keyrings
   $ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
   ```

   

3. repository를 follow하도록 설정

   ```
   $ echo \
     "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
     $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
   ```

   > arm기반의 cpu인 경우 위 명령어 대신 다른 명령어 사용(검색하기)

   

4. install Docker Engine (최신 version)

   ```
   $ sudo apt-get update
   $ sudo apt-get install docker-ce docker-ce-cli containerd.io
   ```

   > 특정 version의 docker engine을 install하고자 한다면 공식 문서 참고

5. Create required directories

   ```
   $ sudo mkdir -p /etc/systemd/system/docker.service.d
   ```

   

6. Create daemon json config file

   ```
   $ sudo tee /etc/docker/daemon.json <<EOF
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
   $ sudo systemctl daemon-reload 
   ```

   

7. check

   ```
   $ sudo docker run hello-world
   ```

   `Hello from Docker!` 이 포함된 출력문이 나오면 된것

   

8. 권한 설정

   root user가 아닌, host의 기본 user에게도 권한을 주기 위해 

   새로운 터미널 띄운 후 

   ```
   $ sudo usermod -a -G docker $USER
   $ sudo systemctl restart docker
   $ sudo systemctl enable docker
   ```

   이후 logout(또는 reboot)후 다시 login

   ```
   $ docker ps
   ```

   

#### Install Mirantis cri-dockerd

[공식 문서](https://computingforgeeks.com/install-mirantis-cri-dockerd-as-docker-engine-shim-for-kubernetes/)

Docker 엔진의 경우 shim 인터페이스가 필요

Kubernetes용 Docker Engine shim으로 **Mirantis cri-dockerd** 설치

> Kubernetes가 v1.20 이후 컨테이너 런타임으로 Docker를 더 이상 사용하지 않지만 Docker 생성 이미지는 항상 그래왔듯이 모든 런타임과 함께 Kubernetes 클러스터에서 계속 작동된다.
>
> **cri-dockerd**를 사용하면 Docker 엔진이 CRI를 준수할 수 있으며, 기본 제공 dockershim에서 외부 dockershim으로 전환하기만 하면 Kubernetes에서 계속 사용할 수 있다.

Mirantis cri-dockerd CRI 소켓 파일 경로는 `/run/cri-dockerd.sock` (Kubernetes 클러스터를 구성할 때 사용)

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
   cri-dockerd 0.2.5 (10797dc)
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
        Active: active (listening) since Tue 2022-09-20 14:01:38 KST; 11s ago
      Triggers: ● cri-docker.service
        Listen: /run/cri-dockerd.sock (Stream)
         Tasks: 0 (limit: 76823)
        Memory: 116.0K
        CGroup: /system.slice/cri-docker.socket
   
   Sep 20 14:01:38 ubuntu systemd[1]: Starting CRI Docker Socket for the API.
   Sep 20 14:01:38 ubuntu systemd[1]: Listening on CRI Docker Socket for the API.
   ```

   

#### NVIDIA DOCKER

docker contianer안에서 GPU를 사용하기 위해선 필수

1. Setting up NVIDIA Container Toolkit

   ```
   $ distribution=$(. /etc/os-release;echo $ID$VERSION_ID) \
         && curl -fsSL https://nvidia.github.io/libnvidia-container/gpgkey | sudo gpg --dearmor -o /usr/share/keyrings/nvidia-container-toolkit-keyring.gpg \
         && curl -s -L https://nvidia.github.io/libnvidia-container/$distribution/libnvidia-container.list | \
               sed 's#deb https://#deb [signed-by=/usr/share/keyrings/nvidia-container-toolkit-keyring.gpg] https://#g' | \
               sudo tee /etc/apt/sources.list.d/nvidia-container-toolkit.list
   ```

   > `ubuntu18.04/$(ARCH)` 떠도 20.04에서 정상 작동

2. install nvidia-docker2

   ```
   $ sudo apt-get update
   $ sudo apt-get install -y nvidia-docker2
   ```

   ```
   *** daemon.json (Y/I/N/O/D/Z) [default=N] ? y
   Installing new version of config file /etc/docker/daemon.json ...
   ```

3. Restart the Docker daemon 

   ```
   $ sudo systemctl restart docker
   ```

   

   confirm : 기본 CUDA container 실행

   ```
   $ sudo docker run --rm --gpus all nvidia/cuda:11.3.1-base-ubuntu20.04 nvidia-smi
   ```

   > cuda와 ubuntu version에 대한tag는 [docker hub-nvidia](https://hub.docker.com/r/nvidia/cuda/tags)에서 검색 후 결정

   ```
   +-----------------------------------------------------------------------------+
   | NVIDIA-SMI 470.161.03   Driver Version: 470.161.03   CUDA Version: 11.4     |
   |-------------------------------+----------------------+----------------------+
   | GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
   | Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
   |                               |                      |               MIG M. |
   |===============================+======================+======================|
   |   0  NVIDIA GeForce ...  Off  | 00000000:07:00.0  On |                  N/A |
   |  0%   27C    P8    15W / 180W |     45MiB / 12052MiB |      0%      Default |
   |                               |                      |                  N/A |
   +-------------------------------+----------------------+----------------------+
                                                                                  
   +-----------------------------------------------------------------------------+
   | Processes:                                                                  |
   |  GPU   GI   CI        PID   Type   Process name                  GPU Memory |
   |        ID   ID                                                   Usage      |
   |=============================================================================|
   +-----------------------------------------------------------------------------+
   ```

   

4. edit daemon

   ```
   $ sudo vi /etc/docker/daemon.json
   ```

   아래내용 추가

   ```
   {
       "default-runtime": "nvidia",
       "runtimes": {
           "nvidia": {
               "path": "nvidia-container-runtime",
               "runtimeArgs": []
           }
       }
   }
   ```

   ```
   $ sudo systemctl daemon-reload 
   ```




### install kubelet, kubeadm, kubectl

1. Add required packages

   ```
   $ sudo apt-get install -y apt-transport-https ca-certificates curl
   ```

   

2. download google cloud public key

   ```
   $ curl -s https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add -
   ```

   

3. add Kubernetes repository for Ubuntu 20.04

   ```
   $ echo "deb https://apt.kubernetes.io/ kubernetes-xenial main" | sudo tee /etc/apt/sources.list.d/kubernetes.list
   ```

   

4. install kubelet, kubeadm, kubectl

   ```
   $ sudo apt-get update
   $ sudo apt-get install -y kubectl=1.22.13-00 kubelet=1.22.13-00 kubeadm=1.22.13-00
   ```

   > 차후 목적을 위해 필요한 version을 명시.

   

5. Confirm installation by checking the version of kubectl.

   ```
   $ kubectl version --client && kubeadm version
   ```

   ```
   Client Version: version.Info{Major:"1", Minor:"22", GitVersion:"v1.22.13", GitCommit:"a43c0904d0de10f92aa3956c74489c45e6453d6e", GitTreeState:"clean", BuildDate:"2022-08-17T18:28:56Z", GoVersion:"go1.16.15", Compiler:"gc", Platform:"linux/amd64"}
   kubeadm version: &version.Info{Major:"1", Minor:"22", GitVersion:"v1.22.13", GitCommit:"a43c0904d0de10f92aa3956c74489c45e6453d6e", GitTreeState:"clean", BuildDate:"2022-08-17T18:27:51Z", GoVersion:"go1.16.15", Compiler:"gc", Platform:"linux/amd64"}
   ```

   hold version

   ```
   $ sudo apt-mark hold kubelet kubeadm kubectl
   ```

   

6. reload, restart

   ```
   $ sudo systemctl daemon-reload
   $ sudo systemctl restart kubelet
   ```

   

   ```
   $ systemctl status kubelet
   ```

   ```
   ● kubelet.service - kubelet: The Kubernetes Node Agent
        Loaded: loaded (/lib/systemd/system/kubelet.service; enabled; vendor preset: enabled)
       Drop-In: /etc/systemd/system/kubelet.service.d
                └─10-kubeadm.conf
        Active: activating (auto-restart) (Result: exit-code) since Tue 2022-09-20 13:27:44 KST; 8s ago
          Docs: https://kubernetes.io/docs/home/
       Process: 2334601 ExecStart=/usr/bin/kubelet $KUBELET_KUBECONFIG_ARGS $KUBELET_CONFIG_ARGS $KUBELET_KUBEADM_ARGS $KUBELET_EXTRA_ARGS (code=exited, status=1/FAILURE)
      Main PID: 2334601 (code=exited, status=1/FAILURE)
   ```

   - Active :`activating` 확인



### Initialize master node

1. confirm br_netfilter

   ```
   $ lsmod | grep br_netfilter
   ```

   ```
   br_netfilter           28672  0
   bridge                176128  1 br_netfilter
   ```

   - `br_netfilter` kernel module이 존재하고 있으나 아무도 사용을 하고 있지 않아서 `0`
   - `br_netfilter`가 이 `bridge` module에 의존해서 동작함을 **확인**

2. set host

   ```
   $ hostnamectl set-hostname master_node_name
   ```

   

   - if you have plan to set up worker nodes

     ```
     $ sudo vi /etc/hosts
     ```

     ```
     127.0.1.1 master.example.com master					# node(cluster)이름
     
     worker_node_내부IP_1	worker node 이름_1
     worker_node_내부IP_1	worker node 이름_2
     ```

     

   > minikube를 설치했다가 삭제한 경우로 인해 아래 문구가 존재하면 #으로 주석처리
   >
   > ````
   > $ sudo vi /etc/hosts
   > ````
   >
   > ```
   > 127.0.0.1       host.minikube.internal
   > 192.168.0.107   control-plane.minikube.internal
   > ```

   

   확인

   ```
   $ hostnamectl
   ```

   ```
      Static hostname: master.example.com
            Icon name: computer-desktop
              Chassis: desktop
           Machine ID: be201804e0da4edf8f8a54cf782b41f3
              Boot ID: 83ae19d476f04e4683a9f25fed50408a
     Operating System: Ubuntu 20.04.5 LTS
               Kernel: Linux 5.4.0-125-generic
         Architecture: x86-64
   ```

   > 또는 hostname file을 직접 확인
   >
   > ```
   > $ sudo vi /etc/hostname
   > ```
   >
   > ```
   > master.example.com
   > ```
   >

   

3. kubeadm init

   ```
   $ sudo kubeadm init \
     --pod-network-cidr=10.244.0.0/16 \
     --apiserver-advertise-address 192.168.219.100\
     --cri-socket /run/cri-dockerd.sock
   ```

   - `--pod-network-cidr` : 포드 네트워크의 IP 주소 범위를 지정 설정

     다양한 네트워크 플러그인 중 하나를 선택해야만 클러스터 네트워킹이 제대로 동작한다. 

     - **Calico 기반 구축** : 192.168.0.0/16

     - **Flannel 기반 구축** :  10.244.0.0/16

       > kubeflow사용시 권장
       >
       > 해당 옵션 사용 시 init이후 flannel CNI를 설치해야 한다. 방법은 아래

   - `--cri-socket` : runtime적용

     ```
     --cri-socket /run/cri-dockerd.sock
     ```

     **Mirantis cri-dockerd** 를 설치했다면 반드시 option에 추가

     > installed `cri-dockerd`

   - `--upload-certs` : control-plane 인증서를 kubeadm-certs Secret에 업로드한다.

   - `--control-plane-endpoint` : control-plane의 IP 주소 또는 DNS 이름을 지정

     ```
     --control-plane-endpoint=k8s-cluster.computingforgeeks.com
     ```

     

   

   출력 확인

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
   
   You can now join any number of control-plane nodes by copying certificate authorities
   and service account keys on each node and then running the following as root:
   
     kubeadm join k8s-cluster.computingforgeeks.com:6443 --token j4u32g.kbxv5bd799hh4a32 \
           --discovery-token-ca-cert-hash sha256:d46b1bed31c13efd6d15ad94ae739a914e359ff8d3244a5da52bdc5e82a444c9 \
           --control-plane 
   
   Then you can join any number of worker nodes by running the following on each as root:
   
   kubeadm join k8s-cluster.computingforgeeks.com:6443 --token j4u32g.kbxv5bd799hh4a32 \
           --discovery-token-ca-cert-hash sha256:d46b1bed31c13efd6d15ad94ae739a914e359ff8d3244a5da52bdc5e82a444c9 
   ```

   위 출력 중 보이는 아래 세 줄을 실행해야됨

   ```
   $ mkdir -p $HOME/.kube
   $ sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
   $ sudo chown $(id -u):$(id -g) $HOME/.kube/config
   ```

   

4. node확인

   ```
   $ kubectl get nodes
   ```

   ```
   NAME                 STATUS     ROLES                  AGE   VERSION
   master.example.com   Ready   control-plane,master   30s   v1.22.13
   ```

   > kubeadm init을 안하면 아래 출력이 나옴
   >
   > ```
   > The connection to the server 192.168.0.107:6443 was refused - did you specify the right host or port?
   > ```

   - STATUS: `NotReady` 인 경우

     1. ```
        $ kubectl get pod -n kube-system
        ```

        ```
        NAME                                     READY   STATUS    RESTARTS   AGE
        coredns-78fcd69978-cdf4d                 1/1     padding   0          49s
        coredns-78fcd69978-snxdp                 1/1     padding   0          49s
        ```

        위 pods의 STATUS: `padding` 인 경우에는 **`install CNI(flannel)`**

        해당 CNI를 설치하지 않으면 nodes의 STATUS가 계속해서 `NotReady`이다.

        ```
        $ kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/master/Documentation/kube-flannel.yml
        ```

        ```
        $ kubectl get pod -n kube-system
        ```

        모든 STAUS가 `Running`임을 확인





### nvidia-device-plugin

[doc](https://github.com/NVIDIA/k8s-device-plugin)

1. graphic driver 존재 확인

   ```
   $ nvidia-smi
   ```

2. create `nvidia-device-plugin` daemonset

   ```
   $ kubectl create -f https://raw.githubusercontent.com/NVIDIA/k8s-device-plugin/v0.13.0/nvidia-device-plugin.yml
   ```

   > version은 공식 doc에서 확인 후 결정

   - kubernetes는 1.6부터 Daemonset이 기본적으로 master node에서 schedule되지 않는다.

     > 정확히는, taint에 의해 master node에서 pod구동이 안되도록 되어 있다.

     만일 master node에서 pod작업을 이어가고자 한다면 taint를 해제

     ```
     $ kubectl taint nodes hibernationno1 node-role.kubernetes.io/master-
     ```

3. confirm enabling GPU support in Kubernetes

   ```
   $ kubectl get nodes "-o=custom-columns=NAME:.metadata.name,GPU:.status.allocatable.nvidia\.com/gpu"
   ```

   ```
   NAME             GPU
   hibernationno1   1
   ```

   > 1 확인

   

   pod구동 확인

   ```
   $ kubectl get pod -A | grep nvidia
   ```

   ```
   kube-system   nvidia-device-plugin-daemonset-k228k     1/1     Running   0              16m
   ```

4. check use GPU at pod

   create pod

   ```
   $ vi gpu-container.yaml
   ```

   ```
   apiVersion: v1
   kind: Pod
   metadata:
     name: gpu
   spec:
     containers:
     - name: gpu-container
       image: nvidia/cuda:11.3.1-runtime-ubuntu20.04
       command:
         - "/bin/sh"
         - "-c"
       args:
         - nvidia-smi && tail -f /dev/null
       resources:
         requests:
           nvidia.com/gpu: 1
         limits:
           nvidia.com/gpu: 1
   ```

   - `nvidia/cuda:10.2-runtime` : 알맞는 cuda version명시해줘야 함
   - ``spec.resources.requests` 와 `spec.resources.limits` 에 `nvidia.com/gpu` 를 포함해야 pod 내에서 GPU 사용이 가능` ★★★

   ```
   $ kubectl create -f gpu-container.yaml
   $ kubectl get pod gpu -n default
   ```

   ```
   NAME   READY   STATUS              RESTARTS   AGE
   gpu    0/1     ContainerCreating   0          90s
   ```

   > `STATUS : Runniing` 확인 후 아래 명령어 실행

   ```
   $ kubectl logs gpu
   ```

   ```
   +-----------------------------------------------------------------------------+
   | NVIDIA-SMI 470.161.03   Driver Version: 470.161.03   CUDA Version: 11.4     |
   |-------------------------------+----------------------+----------------------+
   | GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
   | Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
   |                               |                      |               MIG M. |
   |===============================+======================+======================|
   |   0  NVIDIA GeForce ...  Off  | 00000000:07:00.0 Off |                  N/A |
   |  0%   27C    P8    14W / 180W |     64MiB / 12052MiB |      0%      Default |
   |                               |                      |                  N/A |
   +-------------------------------+----------------------+----------------------+
                                                                                  
   +-----------------------------------------------------------------------------+
   | Processes:                                                                  |
   |  GPU   GI   CI        PID   Type   Process name                  GPU Memory |
   |        ID   ID                                                   Usage      |
   |=============================================================================|
   +-----------------------------------------------------------------------------+
   ```

   



## uninstall

#### kubeadm reset

```
sudo systemctl restart docker
docker rm -f $(docker ps -aq)
docker rmi $(docker images -q)
```

> 한 번에 입력

```
$ sudo kubeadm reset
$ sudo rm -rf /home/ainsoft/.kube
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





### error

**`sudo kubeadm init` 시 발생**

- ```
  Found multiple CRI endpoints on the host. Please define which one do you wish to use by setting the 'criSocket' field in the kubeadm configuration file: unix:///var/run/containerd/containerd.sock, unix:///var/run/cri-dockerd.sock
  To see the stack trace of this error execute with --v=5 or higher
  ```

  kubeadm init을 진행할 때 `--cri-socket` option을 추가해야 함

  

- ````
  I1205 13:40:20.612618   30956 version.go:255] remote version is much newer: v1.25.4; falling back to: stable-1.22
  [init] Using Kubernetes version: v1.22.16
  [preflight] Running pre-flight checks
  error execution phase preflight: [preflight] Some fatal errors occurred:
          [ERROR FileAvailable--etc-kubernetes-manifests-kube-apiserver.yaml]: /etc/kubernetes/manifests/kube-apiserver.yaml already exists
          [ERROR FileAvailable--etc-kubernetes-manifests-kube-controller-manager.yaml]: /etc/kubernetes/manifests/kube-controller-manager.yaml already exists
          [ERROR FileAvailable--etc-kubernetes-manifests-kube-scheduler.yaml]: /etc/kubernetes/manifests/kube-scheduler.yaml already exists
          [ERROR FileAvailable--etc-kubernetes-manifests-etcd.yaml]: /etc/kubernetes/manifests/etcd.yaml already exists
  [preflight] If you know what you are doing, you can make a check non-fatal with `--ignore-preflight-errors=...`
  To see the stack trace of this error execute with --v=5 or higher
  ````

  **kubeadm reset 진행**

  
