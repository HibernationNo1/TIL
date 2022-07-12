# Kubernetes install

## Install

#### minikube

- minikube

  [공식](https://minikube.sigs.k8s.io/docs/start/)

  CPU 2core 이상, Memory 2GB이상, Disk : 20GB이상

  ```
  $ curl -LO https://storage.googleapis.com/minikube/releases/latest/minikube-linux-amd64
  $ sudo install minikube-linux-amd64 /usr/local/bin/minikube
  ```

  check

  ```
  $ minikube version
  ```

- kubectl

  [공식](https://kubernetes.io/ko/docs/tasks/tools/install-kubectl-linux/)

  최신 릴리스 다운로드

  ```
  $ curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl"
  ```

  바이너리 검증

  ```
  $ curl -LO "https://dl.k8s.io/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl.sha256"
  $ echo "$(<kubectl.sha256)  kubectl" | sha256sum --check
  ```

  > 검증 성공시 아래처럼 출력
  >
  > ```
  > kubectl: OK
  > ```

  install kubectl

  ```
  $ sudo install -o root -g root -m 0755 kubectl /usr/local/bin/kubectl
  ```

  check

  ```
  $ kubectl version --client
  ```

  > ```
  > Client Version: version.Info{Major:"1", Minor:"24", GitVersion:"v1.24.2", GitCommit:"f66044f4361b9f1f96f0053dd46cb7dce5e990a8", GitTreeState:"clean", BuildDate:"2022-06-15T14:22:29Z", GoVersion:"go1.18.3", Compiler:"gc", Platform:"linux/amd64"}
  > ```
  >
  > 위 처럼 떠도 정상 (kubenetes server와 client의 version이 모두 출력하는 과정에서, host에서 kubenetes server를 생성하지 않았기 때문에 뜨는 문구)
  >
  > 이를 해결하기 위해 minukube 를 실행하여 kubenetes server를 설치

- kubenetes server

  ```
  $ minikube start --driver=docker
  ```

  check

  ```
  $ minikube status
  ```

  ```
  minikube
  type: Control Plane
  host: Running
  kubelet: Running
  apiserver: Running
  kubeconfig: Configured
  ```

  여기서 다시 아래 명령어를 입력하면

  ```
  $ kubectl version 
  ```

  ```
  Client Version: version.Info{Major:"1", Minor:"24", GitVersion:"v1.24.2", GitCommit:"f66044f4361b9f1f96f0053dd46cb7dce5e990a8", GitTreeState:"clean", BuildDate:"2022-06-15T14:22:29Z", GoVersion:"go1.18.3", Compiler:"gc", Platform:"linux/amd64"}
  Kustomize Version: v4.5.4
  Server Version: version.Info{Major:"1", Minor:"24", GitVersion:"v1.24.1", GitCommit:"3ddd0f45aa91e2f30c70734b175631bec5b5825a", GitTreeState:"clean", BuildDate:"2022-05-24T12:18:48Z", GoVersion:"go1.18.2", Compiler:"gc", Platform:"linux/amd64"}
  
  ```

  minikube 내부에 default로 생성되는 pod들이 정상적으로 생성됐는지 확인

  ```
  $ kubectl get pod -n kube-system
  ```

   

- uninstall

  ```
  $ minikube stop
  $ minikube delete
  $ minikube delete --all
  ```
  
  



