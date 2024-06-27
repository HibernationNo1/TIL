# Kubernetes

- 쿠버네티스는 컨테이너화된 애플리케이션의 배포, 확장 등을 관리하는 것을 자동화하기 위한 플랫폼(컨테이너 오케스트레이션 엔진)이다.

- 쿠버네티스 마스터와 쿠버네티스 노드로 구성되어 있다.

  cluster 그림 삽입

  1개의 master node, N개의 worker node로 구성된 kubernetes환경을 쿠버네티스 클러스터(Kubernetes Cluster)라고 한다.

- kubernetest를 구성하는 주요 resource 유형

  - **Pod**: 쿠버네티스에서 가장 기본적인 배포 단위로, 하나 이상의 컨테이너를 포함할 수 있다. 포드는 일반적으로 서로 긴밀하게 연관된 컨테이너들로 구성된다.

  - **Service**: 포드 집합에 대한 안정적인 네트워크 주소를 제공한다. 서비스는 네트워크 트래픽을 적절한 포드로 라우팅하는 로드 밸런서 역할을 한다.

  - **Deployment**: pod와 ReplicaSet를 관리한다. 스케줄링, 복제 관리, 자동 생성 등을 제공한다.

  - **ReplicaSet**: 지정된 수의 포드 복제본이 클러스터에 항상 실행되도록 보장한다. 일반적으로 디플로이먼트에 의해 관리된다.

  - **Namespace**: 클러스터 내의 리소스를 격리된 그룹으로 나누어 관리할 수 있게 하는 가상의 클러스터. 네임스페이스는 리소스 할당, 접근 권한 분리 등을 위해 사용된다.

  - **ConfigMap**: 구성 데이터를 포드에 주입하는 데 사용되는 API 오브젝트. 환경변수, 커맨드 라인 인수 등을 설정할 때 사용된다.

  - **Secret**: 패스워드, OAuth 토큰, SSH 키 같은 민감한 정보를 저장하는 데 사용된다.

  - **Volume**: 디스크 공간 또는 스토리지 리소스를 포드에 할당하는 방법을 제공한다. 볼륨은 네트워크 스토리지, 로컬 스토리지 등 다양한 백엔드를 지원할 수 있다.

  - **Ingress**: 외부 요청을 클러스터 내의 서비스로 라우팅하는 규칙을 정의. 보통 도메인/URL 기반 라우팅을 설정하는 데 사용된다.

  resource 그림 삽입

  일부 리소스(예: ConfigMap, Secret, Deployment)는 마스터 노드에서 관리되지만, 그 효과는 워커 노드에 있는 파드에 적용된다.

  모든 실제 컴퓨팅 작업(파드 실행, 볼륨 처리)은 워커 노드에서 수행된다.

  마스터 노드는 클러스터의 상태를 관리하고, 워커 노드의 리소스를 조정하고, API를 통해 클러스터와 상호 작용작용한다.

- kubernetest를 구성하고 관리하는 tool

  Kubernetes 클러스터의 설치, 관리, 운영을 위한 핵심적인 구성 요소

  - **kubeadm**

    새 Kubernetes 클러스터를 쉽게 생성하거나, 기존 클러스터를 확장할 때 사용되는 tool.

    Node 초기화와 업그레이드, 클러스터의 구성 요소 관리 등이 표준화된 방법으로 수행될 수 있다.

  - **kubelet**

    모든 Kubernetes 노드에서 실행되는 핵심 구성 요소로, Pod의 생성, 삭제 및 관리를 담당하는 tool

    Kubernetes의 마스터 구성 요소와 통신하여 노드와 Pod의 정보를 보고한다.

  - **kubectl**

     Kubernetes 클러스터를 조작하는 커맨드라인 인터페이스(CLI) 도구

     Kubernetes 클러스터를 조작할 때 `kubectl` 명령어를 사용하여 제어한다.

  





## Pod

- 쿠버네티스 클러스터에서 애플리케이션을 실행하는 배포 단위.

- 한 개 이상의 리눅스 컨테이너로 구성되며, 쿠버네티스 워커노드에 배치되어 실행된다.

  pod_1, pod_2 그림 삽입

