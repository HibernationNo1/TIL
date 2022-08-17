{:toc}



# centOS



**check Hardware information**

- check cpu

  ```
  $ lscpu
  ```

  

- check hardware

  ```
  $ lshw
  ```

  

- check RAM

  ```
  $ free -m
  ```

  

- GPU info

  ```
  $ sudo lshw -C display
  ```

  or

  ```
  $ lspci | grep VGA
  ```

  



## install



### curl, vim

```
$ sudo yum install -y curl vim
```



### git

```
$ sudo yum install git
$ git --version
```





### anaconda

[여기](https://repo.anaconda.com/archive/) 에서 아래 버전 선택해서 다운

[Anaconda3-2021.05-Linux-x86_64.sh](https://repo.anaconda.com/archive/Anaconda3-2021.05-Linux-x86_64.sh)

- download 

  ```
  $ wget https://repo.anaconda.com/archive/Anaconda3-2021.05-Linux-x86_64.sh
  ```

  > 년도에 따라 version 알맞게 사용. 	21.05가 현재까진 범용적

- start install process

  ```
  $ sudo bash Anaconda3-2021.05-Linux-x86_64.sh
  ```

  ```
  Please, press ENTER to continue
  >>> 
  뜨면 Enter하고 다 읽어내린 후 
  ```

  ```
  Do you accept the license terms? [yes|no]
  Please answer 'yes' or 'no':'
  >>> 
  뜨면 yes 입력 후 Enter
  ```

  ```
  Anaconda3 will now be installed into this location:
  /home/hibernation/anaconda3
  
    - Press ENTER to confirm the location
    - Press CTRL-C to abort the installation
    - Or specify a different location below
  
  [/home/{user_name}/anaconda3] >>> 		/home/ainsoft/anaconda3
  뜨면 새롭게 만들 directory의 name을 입력 (걍 anaconda3으로 )
  # 이 때 입력 후 바로 뜨는 문구 `PREFIX=/home/ainsoft/anaconda3` 를 아래 기억★★★
  # 만약 [/root/anaconda3] >>>  으로 뜨면 root에 설치된다는 뜻이지
  # [/root/anaconda3] >>> 		/home/ainsoft/anaconda3
  # 으로 입력
  ```

  ```
  Do you wish the installer to initialize Anaconda3
  by running conda init? [yes|no]
  
  no를 입력하면 콘다는 쉘 스크립트를 수정하지 못한다. yes를 누른다
  ```

- path추가

  ```
  $ sudo vi ~/.bashrc
  ```

  text 편집기가 열리면 맨 아래줄에 추가

  ```
  export PATH=/home/ainsoft/ananconda3/bin:$PATH
  ```

  > 위 설치 도중 만났던 PREFIX값에 + '/bin:$PATH'    

  ```
  $ export PATH=~/anaconda3/bin:$PATH
  ```

  

- 설치 확인

  bashrc 실행

  ```
  $ sudo source ~/.bashrc
  ```

  > (base)뜨는지 확인
  >
  > 안뜨면 `conda init`을 해야 함 (그 전에 `conda -V`을 통해 `conda : command not found` 가 뜨는지 확인)
  >
  > ```
  > $ conda init bash
  > ```
  >
  > bash사용
  >
  > > (base) 없애려면 ` $ conda deactivate`

  check version

  ```
  $ conda -V 
  ```

  > 만일 `conda : command not found` 가 뜨면



### docker

[공식 문서](https://docs.docker.com/engine/install/centos/)

1. Set up the repository

   ```
   $ sudo yum install -y yum-utils
   ```

   ```
   $ sudo yum-config-manager \
       --add-repo \
       https://download.docker.com/linux/centos/docker-ce.repo
   ```

   

2. Install Docker Engine

   ```
   $ sudo yum install docker-ce docker-ce-cli containerd.io docker-compose-plugin
   ```

   

3. check

   start docker

   ```
   $ sudo systemctl start docker
   ```

   docker run

   ```
   $ sudo docker run hello-world
   ```



### kubernetes

[공식](https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/install-kubeadm/)에는 설명이 이상하게 되어있음. [여기](https://www.hostafrica.co.za/blog/new-technologies/install-kubernetes-delpoy-cluster-centos-7/) 들어가보기

#### Prerequisites

1. **check required ports**

   1. listen중인 port확인

      ```
      $ netstat -tnlp
      ```

   2. 방화벽 상태 확인

      ```
      $ firewall-cmd --state
      ```

      > `FirewallD is not running` 뜰 경우
      >
      > ```
      > $ systemctl start firewalld
      > ```

   3. 6443port허용

      ```
      $ sudo firewall-cmd --permanent --zone=public --add-port=6443/tcp
      ```

      ```
      $ sudo firewall-cmd --reload
      ```

   4. check 

      firewall확인

      ```
      firewall-cmd --list-all
      ```

      

      6443에 신호 보내기

      ```
      $ nc --listen --source-port 6443
      ```

      

      new terminal에서 

      ```
      $ netstat -tnlp
      ```

      또는 

      ```
      $ netstat -nap | grep 6443
      ```

      

   > port닫을땐
   >
   > ```
   > $ sudo firewall-cmd --permanent --zone=public --remove-port=6443/tcp
   > ```
   >
   > 
   >
   > firewall stop
   >
   > ```
   > $ systemctl stop firewalld
   > ```

2. **[install docker](#docker)**

   ```
   $ sudo systemctl start docker
   $ sudo systemctl status docker
   ```

   ![](https://www.hostafrica.co.za/blog/wp-content/uploads/2020/05/How-to-Install-Docker-on-Linux-and-Windows_html_m4671b902.png)

3. **Set up the Kubernetes Repository**

   kubenetes package는 공식 CentOS 7 repository가 없기 때문에 새 repo file을 추가해야 한다. 

   ```
   $ sudo vi /etc/yum.repos.d/kubernetes.repo
   ```

   ```
   [kubernetes]
   name=Kubernetes
   baseurl=https://packages.cloud.google.com/yum/repos/kubernetes-el7-x86_64
   enabled=1
   gpgcheck=1
   repo_gpgcheck=0
   gpgkey=https://packages.cloud.google.com/yum/doc/yum-key.gpg https://packages.cloud.google.com/yum/doc/rpm-package-key.gpg
   ```

4. **install kubelet**

   ```
   $ sudo yum install -y kubelet
   ```

   ```
   ...
   
   Complete!
   ```

   

   ```
   $ systemctl enable kubelet.service
   ```

   

5. **install kubeadm**

   Note that **kubeadm** automatically installs **kubectl** as a dependency

   ```
   $ sudo yum install -y kubeadm
   ```

   ```
   ...
   
   Complete!
   ```

   

   check

   ```
   $ kubeadm version
   $ kubectl version --short
   $ kubelet version
   ```

6. **Set hostnames**

   master node위에서 hostname을 set

   ```
   $ sudo hostnamectl set-hostname {master-node-name}
   ```

   - master node가 아니더라도 node이름은 위 명령어로 set가능

   

   */etc/hosts* 에 worker node의 hostnames을 추가

   ```
   root# cat <<EOF>> /etc/hosts
   10.168.10.207 master-node
   10.168.10.208 node1 W-node1
   10.168.10.209 node2 W-node2
   EOF
   ```

   > 또는
   >
   > ```
   > $ sudo vi /etc/hosts 
   > ```
   >
   > 아래 문구 추가
   >
   > ```
   > 10.168.10.207 master-node
   > 10.168.10.208 node1 W-node1
   > 10.168.10.209 node2 W-node2
   > ```

   

7. **Disable SElinux**

   container가 file system에 access할 수 있도록 하려면 SElinux를 "permissive"(허용) 모드를 활성화 해야 됨

   ```
   $ sudo setenforce 0
   ```

   > `setenforce: SELinux is disabled` 라고 뜨면 이미 적용된거

   ```
   $ sudo sed -i --follow-symlinks 's/SELINUX=enforcing/SELINUX=disabled/g' /etc/sysconfig/selinux
   ```

   다시시작 필요

   ```
   $ reboot
   ```

8. **Add firewall rules**(open port)

   pod, container및 VM간의 원활한 통신을 허용하려면 master node의 방화벽에 규칙을 추가해야 함

   check firewall 

   ```
   $ firewall-cmd --state
   ```

   - `not running` 뜨면 

     ```
     $ systemctl start firewalld
     ```

     

   ```
   $ sudo firewall-cmd --permanent --add-port=6443/tcp
   $ sudo firewall-cmd --permanent --add-port=2379-2380/tcp
   $ sudo firewall-cmd --permanent --add-port=10250/tcp
   $ sudo firewall-cmd --permanent --add-port=10251/tcp
   $ sudo firewall-cmd --permanent --add-port=10252/tcp
   $ sudo firewall-cmd --permanent --add-port=10255/tcp
   $ sudo firewall-cmd –reload
   ```

   > 각각의 worker node에서 아래 명령어 실행
   >
   > ```
   > $ sudo firewall-cmd --permanent --add-port=10251/tcp
   > $ sudo firewall-cmd --permanent --add-port=10255/tcp
   > $ sudo firewall-cmd –reload
   > ```

   check 

   ```
   $ firewall-cmd --list-all
   ```

   

9. **Update iptables config**

   ```
   root# cat <<EOF > /etc/sysctl.d/k8s.conf
   net.bridge.bridge-nf-call-ip6tables = 1
   net.bridge.bridge-nf-call-iptables = 1
   EOF
   ```

   > 또는
   >
   > ```
   > $ sudo vi /etc/sysctl.d/k8s.conf
   > ```
   >
   > 아래 문구 추가
   >
   > ```
   > net.bridge.bridge-nf-call-ip6tables = 1
   > net.bridge.bridge-nf-call-iptables = 1
   > ```

   ```
   $ sudo sysctl --system
   ```

   아래 출력 확인

   ```
   * Applying /usr/lib/sysctl.d/00-system.conf ...
   * Applying /usr/lib/sysctl.d/10-default-yama-scope.conf ...
   kernel.yama.ptrace_scope = 0
   * Applying /usr/lib/sysctl.d/50-default.conf ...
   kernel.sysrq = 16
   kernel.core_uses_pid = 1
   kernel.kptr_restrict = 1
   net.ipv4.conf.default.rp_filter = 1
   net.ipv4.conf.all.rp_filter = 1
   net.ipv4.conf.default.accept_source_route = 0
   net.ipv4.conf.all.accept_source_route = 0
   net.ipv4.conf.default.promote_secondaries = 1
   net.ipv4.conf.all.promote_secondaries = 1
   fs.protected_hardlinks = 1
   fs.protected_symlinks = 1
   * Applying /usr/lib/sysctl.d/60-libvirtd.conf ...
   fs.aio-max-nr = 1048576
   * Applying /etc/sysctl.d/99-sysctl.conf ...
   * Applying /etc/sysctl.d/k8s.conf ...
   * Applying /etc/sysctl.conf ...
   ```

10. **Disable swap**

     kubelet이 작동하려면 모든 VM에서 swap을 꺼야함

    ```
    $ sudo sed -i '/swap/d' /etc/fstab
    ```

    ```
    $ swapoff -a
    ```

    

11. **set cgroupdriver of docker**

    check kubelet Cgroup Driver

    ```
    $ systemctl status kubelet
    ```

    ```
    Cgroup Driver: systemd
    ```

    출력 중 윗 문구 찾아서 확인 (`cgroupfs` or `systemd`)

    

    ```
    $ sudo vi /etc/docker/daemon.json
    ```

    ```
    {
    "exec-opts": ["native.cgroupdriver=systemd"],
    "log-driver": "json-file",
    "log-opts": {
    "max-size": "100m"
    },
    "storage-driver": "overlay2"
    }
    ```

    ````
    $ sudo systemctl restart docker
    $ sudo systemctl restart kubelet
    ````

    `["native.cgroupdriver=systemd"]` 부분이 `cgroupfs` or `systemd`

    check

    ```
    $ sudo docker info | grep -i cgroup
    ```

    ```
    Cgroup Driver: cgroupfs
     Cgroup Version: 1
    ```

    

    ```
    $ systemctl status kubelet
    ```

    



#### Deploying a Kubernetes Cluster

1. **kubeadm initialization**

   ```
   $ sudo kubeadm init
   ```

   > error
   >
   > - `[ERROR CRI]` 발생 시
   >
   >   ```
   >   $ sudo rm /etc/containerd/config.toml
   >   $ sudo systemctl restart containerd
   >   $ sudo kubeadm init
   >   ```
   >
   > - `[ERROR FileContent--proc-sys-net-bridge-bridge-nf-call-iptables]` 발생 시
   >
   >   ```
   >   $ sudo modprobe br_netfilter 
   >   $ echo '1'>/proc/sys/net/bridge/bridge-nf-call-iptable
   >   ```

   아래와 같은 출력 확인

   ```
   ... 생략
   
   You should now deploy a pod network to the cluster.
   Run "kubectl apply -f [podnetwork].yaml" with one of the options listed at:
     https://kubernetes.io/docs/concepts/cluster-administration/addons/
   
   Then you can join any number of worker nodes by running the following on each as root:
   
   
   kubeadm join 192.168.20.11:6443 --token wlugbp.qdy05bz7n3lhyzrk \
           --discovery-token-ca-cert-hash sha256:2d53e5f606bd03d90fd13fe561bd63462f54b5ea52685b10f5377a9e4830b633
   ```

   위 출력을 통해 알 수 있는 것

   - pod 배포 명령어 

     ```
     $ kubectl apply -f [podnetwork].yaml
     ```

   - node 추가 명령어

     ```
     $ sudo kubeadm join 192.168.20.11:6443 --token wlugbp.qdy05bz7n3lhyzrk \
             --discovery-token-ca-cert-hash sha256:2d53e5f606bd03d90fd13fe561bd63462f54b5ea52685b10f5377a9e4830b633
     ```

     node 추가 명령어 다시 확인

     ```
     $ sudo kubeadm token create --print-join-command
     ```

     

2. **Create required directories and start managing Kubernetes cluster**

   cluster를 관리하기 위해서 dir을 생성하고 소유권을 결정해야 한다.

   아래 명령어는 `$ sudo kubeadm init` 을 입력했을 때 나온 출력에 포함되어 있음

   ```
   $ mkdir -p $HOME/.kube
   ```

   ```
   $ sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
   $ sudo chown $(id -u):$(id -g) $HOME/.kube/config
   ```

   ```
   $ export KUBECONFIG=$HOST/.kube/config
   ```

   

3. **Set up Pod network for the Cluster**

   cluster 내의 pod는 pod network를 통해 연결된다. (아직 작동 안함)

   아래 명령어를 통해 연결

   ```
   $ kubectl get nodes
   ```

   ```
   NAME          STATUS     ROLES           AGE   VERSION
   master-node   NotReady   control-plane   44m   v1.24.3
   ```

   위 출력을 보면 `STATUS`가 `NotReady`임을 확인할 수 있다.

   아래 명령어 실행 kubectl version --short

   ```
   $ export kubever=$(kubectl version | base64 | tr -d '\n')
   $ kubectl apply -f https://cloud.weave.works/k8s/net?k8s-version=$kubever
   ```

   ```
   serviceaccount/weave-net created
   clusterrole.rbac.authorization.k8s.io/weave-net created
   clusterrolebinding.rbac.authorization.k8s.io/weave-net created
   role.rbac.authorization.k8s.io/weave-net created
   rolebinding.rbac.authorization.k8s.io/weave-net created
   daemonset.apps/weave-net created
   ```

   

   출력 확인

   ```
   $ kubectl get nodes
   ```

   ```
   NAME          STATUS   ROLES           AGE   VERSION
   master-node   Ready    control-plane   58m   v1.24.3
   ```

   

   ```
   $ kubectl get pods --all-namespaces
   ```

   ```
   NAMESPACE     NAME                                  READY   STATUS    RESTARTS      AGE
   kube-system   coredns-6d4b75cb6d-5b64n              1/1     Running   0             58m
   kube-system   coredns-6d4b75cb6d-rzksb              1/1     Running   0             58m
   kube-system   etcd-master-node                      1/1     Running   0             58m
   kube-system   kube-apiserver-master-node            1/1     Running   0             58m
   kube-system   kube-controller-manager-master-node   1/1     Running   0             58m
   kube-system   kube-proxy-s6nbf                      1/1     Running   0             58m
   kube-system   kube-scheduler-master-node            1/1     Running   0             58m
   kube-system   weave-net-s9kgz                       2/2     Running   1 (19s ago)   28s
   
   ```

   

4. **Add nodes to your cluster**

   ```
   $ sudo kubeadm join 192.168.20.11:6443 --token 0crivb.i4exs4wsem5punrk \
           --discovery-token-ca-cert-hash sha256:2968a61e92db2c1b51e5e2f622a2dbf44363d80bd7a7e7871ca4b34bcbfc3c3a
   
   ```

   > error 
   >
   > `[ERROR FileAvailable--etc-kubernetes-kubelet.conf]`
   >
   > ```
   > $ sudo kubeadm reset
   > ```
   >
   > 후 다시 `sudo kubeadm join ...`



```
error execution phase preflight: couldn't validate the identity of the API Server: Get "https://192.168.20.11:6443/api/v1/namespaces/kube-public/configmaps/cluster-info?timeout=10s": dial tcp 192.168.20.11:6443: connect: connection refused

```



```
$ kubectl describe pod/kube-apiserver-master-node -n kube-system
```

```
The connection to the server 192.168.20.11:6443 was refused - did you specify the right host or port?
```







