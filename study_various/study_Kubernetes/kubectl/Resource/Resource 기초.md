# Resource 기초

쿠버네티스를 관리하기 위한 API로, 크게 다섯 가지의 카테고리로 분류된다.



**workload API category** : 클러스터 위에서 컨테이너를 기동하기 위해 사용되는 resource. 내부적으로 사용되는 것을 제외하고 사용자가 직접 관리할 수 있는 것으로 총 여덟가지 종류의 workload resource가 있다.

**Service API category** : 컨테이너 서비스  디스커버리와 클러스터 외부에서도 접속이 가능한 엔드포인트 등을 제공하는 리소스다. 

내부적으로 사용되는 것을 제외하고 사용자가 직접 관리할 수 있는 리소스로 서비스와 ingress라는 두 종류의 서비스 API카테고리가 있다.

서비스에는 엔드포인트 제공 방식이 다른 여러 타입이 준비되어 있다.

**config & storage API category** : 설정과 기밀 데이터를 컨테이너에 담거나 영부 볼륨을 제공하는 resource다.

secret과 configmap은 모두 key-value형태의 데이터 구조로 되어 있고, 저장할 데이터가 기밀 데이터인지 일반적인 설정 정보인지에 따라 구분된다.

영구 볼륨 클레임은 컨테이너에서 영구 볼륨을 요청할 때 사용한다.

**cluster API category** : 클러스터 자체 동작을 정의하는  resource다. 보안 관련 설정이나 정책, 클러스터 관리성을 향상시키는 기능을 위한 리소스 등 여러 리소스가 있다.

**metadata API category** : 클러스터 내부의 다른 리소스 동작을 제어하기 위한 resource



- resource를 생성 과정

  manifest file을 작성

  `kubecrl create` 명령어를 통해 manifest file에 저장된 resource정보를 등록 >> 생성



- 용어 설명
  - field : resource내부 상태의 설정 항목 





### command

- **create**

  resource를 생성하는 명령어

  ```
  $ kubectl create -f [manifest_file]
  ```

  > 해당 리소스가 존재할 경우 에러 발생
  >
  > `manifest_file` : recource정보를 담은 yaml형식의 file

  **기본적으로 create보다  `$ kubectl apply`가 더 편하고 안전하기 때문에 apply만 사용하자.**



- **delete**

  resource를 제거하는 명령어

  - manifest file 사용

    ```
    $ kubectl delete -f [manifest_file]
    ```

    > 해당 리소스가 존재하지 않을 경우 에러 발생
    >
    > `manifest_file` : recource정보를 담은 yaml형식의 file

  - manifest file 사용 안할 때

    resource종류, resource이름 을 지정하여 삭제

    ```
    $ kubectl delete pod [pod_name]
    ```

    > `pod [pod_name]` : resource종류 중 pod 중에서 pad_name이라는 pod만 제거

    ```
    $ kubectl delete pod --all
    ```

    > pod라는 resource를 종류에 해당되는 것을 모두 제거

  **--wait**

  kubectl명령어 실행은 바로 완료되지만, kubenetes에 의한 실제 resource 처리는 비동기로 실행되기 때문에 바로 완료되지 않는다. 

  `--wait` 옵션을 사용하면 resource의 삭제 완료를 기다렸다가 명령어 실행을 종료할 수 있다.

  > delete명령이 끝난 후 `$ kubectl wait` 명령이 진행되는 것임

  ```
  $ kubectl delete -f sample-pod.yaml --wait
  ```

  > resource삭제 완료 대기

  **--force**

  resource를 강제로 즉시 삭제하는 옵션이다. 

  ```
  $ kubectl delete -f sample-pod.yaml --force
  ```

  

- **apply**

  manifest file에 변경 사항이 있을 경우 resource updata를 하는 명령어

  > manifest file에 변경 사항이 있을 경우 태그를 붙여 백업한다.
  >
  > ```
  > $ cp -av sample-pod.yaml{, .lod}
  > ```
  >
  > `sample-pod.yaml` 라는 manifest file이 `$ kubectl create`에 의해 이미 등록되어 있는 상태에서 `sample-pod.yaml`에 변경이 있을 경우
  >
  > 변경된 `sample-pod.yaml` 라는 manifest file을 `sample-pod.yaml.old` 로 태그를 붙여 백업한다.

  - **diff**

    두 개의 manifest file을 비교하여 변경 사항이 있는지 확인

    ```
    $ diff sample-pod.yaml.old sample-pod.yaml
    ```

    > `sample-pod.yaml.old` : 변경된 후 .old라는 태그가 붙여진 sample-pod.yaml file
    >
    > `sample-pod.yaml` : 변경되기 전 `$ kubectl create`에 의해 등록된 resource

  ```
  $ kubectl applty -f sample-pod.yaml
  ```

  > 기존에 등록된 `sample-pod.yaml`라는 파일에 변경사항이 있다면 업데이트
  >
  > 등록된 resource가 없는 경우 `$ kubectl create` 와 같은 동작을 한다.

  kubenetes는 생성한 resource 상태를 내부에 기록한다. 한 번 기록된 resource의 field대부분은 변경 가능하지만, 변경 불가능한 field도 있다는 점을 기억하자.



- **wait**

  kubectl 명령어를 연속적으로 실행하여 resource를 조작할 때, 다음 명령령어를 실행하기 전에 그때까지 작업한 resource가 의도한 상태가 된 후 다음 명령어를 실행하도록 한다.

  > pod를 예시로 들어본다. (pod외 어떠한 resource에 대해서도 똑같이 사용 가능)

  - `--for` : 특정 상태를 지정

    - `condition=Ready pod` : pod가 기동(ready)하는 상태

      ```
      $ kubectl wait --for=condition=Ready pod/sample-pod
      ```

      > sample-pod가 정상적으로 기동할 때 까지 대기

    - `condition=PodScheduled pod` : pod가 PodScheduled 하는 상태

      ```
      $ kubectl wait --for=condition=PodScheduled pod --all
      ```

      > 모든 pod가 스케줄링 될 때 까지 대기 

    - `delete pod` :  pod 가 삭제되는 상태

      ```
      $ kubectl wait --for=delete pod --all
      ```

      > 모든 pod가 삭제될 때 까지 대기

  - `--timeout` : 기다리는 마지노선 시간. 할당한 시간까지 명령어 실행이 안되면 timeout한다.

  ```
  $ kubectl wait --for=delete pod --all --timeout=5s
  ```

  > 모든 pod가 삭제될 때 까지 pod마다 최대 5초씩 대기.

  

  ```
  $ kubectl wait --for=condition=Ready -f manifest_file.yaml
  ```

  > manifest file을 지정하고 resource가 정상적으로 기동할 때 까지 대기

  









### workload API category

#### pod

#### Replication Controller

#### ReplicaSet

#### Peloyment

#### DaemonSet

#### StatefunSet

#### Job

#### CronJob



### Service API category

#### Service

##### ClusterIP

##### ExternalIP

ClusterIP의 한 종류

##### NodePort

##### Headless(None)

##### ExternalName

##### None-Selector

#### ingress





### config & storage API category

#### Secret

#### ConfigMap

#### PresistentVolumeClaim



### cluster API category

#### Nond

#### Namespace

#### PeristentVolume

#### ResourceQuota

#### ServiceAccount

#### Role

#### ClusterRole

#### RoleBinding

#### ClusterRoleBinding

#### NetworkPolicy





### metadata API category

#### LimitRange

#### HorizontalPodAutoscaler(HPA)

#### PodDisruptionBudget(PDB)

#### CustomResourceDefinition