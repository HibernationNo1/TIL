

{:toc}



# Central Dashboard

## link

### port forwarding

1. kubernetes 확인

   ```
   $ minikube status
   ```

   ```
   type: Control Plane
   host: Running
   kubelet: Running
   apiserver: Running
   kubeconfig: Configured
   ```

   > 아래처럼 출력 될 경우
   >
   > ```
   > type: Control Plane
   > host: Stopped
   > kubelet: Stopped
   > apiserver: Stopped
   > kubeconfig: Stopped
   > ```
   >
   > minikube start 
   >
   > ```
   > minikube start --driver=docker \
   > --cpus='4' --memory='7g' \
   > --kubernetes-version=v1.19.3 \
   > --extra-config=apiserver.service-account-signing-key-file=/var/lib/minikube/certs/sa.key \
   > --extra-config=apiserver.service-account-issuer=kubernetes.dafault.svc
   > ```

   ```
   $ kubectl get nodes
   ```

   ```
   NAME       STATUS   ROLES    AGE   VERSION
   minikube   Ready    master   29h   v1.19.3
   ```

   kubeflow namespace의 resource check

2. istio-ingressgateway 확인

   ```
   $ kubectl get svc -n istio-system
   ```

   ```
   NAME                    TYPE           CLUSTER-IP       EXTERNAL-IP   PORT(S)
   istio-ingressgateway    LoadBalancer   10.102.172.178   <pending>     15021:32503/TCP,80:30116/TCP,443:31897/TCP,31400:31214/TCP,15443:30902/TCP  
   ```

   > port 80 확인
   >
   
3. port forward

   ```
   $ kubectl port-forward svc/istio-ingressgateway -n istio-system 8080:80
   ```

   > host `127.0.0.1:8080` ==> node1 `10.102.172.178:30116` 연결

4. localhost 8080접속

   ```
   localhost:8080
   ```

   `Eamail Address`, `PW` 입력

   > deault : `user@example.com`, `12341234`

   **Central Dashboard**의 **pipeline** 에서 `+Upload pipeline` , Upload a file 에서 `add_exam.yaml` 선택 >> create

   `+Create run` : 해당 pipeline을 실행 

   > 선택할 experiments가 없으면 Experiments(KFP) 에서 `+Create experiment` 눌러서  experiment만들고 바로 pipeline선택해서 run만들기

   Run이 만들어진 후 시간이 지나면 Graph에서 각 componenet의 상태 확인 가능

   > 모든 output, log는 minio에 저장되며 해당 file을 다운받으면 관련 data를 확인할 수 있다.



### access from outside 

#### ngrok

방화벽 넘어서 외부에서 로컬에 접속 가능하게 하는 터널 프로그램

외부에서도 `localhost:8080` 과 같은 local server에 접근할 수 있도록 임시 URL을 만들어준다.



```
ngrok http 8080
```

> snap으로 install했을 시 위 명령어.



#### kubernetes

minikube는 kubernetes와 다르게 `로컬 쿠버네티스 엔진` 이기 때문에 minikube를 사용할 경우 아래의 LoadBalancer의 `EXTERNAL-IP`이 `<pending>` 인 것을 볼 수 있다.

> istio-ingressgateway 확인
>
> ```
> $ kubectl get svc -n istio-system
> ```
>
> ```
> NAME                    TYPE           CLUSTER-IP       EXTERNAL-IP   PORT(S)
> istio-ingressgateway    LoadBalancer   10.102.172.178   <pending>     15021:32503/TCP,80:30116/TCP,443:31897/TCP,31400:31214/TCP,15443:30902/TCP  
> ```
>

때문에 외부에서 접근하기 위해서는 kubectl proxy를 실행하고  `minikube tunnel`를 실행해야 하는 등 번거로운 과정이 많다.

하지만 kubernetes를 설치하면 `EXTERNAL-IP`이 할당되고, 외부로 IP노출이 가능하기 때문에 외부에서 쉽게 접근이 가능하다.



## add user

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
     hash: $2a$12$mAIZSsmCcHk9SMU6yAoYQOt7zXV.7UVboJIfcSB3PF5pD3Nc/oyHi
     userID: "taeuk"
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

   >  vim deiter로 변경

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
        name: testuser
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
   
   3. edit
   
      ```
      $ kubectl edit profile <namespace_name>
      ```
   
      



## menu

### Home

- Dashboard
  - Quick shortcuts : 자주 사용하는 menu
  - 

- Activiry

  해당 namespace에 대한 activity log



