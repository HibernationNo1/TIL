[TOC]



### Install

#### windows

1. install WSL2 setup + Ubuntu

2. install docker desktop

3. docker desktop에서 kubernetes사용
   
   1. 설정에서 Enable Kubernetes를 체크
   
   2. Resources에서 CPU, memory등을 설정
      
      > CPU 8개, momry는 최소한 12GB, Disk image size도 충분히
      
      설정 후 apply & restart
      
      > kubernetes실행되는지 확인

4. install kfctl (windows)
   
   ```
   $ wsl bash  
   ```
   
   > windows라면 WSL2를 설치 후 위 명령어로 linux사용
   
   ```
   $ wget https://github.com/kubeflow/kfctl/releases/download/v1.2.0/kfctl_v1.2.0-0-gbc038f9_linux.tar.gz
   $ tar -xvf kfctl_v1.2.0-0-gbc038f9_linux.tar.gz
   $ export PATH=$PATH:$PWD
   ```
   
   확인
   
   ```
   $ kfctl version
   ```

5. download `kfctl_istio_dex.v1.2.0.yaml`
   
   ```
   $ mkdir kubeflow
   $ cd kubeflow/
   $ export CONFIG_URI="https://raw.githubusercontent.com/kubeflow/manifests/v1.2-branch/kfdef/kfctl_istio_dex.v1.2.0.yaml"
   $ wget -O kfctl_istio_dex.yaml $CONFIG_URI
   ```
   
   ```
   $ ls
   ```
   
   > `kfctl_istio_dex.yaml`

6. kubeflow cluster 배포
   
   ```
   $ kfctl apply -f kfctl_istio_dex.yaml -V
   ```
   
   확인(pods)
   
   ```
   $ kubectl get pods -n istio-system
   ```
   
   ```
   $ kubectl get pods -n kubeflow
   ```
   
   > kubeflow라는 namespace의 pods를 볼 수 있다.



#### linux



### dashboard

```
$ kubectl port-forward svc/istio-ingressgateway -n istio-system 8080:80
```

> port : 80 에 연결된 `istio-ingressgateway` 라는 서비스에 local의 8080을 mapping한다. 
>
> `istio-system` 는 name space

이러고 `localhost:8080` 하면 504에서 뜸. 여기서부터 해결할 것.
