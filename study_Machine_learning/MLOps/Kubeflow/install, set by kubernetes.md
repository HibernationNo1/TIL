# Install kubeflow at Kubernetes

## Kubernetes

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
   $ sudo apt-get install -y kubectl=1.25.4-00 kubelet=1.25.4-00 kubeadm=1.25.4-00
   ```

   > 차후 `kserve`를 위해  version을 1.25.4으로 결정 (`1.25.4-00`) 이라 명시해줘야 함

   

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





### dynamic volume provisioner

kubernetes에서 kubeflow를 사용하려면 [dynamic volume provisioner](https://kubernetes.io/docs/concepts/storage/dynamic-provisioning/)가 필요

-  [Local Path Provisioner](https://github.com/rancher/local-path-provisioner#deployment) 

  로컬 디렉토리를 이용하는 dynamic volume provisioner

  

  install Local Path Provisioner

  ````
  $ kubectl apply -f https://raw.githubusercontent.com/rancher/local-path-provisioner/master/deploy/local-path-storage.yaml
  ````

  > 조회
  >
  > ```
  > $ kubectl get storageclass
  > ```



kubeflow는 default storageclass를 사용하기 때문에, local-path storageclass를 default storageclass로 설정해야 한다.

```
$ kubectl patch storageclass local-path -p '{"metadata": {"annotations":{"storageclass.kubernetes.io/is-default-class":"true"}}}'
```

> 기본 클래스가 설정된 것을 확인
>
> ```
> $ kubectl get storageclass
> ```





## kubeflow

### **kustomize** 

[여기](https://github.com/kubernetes-sigs/kustomize/) 에서 현재 k8s version에 맞는 kustomize version을 확인하고 download binary

```
$ kubectl version
```

> kustomize 3.2.0에 알맞는 version확인

[여기](https://github.com/kubernetes-sigs/kustomize/releases/tag/v3.2.0)의 **Asset** 아래 `kustomize_3.2.0_darwin_amd64` 의 링크 복사 (arm이면 arm꺼 복사)

> 링크 없어지면 [releases](https://github.com/kubernetes-sigs/kustomize/releases?page) 에서 3.2.0 찾은 후 진행

```
$ sudo wget https://github.com/kubernetes-sigs/kustomize/releases/download/v3.2.0/kustomize_3.2.0_linux_amd64
```

> - 4.2.0 설치 시 (**아직까진  kubeflow가 3.2.0외의 version과는 호환되지 않고 있음**)
>
>   releases에서 4.2.0찾은 후 `kustomize_v4.2.0_linux_amd64.tar.gz` 복사 
>
>   ```
>   sudo wget https://github.com/kubernetes-sigs/kustomize/releases/download/kustomize%2Fv4.2.0/kustomize_v4.2.0_linux_amd64.tar.gz
>   ```
>
> 
>
>   압축 풀고 진행
>
>   ```
> $ gzip -d kustomize_v4.2.0_linux_amd64.tar.gz
> $ tar -xvf kustomize_v4.2.0_linux_amd64.tar
>   ```

file의 mode 변경 (실행 가능하도록)

```
$ sudo chmod +x kustomize_3.2.0_linux_amd64
```

압축 풀고 file위치 변경

```
$ sudo mv kustomize_3.2.0_linux_amd64 /usr/local/bin/kustomize
```

check(새 terminal 열고)

```
$ kustomize version
```

```
Version: {KustomizeVersion:3.2.0 GitCommit:a3103f1e62ddb5b696daa3fd359bb6f2e8333b49 BuildDate:2019-09-18T16:26:36Z GoOs:linux GoArch:amd64}
```

> uninstall : `sudo rm /usr/local/bin/kustomize`
>
> - 4.2.0설치 시 `kustomize_3.2.0_linux_amd64` 라는 file 대신 `kustomize` 라는 file 존재
>
>   ```
>   $ sudo chmod +x kustomize
>   $ sudo mv kustomize /usr/local/bin/kustomize
>   $ kustomize version
>   ```





### **kubeflow**

1. git clone [kubeflow/manifests](https://github.com/kubeflow/manifests)

   ```
   $ cd ~/hibernation			# git clone할 임의의 위치
   $ git clone https://github.com/kubeflow/manifests.git
   $ cd manifests
   ```

   > ```
   > $ git checkout tags/v1.4.0 
   > ```
   >
   > 위 명령어를 통해 특정 version으로 checkout하면 `manifests/apps/pipeline/upstream/env/` 의 cert-manager dir이 사라지는  현상 발생 

   ```
   $ while ! kustomize build example | kubectl apply -f -; do echo "Retrying to apply resources"; sleep 10; done
   ```
   
   위 명령어로 자동 install을 하면 몇 가지 기능이 빠진 채 진행이 안될 수 있다.
   
   가능하면 [kubeflow/manifasts](https://github.com/kubeflow/manifests)에서 하나하나 복사해가며 진행하자.



#### connect from external

```
$ kubectl get svc istio-ingressgateway -n istio-system
```

```
NAME                   TYPE       CLUSTER-IP     EXTERNAL-IP   PORT(S)                                                                      AGE
istio-ingressgateway   NodePort   10.96.89.178   <none>        15021:32680/TCP,80:32075/TCP,443:32334/TCP,31400:30226/TCP,15443:30276/TCP   15m
```

- `NodePort` 인 경우 (EXTERNAL-IP없음)

  1. port-forward

     ```
     kubectl port-forward svc/istio-ingressgateway -n istio-system 8080:80
     ```

  2. ssh

     ```
     ssh -L {외부Port}:{내부IP}:80 taeuk4958@{외부IP} -p {외부Port}
     ```

     

- `Connection refused` 가 뜰 때

  port-forward을 한 상태에서 localhost:8080으로 접속이 거부당한 경우

  port-forward를 한 pc에서 새 terminal키고 아래 명령어로 문제가 있는지 확인

  ```
  $ curl http://127.0.0.1:8080
  ```

  ```
  <a href="/dex/auth?client_id=kubeflow-oidc-authservice&amp;redirect_uri=%2Flogin%2Foidc&amp;response_type=code&amp;scope=profile+email+groups+openid&amp;state=MTY3MDg5Mzc4OHxFd3dBRUdNeVYwUTRSakp4VG1aSVN6VmhPRFE9fF3WLfxMIG835gne0SjDh4WzG1p56rNw64yirgAFPW92">Found</a>.
  ```

  이상 없을 경우 위 출력과 같이 보인다.

  이후 접속해보면 됨.

  
  
  그래도 안될 경우

  1. 모든 bind의 주소를 열어주는 방향으로 port-forward

     ```
     $ kubectl port-forward --address=0.0.0.0 svc/istio-ingressgateway -n istio-system 8080:80
     ```

  2. 공인 IP를 통해 접속 시도
  
     ```
     http://<공인_IP>:8080
     ```
  
     만약 여기서 성공한다면, 다시 `--address=0.0.0.0` option을 제거하고 port forward를 한 후  localhost8080에 접속해본다.





### add user

dashboard에 user를 추가하기 위해서는 cm dex를 수정해야 한다.

1. **check dex**

   dex는 namespace auth에 있음

   ```
   $ kubectl -n auth get cm dex -o yaml
   ```

   ```yaml
   apiVersion: v1
   data:
     config.yaml: |
       issuer: http://dex.auth.svc.cluster.local:5556/dex
       storage:
         type: kubernetes
         config:
           inCluster: true
       web:
         http: 0.0.0.0:5556
       logger:
         level: "debug"
         format: text
       oauth2:
         skipApprovalScreen: true
       enablePasswordDB: true
       staticPasswords:
       - email: user@example.com
         hash: $2y$12$4K/VkmDd1q1Orb3xAt82zu8gk7Ad6ReFR4LCP9UeYE90NLiN9Df72
         # https://github.com/dexidp/dex/pull/1601/commits
         # FIXME: Use hashFromEnv instead
         username: user
         userID: "15841185641784"
       staticClients:
       # https://github.com/dexidp/dex/pull/1664
       - idEnv: OIDC_CLIENT_ID
         redirectURIs: ["/login/oidc"]
         name: 'Dex Login Application'
         secretEnv: OIDC_CLIENT_SECRET
   ... 이하 생략
   
   ```

   위의 `staticPasswords` 에 아래 4가지를 추가해야 한다.

   ```
       - email: winter4958@gmail.com
         hash: $2a$12$lRDeywzDl4ds0oRR.erqt.b5fmNpvJb0jdZXE0rMNYdmbfseTzxNW
         userID: "84604958"
         username: taeuk
   ```

   - `email` : dashdoard접속시 입력할 email

   - `hash` : dashdoard접속시 입력할 passward

     > [BCrypt Hash Generator](https://bcrypt-generator.com/) 에서 hash값을 생성할 수 있다.

   - `userID`, `username` : user정보

2. **add user information**

   ```
   $ kubectl -n auth edit cm dex
   ```

   >  vim editer로 변경

3. **rollout restart**

   dex manifast를 수정하고 난 후 해당 resource를 restart해주어야 한다.

   ```
   $ kubectl rollout restart deployment dex -n auth
   ```

4. **create namespace**

   이후 해당 ID/PW로 접속이 가능하지만, namespace가 지정되지 않아 자원 생성이 불가능하다. 

   이를 위해 namespace를 생성하자

   1. add profile

      ```
      $ vi profile.yaml
      ```

      ```yaml
      #profile.yaml
      apiVersion: kubeflow.org/v1beta1
      kind: Profile
      metadata:
        name: namesapce
      spec:
        owner:
          kind: User
          name: winter4958@gmail.com
        resourceQuotaSpec: {}
      ```

      - `metadata.name` : kubeflow pipeline에서 사용할 namesapce의 name

      - `spec.owner`

        - `kind` : User로 고정
        - `name` : 위 dex resource에 추가한 User의 email

      - `resourceQuotaSpec` : 해당 namesapce의 resource 할당량 제한 (optional)

        ```
          resourceQuotaSpec:
            hard:
              cpu: "2"
              memory: 2Gi
              persistentvolumeclaims: "1"
              requests.nvidia.com/gpu: "1"
              requests.storage: "10Gi"
        ```

        - `cpu: "2"` : cpu제한 2개

        - `memory` : 메모리 제한 2 기가

        - `requests.nvidia.com/gpu` : 사용 가능항 GPU제한 1개

        - `persistentvolumeclaims` : volume 1개

        - `requests.storage` : 저장소 공간 제한 10GB

          > resourceQuotaSpec에 위 처럼 특정 값을 넣으면 아래의 에러가 발생
          >
          > ```
          > This step is in Error state with this message: task 'hibernation-project-9kj4p.set-config' errored: pods "hibernation-project-9kj4p-3036383870" is forbidden: failed quota: kf-resource-quota: must specify cpu,memory
          > ```

   2. apply

      ```
      $ kubectl apply -f profile.yaml
      ```

      > 만일 `no matches for kind "Profile" in version "kubeflow.org/v1beta1"` 라는 error message가 뜬다면  [kubeflow/manifasts](https://github.com/kubeflow/manifests)에서 `Profiles + KFAM`와 `User Namespace`를 install이 제대로 됐는지 확인하자.

   3. edit

      profile 변경이 필요할 시
   
      ```
      $ kubectl edit profile <namespace_name>
      ```
   
      



## KServe

[doc_kserve0.9](https://kserve.github.io/website/0.9/admin/serverless/#5-install-kserve-built-in-clusterservingruntimes)

`Istio`, `Knative Serving`, `Cert Manager` 는 전부 kubeflow에 설치한 resource그대로 사용



kubeflow/manifast공시 gitgub에 있는 건 뭐냐?



### KServe

```
$ kubectl apply -f https://github.com/kserve/kserve/releases/download/v0.9.0/kserve.yaml
```

confirm 

```
$ kubectl get pod -n kserve
```

```
NAME                                         READY   STATUS    RESTARTS   AGE
kserve-controller-manager-5fc887875d-td89t   2/2     Running   0          3m58s
```





### Built-in ClusterServingRuntimes

```
$ kubectl apply -f https://github.com/kserve/kserve/releases/download/v0.9.0/kserve-runtimes.yaml
```

> **ClusterServingRuntimes** are required to create InferenceService for built-in model serving runtimes with KServe v0.8.0 or higher.





### exam

**preparations**

1. namespace생성

   ```
   $ kubectl create namespace kserve-test
   ```

2. 배포하고자 하는 model에 대한 InferenceService 작성 후 apply

   ```
   $ kubectl apply -n kserve-test -f - <<EOF
   apiVersion: "serving.kserve.io/v1beta1"
   kind: "InferenceService"
   metadata:
     name: "sklearn-iris"
   spec:
     predictor:
       model:
         modelFormat:
           name: sklearn
         storageUri: "gs://kfserving-examples/models/sklearn/1.0/model"
   EOF
   ```

   > - `metadata.name` : Knative service name
   >
   > 
   >
   > ```
   > $ kubectl get pods -n kserve-test -w
   > ```
   >
   > `STATUS : Running` 확인 후 진행

3. confirm domain

   ```
   $ kubectl get inferenceservices sklearn-iris -n kserve-test
   ```

   ```
   NAME           URL                                           READY   PREV   LATEST   PREVROLLEDOUTREVISION   LATESTREADYREVISION                    AGE
   sklearn-iris   http://sklearn-iris.kserve-test.example.com   True           100                              sklearn-iris-predictor-default-00001   5h11m
   ```

   `URL` : 기본 도메인 값은 `http://{Knative service name}.{namespace}.example.com` 이다.

