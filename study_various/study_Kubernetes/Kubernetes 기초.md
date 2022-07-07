# Kubernetes 기초

쿠버네티스는 컨테이너화된 애플리케이션의 배포, 확장 등을 관리하는 것을 자동화하기 위한 플랫픔(컨테이너 오케스트레이션 엔진)이다.



쿠버네티스는 하나의 클러스터를 의미하기도 하며, 쿠버네티스 마스터와 쿠버네티스 노드로 구성되어 있다.

클러스터는 하나 이상의 서버를 묶어 구축을 하게 되는데, 이를 통해 사용자는 여러 서버를 하나의 PC환경처럼 사용할 수 있게 된다.

- cubernetis node(worker node) : 쿠버네티스에서 실제 컨테이너가 가동하는 노드(host가 되는 물리 머신이나 가상 머신) 

  > worker node의 구성 요소
  >
  > kubelet : control plane으로부터 명령을 받고, 자신의 상태를 control plane으로 전달하는 역할을 하는 component

- cubernetis master(control plane) : cubernetis node를 관리하고 모니터링하며, Client로부터 요청이 오면 그 요청에 맞는 worker node를 scheduling해서 해당 node로 요청을 전달한다.

  > control plane의 구성 요소
  >
  > - API server : client로부터 오는 요청을 받는 component
  > - controller manager
  > - etcd(persistence store) : client로부터 오는 요청 key value형식으로 저장하는 component
  > - ...



쿠버네티스는 독립적으로 하나의 플랫폼으로 사용할 수 있지만 외부 에코시스템과의 연계도 활발히 이루어지고 있다. 많은 미들웨어(kubeflow 등의)가 쿠버네티스를 지원하는 추세이다.



### 기본 용어

**kubernetes master** : API 엔드포인트 제공, 컨테이너 스케줄링, 컨테이너 스케일링 등을 담당하는 노드

**kubernetes node** : 도커 호스트에 해당하며 실제로 컨테이너를 기동시키는 노드

**manifest file** : 쿠버네티스 마스터에 resource를 등록하는 file로, YAML 형식으로 작성하는것이 일반적

**cuberctl** : 쿠버네티스 클러스터를 관리하는 CLI도구. manifest file의 정보를 바탕으로 쿠버네티스 마스터가 가진 API에 요청을 보내어 쿠버네티스를 관리한다.

- kubeconfig : kubectl이 kubenetes master와 통신할 때 필요한 '접속 대상의 서버 정보', '인증 정보' 등을 담은 파일이다.



**resource** : 쿠버네티스를 관리하기 위한 API. 쿠버네티스에 의해 리소스 등록을 비동기로 처리할 수 있다.

> container는 하나의 process와 거의 같은 아주 작은 resource다. 또한 pod도 여러 container로 이루어진 작은 resource다. cluster는 pod와 같이 작은 resource를 대량으로 처리한다.

**Custom Resource(CR)** : 쿠버네티스의 API확장판. 

user가 직접 정의한 resource(pod, Deployment, Service 와 같은 것이 아닌, 개발자가 직접 정의)

이러란 CR을 쿠버네티스의 API를 사용해서 관리하고 싶은 경우에 CR의 lifecycle과 동작을 관리할 controller를 구현 후 cluster에 배포해야 한다.

- CR을 cluster에 등록하는 방법에는 Custom Resource Definition(CRD) 방식과 API Aggregation(AA)방식 두 가지가 있다.
  - CRD 방식은 CR을 관리할 Custom Controller를 구현하고 배포하여 사용하게 되며 controller는 대부분 operator pattern으로 개발된다.

> 요약 : 배포된 custom controller에 의해 관리되는 resource이다.
>
> Custom Resource을 개발하기 위해서는 Operator로 개발해야 한다.



**NameSpace** : 가상적인 쿠버네티스 클러스터 분리 기능. 완전한 분리 개념은 아니기 때문에 용도는 제한되지만, 하나의 쿠버네티스 클러스터를 여러 팀에서 사용하거나 서비스 환경/스테이징 환경/개발 환경으로 구분하는 경우 사용할 수 있다.

