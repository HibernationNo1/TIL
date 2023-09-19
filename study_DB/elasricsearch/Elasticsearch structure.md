# Elasticsearch structure

Elasticsearch란 아파치 루씬(Lucene) 기반의 오픈소스 실시간 분산 검색 엔진으로 JSON 기반의 비정형 데이터 분산 검색 및 분석을 지원한다.



### logical structure

![](https://velog.velcdn.com/images/koo8624/post/8584d80f-950b-46c9-8cd0-78ba2e2c53f4/1.png)

Elasticsearch cluster는 1개 이상의 Node(server와 같은 device)로 구성한다.

보통 3개 이상의 node로 구성한다.

위 그림은 1개의 node에 index가 포함되어 있는 것 처럼 보이지만, 실제 구조는 위와 같지 않다.



논리적 구조는 아래와 같다

`cluster > Index > document`



![](https://res.cloudinary.com/practicaldev/image/fetch/s--Eo5Qbg_b--/c_limit%2Cf_auto%2Cfl_progressive%2Cq_auto%2Cw_800/https://user-images.githubusercontent.com/60980933/110810286-e36dac00-8242-11eb-823f-5f9cfba46d58.png)



#### Index 

여러개의 document의 집합을 의미하며, index에 속한 document는 여러 node에 나뉘어 저장될 수 있다. 

- `document`: json형태의 tree구조

index에 저장할 document는 각 field(key)가 정해져있어야 한다.

이는 **mappings**에 의해 설정되며, field내부의 field또한 정해야 한다.





### physical structure

물리적 구조는 아래와 같다

`cluster > node > shard`

![](https://sematext.com/wp-content/uploads/2023/04/elasticsearch-unassigned-shards-4.jpg)

#### node

클러스터에 포함된 단일 server(device)

node는 master node와 data node로 구분된다.

- master node

  cluster 관리 node. 

  node 추가/제거, index 생성/삭제 등 cluster의 전반적 관리 담당

- data node

  document가 저장되는 node

  data가 분산 저장되는 물리적인 공간인 shard가 배치되는 node이며, 색인/검색/통계 등 데이터 작업 수행(resource가 많이 필요함. 모니터링 필수)

기본적으로는 모든 노드가 마스터 노드로 선출될 수 있는 마스터 후보 노드 (master eligible node)이다.

현재 마스터 역할을 수행하고 있는 노드가 네트워크상에서 끊어지거나 다운되면 다른 마스터 후보 노드 중 하나가 마스터 노드로 선출이 되어 마스터 노드의 역할을 대신 수행하게 된다.



##### shard

[공식](https://esbook.kimjmin.net/03-cluster/3.2-index-and-shards)

shard란 index의 document를 분산 저장하는 저장소로, index는 기본적으로 shard단위로 분리된다.

shard에 개수에 따라 document를 분산해서 저장한다.



- primary & replica

  shard는 처음 생성된 후 복제본을 따로 만들어 저장하는데, 처음 생성된 shard를 primary shard라 부르고 복제본은 replica shard라고 부른다.

  replica의 default생성 개수는 1개이다.

  ![](https://1535112035-files.gitbook.io/~/files/v0/b/gitbook-legacy-files/o/assets%2F-Ln04DaYZaDjdiR_ZsKo%2F-LnUxLhQtL_hJwYydM_5%2F-LnKhmx31SnLDNMKr_YT%2Fimage.png?alt=media&token=fc99a84d-5f9f-4d3d-aad6-21e503567b33)

  > - 1개의 index에 0, 1, 2, 3, 4라는 5개의 shard가 존재
  > - cluster가 4개의 node로 구성된 경우
  >
  > 위의 경우는 node 4개에 primary shard 5개와 replica 5개가 나뉘어 저장된 모습이다.

  primary shard와 replica는 동일한 data를 담고 있으며, 반드시 서로 다른 node에 저장된다.

  이는 특정 node가 문제발생으로 인해 소실되더라도 data는 다른 node로부터 확보하기 위함이다.

  shard의 개수는 index를 처음 생성할 때 지정할 수 있다.

  - 예시

    ![](https://1535112035-files.gitbook.io/~/files/v0/b/gitbook-legacy-files/o/assets%2F-Ln04DaYZaDjdiR_ZsKo%2F-LnUxLhQtL_hJwYydM_5%2F-LnKl_15PVn3pJ-V-jG6%2Fimage.png?alt=media&token=a3fdac30-9030-44f8-b2a1-08811e09b2d9)

    > - node의 개수: 4개
    >
    > - index의 개수 2개
    >
    >   - books
    >
    >     shard의 개수 5개
    >
    >     각 shard의 replica 1개
    >
    >   - magazines
    >
    >     shard의 개수 0개
    >
    >     각 shard의 replica 0개

    