4. port forward

   ```
   kubectl port-forward svc/istio-ingressgateway -n istio-system 8080:80
   ```

   





- SERVICE_HOSTNAME

  ```
  $ SERVICE_HOSTNAME=$(kubectl get inferenceservice sklearn-iris -n kserve-test -o jsonpath='{.status.url}' | cut -d "/" -f 3)
  ```

  ```
  sklearn-iris.kserve-test.example.com
  ```

  

  

- INGRESS_HOST

  ```
  INGRESS_HOST=192.168.219.100
  ```

  내부 IP

  

- INGRESS_PORT

  ```
  $ INGRESS_PORT=$(kubectl -n istio-system get service istio-ingressgateway -o jsonpath='{.spec.ports[?(@.name=="http2")].nodePort}')
  ```

  > ```
  > $ echo $INGRESS_PORT
  > ```
  >
  > install시 random으로 할당됨



호출

- internal

  ```
  $ curl -v -H "Host: ${SERVICE_HOSTNAME}" http://${INGRESS_HOST}:${INGRESS_PORT}/v1/models/sklearn-iris:predict -d @./iris-input.json
  ```

  > ```
  > $ curl -v -H "Host: sklearn-iris.kserve-test.example.com" http://192.168.219.100:30551/v1/models/sklearn-iris:predict -d @./iris-input.json
  > ```

