# Kubernetes Dashboard



#### install

[공식](https://kubernetes.io/ko/docs/tasks/access-application-cluster/web-ui-dashboard/)

1. 대시보드 UI는 기본으로 배포되지 않는다.  아래 명령어 실행

   ```
   $ kubectl apply -f https://raw.githubusercontent.com/kubernetes/dashboard/v2.6.1/aio/deploy/recommended.yaml
   ```

   이후

   - **kubectl proxy**

     ```
     $ kubectl proxy
     ```

     dashboard에 접속할 수 있게 해준다.

     단, proxy를 사용하면 오직 위 command가 실행 된 machine에서만 접속이 가능하다. (ssh로 원격 연결해도 안됨)

   

   

   - 

   - kube-apiserver

     1. kube-apiserver 접근하기 위한 인증서 생성

        `.kube/config` 파일의 client certificate를 추출하여 kubecfg.crt로 저장

        ```
        $ grep 'client-certificate-data' ~/.kube/config | head -n 1 | awk '{print $2}' | base64 -d >> kubecfg.crt
        ```

        > 확인
        >
        > ```
        > $ cat kubecfg.crt
        > ```

        `.kube/config` 파일의 client key를 추출하여 kubecfg.key로 저장

        ```
        $ grep 'client-key-data' ~/.kube/config | head -n 1 | awk '{print $2}' | base64 -d >> kubecfg.key
        ```

        > 확인
        >
        > ```
        > $ cat kubecfg.key
        > ```

     2. Key를 포함한 p12 인증서 생성

        `openssl`를 사용해야 한다.

        ```
        $ openssl pkcs12 -export -clcerts -inkey kubecfg.key -in kubecfg.crt -out kubecfg.p12 -name "kubernetes-admin"
        ```

        - `-export`: 개인 키와 인증서를 포함한 PKCS #12 파일을 생성

          보통 키와 인증서를 하나의 파일로 결합하여, 이후 다른 서버에서 사용할 수 있도록 배포하기 위해 사용

        - `-clcerts`: 서버 인증서 체인을 생성할 때, 중간 인증서를 포함하지 않는다. (인증서 체인의 길이를 줄일 수 있다.)

        - `-inkey`: 개인 키 파일을 지정

          개인 키는 공개 키와 함께 사용되며, SSL/TLS 연결을 설정할 때 서버 인증서를 검증하는 데 사용

        - `in`: 입력 파일 을 지정

          보통 `.pem` 확장자를 가진 인증서 또는 개인 키 파일을 지정

        설정하고자 하는 Password 입력

        ```
        Enter Export Password:
        ```

        이후

        `kubecfg.p12`와 `/etc/kubernetes/pki/`에 있는 `ca.crt`파일을 client PC에 다운로드

     3. 인증서 적용

        - windows10

          1. `ca.crt`파일: 신뢰할 수 있는 루트 인증 기관 인증서에 설치

             해당 인증서 파일 실행 > 인증서 가져오기 마법사 실행

             저장소 위치 선택 > 로컬 컴퓨터 선택 후 next

             인증서 저장소 화면에서 '모든 인증서를 다음 저장소에 저장' 선택 후 Browse >  `신뢰할 수 있는 루트 인증 기관` 폴더 선택

             next 후 마침

          2.  `kubecfg.p12` : 개인용 인증서로 설치

             해당 인증서 파일 실행 > 인증서 가져오기 마법사 실행

             저장소 위치 선택 > 로컬 컴퓨터 선택 후 next

             가져오는 파일 위치 맞는지 확인 후 next
             암호 입력 후 next

             모든 인증서를 다음 저장소에 저장 > Browse  > 개인용 폴더 선택 >  next



### 외부 접속

https://choco-life.tistory.com/m/52

참고

#### 1. Ingress

kubernetes-dashboard는 https 요청을 강제하지만, 외부에서 Ingress Controller로 들어오는 부분이 TLS 인증 처리가 되어 있으므로 kubernetes 내부에서 동작하는 dashboard 서비스 및 pod는 http를 사용할 수 있다.



1. edit ``

   ```
   $ kubectl edit svc kubernetes-dashboard  -n kubernetes-dashboard 
   ```

   ```
     - port: 443  >> 80
       protocol: TCP
       targetPort: 8443  >> 9090
     selector:
   ```

   ```
     type: ClusterIP
   ```

   

   ```
   $ kubectl rollout restart svc kubernetes-dashboard  -n kubernetes-dashboard
   ```

   ```
   $ kubectl get svc kubernetes-dashboard -n kubernetes-dashboard
   ```

   ```
   NAME                   TYPE       CLUSTER-IP    EXTERNAL-IP   PORT(S)         AGE
   kubernetes-dashboard   NodePort   10.110.53.3   <none>        443:32385/TCP   92m
   ```

   

#### 2. NodePort



1. edit kubernetes-dashboard service

   ```
   $ kubectl edit svc kubernetes-dashboard  -n kubernetes-dashboard 
   ```

   ```
   ...
   sepc
     - port: 443
       protocol: TCP
       targetPort: 8443
     selector:
       k8s-app: kubernetes-dashboard
     sessionAffinity: None
     type: ClusterIP
   status:
   ...
   ```

   위를 아래처럼 변경

   ```
   ...
   sepc
     - port: 443
       protocol: TCP
       targetPort: 8443
     selector:
       k8s-app: kubernetes-dashboard
     sessionAffinity: None
     type: ClusterIP
   status:
   ...
   ```

   





#### 3. kube-apiserver

단점: 

- Host가 외부와 직접 연결되는 환경에서만 사용할 수 있다.
- Kubernetes 관리자가 아닌 사용자가 직접 브라우저에 인증서를 설치하는 과정이 필요
- Kubernetes API Server를 외부와 직접 노출하는 것은 바람직하지 않음





1. kube-apiserver 접근하기 위한 인증서 생성

   `.kube/config` 파일의 client certificate를 추출하여 kubecfg.crt로 저장

   ```
   $ grep 'client-certificate-data' ~/.kube/config | head -n 1 | awk '{print $2}' | base64 -d >> kubecfg.crt
   ```

   > 확인
   >
   > ```
   > $ cat kubecfg.crt
   > ```

   `.kube/config` 파일의 client key를 추출하여 kubecfg.key로 저장

   ```
   $ grep 'client-key-data' ~/.kube/config | head -n 1 | awk '{print $2}' | base64 -d >> kubecfg.key
   ```

   > 확인
   >
   > ```
   > $ cat kubecfg.key
   > ```

2. Key를 포함한 p12 인증서 생성

   `openssl`를 사용해야 한다.

   ```
   $ openssl pkcs12 -export -clcerts -inkey kubecfg.key -in kubecfg.crt -out kubecfg.p12 -name "kubernetes-admin"
   ```

   - `-export`: 개인 키와 인증서를 포함한 PKCS #12 파일을 생성

     보통 키와 인증서를 하나의 파일로 결합하여, 이후 다른 서버에서 사용할 수 있도록 배포하기 위해 사용

   - `-clcerts`: 서버 인증서 체인을 생성할 때, 중간 인증서를 포함하지 않는다. (인증서 체인의 길이를 줄일 수 있다.)

   - `-inkey`: 개인 키 파일을 지정

     개인 키는 공개 키와 함께 사용되며, SSL/TLS 연결을 설정할 때 서버 인증서를 검증하는 데 사용

   - `in`: 입력 파일 을 지정

     보통 `.pem` 확장자를 가진 인증서 또는 개인 키 파일을 지정

   설정하고자 하는 Password 입력

   ```
   Enter Export Password:
   ```

   이후

   `kubecfg.p12`와 `/etc/kubernetes/pki/`에 있는 `ca.crt`파일을 client PC에 다운로드

3. 인증서 적용

   - windows10

     1. `ca.crt`파일: 신뢰할 수 있는 루트 인증 기관 인증서에 설치

        해당 인증서 파일 실행 > 인증서 가져오기 마법사 실행

        저장소 위치 선택 > 로컬 컴퓨터 선택 후 next

        인증서 저장소 화면에서 '모든 인증서를 다음 저장소에 저장' 선택 후 Browse >  `신뢰할 수 있는 루트 인증 기관` 폴더 선택

        next 후 마침

     2.  `kubecfg.p12` : 개인용 인증서로 설치

        해당 인증서 파일 실행 > 인증서 가져오기 마법사 실행

        저장소 위치 선택 > 로컬 컴퓨터 선택 후 next

        가져오는 파일 위치 맞는지 확인 후 next
        암호 입력 후 next

        모든 인증서를 다음 저장소에 저장 > Browse  > 개인용 폴더 선택 >  next

   - linux

4. 접속

   ```
   $ https://<MasterIP>:<MasterPort>/api/v1/namespaces/kubernetes-dashboard/services/https:kubernetes-dashboard:/proxy/
   ```

   