- 쿠버네티스의 목적이 바로 파드들을 안정적이고 효율적으로 클러스터 내에서 실행시키는 것이다.

  예시

  - 파드 3개를 실행시켜달라고 쿠버네티스에 명령하면 쿠버네티스가 자동으로 파드 3개를 클러스터 내부에 배포

  - 파드에 버그가 발생하면 자동으로 해당 파드를 종료하고 새로운 파드를 재실행
  - 파드의 버전이 업그레이드가 되면 자연스럽게 예전 버전의 파드를 제거하고 새로운 버전의 파드가 실행되는 동작 수행

이러한 pod들의 동작을 제어하기 위해 **Deployment**, **ReplicaSet** 를 사용한다



## ReplicaSet

지정된 수의 파드 복제본이 클러스터에 항상 존재하도록 보장하는 Kubernetes 리소스. 

ReplicaSet의 주요 목적은 안정적으로 지정된 수의 동일한 파드를 유지하는 것으로, 이는 시스템의 장애 내성을 높이고, 여러 노드에 걸쳐 파드를 분산시켜 부하를 분산시키는 데 유용하다.

- **복제본 유지 관리**: ReplicaSet은 원하는 복제본 수를 유지한다. 파드가 종료되거나 삭제될 경우, ReplicaSet은 새 파드를 생성하여 원하는 복제본 수를 유지한다.

- **부하 분산 및 장애 내성 향상**: 여러 복제본을 사용함으로써 애플리케이션의 부하를 여러 서버에 분산시키고, 하나의 서버 또는 인스턴스에 문제가 발생해도 서비스가 계속 작동하도록 할 수 있다.

- ReplicaSet은 특정 라벨 셀렉터를 사용하여 관리해야 할 파드를 정의한다. 이

  셀렉터는 ReplicaSet이 관리하는 파드와 일치해야 하며, 이를 통해 ReplicaSet은 파드의 생성, 삭제 및 교체를 관리하게된다. 

  Deployment와 달리 ReplicaSet은 파드의 업데이트 방식을 관리하지 않으며 단순히 지정된 수의 파드가 유지되는 것을 보장한다.

> Deployment를 정의하여 배포한다면, ReplicaSet은 따로 정의하여 배포하지 않아도 된다. (Deployment에서 내부적으로 ReplicaSet 을 지정하기 때문에)





## Deployment

Deployment는 애플리케이션 인스턴스들의 상태를 원하는 상태(Desired State)에 맞춰 관리하며, 특히 애플리케이션의 배포, 스케일링, 업데이트를 쉽고 안정적으로 처리할 수 있도록 설계되었다.

- **자동화된 롤아웃 및 롤백**: Deployment는 애플리케이션을 새 버전으로 점진적으로 롤아웃할 수 있으며, 문제가 발생할 경우 이전 버전으로 롤백할 수 있다.
- **선언적 업데이트**: 사용자는 원하는 상태를 Deployment 리소스를 통해 선언하고, Kubernetes는 실제 상태를 원하는 상태에 맞게 조정한다.
- **스케일링**: Deployment는 애플리케이션의 복제본 수를 쉽게 늘리거나 줄일 수 있다. 이를 통해 부하에 따라 애플리케이션을 자동으로 스케일링할 수 있다.
- **자가 치유**: Deployment는 실패한 컨테이너를 자동으로 교체한다. 이는 애플리케이션의 가용성을 높여줍니다.
- Deployment는 내부적으로 **ReplicaSet**을 생성하여 지정된 수의 파드 복제본을 유지 관리한다.
- Deployment 구성에 변경이 발생하면, Deployment는 새 ReplicaSet을 생성하여 새로운 설정에 따라 파드를 롤아웃하고, 이전 ReplicaSet의 파드를 점진적으로 줄인다.



#### create

```
$ vi depolyment-example.yaml
```

```
apiVersion: apps/v1
kind: Deployment
metadata:
  name: deployment-name		# Deployment의 이름 정의
  labels:
    app: app-name-example	# Deployment의 label정의. 일반적으로 matchLabels와 같은 값
spec:
  replicas: 1
  selector:
    matchLabels:
      app: app-name-example
  template:
    metadata:
      labels:
        app: app-name-example		# matchLabels에서 설정한 값 과 일치해야함
    spec:
      containers:
      - name: container-name-example
        image: {container_registry_IP}:{container_registry_Port}/image_example:latest
        command: ["sh", "start.sh"]  
        ports:
        - containerPort: 10010
        env:
        - name: NVIDIA_VISIBLE_DEVICES
          value: "0"
          value: "10015"
        volumeMounts:
        - mountPath: /workspace
          name: workspace
        - mountPath: /sample
          name: sample
        resources:
          limits:
            nvidia.com/gpu: 1
      volumes:
      - name: workspace
        persistentVolumeClaim:
          claimName: workspace-pvc-example
      - name: sample
        persistentVolumeClaim:
          claimName: sample-pvc-example
```

