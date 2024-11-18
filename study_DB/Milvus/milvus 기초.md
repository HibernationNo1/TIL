# Milvus

벡터 데이터(예: 이미지, 동영상, 오디오, 텍스트 등의 임베딩)를 저장하고 검색하는 데 최적화된 **오픈소스 vector 데이터베이스**이다.

벡터 데이터베이스는 이미지, 오디오, 비디오, 텍스트 콘텐츠와 같은 데이터 항목의 본질을 포착하는 벡터 임베딩 및 수치 표현을 통해 비정형 데이터를 관리하고 검색하도록 설계된 특수 시스템이다. 

정확한 검색 작업으로 구조화된 데이터를 처리하는 기존의 관계형 데이터베이스와 달리 벡터 데이터베이스는 ANN(Approximate Nearest Neighbor) 알고리즘과 같은 기술을 사용하여 의미적 유사성 검색에 뛰어나다. 이 기능은 추천 시스템, 챗봇, 멀티미디어 콘텐츠 검색 도구를 포함한 다양한 도메인에서 애플리케이션을 개발하고 AI 및 ChatGPT와 같은 대규모 언어 모델이 제기하는 문제(예: 맥락 및 뉘앙스 이해, AI 환각)를 해결하는 데 필수적이다.



### **MIlvis 구성**

Milvus는 벡터 데이터를 효율적으로 처리하고 처리하도록 설계된 다층 아키텍처를 중심으로 구성되어 확장성, 조정 가능성 및 데이터 격리를 보장한다.

- **Access Layer**

  cluster와 user application 간의 interface 역할을 담당하는 layer로, client가 Milvus DB와 상호작용할 수 있도록 다양한 기능과 protocol을 제공한다

  이 layers는 Milvus의 전체 아키텍처에서 가장 상위에 위치하며, 요청을 처리하고 클러스터의 내부 구성 요소와 통신하는 주요 책임을 맡는다.

- **Coordinator Service**

  Milvus cluster에서 작업을 관리하고 조정하는 중심 역할을 수행한다.

- **Message Storage**

  Milvus cluster내에서 구성 요소 간의 비동기 messaging을 처리한다.

  Kafka, Pulsar와 같은 메시지 브로커가 사용될 수 있다.

- **Worker Node**

  Milvus cluster에서 실제 데이터를 처리하고 검색 작업을 수행하는 Node

  분산 환경에서 여러 Worker Node가 동시에 작업을 수행할 수 있다.

  데이터 분할(Sharding)을 통해 작업을 병렬로 처리할 수 있다.

- **Object Storage**

  Milvus에서 대규모 데이터와 벡터 파일을 저장하는 외부 스토리지 시스템

  데이터 노드가 작업 처리 후 데이터 블록을 Object Storage에 저장한다.

