{:toc}

# Kubeflow



### Introduction

[공식](https://www.kubeflow.org/docs/started/introduction/)

**Kubeflow Features**

1. 조합가능성 Composability
   
   kubeflow의 핵심 구성 요소는 이미 머신러닝 실무자들에게 익숙한 데이터 과학 도구를 사용한다.
   
   이들은 기계 학습의 특정 단계를 용이하게 하기 위해 독립적으로 사용되거나, end to end pipeline을 형성하기 위해 함께 구성될 수 있다.

2. 이식성 Portability
   
   container 기반 설계를 갖추고 kubernetes 및 cloud 네이티브 아키텍처를 활용함으로써 kubeflow는 특정 개발환경에 종속될 필요가 없다.
   
   labtop에서 실험 및 프로토타입 작업을 수행할 수 있으며, 프로덕션 환경에 손쉽게 배포할 수 있다.

3. 확장성 Scalability
   
   kubenetes를 사용하면 기본 컨테이너와 기계의 수와 크기를 변경하여 클러스터의 요구에 따라 동적으로 확장할 수 있다.

**kubeflow moduel**

- pipeline

  pipeline은 각 component를 이어서 만든 것으로, 여러 component(preprocessing, training 등)을 구성하여 만드는 것이다.

  component는 특정 function에 `@kfp.das.python_componenet`라는 decorator를 적어주면 된다.

  이를 'component로 추상화한다.' 라고 한다. 

  component로 추상화한다는 말은, docker image로 만든다는 의미이다.

  이러한 여러가지 component를 조합하여 pipeline을 구성한다.

  이렇게 구성된 pipeline을 build하게 되면 yaml file이 만들어지게 되는데, 이를 pipeline을 compile한다고 한다. 이러한 yaml file을 kubeflow 대시보드에서 업로드하거나 kfctl명령으로 업로드 할 수 있다.

- Katlib

  kubeflow에서 model tuning(Auto ML)을 담당하는 모듈을.

- Training Operators

  

- Kserving 

  online inference server를 배포하는 모듈

  seldon core처럼 model serving에 사용된다.

  [공식](https://www.kubeflow.org/docs/external-add-ons/kserve/kserve/) 문서를 확인하여 공부하고 사용해보자. (또는 인강)

- MinIO

  kubeflow pipeline간의 저장소 기능을 수행하는 솔루션으로, MinIO에 pipeline 중간에 생기는 부산물들을 저장할 수 있다.



- Central dashboard 

  kubeflow에서 제공하는 모든 기능을 통합하여 제공하는 UI



**Pipeline이란** 

- 머신러닝 workflow르 DAG(방향 순환이 없는 그래프)형태로 정의한 것

- kubeflow에 배포 후 run하면 pipeline을 구성하는 component들이 k8s위에서 pod로 생성되어 서로 data를 주고받으며 흘러감
- model을 serving까지 보내는데 필요한 머든 작업을 재사용 가능한 단위(component)로 나누고, k8s위에서 연결시켜주는 역할

- gaol

  - End to End Orchestration

    model연구 및 training과정과 serving과정의 괴리가 없도록 한다.

  - Easy Experimentation

    다양한 configuration에 따라 수많은 시도를 쉽게 한다.

  - Easy Re-Use

    잘 설계된 kfp component들은 재사용 가능하므로, 새로 Pipelin을 만들 때의 작업 효율 향상

- how to make?

  python code에 detorator기능을 통해 pipeline으로 감싸주면, kubeflow에서 자동으로 kfp yaml format으로 만들어준다.

  이렇게 만들어진 yaml file을 UI나 CLI를 통해서 실행 요청을 할 수 있다.



### install

#### linux(Ubuntu)

[공식](https://www.kubeflow.org/docs/started/installing-kubeflow/), [github](https://github.com/kubeflow/manifests)

Prerequisites : `Kubernetes` , `kustomize` (version `3.2.0`) 

**Install the Kubeflow Manifests manually**

kustomzie V3 기반으로  manifests file을 관리한다.

> kustomzie : helm과 비슷한 역할을 하며, 여러개의 yaml file을들 쉽게 관리하기 위한 도구이다.
>
> 여러 resource드르이 configuration을 템플릿과 커스터마이제션한 부분으로 나누어서 관리할 수 있다.

1. kustomize 설정

   [여기](https://github.com/kubernetes-sigs/kustomize/) 에서 현재 k8s version에 맞는 kustomize version을 확인하고 download binary

   ```
   $ kubectl version
   ```

   > kustomize 3.2.0에 알맞는 version확인

   [여기](https://github.com/kubernetes-sigs/kustomize/releases/tag/v3.2.0)의 **Asset** 아래 `kustomize_3.2.0_darwin_amd64` 의 링크 복사 (arm이면 arm꺼 복사)

   > 링크 없어지면 [releases](https://github.com/kubernetes-sigs/kustomize/releases?page) 에서 3.2.0 찾은 후 진행

   ```
   $ sudo wget https://github.com/kubernetes-sigs/kustomize/releases/download/v3.2.0/kustomize_3.2.0_linux_amd64
   ```

   > 만약`.tar.gz` format밖에 없다면 압축 풀고 진행
   >
   > ```
   > $ gzip -d kustomize_v3.2.0_linux_amd64.tar.gz
   > $ tar -xvf kustomize_v3.2.0_linux_amd64.tar
   > ```

   file의 mode 변경 (실행 가능하도록)

   ```
   $ sudo chmod +x kustomize_3.2.0_linux_amd64
   ```

   압축 풀고 file위치 변경

   ```
   $ sudo mv kustomize_3.2.0_linux_amd64 /usr/local/bin/kustomize
   ```

   check(새 terminal 열고)

   ```
   $ kustomize version
   ```

   ```
   Version: {KustomizeVersion:3.2.0 GitCommit:a3103f1e62ddb5b696daa3fd359bb6f2e8333b49 BuildDate:2019-09-18T16:26:36Z GoOs:linux GoArch:amd64}
   ```

   > uninstall : `sudo rm /usr/local/bin/kustomize`

2. start kubenetes 

   ```
   $ minikube start --driver=docker \
    --cpus='4' --memory='7g' \
    --kubernetes-version=v1.19.3 \
    --extra-config=apiserver.service-account-signing-key-file=/var/lib/minikube/certs/sa.key \
    --extra-config=apiserver.service-account-issuer=kubernetes.dafault.svc
   ```

   > `--extra-config` : token Request활성화 관련 설정
   >
   > `--kubernetes-version=v1.19.3` : version정확히 명시해야됨
   >
   > version잘못 명시하면 다시 install
   >
   > ```
   > $ minikube stop
   > $ minikube delete
   > $ minikube delete --all
   > ```

   check

   ```
   $ kubectl get sc
   ```

   ```
   NAME                 PROVISIONER                RECLAIMPOLICY   VOLUMEBINDINGMODE   ALLOWVOLUMEEXPANSION   AGE
   standard (default)   k8s.io/minikube-hostpath   Delete          Immediate           false                  15s
   
   ```

   

3. git clone [kubeflow/manifests](https://github.com/kubeflow/manifests)

   ```
   $ cd ~/hibernation			# git clone할 임의의 위치
   $ git clone https://github.com/kubeflow/manifests.git
   $ cd manifests
   ```

   > ```
   > $ git checkout tags/v1.4.0 
   > ```
   >
   > 위 명령어를 통해 특정 version으로 checkout하면 `manifests/apps/pipeline/upstream/env/` 의 cert-manager dir이 사라지는  현상 발생 

   check

   ```
   $ git log
   ```

   > 마지막 commit확인

4. kubeflow의 individual components install ([github](https://github.com/kubeflow/manifests) 에 다 있음. 가능하면 해당 link에서 보고 install)

   > 각각 yaml file을 build이후 kubectl apply -f를 진행하게 되는, 이는 모두 순서대로 해야한다. 특정 kubeflow version을 설치한다면, 대한 version에 대한 tag로 이동하여 해당 version에 맞는 명령어를 입력해야 한다.

   1. cert-manager

      ```
      $ kustomize build common/cert-manager/cert-manager/base | kubectl apply -f -
      $ kustomize build common/cert-manager/kubeflow-issuer/base | kubectl apply -f -
      ```

      check

      ```
      $ kubectl get pod -n cert-manager
      ```

   2. istio

      ```
      $ kustomize build common/istio-1-14/istio-crds/base | kubectl apply -f -
      $ kustomize build common/istio-1-14/istio-namespace/base | kubectl apply -f -
      $ kustomize build common/istio-1-14/istio-install/base | kubectl apply -f -
      ```

      > kubeflow version에 따라 istio의 version이 다를 수 있으니 확인할 것

      ```
      $ kubectl get pod -n istio-system 
      ```

   3. Dex

      ```
      $ kustomize build common/dex/overlays/istio | kubectl apply -f -
      ```

   4. OIDC AuthService

      ```
      $ kustomize build common/oidc-authservice/base | kubectl apply -f -
      ```

   5. Knative

      > 설치 안됨 
      >
      > ```
      > unable to recognize "STDIN": no matches for kind "PodDisruptionBudget" in version "policy/v1"
      > unable to recognize "STDIN": no matches for kind "PodDisruptionBudget" in version "policy/v1"
      > ```
      >
      > 

      ```
      $ kustomize build common/knative/knative-serving/overlays/gateways | kubectl apply -f -
      $ kustomize build common/istio-1-14/cluster-local-gateway/base | kubectl apply -f -
      ```

   6. Kubeflow Namespace

      ```
      $ kustomize build common/kubeflow-namespace/base | kubectl apply -f -
      ```

      check

      ```
      $ kubectl get namespace   # Kubeflow라는 namespace생성되어야함
      ```

   7. Kubeflow Roles

      ```
      $ kustomize build common/kubeflow-roles/base | kubectl apply -f -
      ```

   8. Kubeflow Istio Resources

      ```
      $ kustomize build common/istio-1-14/kubeflow-istio-resources/base | kubectl apply -f -
      ```

      > kubeflow version에 따라 istio의 version이 다를 수 있으니 확인할 것

   9. Kubeflow Pipelines

      ```
      $ kustomize build apps/pipeline/upstream/env/cert-manager/platform-agnostic-multi-user | kubectl apply -f -
      ```

      > If your container runtime is not docker, use pns executor instead:
      >
      > ```
      > $ kustomize build apps/pipeline/upstream/env/platform-agnostic-multi-user-pns | kubectl apply -f -
      > ```

      만약 아래와 같은 error가 떳다면

      ```
      unable to recognize "STDIN": no matches for kind "CompositeController" in version "metacontroller.k8s.io/v1alpha1"
      ```

      위 설치 명령어 다시 입력

   10. KServe

       Install the KServe component

       ```
       $ kustomize build contrib/kserve/kserve | kubectl apply -f -
       ```

       > ```
       > anable to recognize "STDIN": no matches for kind "ClusterServingRuntime" in version "serving.kserve.io/v1alpha1"
       > ```
       >
       > 가 뜬다면 위 명령어 한번 더 입력

       Install the Models web app

       ```
       $ kustomize build contrib/kserve/models-web-app/overlays/kubeflow | kubectl apply -f -
       ```

   11. Katib

       ```
       $ kustomize build apps/katib/upstream/installs/katib-with-kubeflow | kubectl apply -f -
       ```

   12. Central Dashboard

       ```
       $ kustomize build apps/centraldashboard/upstream/overlays/kserve | kubectl apply -f -
       ```

   13. Admission Webhook

       ```
       $ kustomize build apps/admission-webhook/upstream/overlays/cert-manager | kubectl apply -f -
       ```

   14. Notebooks

       Install the Notebook Controller official Kubeflow component

       ```
       $ kustomize build apps/jupyter/notebook-controller/upstream/overlays/kubeflow | kubectl apply -f -
       ```

       Install the Jupyter Web App official Kubeflow component

       ```
       # kustomize build apps/jupyter/jupyter-web-app/upstream/overlays/istio | kubectl apply -f -
       ```

   15. Profiles + KFAM

       ```
       $ kustomize build apps/profiles/upstream/overlays/kubeflow | kubectl apply -f -
       ```

   16. Volumes Web App

       ```
       $ kustomize build apps/volumes-web-app/upstream/overlays/istio | kubectl apply -f -
       ```

   17. Tensorboard

       Install the Tensorboards Web App official Kubeflow component

       ```
       $ kustomize build apps/tensorboard/tensorboards-web-app/upstream/overlays/istio | kubectl apply -f -
       ```

       Install the Tensorboard Controller official Kubeflow component

       ```
       $ kustomize build apps/tensorboard/tensorboard-controller/upstream/overlays/kubeflow | kubectl apply -f -
       ```

   18. training operator

       ```
       $ kustomize build apps/training-operator/upstream/overlays/kubeflow | kubectl apply -f -
       ```

   19. User Namespace

       ```
       $kustomize build common/user-namespace/base | kubectl apply -f -
       ```

5. 모든 pod 구동

   ```
   $ kubectl get po -A -w
   ```

   > 길게는 몇십분까지 걸림

6. kubeflow 접속

   1. 새로운 terminal에서 port forwarding

      ```
      $ kubectl port-forward svc/istio-ingressgateway -n istio-system 8080:80
      ```

      > user 접속 정보 관련 설정을 변경하지 않는 경우의 default접속 정보는 아래와 같다
      >
      > - ID : user@example.com
      > - PW : 12341234

      이 terminal은 항상 열고있어야한다.

   2. 접속

      `localhost:8080` 으로 접속 후 login



#### windows

**powershell (관리자 권한)** 사용

1. install docker desktop(with WSL 2)

   install 후 

   - dash board에서 setting > General > Use the WSL 2 based engine 체크되어있는지 확인

   - dash board에서 setting > REsources > =WSL Integration > Enable integration with my default WSL distro 체크되어있는지 확인

   check

   ```
   $ docker ps
   ```

   

2. 보안정책 수정

   ```
   $ Get-ExecutionPolicy
   ```

   ```
   Restricted
   ```

   

   ```
   $ Set-ExecutionPolicy AllSigned
   ```

   ```
   AllSigned
   ```

   `AllSigned` 출력됨을 확인

3. install chocolatey 

   ```
   $ Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
   ```

   check

   ```
   $ choco
   ```

   ```
   Chocolatey v1.1.0
   Please run 'choco -?' or 'choco <command> -?' for help menu.
   ```

4. install minikube

   [공식](https://minikube.sigs.k8s.io/docs/start/) 에서 명령어 복사

   ```
   Operating system : windows
   Architecture : x86-64
   Release type : Stable
   Installer type : Chocolatey
   ```

   

   ```
   $ choco install minikube
   ```

5. create kubernetes cluster with minikube

   ```
   $ minikube start --driver=docker --memory=12g --cpus=4 --disk-size 50GB --kubernetes-version=1.20.11 --profile=mk
   ```

   

   기본 profile 설정

   ```
   $ minikube config set profile mk
   ```

6. **install kustomize** (version `3.8.4`) 

   ```
   $ choco install kustomize --version=3.8.4
   ```

7. **Install Kubeflow**

   ```
   $ choco install git
   $ git --version
   ```

   git clone [kubeflow/manifests](https://github.com/kubeflow/manifests)

   ```
   $ cd ~/Desktop/
   $ mkdir minikube
   $ cd minikube
   $ git clone https://github.com/kubeflow/manifests.git
   $ cd manifests 
   ```

   여기까지

   [추가 내용](https://velog.io/@moey920/Window%EC%97%90%EC%84%9C-Minikube-Kubeflow-%EA%B5%AC%EC%B6%95%ED%95%98%EA%B8%B0)



