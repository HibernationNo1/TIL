# Node

Helm은 Kubernetes 애플리케이션의 패키지 매니저로, 애플리케이션의 설치와 관리를 단순화하는 도구이다.

Helm을 사용하면 애플리케이션의 모든 부분을 하나의 단위로 처리할 수 있는 **차트**라고 하는 패키지 형식을 사용하여 여러 Kubernetes 리소스(Deployment, Service, ConfigMap 등)를 한번에 정의, 설치, 업그레이드 할 수 있다.

- **chart**: 헬름 패키지로, 애플리케이션을 실행하는데 필요한 모든 리소스 정의 파일들을 포함한 단위.

- **release**: 차트의 인스턴스로, 실제로 클러스터에서 실행되는 차트의 이름.

- **repository**: 차트를 저장하는 장소로, Helm이 차트를 검색하거나 설치할 수 있는 URL을 제공. 

  docker hub와 비슷하게, 다양한 차트가 있다. 

  가장 많이 사용되는 repo: [artifacthub](https://artifacthub.io/)

Helm은 복잡한 Kubernetes 애플리케이션을 더 쉽게 관리하고, 구성 요소들을 일관된 방식으로 배포할 수 있게 도와준다. 예를 들어, 개발 환경과 프로덕션 환경의 설정을 분리하여 관리할 수 있고, 애플리케이션을 업그레이드하거나 롤백하는 작업을 간편하게 처리할 수 있다.



- Helm은 어디세 설치하는가?

  Helm은 Kubernetes 클러스터와 통신하여 애플리케이션을 배포하고 관리하는 도구이기 때문에, Helm 자체는 Kubernetes 클러스터의 어떤 노드에도 설치되지 않고, 사용자의 로컬 머신이나 CI/CD 파이프라인과 같은 외부 시스템에 설치하여 사용한다. 

  Helm 클라이언트는 Kubernetes API 서버와 통신하여 차트를 클러스터에 설치하고 관리한다. 



### install 

helm 설치

```
$ curl https://raw.githubusercontent.com/helm/helm/main/scripts/get-helm-3 | bash
```

확인

```
$ helm version
```

```
version.BuildInfo{Version:"v3.14.4", GitCommit:"81c902a123462fd4052bc5e9aa9c513c4c8fc142", GitTreeState:"clean", GoVersion:"go1.21.9"}
```





### kube-prometheus-stack

kube-prometheus-stack 을 helm을 이용해서 설치

1. Helm 저장소 추가 및 Helm 저장소 목록 업데이트

   ```
   $ helm repo add prometheus-community https://prometheus-community.github.io/helm-charts
   $ helm repo update
   ```

2. Helm 차트 설치 (version: 60.2.0)

   - 바로 install

     helm install을 할 경우 chart의 template을 kubernetes manifest로 바로 렌더링하며, 렌더링된 manifest를 cluster에 적용하여 resource를 생성한다.

     즉, 자동으로 resource들을 배포하는 것이다.

     ```
     $ helm install {release_name} prometheus-community/kube-prometheus-stack --version 60.2.0
     ```

   - **pull**

     차트를 설치하지 않고, 차트의 내용을 수정하거나 템플릿을 미리 확인하고자 할 때 유용하다.

     customizing을 할 경우에는 pull을 하자.

     1. ```
        $ helm pull prometheus-community/kube-prometheus-stack --version 60.2.0
        ```

     2. 압축해제

        ```
        $ tar xvfz kube-prometheus-stack-60.2.0.tgz
        ```

     3. 설정 수정

        - prometheus 설정 수정

          values.yaml 내부에 내용을 수정한다.

          ```
          $ vi kube-prometheus-stack/values.yaml 
          ```

        - grafana 설정 수정

          ```
          $ vi kube-prometheus-stack/charts/grafana/values.yaml 
          ```

     4. 수정된 menifest 배포

        namespace 생성 후 배포

        ```
        $ kubectl create namespace monitoring
        ```

        ```
        $ helm install test-prometheus ./kube-prometheus-stack -n monitoring
        ```

        

3. kube-prometheus-stack 관련 pod가 제대로 배포되었는지 확인

   ```
   $ kubectl -n monitoring get pods
   $ kubectl get svc -n monitoring
   ```

4. 만일 설정파일을 수정했다면 재배포

   ```
   $ helm upgrade test-prometheus ./kube-prometheus-stack --namespace monitoring
   ```

   

5. 만일 삭제가 필요하면

   ```
   $ helm uninstall test-prometheus --namespace monitoring
   ```



grafana pod의 인터넷 연결 안됨