### Notebooks

해당 namespace에 대한 Notebook server생성



`New Noteboock` : 메타 정보를 user로부터 입력받아서 생성

입력받은 메타 정보는 고정되며, 해당 resource를 기반으로 server가 동작하게 된다.

- Docker Image

- Workspace Volume : 작업 내역을 보존하고싶다면 반드시 할당

  - Mount path

    해당 위치에 대해 Mount를 하는데, 이후에 다른 user를 만들어서 같은 위치로 mount해도 해당 부분은 data가 보존되지 않을 수 있다.



- Data Volume

  다른 dir에 mount할때 사용



- Configurations

  특정한 민감 정보를 kubernetes에 secret하게 하고자 할 때 해당 정보를 notebook에서 가져와 사용할 수 있도록 한다.



- Affinity / Tolerations 

  어떤 Node는 GPU 가 있고, 어떤 Node는 memory가 빵빵하고.. 등 각 Node당 특징이 있다. 이런 경우 해당 notebook server를 특정 node에 scheduling하고자 할 때 사용한다.



**LANLCH**

여러 정보를 입력 후 진행하면 notebook server생성

생성 후 CONNECT를 누르면 jupyterLab으로 새 창 열기  >> python code, termina등 사용 가능





### Volume

namespace에 속한 PVC resource를 관리할 수 있다.

`New Volume` 

- 관련 검색 필요



### Models



### Experiments(AutoML)

Katib를 사용하여 HPO를 1회 하는 개념

`New Experiments` : 





### Experiments(KFP)

여러 kubeflow pipeline을 실행한 결과를 실험, data, model 등의 단위로 user가 자유롭게 group지어서 관리할 수 있다.

user가 pipeline을 실행시킬 때 반드시 KFP run에 실행 결과를 어떤 experiment에 저장할지 명시해야 하기 때문에 미리 생성되어있어야 한다.

`New Experiments` : 





### Pipelines

`source code` : yaml file로 만들어지기의 전 python code를 볼 수 있다.

`pipeline name` : dag의 형태로 각 component 연결되어 있는 모습을 볼 수 있다.

- `component`선택 : 각각의 component별로 `Input parameters`, `Output parameters`, `Arguments`, `Command`등을 확인할 수 있다.

- `+Upload pipeline` :  python code로 작성한 pipeline을 compile하고 나면 해당 yaml file을 업로드 할 수 있다.

### Runs

Pipeline의 실행한 결과들을 저장한다.

우측 상단 ` +Create run` :

- `Pipeline` : 사전에 생성해놓은 Pipeline 중 선택
- `Pipeline Version`
- `Run name` : pipe line을 실행한 결과의 name
- `Experiment` : 사전에 생성해놓은 Experiments 중 선택
- `Run type` : 
  - `One-off` : Runs 에서만 선택
  - `Recurring`: schedule을 정해서 특정 KFP를 Run하고 싶을때 사용할 수 있는 기능. 해당 type을 선택할 경우 아래를 사용할 수 있다.
    - `Run every` : 어떠한 주기 별로 Run을 할 것인지

- `Run parameters` : pipeline이 받는 input

start를 누르면 각각의 component 단위로 실행이 되며 성공 or 실패 여부에 따라 진행이 된다.



### Recurring Runs

우측 상단 ` +Create run` :

- `Run type` : 

  - `One-off` : 

  - `Recurring`: Recurring Runs에서만 선택

    schedule을 정해서 특정 KFP를 Run하고 싶을때 사용할 수 있는 기능. 해당 type을 선택할 경우 아래를 사용할 수 있다.

    - `Run every` : 어떠한 주기 별로 Run을 할 것인지



### Artifacts

KFP Run의 실행 결과를 모아볼 수 있다.



### Executions

어떠한 Run들이 execution되는지 모아서 mete정보와 함께 볼 수 있다.



### Manage Contributors

실무에서는 여러명이서 동일한 kubeflow cluster를 사용하지만 namespace에 의해 각 사용자가의 정보와 진행 결과가 격리되는데, 프로젝트를 진행하다 보면 동일한 notebook을 공유하거나 KFP Run의 결과를 공유하고 싶은 경우가 있을 수 있다.

이 때 Manage Contributors에 공유할 유저의 계정 정보를 추가하면 해당 계정 user는 공유를 열어준 namespace에 접근할 수 있게 된다.

> `Contributors to your namespace - kubeflow-user-example-com` 에 특정 user 계정을 추가하게 되면 그 사람이 나의 namespace에 접근 가능