# Attu

Milvus의 **Web UI 도구**로, Milvus 클러스터를 시각적으로 관리하고 데이터를 탐색할 수 있도록 지원한다.

이를 통해 사용자는 Milvus 데이터베이스를 손쉽게 설정하고, 데이터 컬렉션, 인덱스, 데이터 검색 등을 시각적으로 확인하거나 조작할 수 있다.

**주요 기능**

- 컬렉션 및 데이터 관리

  Milvus의 컬렉션 생성, 수정, 삭제가 가능하다

- 데이터 탐색

  검색 쿼리를 실행하여 검색 결과를 확인할 수 있다.

- 인덱스 관리

  Milvus에 저장된 벡터 데이터에 대해 인덱스를 생성하거나 관리할 수 있다.

- 통계 확인

  컬렉션의 데이터 개수, 저장 용량, 인덱스 상태 등의 통계를 제공한다.

- 실시간 연결

  Milvus 서버와 실시간으로 연결되며, Milvus 상태를 모니터링할 수 있다.





### install 

#### with docker-compose

```yaml
version: '3.8'
services:
  milvus-attu:
    image: zilliz/attu:v2.4
    container_name: milvus-attu
    environment:
      SERVER_PORT: 3000						# service에 연결하고자 하는 port설정
      MILVUS_URL: milvus:19530		# 연결하고자 하는 milvus 의 주소
    ports:
      - "3000:3000"
    networks:
      - milvus-network
      

networks:
  milvus-network:
    driver: bridge

# docker-compose -f docker-compose.yaml up -d 
```

- 접속: `localhost:3000`
  - Milvus Address: {milvus_container_name}19530
  - Milvus Database(optional): 해당 필드를 빈칸으로 남겨두는 것은 기본 데이터베이스를 사용하겠다는 의미