```
$ kubectl apply -f yolo-api-depolyment.yaml
```

- **GPU는 cluster에 소속된 node중에서 제약없이 가져다 사용한다.**

  특정 node의 GPU만 할당하고자 한다면 `spec.affinity.nodeAffinity` 를 할당해야 한다.

  ```
      spec:
        affinity:
          nodeAffinity:
            requiredDuringSchedulingIgnoredDuringExecution:
              nodeSelectorTerms:
              - matchExpressions:
                - key: kubernetes.io/hostname
                  operator: In
                  values:
                  - sirs-system-product-name  # 특정 노드의 이름을 지정
  ```

  replicas 의 숫자가 cluster에 속한 GPU보다 적은 숫자면, GPU의 개수만큼의 pod가 생성되며, 나머지 pod는 pending상태가 된다.

- volume은 PVC를 주로 사용한다. 

  volume을 hostpath으로 사용하면 mount가 안되는 경우가 많으며, 보안적으로도 위험하다.  

- command 에서 아무 동작 없이, 하지만 container가 종료되지 않기 하기 위해선 아래와 같이 정의한다.

  ```
  command: ["sh", "-c", "sleep infinity"]  # 컨테이너가 종료되지 않도록 설정
  ```

- image를 localhost에서 추적하지 못한다. registry에 push되어 있거나, load상태로 존재하는 image만 추적할 수 있다. 

  - docker registry는 https 프로토콜을 사용하기 때문에 각 node에서 docker registory의 image를 pull하기 위해선 아래와 같이 설정해야 한다.

    ```
    $ sudo vi /etc/docker/daemon.json
    ```

    ```
    {
        "default-runtime": "nvidia",
        "runtimes": {
            "nvidia": {
                "path": "nvidia-container-runtime",
                "runtimeArgs": []
            }
        },
        "insecure-registries": ["http://{container_registry_IP}:{container_registry_Port}"]
    }
    ```

    적용: `$ sudo systemctl restart docker`

    확인: `$ docker info`  (insecure-registries 제대로 적용됨 확인)

    `ubuntu 20.04`, `docker 26` 이상의 version을 사용해야 daemon 파일의 내용이 제대로 적용된다.

    







## Ingress



## Service

- 포드 집합에 대한 안정적인 네트워크 주소를 제공한다.

- 네트워크 트래픽을 적절한 포드로 라우팅하는 로드 밸런서 역할을 수행한다.

- Service는 selector 범위에 포함 된 pod에 대해서만 관리한다.

  service_selector 그림 삽입

  pod를 구성할 때 label을 selector와 같은 값으로 구성하면 service의 범위에 포함된다. 

- Service는 Node와 Pod를 관리할 때, 각각의 Node에 위치한 kube-proxy를 활용한다.

  kube-proxy는 마스터 노드의 etcd에서 서비스와 엔드포인트의 정보를 주기적으로 가져와서 자신의 라우팅 테이블을 갱신한다

  - **kube-proxy**: 서비스의 정의를 바탕으로 들어오는 네트워크 트래픽을 적절한 파드로 포워딩하는 역할을 수행

  - **etcd**: Kubernetes의 모든 리소스와 상태, 예를 들어 파드, 서비스, 레플리카셋의 구성과 상태 정보를 key-value 형태로 저장하는 저장소

    모든 중요한 정보를 etcd에 저장함으로써, Kubernetes는 중앙 집중식으로 클러스터의 상태를 관리하고 감시할 수 있다.

  kube-proxy 그림 삽입





### Service type

- **ClusterIP**: 클러스터 내부 트래픽을 위한 기본 서비스 유형. 이 서비스는 내부 IP를 사용하여 클러스터 내부에서만 접근할 수 있다.

- **NodePort**: 외부 트래픽을 특정 노드의 포트를 통해 파드로 라우팅할 수 있게 한다. 

  이 경우 외부의 요청이 특정 노드의 포트로 들어오면, kube-proxy가 클러스터 내의 적절한 파드로 트래픽을 라우팅합니다.

- **LoadBalancer**: 외부 로드 밸런서를 사용하여 트래픽을 파드로 분산한다. 