목적에 따라 임의의 네임스페이스를 생성할 수 있지만, 하나의 쿠버네티스 클러스터를 여러 목적을 지닌 공용의 것으로 사용하지 않고 시스템이 복잡하지 않을 경우에는 기본 네임스페이스를 사용해도 된다.

> NameSpace는 cluster별로 나눠야 한다.

- kube-system : 쿠버네티스 클러스터 구성 요소와 애드온이 배포될 네임스페이스

  관습적으로 쿠버네티스 대시보드 같은 시스템 구성 요소와 애드온을 배포하기 위해 생성되는 네임스페이스.

- kube-public : 모든 사용자가 사용할 수 있는 컨피크맵 등을 배치하는 네임스페이스

  관습적으로 모든 사용자가 공통으로 사용하는 설정값 등을 저장하기 위해 생성되는 네임스페이스

- kube-node-lease : 노드 하트비트 정보가 저장된 네임스페이스

  하트비트 정보를 저장하기 위한 lease리소스가 저장되는 전용 네임스페이스

  관리자 이외에는 그다지 신경 쓰지 않아도 됨

- default : 기본 네임스페이스

  사용자가 임의의 리소스를 등록하는 데 사용됨



**stateless** : client와 server관계에서, server가 client의 상태를 보존하지 않음을 의미

- 장점 : server의 확장성이 높기 때문에 대량의 트래픽 발생 시에도 대처를 수월하게 할 수 있다.
- 단점 : client의 요청에 상대적으로 stateful보다 더 많은 data가 소모된다.

**stateful** : server가 client의 상태를 보존함을 의미



관리형 서비스나 구축 도구로 구축된 경우 대부분의 쿠버네티스 클러스터는 Role-Based Access Contal(RBAC)가 기본값으로 활성화되어 있다.



**Operator pattern**

- **controller** : Desired State와 Current State를 비교하여, Current State를 Desired State에 일치시키도록 지속적으로 동작하는 무한 loof

- **Operator** : Controller pattern을 사용하여 사용자의 application을 자동화하는 것

  > 주로 Custom resource의 Current/Desired State를 지속적으로 관찰하고 일치시키도록 동작하는 역할을 위해 사용된다.
  >
  > seldon-core, kubeflow 등을 포함한 쿠버네티스 생태계에서 동작하는 많은 module이 이러한 Operator로 개발되어 있다.



**Helm** : 쿠버네티스 module의 package managing tool

하나의 kubernetes module은 다수의 resource(.yaml format)를 포함하고 있는 경우가 많은데, 이러한 resource들을 템플릿화 해서 여러개를 하나처럼 관리할 수 있게 도와주는 도구

> Ubuntu의 package managing tool인 apt, python의 package managing tool인 pip와 비슷한 역할



### why cubernetis?

- **선언적 code를 사용한 관리 (Infrastructure as Code)**

  쿠버네티스는 YAML형식이나 JSON형식으로 작성한 선언적 코드(manifest)를 통해 배포하는 컨테이너로 주변 resource를 관리할 수 있어 IaC를 구현할 수 있다.

- **scaling, auto scaling**

  쿠버네티스는 컨테이너 cluster를 구성하여 여러 쿠버네티스 노드를 관리한다.

- **scheduling**

  컨테이너를 쿠버네티스 노드에 배포할 때 어떤 쿠버네티스 노드에 배포할 것인지를 결정하는 단계. Affinity와 Anti-Affinity기능을 사용하여 컨테이너화된 애플리케이션 워크로드의 특징이나 쿠버네티스 노드의 성능을 기준으로 스케줄링 할 수 있다.

- **resource관리**

  컨테이너 배치를 위한 지정이 특별히 없을 경우 쿠버네티스 노드의 CPU나 메모리의 여유 리소스 상태에 따라 스케줄링되기 때문에 사용자는 어떤 쿠버네티스 노드에 컨테이너를 배치할지 관리할 필요가 없다.

