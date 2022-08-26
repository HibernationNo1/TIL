# minikube



### install

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

- kubenetes start

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





### start

#### driver

##### docker

docker container기반 kubernetes cluster node

GPU passthrouh를 지원하지 않음

```
$ minikube start --driver=docker \
--cpus='4' --memory='20g' \
--kubernetes-version=v1.19.3 
```

- `--cpus` : cluster에 할당할 cpu의 개수
- `--memory` : cluster에 할당할 memory의 크기
- `--kubernetes-version` : kubernetes명시







##### kvm2



##### None

VM을 생성하지 않고 host의 정보를 이용한다.

`--cpus` , `--memory` , `--profile`등의 flag를 지원하지 않는다.

```
$ minikube start --driver=none \
  --kubernetes-version=v1.19.3 
```



### GPU

1. **install NVIDIA driver**

   check

   ```
   $ nvidia-smi
   ```

    

2. **install NVIDIA-docker**

   1. Setting up NVIDIA Container Toolkit

      ```
      $ distribution=$(. /etc/os-release;echo $ID$VERSION_ID) \
            && curl -fsSL https://nvidia.github.io/libnvidia-container/gpgkey | sudo gpg --dearmor -o /usr/share/keyrings/nvidia-container-toolkit-keyring.gpg \
            && curl -s -L https://nvidia.github.io/libnvidia-container/$distribution/libnvidia-container.list | \
                  sed 's#deb https://#deb [signed-by=/usr/share/keyrings/nvidia-container-toolkit-keyring.gpg] https://#g' | \
                  sudo tee /etc/apt/sources.list.d/nvidia-container-toolkit.list
      ```

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

      

      check : 기본 CUDA container 실행

      ```
      $ sudo docker run --rm --gpus all nvidia/cuda:10.1-devel-ubuntu18.04 nvidia-smi
      ```

      > cuda와 ubuntu version에 대한tag는 [docker hub-nvidia](https://hub.docker.com/r/nvidia/cuda/tags)에서 검색 후 결정

   4. edit daemon

      ```
      $ sudo vi /etc/docker/daemon.json
      ```

      아래처럼 변경

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


   

3. **start minikube**

   ```
   $ minikube start --driver=none \
     --kubernetes-version=v1.19.3  \
     --extra-config=apiserver.service-account-signing-key-file=/var/lib/minikube/certs/sa.key \
     --extra-config=apiserver.service-account-issuer=kubernetes.default.svc
   ```

   - `--extra-config=apiserver.service-account-signing-key-file=/var/lib/minikube/certs/sa.key` : kubeflow를 사용하기 위한 flag
   - `--extra-config=apiserver.service-account-issuer=kubernetes.default.svc`  : kubeflow를 사용하기 위한 flag

   > error
   >
   > ```
   > Exiting due to HOST_JUJU_LOCK_PERMISSION: Failed to save config: failed to acquire lock for /home/ainsoft/.minikube/profiles/minikube/config.json: {Name:mk2998bbe62a1ef4b160001f97b8d3cac88d028d Clock:{} Delay:500ms Timeout:1m0s Cancel:<nil>}: unable to open /tmp/juju-mk2998bbe62a1ef4b160001f97b8d3cac88d028d: permission denied
   > ```
   >
   > 해결방법 
   >
   > ```
   > $ sudo rm -rf /tmp/juju-mk*
   > $ sudo rm -rf /tmp/minikube.*
   > ```

   

   check

   ```
   $ kubectl get namespace
   ```

   > error
   >
   > ```
   > error: unable to read client-key /home/ainsoft/.minikube/profiles/minikube/client.key for minikube due to open /home/ainsoft/.minikube/profiles/minikube/client.key: permission denied
   > ```
   >
   > 해결방법 : 권한 설정
   >
   > ```
   > sudo chown -R $HOME/.minikube
   > ```
   >
   > 이래도 안되면
   >
   > ```
   > sudo chown -R $USER $HOME/.kube
   > ```
   >
   > 도 추가

   ```
   kubectl get pods -A
   ```

   

4. **install nvidia-device-plugin**

   ```
   $ kubectl create -f https://raw.githubusercontent.com/NVIDIA/k8s-device-plugin/master/nvidia-device-plugin.yml
   ```

   

   check

   ```
   $ kubectl get pod -A | grep nvidia
   ```

   > ```
   > kube-system   nvidia-device-plugin-daemonset-rs69d   1/1     Running   0          48s
   > ```

   

   ```
   $ kubectl get nodes "-o=custom-columns=NAME:.metadata.name,GPU:.status.allocatable.nvidia\.com/gpu"
   ```

   > ```
   > NAME     GPU
   > ubuntu   1
   > ```
   >
   > 위 처럼 1이 보여야 한다.

5. check use GPU at pod

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
       image: nvidia/cuda:10.2-runtime
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
   ```

   ```
   Thu Aug 25 00:45:45 2022       
   +-----------------------------------------------------------------------------+
   | NVIDIA-SMI 440.33.01    Driver Version: 440.33.01    CUDA Version: 10.2     |
   |-------------------------------+----------------------+----------------------+
   | GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
   | Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
   |===============================+======================+======================|
   |   0  GeForce RTX 208...  On   | 00000000:01:00.0 Off |                  N/A |
   |  0%   40C    P8    12W / 300W |   2672MiB / 11019MiB |      0%      Default |
   +-------------------------------+----------------------+----------------------+
                                                                                  
   +-----------------------------------------------------------------------------+
   | Processes:                                                       GPU Memory |
   |  GPU       PID   Type   Process name                             Usage      |
   |=============================================================================|
   +-----------------------------------------------------------------------------+
   ```

   





### command

#### profile list

해당 PC(node)에 몇 개의 profile(cluster)가 생성되어 있는지 확인할 수 있다.

```
$ minikube profile list
```



#### delete

profile(cluster)를 삭제

```
$ minikube delete -p {profile_name}
```



#### status

```
$ minikube status
```



#### addons list

addon의 list를 보여준다.

```
$ minikube addons list
```



- disable addons : 사용하지 않은  addon을 비활성화

  ```
  $ minikube addons disable storage-provisioner
  $ minikube addons disable default-storageclass
  ```

  > 예시