각 서비스는 서로 다른 트래픽 요구사항을 충족시키기 위해 존재하기 때문에 하나의 쿠버네티스 클러스터 내에서 ClusterIP, NodePort, LoadBalancer 등 여러 유형의 서비스를 동시에 만들고 운영한다.



#### ClusterIP

ClusterIP는 쿠버네티스 클러스터 내부에서만 접근할 수 있는 내부 IP 주소를 서비스에 제공. (default type)

클러스터 외부에서는 접근할 수 없으므로 클러스터 내부 통신에 사용된다.



**예시**

`Worker node 1`에 8007 port를 사용하는 **API_A**가 있고, `Worker node 2`에 8008 port를 사용하는 **API_B**가 있고

**API_A**는 내부 동작 중 **API_B**에 request를 보내는 동작이 포함되어 있을 때 ClusterIP 의 동작 예시

- ClusterIP구성

  ```
  apiVersion: v1
  kind: Service
  metadata:
    name: my-clusterip-service
  spec:
    selector:
      app: myapp
    ports:
      - protocol: TCP
        port: 8008
        targetPort: 9376
    type: ClusterIP
  ```

  그 동작은 아래와 같다.

  ClusterIP 그림 삽입





**Description**

- selector에 의해 지정된 모든 파드로 트래픽을 라우팅할 수 있기 때문에 load balancer역할도 가능하다.

  ClusterIP_2 그림 삽입



#### NodePort

NodePort 서비스는 클러스터 외부에서 파드로의 접근을 허용하는 역할을 한다.



**예시**

두 개의 Worker Node가 있고, Master Node에 NodePort 타입의 Service를 아래와 같이 정의했을 때

```
apiVersion: v1
kind: Service
metadata:
  name: example-nodeport-service
spec:
  type: NodePort		# type 선언
  selector:
    app: myapp  # 해당 파드를 선택하는 레이블
  ports:
  - protocol: TCP
    port: 10010  			# 서비스 자체가 클러스터 내에서 사용하는 포트     
    targetPort: 10010  		# 파드에서 실제로 리스닝하고 있는 포트    
    nodePort: 30010  		#  클러스터 외부에서 서비스에 접근할 때 사용하는 포트
```

> - **nodePort**: 모든 node의 해당 port를 LISTEN 상태로 설정한다.
>
> - **targetPort**: 파드에서 실제로 리스닝하고 있는 포트
>
>   - 이 포트로 서비스에서 라우팅된 트래픽이 전달된다.
>   - 파드는 해당 포트에서 트래픽을 수신하도록 설정되어 있어야 한다.
>
> - **port**: 서비스 자체가 클러스터 내에서 사용하는 포트
>
>   클러스터 내부에서 이 10010  port를 사용하는 서비스(APP)를 찾을 때 사용된다.

그 동작은 아래와 같다.

NodePort 그림 삽입



```
$ kubectl get svc example-nodeport-service
```

```
NAME                              TYPE       CLUSTER-IP     EXTERNAL-IP   PORT(S)           AGE
example-nodeport-service          NodePort   10.100.19.59   <none>        10010:30010/TCP   2m1s
```





**Description**

- node가 수백개로 구성된 클러스터라도, Nodeport는 모든 node에 대해 30010 포트를 하나의 API에 대응되도록 하기 때문에 

  외부에서는 클러스터를 마치 하나의 거대한 서비스로 인식할 수 있게 된다.

  ???: NodePort 사용 시 NodePort가 어느 IP에서 배포되는가와 상관 없이, 요청은 결국 서비스가 동작하고 있는 node의 IP를 명시해야 하기 때문에, 그냥 docker로 배포하는것과 다를것이 없다.

- 단점

  - **포트 충돌**: NodePort 서비스는 사용 가능한 포트 범위(기본적으로 30000-32767) 내에서 포트를 할당받는다.

    포트 번호가 제한적이므로, 많은 수의 NodePort 서비스를 사용하고자 할 때 포트 번호 충돌이 발생할 수 있다.

    ```
    The Service "yolo-api-service" is invalid: spec.ports[0].nodePort: Invalid value: 10010: provided port is not in the valid range. The range of valid ports is 30000-32767
    ```

  - **효율성 문제**: 모든 노드가 트래픽을 받을 준비가 되어 있으므로, 네트워크 트래픽이 분산되는 방식이 최적화되지 않을 수 있다. 
  
    예를 들어, 일부 노드에만 트래픽이 집중될 수 있다.
  
    이런 경우 LoadBalancer 를 사용하여 트래픽을 분산시켜주어야 한다.