- **자동화된 복구**

  다중화 관점에서는 쿠버네티스의 중요한 콘셉트 중 하나인 자동화된 복구 기능이 있다. 쿠버네티스는 표준으로 컨테이너 프로세스를 모니터링하고 프로세스 정지를 감지하면 다시 컨테이너 스케줄링을 실행하여 컨테이너를 자동으로 재배포한다. cluster node에 장애가 발생하거나 node를 축출했을 경우 그 노드의 컨테이너가 사라진다 하더라도 서비스에 영향 없이 애플리케이션을 자동으로 복구할 수 있도록 만들어져 있다.

- **Load Balancing과 Service Discovery**

  **Load Balancing** : 사전에 정의한 조건과 일치하는 컨테이너 그룹에 라우팅하는 엔드포인트를 삭제할 수 있다. 컨테이너를 확장할 때 엔드포인드가 되는 서비스에 컨테이너의 자동 등록과 삭제, 컨테이너 장애 시 분리, 컨테이너 롤링 업데이트 시 필요한 사전 불리 작업도 자동으로 실행해준다. 이를 통해 높은 서비스 레벨을 구현하면서 엔드포인트 관리를 쿠버네티스에게 맡길 수 있다.

  **Service Discovery** : 서비스에 Service Discovery 기능이 있어 각각의 마이크로서비스가 정의된 복수의 매니페스트를 이용하여 시스템 전체를 쉽게 연계할 수 있다.

- **데이터 관리**

  쿠버네티스는 백엔드 데이터 스토어로 etcd를 채용하고 있다. etcd는 클러스터를 구성하여 이중화가 가능하고 컨테이너나 서비스의 매니페스트 파일도 이중과 구조로 저장한다. 또 쿠버네티스는 컨테이너가 사용하는 설정 파일이나 인증 정보 등의 데이터를 저장하는 구조도 가지고 있어 컨테이너 공통 설정이나 애플리케이션에서 사용되는 데이터베이스 인증 정보 등을 안전하고 지우화 된 상태로 쿠버네티스에서 집중적으로 관리할 수 있다.

  

### environment

쿠버네티스는 여러 플랫폼 환경에서 클러스터를 구성하여 사용할 수 있다.

네트워크가 연결되지 않아도 됙 바로 눈으로 확인할 수 있다는 점에서 개인적인 테스트나 개발 환경으로 적당하다.

개발 구서와 공유하여 사용하는 스테이징 및 서비스 환경용 클러스터는 쿠버네티스 구축 도구나 관리형 쿠버네티스 서비스를 사용하는 것이 좋다.

- **로컬 쿠버네티스**

  물리 머신 한 대에 구축하여 사용

  > Docker Desttop for Mac/Windows 설치 후 preference에서 kubenetes 활성화(도커 화면 왼쪽 아래 표시가 Docker Running, Kubernetes running과 같이 보이면 설치에 성공)
  >
  > **kind사용**

- **쿠버네티스 구축 도구**

  도구를 사용하여 온프레미스/클라우드에 클러스더를 구축하여 사용

  온프레미스에 배포하는 경우나 세밀한 커스터마이즈가 필요한 경우에 사용

  > kubeadm사용

- **관리형 쿠버네티스 서비스**

  퍼블릭 클라우드의 관리형 서비스로 제공하는 클러스터를 사용

  > **Google kubernetes engine(GKE)사용**



**Google kubernetes engine(GKE)**

GEK에서는 쿠버네티스 노드로 GCE(Google Compute Engine)가 사용된다. 또 GCE는 선점형 인스턴스라고 불리는, 가동 시간이 24으로 제약되어 있는 저비용 인스턴스를 쿠버네티스 노드로 사용할 수 있다. 선점형 인스턴스를 사용하여 클러스터를 구성하면 비용을 절감할 수 있지만, 선점형 인스턴스를 사용하기 때문에 노드가 정지되는 경우가 있다. 그러나 컨테이너 환경 설정을 서비스 구성에 맞기 설정해 두면 인스턴스가 다시 생성되더라도 서비스에 영향을 미치지 않고도 자동 복구가 가능하다. 

또 선점형 인스턴스만으로 클러스터를 구성하면 24시간 후에 모든 노드가 정지해버릴 수 있기 때문에 랜덤으로 서서히 노드를 교체할 수 있는 preemprible-killer의 사용 등도 검토해 보자.





