# kubectl

kubenetes에서 cluster 조작은 모두 kubenetes master의 API를 통해 이루어진다. 직접 API에 요청을 보내거나 클라이언트 라이브러리를 사용하여 cluster를 조작할 수도 있지만, 수동으로 조작하는 경우에는 CLI 도구인 kubectl을 사용하는 것이 일반적이다.



kubectl이 kubenetes master와 통신할 때는 접속 대상의 서버 정보, 인증 정보 등이 필요하다. kubectl은 kubecofig(기본 위치는 ~/.kube/config)에 쓰여 있는 정보를 사용하여 접속한다. 

> kubeconfig도 manifest와 동일한 형식으로 작성된다.

kubeconfig에서 구체적으로 설정이 이루어지는 부분은 clusters, users, contexts 세 가지다. 이 세 가지 설정 항목은 모두 배열로 되어 있어 여러 대상을 등록할 수 있다.





#### install 

1. WSL설치

2. Docker Desktop for windows설치

3. Docker Desktop for windows의 preference에서 kubernetes에

   Enable Kubernetes 선택 (활성화)

   > 왼쪽 하단에 docker running과 kubenetes running이 떠야 한다.

4. kubectl 설치

   **직접 설치**

   - windows
   
     ```
     $ curl -LO "https://dl.k8s.io/release/v1.22.0/bin/windows/amd64/kubectl.exe"
     ```

     설치됐는지 버전 확인
   
     ```
     $ kubectl version --client
     ```
   
     




### initial

- 컨텍스트 전환(local에서 kind사용시)

  여러 kubernetes를 사용하는 경우에는 kubectl의 컨텍스트를 전환하여 사용해야 한다.

  ```
  $ kubectl config use-context docker-desktop
  ```

  위 명령어로 컨텍스트를 전환한 후에는 kubectl을 사용하여 Docker Desktop Cluster를 조작할 수 있다.



- 노드 확인

  ```
  $ kubectl get nodes
  ```

  kubectl에서는 local mashin에 기동 중인 docker host를 kubernetes node로 인식한다.



- component 확인

  Docker Desktop for windows의 preference에서 kubernetes에

  `Enable Kubernetes` 선택 (활성화)할 때 `show system container(advanced)`를 선택하면 `docker container ls`명령어로 구성 요소를 확인할 수 있다.

  ```
  $ docker container ls
  ```

  

### command

**get**

target으로 한 정보의 목록을 가져온다.

```
$ kubectl get pod
```

> 예시 : pod목록 가져옴