#### LoadBalancer

클라우드 제공 업체가 제공하는 서비스(예: AWS의 ELB, Google Cloud의 Cloud Load Balancing, Azure의 Load Balancer)를 통해 구현된 외부 로드 밸런서를 사용한다.

로드 밸런서는 인터넷에서 들어오는 트래픽을 클러스터의 여러 노드에 분산시켜 서비스의 가용성과 내구성을 증가시킨다.

- **클라우드 환경**: LoadBalancer 타입을 사용하면, 클라우드 제공 업체의 로드 밸런싱 솔루션을 통해 트래픽 관리가 자동으로 이루어진다.

- **비클라우드 환경**: 클라우드 환경이 아닌 경우, 자체 로드 밸런싱 솔루션을 설정해야 하거나, NodePort와 같은 다른 방법을 사용해 외부 트래픽을 관리해야 한다. 

  이 경우, MetalLB와 같은 솔루션을 사용하여 온-프레미스 환경에서도 LoadBalancer 기능을 모방할 수 있다.

```
apiVersion: v1
kind: Service
metadata:
  name: my-loadbalancer-service
spec:
  selector:
    app: myapp
  ports:
    - protocol: TCP
      port: 80
      targetPort: 9376
  type: LoadBalancer
```





### Compare with Nginx

**Service 와 Nginx의 공통점**

- 다수의 요청이 있을 때, 여러 server로 요청을 균일하기 분산하는 load balance 역할 수행

- TCP(Transmission Control Protocol)와 UDP(User Datagram Protocol) 트래픽 지원

  > TCP, UDP:  TCP/IP (Transmission Control Protocol / Internet Protocol)계층 프로토콜
  >
  > - TCP:  네트워크에서 데이터를 신뢰성을 보장하여 전송하는 데 사용되는 연결형 프로토콜
  >
  >   1. 3-way handshake 이라는 신뢰 확인 과정을 거치며 연결을 설정한다.
  >      - 3-way handshake: 네트워크 상의 양 당사자가 신뢰가 있음을 확인하기 위해 수행
  >   2. 연결이 설정되면 데이터를 전송한다.
  >   3. 데이터 전송 과정이 끝나면 4-way handshake이라는 신뢰 확인 세션을 종료한다.
  >      - 4-way handshake: 네트워크 상의 양 당사자가 모두 데이터 전송이 완전히 끝났음을 확인하고 연결을 안전하게 종료하기 위해 수행
  >
  >   3_4-way handshake 그림 삽입
  >
  >   TCP가 사용하는 응용 계층(Application Layer) 프로토콜
  >
  >   - HTTP(HyperText Transfer Protocol): 웹 페이지와 관련 리소스를 전송하는 데 사용
  >
  >   - HTTPS(HyperText Transfer Protocol Secure): SSL/TLS를 사용하여 HTTP 통신을 암호화
  >
  >     - SSL/TLS
  >
  >       **SSL (Secure Sockets Layer)** 과 **TLS (Transport Layer Security)** 는 인터넷 통신의 보안을 위해 설계된 프로토콜
  >
  >       이들은 HTTPS를 사용할 때 암호화, 인증, 무결성 보장을 제공한다.
  >
  >       SSL은 이제 구식이 되어 TLS가 그 자리를 대체했다.
  >
  >   - FTP(File Transfer Protocol): 파일을 전송하는 데 사용
  >
  >   - SMTP(Simple Mail Transfer Protocol): 이메일을 전송하는 데 사용
  >
  >   - Telnet: 원격 컴퓨터에 로그인하는 데 사용되는 텍스트 기반 프로토콜
  >
  > - UDP: 비연결형 프로토콜로, 데이터 전송에 대한 신뢰성을 보장하지 않는다.
  >
  >   1. 데이터를 전송한다.   데이터 전송 과정이 끝나면 연결을 자동으로 종료한다.
  >
  >   UDP가 사용하는 응용 계층(Application Layer) 프로토콜
  >
  >   - DNS(Domain Name System): 클라이언트가 DNS 서버에 UDP 요청을 보내 도메인 이름에 대한 IP 주소를 조회
  >
  >   - DHCP(Dynamic Host Configuration Protocol): 네트워크 장치에 IP 주소와 기타 네트워크 설정을 자동으로 할당
  >
  >     라우터는 DHCP 서버 기능을 내장하여 네트워크에 연결된 디바이스에 자동으로 IP 주소를 할당한다.
  >
  >   - VoIP (Voice over Internet Protocol): 인터넷을 통해 음성 통신을 할 때 사용
  >
  >   - Video streaming applications: 비디오 스트리밍 서비스에 사용





