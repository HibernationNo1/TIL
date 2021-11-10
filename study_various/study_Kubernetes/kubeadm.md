# kubeadm

#### Install

kubelet, kubeadm, kubectl 한 번에 설치

1. 필요한 의존 package 설치

   ```
   $ sudo apt update && sudo apt install -y apt-transport-https curl
   ```

2. 저장소 등록 및 업데이트

   ```
   $ curl -s http://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add -
   ```

   ```
   $ cat << E0F | sudo tee /etc/apt/sources.list.d/kubernetes.list
   > deb http://apt.kubernetes.io/ kubernetes-xenial main
   > E0F
   ```

   ```
   $ sudo apt update
   ```

3. kubernetes관련 package 설치

   ```
   $ sudo apt install -y kubelet=1.18.15-00 kubeadm=1.18.15-00 kubectl=1.18.15-00
   ```



> 오버레이 네트워크용 kernel parameter 변경
>
> ```
> $ cat << E0F | sudo tee /etc/sysctl.d/k8s.conf
> net.bridge.gridge-nf-call-ip6tables = 1
> net.bridge.bridge-nf-call-iptables = 
> net.ipv4.ip_forward = 1
> E0F
> $ sudo sysctl --system
> ```



#### master node 구축

kubeadm 초기화를 하면 그게 곧 kubernetes master node이다.

```
$ sudo swapoff -a  # 일시적 비활성화
```

> 사전에 swap이 비활성화 되어 있어야 한다. 

```
$ sudo kubeadm init \
--kubernetes-version=1.18.15 \
--pod-network-cidr=172.31.0.0./16
```

> `--kubernetes-version=1.18.15` : master node의 kunernetes version설정
>
> `--pod-network-cidr` : cluster 내부 네트워크(pod 네트워크)용으로 플라넬을 사용하기 위한 설정

#### worker node 구축

kubernetes master설정이 성공하면 node가 될 node에서 실행해야 할 명령어가 출력되고, 그 명령어를 node가 될 머신에서 실행한다. (kubernetes node를 여러 대 추가할 경우 각 node에서 이 명령어를 실행하면 된다.)

- 예시

  ```
  $ sudo kebeadm join 172.31.2.189:6443 --token zpn...
  ```

  > kebernetes node위에서 실행



##### 인증용 파일 copy



이제 각 node에 master/worker node로 필요한 kubernetes process가 모두 기동중인 상태다. 

multi node kubernetes cluster는 여기에서 서로 다른 node에 배포된 pod간 통신이 되는 것을 의미한다.

> multi node kubernetes cluster는 p.73