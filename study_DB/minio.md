# MinIO

MinIO는 **고성능 오브젝트 스토리지(Object Storage)** 솔루션으로, cloud native 환경에서 대규모 데이터를 저장하고 관리하는 데 최적화된 경량화된 소프트웨어이다.

MinIO는 Amazon S3와 호환되는 API를 제공하며, 다양한 환경에서 사용될 수 있다.



**MinIO의 구성 요소**

- Server

  - 데이터 저장 및 관리의 핵심 기능을 제공하며, 단일 노드 또는 분산 클러스터 형태로 배포가 가능하다.

- Client

  mc(MinIO Client) 명령줄 도구를 통해 데이터를 업로드, 다운로드하거나 관리할 수 있

- Console

  웹 기반 관리 콘솔로, 스토리지를 시각적으로 관리할 수 있다.

- SDK 및 API

  다양한 프로그래밍 언어에서 사용할 수 있는 SDK를 제공한다.



### install

#### with docker-compose

```yaml
version: '3.8'

services:
  minio:
    # FIPS(Federal Information Processing Standards) 인증을 준수하여 암호화 관련 보안을 강화한 image 사용
    # 별 다른 기본 tag가 없음
    image: minio/minio:RELEASE.2024-11-07T00-52-20Z
    container_name: minio
    environment:
      MINIO_ACCESS_KEY: minioadmin             # Access Key 설정
      MINIO_SECRET_KEY: minioadmin             # Secret Key 설정
      MINIO_ROOT_USER: minioadmin              # (Optional) 루트 사용자 이름
      MINIO_ROOT_PASSWORD: minioadmin          # (Optional) 루트 사용자 비밀번호
      MINIO_BROWSER: "on"                      # 브라우저를 통한 관리 페이지 활성화
    volumes:
      - ./minio-data:/data                     # 로컬 데이터 저장 경로 마운트
      - ./minio-config:/root/.minio            # MinIO 설정 디렉토리 마운트
    ports:
      - "9000:9000"                            		# MinIO 웹 콘솔 및 API 포트
      - "9001:9001"                            		# MinIO Console Port
    command: server /data --console-address ":9001" 		# MinIO 서버 실행 명령
    restart: unless-stopped                    		# 컨테이너 충돌 후 재시작 설정


# docker-compose -f docker-compose.yaml up -d
```





### mc

Bucket 만들기 예시

1. Enter to minio container

   ```shell
   $ docker exec -it {minio_container_name} /bin/bash
   ```

2. Set alias to `milvus_minio`

   ```shell
   milvus-minio$ mc {alias_name} set {minio_container_name} http://127.0.0.1:9000 {Access Key} {Secret Key}
   ```

3. add bucket

   ```shell
   milvus-minio$ mc mb {alias_name}/{bucket_name}
   ```

4. check bucket

   ```shell
   milvus-minio$ mc ls {alias_name} 
   ```

   또는 container의 내부  `/data`위치에 milvus_minio라는 폴더가 있는지 확인