**Service는 불가능하고, NginX는 가능한 역할**

- reverse proxy

  들어온 요청에 대해 응용 계층(Application Layer) 프로토콜의 변환을 수행한다.

  클라이언트가 직접 서버에 접근하는 것이 아니라 리버스 프록시가 클라이언트의 요청을 받아 전처리하여 전달하는 역할

  예를 들어, 보안 protocol(HTTPS)을 통해 들어온 요청을 내부 네트워크에서는 protocol HTTP로 처리할 수 있게 해준다.

  NginX 그림 삽입

  이 기능은 특히 SSL/TLS 종료를 외부에서 처리하고, 내부 네트워크에서는 암호화되지 않은 통신을 용이하게 할 때 유용하다.

- 캐싱 수행

  자주 요청되는 리소스를 로컬에 저장하고, 이를 클라이언트에게 빠르게 제공하여 서버의 부하를 줄이고 응답 속도를 향상시킨다.

- 쿠버네티스 환경에서 Nginx를 사용하려면 쿠버네티스의 인그레스 컨트롤러로서 구성하여 사용해야한다.





**Service는 가능하고, NginX는 불가능한 역할**

- **Auto routing**

  클러스터 내의 파드로 트래픽을 자동으로 라우팅하여, 클라이언트가 파드의 특정 인스턴스에 대해 신경 쓰지 않도록 한다.

  Nginx는 APP의 IP가 변경되면 Nginx 설정 파일을 수동으로 업데이트하고 프록시 서비스를 재시작해야 한다.

  반면 Service는 APP을 pod에 띄우고, pod의 label과 Service의 selector를 사용하여 라우팅을 관리한다.

  - Service의 selector

    서비스가 트래픽을 전달해야 하는 파드를 식별하는 데 사용되는 것으로, 키-값 쌍의 집합으로 정의되어 있으며 서비스를 생성할 때 지정된다.

    서비스 셀렉터는 해당 셀렉터와 일치하는 라벨을 가진 모든 파드에 트래픽을 라우팅한다.

  - 파드가 충돌하거나 새로운 파드가 생성될 때 자동으로 이전의 pod의 label과 같은 label을 가진 pod 가 생성되도록 다른 관리형 리소스로 제어할 수 있다.

  파드가 충돌하거나 새로운 파드가 생성될 때 자동으로 네트워크 트래픽을 적절한 파드로 리다이렉트하는 능력을 포함

- **Dynamically redirection**

  파드가 시작되거나 종료될 때, 쿠버네티스는 해당 파드의 라이프 사이클을 모니터링하고, 서비스에 지정된 셀렉터 기준에 맞는 파드에 자동으로 트래픽을 전달하도록 설정한다.

- **Service discovery**

  쿠버네티스 DNS는 서비스 이름을 DNS 레코드로 유지하며, 이를 통해 파드는 서비스 이름을 사용하여 서로를 찾고 통신할 수 있다.

  이 방식으로, 파드의 IP 주소가 변경되더라도 서비스 이름은 동일하게 유지되어 연속적인 통신이 가능하다.

  - 쿠버네티스 DNS

    쿠버네티스 클러스터 내에서 동작하는 DNS 서버로, 클러스터 내의 서비스와 파드에 대한 DNS 레코드를 자동으로 관리한다.

    쿠버네티스 DNS는 일반적으로 클러스터가 초기화될 때 자동으로 배포된다.





## PersistentVolume

**PersistentVolume (PV)**: 클러스터 관리자가 생성하고 클러스터 내에서 사용할 수 있는 스토리지 자원을 정의하는 리소스

PV는 클러스터에서 사용할 수 있는 물리적 스토리지 또는 네트워크 스토리지와 같은 외부 스토리지를 추상화하여 제공한다.



Persistent Volume 으로 사용할 수 있는 Stoage는 여러가지가 있다.

