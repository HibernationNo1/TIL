# etcd

**CoreOS** 에서 개발한 **Etcd**는 분산 시스템에서 사용되는 고가용성, 고신뢰성의 분산 키-값(key-value) 저장소로, 주로 cluster 환경에서 메타데이터 관리, 서비스 디스커버리, 분산 시스템의 상태 관리를 위해 사용된다.

- **주요 특징**
  - 모든 데이터가 디스크에 저장된다.
  -  고가용성 및 일관성 중심으로 설계되어 성능보다는 안정성 우선되어있다.  장애 발생 시 데이터 복구와 지속적인 서비스 제공을 지원한다
  - 쉽고 직관적인 API:    HTTP/gRPC API를 통해 데이터를 읽고 쓰는 작업을 단순화한다.

- **Etcd의 주요 기능**

  - 키-값 저장

    간단한 데이터 저장 방식으로 키와 값을 저장하며, 분산 환경에서도 데이터의 일관성을 보장한다.

  - 클러스터 구성 관리

    클러스터의 구성 요소 상태를 관리한다.  예를 들어, Kubernetes는 노드의 상태 및 리더 선출에 Etcd를 사용한다.

  - service discovery

    클러스터 내의 서비스 정보를 관리하며, 각 서비스와 해당 IP 및 포트를 연결한다.

    각 서비스는 시작 시 자신의 위치(IP 주소, 포트 번호)를 Etcd에 등록하며, 클라이언트는 Etcd에서 특정 서비스의 정보를 **검색**하여 동적으로 위치를 확인하고 요청을 보낸다.

    - Service Discovery란?

      분산 시스템에서 동적으로 변화하는 서비스의 위치(IP/포트)를 찾는 과정을 의미한다.

      분산 환경에서는 서비스가 동적으로 스케일링되거나 이동하기 때문에 고정된 주소로 접근이 불가능하기 때문에 Service Discovery 가 필요로 한다.

      - 예시
        - DNS 기반: 서비스 이름을 DNS 엔트리로 등록하여 사용.
        - Etcd 기반: 서비스 정보를 Etcd에 저장하고 클라이언트가 이를 검색.

  - 분산 합의(Consensus)

    Raft 알고리즘을 사용하여 모든 노드가 동일한 데이터를 갖도록 하여 데이터의 일관성을 보장한다.

    - Raft algorithm이란?

      분산 시스템에서 노드들이 동일한 상태를 유지하도록 보장하는 알고리즘인 `합의(Consensus) algorithm`이다.

  - 워치(Watch)

    특정 키에 대한 변경 사항을 실시간으로 감지하여 다른 서비스와 동기화할 수 있다.

- **일관성 보장 방법**

  Raft algorithm을 사용한다.  Raft algorithm 은 아래 세 가지의 단계를 수행한다.

  - 리더 선출(Leader election)

    클러스터 내에서 하나의 리더(Leader)를 선출하고, 모든 쓰기 작업은 리더를 통해서만 수행된다.

    리더는 데이터 변경 사항을 팔로워(Follower) 노드에 복제한다.

  - 쓰기 작업

    리더는 변경 내용을 **WAL(Write Ahead Log)**에 기록한 후 팔로워 노드로 전파한다.

    - WAL: 모든 쓰기 작업을 디스크에 기록한 후 실행하는 방식

  - 장애 복구

    리더가 장애를 일으키면 새로운 리더를 선출하여 작업을 지속한다.

    데이터는 디스크 및 로그로 저장되어 복구 가능성이 높다.



### install

#### with docker-compose

```
version: '3.8'
services:
  etcd:
    image: quay.io/coreos/etcd:v3.5.17-arm64		#  mac환경: arm64 cpu architecture 전용 image
    container_name: etcd-arm64-test
    environment:
      - ALLOW_NONE_AUTHENTICATION=yes 				# 인증 없이도 작동 가능 (필요에 따라 설정 변경)
      - ETCD_NAME=milvus-etcd           				# 노드 이름
      - ETCD_DATA_DIR=/etcd-data      				# container 내부 etcd 데이터 저장소
      - ETCD_AUTO_COMPACTION_MODE=revision		# 자동 컴팩션(Automatic Compaction) 모드 설정
      - ETCD_AUTO_COMPACTION_RETENTION=1000		# 유지할 리비전 수
      - ETCD_QUOTA_BACKEND_BYTES=4294967296		# etcd 데이터베이스(ETCD_DATA_DIR)의 최대 크기를 4GB로 제한 (byte단위, default=2GB)
      - ETCD_SNAPSHOT_COUNT=50000					# transaction 기준으로 snapshot 주기 설정
    volumes:
      - ./etcd-data:/etcd-data        # 로컬 디렉토리 마운트
    ports:
      - "2379:2379"                   # 클라이언트 통신 port
      - "2380:2380"                   # etcd 클러스터 내 노드들 간의 통신하기 위한 port
    restart: unless-stopped			# 컨테이너가 충돌 후 자동으로 재시작되도록 설정.
    command:
      - etcd
      - --listen-client-urls=http://0.0.0.0:2379    # 클라이언트 요청을 수신할 URL
      - --advertise-client-urls=http://milvus-etcd:2379 # 클라이언트에게 광고할 URL
      - --listen-peer-urls=http://0.0.0.0:2380      # etcd 노드 간 통신을 위한 URL

# docker-compose -f docker-compose.yaml up -d

# health check: curl http://localhost:2379/health
```

- `ETCD_INITIAL_CLUSTER_STATE`

  - new: etcd가 최초소 cluster에 포함되는 경우

  - existing: 이미 etcd가 있는 cluster에 새로운 etcd를 또 추가하는 경우. 

    - 이런 경우에는 새 노드(etcd)는 기존 cluster 상태를 복제하고, 클러스터에 참여하게 된다.

    - 이런 경우에는 `ETCD_INITIAL_CLUSTER`값이 기존 cluster의 구성 정보(노드 주소)가 포함되어야 한다.

- `ETCD_AUTO_COMPACTION_MODE`: 자동 컴팩션(Automatic Compaction) 모드 설정

  - `revision`: revision단위 compaction

    수정 이력의 리비전 개수를 기준으로 불필요한 데이터를 정리

    `ETCD_AUTO_COMPACTION_RETENTION` 으로 보존할 revision의 수를 설정한다.

    ```
    ETCD_AUTO_COMPACTION_MODE=revision
    ETCD_AUTO_COMPACTION_RETENTION=1000
    ```

  - `periodic` : 주기적 compaction

    시간 간격을 기준으로 불필요한 데이터를 정리

    `ETCD_AUTO_COMPACTION_RETENTION` 으로 시간 단위로 주기 설정이 가능하다.

    ```
    ETCD_AUTO_COMPACTION_MODE=periodic
    ETCD_AUTO_COMPACTION_RETENTION=1
    ```

- Automatic Compaction이란?

  디스크 공간을 최적화하기 위해 과거 데이터를 정리하는 기능

  - revision: revision 단위로 과거 데이터를 컴팩션(삭제)

    - revision이란?

      etcd에서 데이터 수정의 단위(버전 번호)를 의미하며 etcd에서 데이터가 추가, 수정 또는 삭제될 때마다 새로운 revision이 생성된다.

      ```
      •	초기 상태: revision = 1 (빈 데이터베이스)
      •	PUT key1 value1 → revision = 2
      •	DELETE key1 → revision = 3
      ```





