

{:toc}



# Central Dashboard

#### port forwarding

1. istio-ingressgateway 확인

   ```
   $ kubectl get svc -n istio-system
   ```

   ```
   NAME                    TYPE           CLUSTER-IP       EXTERNAL-IP   PORT(S)
   istio-ingressgateway    LoadBalancer   10.102.172.178   <pending>     15021:32503/TCP,80:30116/TCP,443:31897/TCP,31400:31214/TCP,15443:30902/TCP  
   ```

   > port 80 확인
   >
   > ```
   > ▒ istioctl install --set profile=default -f - <<EOF
   > apiVersion: install.istio.io/v1alpha1
   > kind: IstioOperator
   > spec:
   >   components:
   >     ingressGateways:
   >     - enabled: true
   >       k8s:
   >         service:
   >           ports:
   >           - name: status-port
   >             port: 15021
   >             targetPort: 15021
   >           - name: http2
   >             port: 80
   >             targetPort: 8080
   >             nodePort: 32080
   >           - name: https
   >             port: 443
   >             targetPort: 8443
   >             nodePort: 32443
   >           - name: tls
   >             port: 15443
   >             targetPort: 15443
   >       name: istio-ingressgateway
   >   values:
   >     gateways:
   >       istio-ingressgateway:
   >         type: NodePort
   > EOF
   > ```

2. port forward

   ```
   $ kubectl port-forward svc/istio-ingressgateway -n istio-system 8080:80
   ```

   > host `127.0.0.1:8080` ==> node1 `10.102.172.178:30116` 연결

3. localhost 8080접속

   ```
   localhost:8080
   ```

   `Eamail Address`, `PW` 입력

   > `user@example.com`, `12341234`

   **Central Dashboard**의 **pipeline** 에서 `+Upload pipeline` , Upload a file 에서 `add_exam.yaml` 선택 >> create

   `+Create run` : 해당 pipeline을 실행 

   > 선택할 experiments가 없으면 Experiments(KFP) 에서 `+Create experiment` 눌러서  experiment만들고 바로 pipeline선택해서 run만들기

   Run이 만들어진 후 시간이 지나면 Graph에서 각 componenet의 상태 확인 가능

   > 모든 output, log는 minio에 저장되며 해당 file을 다운받으면 관련 data를 확인할 수 있다.



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