- `AWS Elastic Block Store (EBS)`: WS의 블록 스토리지 서비스로, 특정 AWS EC2 인스턴스에 연결하여 사용
- `Azure Disk`: Azure의 관리형 디스크 서비스로, Azure VM에 연결하여 사용
- `Google Persistent Disk (GPD)`: Google Cloud의 블록 스토리지 서비스로, Google Cloud VM에 연결하여 사용
- `nfs(Network File System)`



```
$ vi pv_example.yaml
```

```
apiVersion: v1
kind: PersistentVolume
metadata:
  name: workspace-pv-example
spec:
  capacity:
    storage: 10Gi
  accessModes:
    - ReadWriteMany
  nfs:
    path: /path/of/workspace
    server: 192.168.110.206
```

- `accessModes`: PV에 대한 접근 모드를 정의

  - **ReadWriteOnce (RWO)**: 하나의 노드에서 읽기/쓰기가 가능

    데이터베이스와 같은 단일 인스턴스 애플리케이션에서 사용된다.

  - **ReadOnlyMany (ROX)**: 여러 노드에서 읽기가 가능합니다.

    로그 파일이나 백업 데이터 등 읽기 전용 데이터를 여러 노드에서 액세스할 때 사용된다.

  - **ReadWriteMany (RWX)**: 여러 노드에서 읽기/쓰기가 가능합니다.

    여러 인스턴스가 동시에 데이터에 읽기/쓰기 접근해야 하는 분산 파일 시스템 또는 공유 데이터 애플리케이션에서 사용된다.

  - **ReadWriteOncePod (RWOP)**: 단 하나의 파드에서만 읽기/쓰기가 가능

    특정 파드에서만 독점적으로 볼륨에 접근할 때 사용된다.

  하나의 accessModes 에 여러개의 mode를 할당할 수 있다.



#### NFS 설정

1. nfs 설치

   ```
   $ sudo apt-get update
   $ sudo apt-get install nfs-kernel-server
   ```

2. 공유할 path 추가

   ```
   $ sudo vi /etc/exports
   ```

   아래 내용 추가 (no_root_squash 설정을 해야 클라이언트의 root 사용자가 서버의 root 사용자로 동작할 수 있도록 하기 때문에 permission denied error가 발생하지 않는다.)

   ```
   /path/of/workspace 192.168.110.0/24(rw,sync,no_subtree_check,no_root_squash)
   ```

3. nfs 활성화

   ```
   $ sudo systemctl enable nfs-kernel-server
   $ sudo systemctl start nfs-kernel-server
   ```

4. 확인

   - 설정파일 적용 되었는지 확인

     ```
     sudo exportfs -v
     ```

   - 설정파일 경로 접근 가능한지 확인(mount test)

     ```
     sudo mount -t nfs 192.168.110.206:/path/of/workspace /mnt
     ```

     



## PersistentVolumeClaim

**PersistentVolumeClaim (PVC)**: 사용자(또는 애플리케이션)가 특정 스토리지 리소스를 요청할 때 사용하는 리소스

 PVC가 생성되면 Kubernetes는 PVC의 요청에 맞는 PV를 찾아서 binding한다.

- **pvc를 사용하는 이유**

  - **추상화와 분리**: PV는 클러스터 관리자가 프로비저닝하는 스토리지 리소이지만, PVC는 개발자가 필요한 스토리지 리소스를 요청하는 방식이다.

    이를 통해 스토리지 프로비저닝과 사용의 책임을 분리할 수 있다.

  - **동적 프로비저닝**: PVC를 사용하면 동적으로 스토리지를 생성하고 관리할 수 있습니다. 스토리지 클래스를 사용하여 자동으로 PV를 생성할 수 있다.(단 프로비저닝 기능을 사용해야 함)

  - **재사용성과 관리**: PV는 클러스터의 공유 자원으로 존재하며, PVC를 통해 요청된 스토리지를 다른 사용자나 애플리케이션이 재사용할 수 있다.

  - **정책 기반 관리**: PVC를 통해 스토리지 요구사항(예: 크기, 액세스 모드 등)을 명확하게 정의할 수 있다.



```
$ vi pvc_example.yaml
```

```
apiVersion: v1
kind: PersistentVolumeClaim
metadata:
  name: workspace-pvc-example
spec:
  volumeName: workspace-pv-example
  accessModes:
    - ReadWriteMany
  resources:
    requests:
      storage: 10Gi
```

- `volumeName` : PV 이름 명시
- `storage`: PV의 storage보다 작거나 같아야 한다.