![](https://milvus.io/images/milvus-architecture-overview.png)



#### Access Layer

cluster와 user application 간의 interface 역할을 담당하는 layer로, client가 Milvus DB와 상호작용할 수 있도록 다양한 기능과 protocol을 제공한다

이 layers는 Milvus의 전체 아키텍처에서 가장 상위에 위치하며, 요청을 처리하고 클러스터의 내부 구성 요소와 통신하는 주요 책임을 맡는다.

**주요 기능**

- 클라이언트 요청 처리

  - 사용자 애플리케이션에서 오는 요청(API 호출, 데이터 검색 등)을 받아 내부 구성 요소로 전달.
  - HTTP/gRPC protocol을 통해 클라이언트와 상호작용.

- query 관리

  - Milvus Query Language(MilvusQL) 또는 API 호출을 기반으로 사용자의 검색 요청을 해석한다.
    - 데이터 검색, 필터링, 삽입, 삭제 등 다양한 작업을 MilvusQL을 통해 수행이 가능하다.
    - Milvus QL은 Milvus Dashboard뿐만 아니라 Python SDK(PyMilvus)와 REST API에서도 사용할 수 있다.

  - 쿼리 최적화를 수행하여 벡터 검색, 필터링, 정렬 등 다양한 작업을 효율적으로 처리한다.

- data insert, update

  - client가 제공하는 vector data를 적절한 형식으로 변환하여 Milvus 클러스터에 전달한다.

- metadata 관리

  - 컬렉션(collection), 파티션(partition), 필드(field) 등의 메타데이터를 생성, 조회, 수정한다.
  - 데이터 구조를 정의하고 관리하기 위한 API를 제공한다.

- 인증 및 권한 부여

  - 사용자의 인증(Authentication) 및 권한 부여(Authorization)를 수행하여 DB 보안을 유지한다.

- Load balancing

  - client 요청을 Milvus cluster 내 적절한 노드로 분산하여 부하를 균등하게 분배.



**Access layer에서 사용하는 명령어 catetory**

- **DDL** (Data Definition Language)
  - 데이터베이스의 구조나 스키마를 정의하고 관리하기 위한 명령어.
  - 데이터베이스, 테이블, 컬렉션, 파티션 등을 생성하거나 삭제하는 데 사용된다.
  - Milvus에서는 컬렉션과 파티션 생성 및 관리에 사용된다.
  - **Coordinator Service의 Meta Storage와 통신할때 사용된다.**
  - 주요 특징
    - 데이터의 구조를 정의함(데이터 자체를 조작하지 않음).
    - 실행 결과는 database schema에 영향을 미침.	
    - Coordinator Service의 Meta Storage에
  - 주요 명령
    - `CREATE`: 데이터베이스, 테이블, 컬렉션 등을 생성
    - `DROP`: 데이터베이스, 테이블, 컬렉션 등을 삭제.
    - `ALTER`: 기존의 구조를 변경(스키마 수정).
    - `DESCRIBE`: 데이터베이스나 테이블의 구조 조회.
- **DCL** (Data Control Language)
  - 데이터베이스에 대한 접근 권한을 제어하기 위한 명령어.  (사용자 및 권한 관리를 다룸.)
  - Milvus에서는 제한적 지원을 통해 컬렉션 접근 권한 제어 가능.
  - **Coordinator Service의 Meta Storage와 통신할때 사용된다.**
  - 주요 특징
    - 보안과 관련된 작업에 사용.
  - 주요 명령
    - `GRANT`: 특정 사용자에게 권한 부여
    - `REVOKE`: 특정 사용자로부터 권한 제거
- **DML** (Data Manipulation Language)
  - 데이터 자체를 조작(삽입, 삭제, 조회 등)하는 데 사용되는 명령어. (Milvus에서는 벡터 데이터의 삽입, 삭제, 검색 등이 이에 해댕)
  - **Message Storage와 통신할때 사용된다.**
  - 주요 명령어
    - `INSERT` `DELETE` `SEARCH` 등...



#### Coordinator Service

Milvus cluster에서 작업을 관리하고 조정하는 중심 역할을 수행한다.

Coordinator Service는 Root, Query, Data, Index 총 4개의 coordinator 와 Meta Storage 구성된다.

- **Root Coordinator**
  - 모든 메타데이터 관리와 클러스터 전반적인 조정을 담당.
  - DDL 명령 처리: 컬렉션 생성/삭제, 파티션 생성/삭제 등.
- **Query Coordinator**
  - 검색 요청의 최적 경로를 설정.
  - 검색 요청을 Query Node에 라우팅.
- **Data Coordinator**
  - 데이터 삽입, 삭제 등의 작업을 Data Node에 라우팅.
  - 데이터 로드 작업 관리.
- **Index Coordinator**
  - index 생성 작업을 관리.
  - index 생성을 위한 resource 할당.

- **Meta Storage**

  클러스터의 모든 메타데이터를 저장하고 관리하는 핵심 저장소

  - Milvus 클러스터에 대한 모든 메타데이터를 저장하며, 메타데이터는 데이터의 구조, 위치, 상태 등을 포함한다.

  - Milvus는 분산 시스템이기 때문에 여러 노드 간의 일관성을 유지하는 것이 중요하다. 

    Meta Storage는 최신 메타데이터를 보장하여 클러스터가 동기화된 상태를 유지하도록 한다.

  - 여러 Coordinator가 동시에 동작할 경우, Meta Storage는 각 Coordinator가 공통된 정보를 공유하도록 보장한다.

    작업 분배, 상태 관리 등의 작업에서 메타데이터를 통해 조율이 이루어진다.

  - 노드가 비정상적으로 종료되거나 장애가 발생할 경우, Meta Storage에 저장된 정보를 바탕으로 복구를 지원한다.

  - 컬렉션 생성, 삭제, 파티션 추가 등 DDL 명령어에 대한 변경 사항을 기록한다.



#### Message Storage

Milvus cluster내에서 구성 요소 간의 비동기 messaging을 처리한다.

Kafka, Pulsar와 같은 메시지 브로커가 사용될 수 있다.

- Milvus의 다양한 서비스(Access Layer, Coordinator Service, Worker Node) 간 데이터를 전달하는 역할을 한다.
- 태스크(예: 데이터 로드, 쿼리 처리, 인덱스 생성 등)가 여러 노드로 분배될 때, 이를 Message Storage를 통해 전달하고 실행 상태를 추적한다.
- 메시지 큐 시스템을 기반으로 작동하며, 다양한 데이터 브로커(Message Broker)를 지원하여 시스템 간 통신 및 작업 분배를 처리한다.

**Message Broker**

Message Broke는 milvus 구성 파일에서 관련 정보를 명시하여 적용할 수 있다.

`Apache Pulsar`(Milvus에서 기본적으로 사용되는 메시지 브로커), `Apache Kafka`, `RabbitMQ` 등이 사용될 수 있다.



#### Worker Node

milvus 분산 아키텍처에서 실제 데이터 처리를 담당하는 핵심 구성 요소로, 사용자 요청을 실행하거나 데이터를 저장, 검색, 및 관리하는 역할을 수행한다. 

**주요 동작**

- 데이터 처리

  벡터 데이터 삽입, 쿼리 실행, 인덱스 생성

- 저장 및 관리

  데이터를 로컬 디스크, 분산 스토리지, 또는 Milvus의 Object Storage에 저장한다.

  메타데이터와 데이터 간의 매핑을 관리하여 효율적인 검색을 지원한다.

- 노드 간 협업

  Worker Node는 서로 통신하여 클러스터에서 분산된 데이터의 처리를 조정한다.

  데이터 복제 및 재분배를 통해 장애 복구와 고가용성을 보장한다.

- Load balancing

  요청이 많은 경우 Worker Node 간의 작업을 자동으로 분배하여 성능을 최적화한다.



**구성 요소**

- Query Node

  검색 및 쿼리 요청을 처리하는 역할을 수행하며, 벡터 데이터와 메타데이터를 조회하고, 검색 결과를 반환한다.

  고성능 검색을 위해 인덱스와 함께 작동한다.

- Data Node

  벡터 데이터를 삽입하고 영구 저장소(Object Storage 등)에 데이터를 저장한다.

  데이터의 분할(partition) 및 복제를 관리한다.

- Index Node

  벡터 데이터에 대한 인덱스를 생성하고 유지한다.

  검색 효율성을 극대화하기 위해 다양한 인덱스 유형을 지원(SQ8, IVF 등)





#### Object Storage

 벡터 데이터를 효율적으로 저장하고 관리하기 위한 외부 저장소

Amazon S3, miniO, Google Cloud Storage, Azure Blob Storage 등을 사용할 수 있다.

milvus의 object storage 설정 파일 예시

```yaml
storage:
  type: minio  # 사용할 Object Storage 유형
  path: "milvus-data"  # 데이터 저장 경로
  host: "127.0.0.1"  # MinIO 서버 주소
  port: 9000  # MinIO 서버 포트
  accessKeyID: "minioadmin"  # 액세스 키
  secretAccessKey: "minioadmin"  # 비밀 키
  useSSL: false  # SSL 사용 여부
```



**주요 데이터 유형**

- Log Snapshot

  Log Snapshot은 Milvus에서 특정 시점의 데이터 상태를 기록한 데이터 스냅샷으로, 데이터의 복구 및 재구성을 위해 사용된다.

  데이터베이스 재시작 또는 장애 복구 상황에서 중요하다.

  - Milvus는 주기적으로 스냅샷을 생성하여 저장소에 기록한다.
  - 장애 상황에서 Log Snapshot을 이용하여 데이터베이스를 특정 시점으로 복구한다.

- Delta File

  Milvus에서 데이터 변경 내역을 기록하는 파일로, 새로운 데이터 추가, 데이터 수정, 삭제 요청 등 데이터 조작(DML) 작업의 결과를 기록한다.

  - 데이터가 생성, 수정, 삭제될 때마다 변경 내역이 Delta File에 저장한다.
  - Log Snapshot과 함께 사용되어 데이터를 최신 상태로 유지한다.
  - Milvus는 주기적으로 Delta File을 병합하여 데이터 저장소의 효율성을 최적화한다.

- Index File

  Index File은 Milvus에서 벡터 데이터를 빠르게 검색하기 위해 생성되는 파일로, 데이터 검색 성능을 최적화하며 특히 대규모 벡터 데이터셋에서 중요한 역할을 한다.

  - 벡터 데이터의 인덱스를 포함하여 검색 요청 시 빠른 응답이 가능하다.
  - Milvus는 사용자가 설정한 알고리즘(예: IVF, HNSW 등)을 기반으로 인덱스를 생성한다.
  - 인덱스는 메모리가 아닌 Object Storage에 저장되어 메모리 사용량을 절감한다.



**Object Storage에 저장되는 파일 구성**

```
Object Storage/
├── Log Snapshot/
│   ├── snapshot_001
│   ├── snapshot_002
├── Delta File/
│   ├── delta_001
│   ├── delta_002
├── Index File/
│   ├── index_ivf_001
│   ├── index_hnsw_002
```





### install 

#### with docker-compose

1. create network

   ```shell
   $ docker network create milvus-network
   ```

2. install etc, minio

   ```yaml
   version: '3.8'
   services:
     milvus-etcd:
       image: quay.io/coreos/etcd:v3.5.17-arm64		#  mac환경: arm64 cpu architecture 전용 image
       container_name: milvus-etcd
       environment:
         - ALLOW_NONE_AUTHENTICATION=yes 				# 인증 없이도 작동 가능 (필요에 따라 설정 변경)
         - ETCD_NAME=milvus-etcd           				# 노드 이름
         - ETCD_DATA_DIR=/etcd-data      				# container 내부 etcd 데이터 저장소
         - ETCD_AUTO_COMPACTION_MODE=revision		# 자동 컴팩션(Automatic Compaction) 모드 설정
         - ETCD_AUTO_COMPACTION_RETENTION=1000		# 유지할 리비전 수
         - ETCD_QUOTA_BACKEND_BYTES=4294967296		# etcd 데이터베이스(ETCD_DATA_DIR)의 최대 크기를 4GB로 제한 (byte단위, default=2GB)
         - ETCD_SNAPSHOT_COUNT=50000					# transaction 기준으로 snapshot 주기 설정
       volumes:
         - ./etcd-data/data:/etcd-data         # mount data dir
       ports:
         - "2379:2379"                   # 클라이언트 통신 port
         - "2380:2380"                   # etcd 클러스터 내 노드들 간의 통신하기 위한 port
       restart: unless-stopped			# 컨테이너가 충돌 후 자동으로 재시작되도록 설정.
       command:
         - etcd
         - --listen-client-urls=http://0.0.0.0:2379    # 클라이언트 요청을 수신할 URL
         - --advertise-client-urls=http://milvus-etcd:2379 # 클라이언트에게 광고할 URL
         - --listen-peer-urls=http://0.0.0.0:2380      # etcd 노드 간 통신을 위한 URL
       networks:
         - milvus-network
   
     milvus-minio:
       # FIPS(Federal Information Processing Standards) 인증을 준수하여 암호화 관련 보안을 강화한 image 사용
       # 별 다른 기본 tag가 없음
       image: minio/minio:RELEASE.2024-11-07T00-52-20Z
       container_name: milvus-minio
       environment:
         MINIO_ACCESS_KEY: minioadmin             # Access Key 설정
         MINIO_SECRET_KEY: minioadmin             # Secret Key 설정
         MINIO_ROOT_USER: minioadmin              # (Optional) 루트 사용자 이름
         MINIO_ROOT_PASSWORD: minioadmin          # (Optional) 루트 사용자 비밀번호
         MINIO_BROWSER: "on"                      # 브라우저를 통한 관리 페이지 활성화
       volumes:
         - ./minio-data/data:/data                     # mount minio data dir
         - ./minio-data/configs:/root/.minio           # mount MinIO config dir
       ports:
         - "9000:9000"                            		# MinIO 웹 콘솔 및 API 포트
         - "9001:9001"                            		# MinIO Console Port
       command: minio server /data --console-address ":9001" 		# MinIO 서버 실행 명령   
       restart: unless-stopped                    		# 컨테이너 충돌 후 재시작 설정
       healthcheck:      # health check 설정
         test: ["CMD", "curl", "-f", "http://localhost:9000/minio/health/live"]
         interval: 30s
         timeout: 20s
         retries: 3
       networks:
         - milvus-network
   
     milvus-attu:
       image: zilliz/attu:v2.4
       container_name: milvus-attu
       environment:
         SERVER_PORT: 3000             # service에 연결하고자 하는 port설정   
         MILVUS_URL: milvus:19530      # 연결하고자 하는 milvus 의 주소
       ports:  
         - "3000:3000"
       networks:
         - milvus-network
         
   
   networks:
     milvus-network:
       driver: bridge
   
   # docker-compose -f docker-compose_base.yaml up -d
   ```

3. Add minio bucket for using milvus

   1. Enter to minio container

      ```shell
      $ docker exec -it milvus-minio /bin/bash
      ```

   2. Set alias to `milvus_minio`

      ```shell
      milvus-minio$ mc alias set milvus_minio http://127.0.0.1:9000 minioadmin minioadmin
      ```

   3. add bucket

      ```shell
      milvus-minio$ mc mb milvus_minio/milvus-bucket
      ```

   4. check bucket

      ```shell
      milvus-minio$ mc ls milvus_minio 
      ```

      또는 container의 내부  `/data`위치에 milvus_minio라는 폴더가 있는지 확인

4. install milvus

   ```yaml
   version: '3.8'
   services:
     milvus:
       image: milvusdb/milvus:v2.4.14-20241115-8370caa4-arm64
       container_name: milvus
       environment:
         ETCD_ENDPOINTS: milvus-etcd:2379			# etcd service port
         MINIO_ADDRESS: milvus-minio:9000			# minio service port
         MINIO_ACCESS_KEY: minioadmin					# MinIO 접속을 위한 Access key
         MINIO_SECRET_KEY: minioadmin					# MinIO 접속을 위한 Secret Key
         MINIO_BUCKET_NAME: milvus-bucket			# Milvus가 사용할 MinIO의 버킷 이름
         LOG_LEVEL: info					# Milvus service의 로그 레벨 설정
       ports:
         - "19530:19530"  # Milvus RPC port
         - "9091:9091"    # Milvus monitoring port
       volumes:
         - ./volumes-data:/var/lib/milvus
       networks:
         - milvus-network
   
   networks:
     milvus-network:
       driver: bridge
   
   # docker-compose -f docker-compose_milvus.yaml up -d
   ```

   - `Milvus RPC(Remote Procedure Call)`: 원격 시스템 간에 함수 호출을 수행하는 프로토콜을 의미한다.

     클라이언트와 서버 간 호출을 동기적 또는 비동기적으로 처리할 수 있다.







- Milvus RPC port 에서 RPC란 무슨 의미지?

  

#### with Kubernetes