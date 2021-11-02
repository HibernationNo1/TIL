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