- external

  ```
  curl -v -H "Host: sklearn-iris.kserve-test.example.com" http://{외부IP}:${INGRESS_PORT}/v1/models/sklearn-iris:predict -d @./iris-intput.json
  ```



이대로 호출하면 302 가 뜬다(dex인증 필요)



#### indirection

[configmap](https://istio.io/latest/docs/reference/config/istio.mesh.v1alpha1/#MeshConfig-ExtensionProvider-EnvoyExternalAuthorizationHttpProvider)

```
$ kubectl edit configmap istio -n istio-system
```

```
data:
  mesh: |-
    extensionProviders:
      - name: dex-auth-provider
          envoyExtAuthzHttp:
            service: "authservice.istio-system.svc.cluster.local"
            port: "8080"
            includeRequestHeadersInCheck: ["authorization", "cookie", "x-auth-token"]
            headersToUpstreamOnAllow: ["kubeflow-userid"]
```



[AuthorizationPolicy](https://istio.io/latest/docs/reference/config/security/authorization-policy/)

```
$ vi authorizationpolicy.yaml
```

```
apiVersion: security.istio.io/v1beta1
kind: AuthorizationPolicy
metadata:
  name: dex-auth
  namespace: istio-system
spec:
  selector:
    matchLabels:
      istio: ingressgateway
  action: CUSTOM
  provider:
    # The provider name must match the extension provider defined in the mesh config.
    name: dex-auth-provider
  rules:
  # The rules specify when to trigger the external authorizer.
  - to:
    - operation:
        notPaths: ["/v1*"]
```

> - `action: CUSTOM`:  `-n istio-system`의 `configmap` 에서 설정한  `dex-auth-provider`애 의해 차단 설정을 구축하기 위해선 `CUSTOM` 선택  
> - `name: dex-auth-provider`:  `-n istio-system`의 `configmap` 에서 설정한  `extensionProviders`의 이름과 같아야 한다.
> - `notPaths: ["/v1*"]`: `/v1` 로 시작하는 route제외 전부 차단

```
$ kubectl apply -f authorizationpolicy.yaml 
```



이후 `authn-filter` 삭제

```
$ kubectl delete -n istio-system envoyfilters.networking.istio.io authn-filter
```

```
$ kubectl rollout restart deployment/istiod -n istio-system
```



> ```
> $ kubectl delete -n istio-system AuthorizationPolicy dex-auth
> ```



TODO: 실패



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

