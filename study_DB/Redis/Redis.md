# Redis

### introduce

1. redis는 주로 key-value 저장소로 알려져 있지만, 그 기본적인 key-value 저장 방식 외에도 여러 다양한 데이터 타입을 지원한다.

   - **Strings**: 기본적인 key-value 쌍에서 사용되며, 단일 값(문자열 또는 숫자)을 저장한다.

     - value는 문자열 또는 바이너리 데이터

       - 예시

         ```
         SET mykey "Hello, Redis!"		# `mykey`라는 key에 "Hello, Redis!"라는 문자열 값을 저장
         GET mykey						# `mykey`라는 값을 확인하는 경우
         ```

         ```
         "Hello, Redis!"					# 출력
         ```

   - **Lists**: 순서가 있는 요소들의 목록으로, **Queue** 또는 **Stack** 구현에 사용될 수 있다.

     - `LPUSH`, `RPUSH`, `LPOP`, `RPOP` 등의 명령을 사용하여 리스트의 앞이나 뒤에 항목을 추가하거나 제거할 수 있다.

       - 예시

         ```
         LPUSH mylist "World"		# mylist라는 이름의 리스트를 만들고, 문자열 요소 "World"를 왼쪽 끝에 추가합니다. 
         LPUSH mylist "Hello"		# mylist라는 이름의 리스트에 문자열 요소 "Hello"를 왼쪽 끝에 추가
         LRANGE mylist 0 -1			# 내용 확인
         ```

         ```
         1) "Hello"
         2) "World"
         ```

   - **Sets**: 중복되지 않는 요소들의 집합으로, **교집합**, **합집합**, **차집합** 연산을 지원한다.
     - `SADD`, `SREM`, `SMEMBERS` 등의 명령을 사용한다.

   - **Sorted Sets**: 점수와 함께 저장된 집합으로, 점수를 기반으로 요소들을 정렬하고 검색할 수 있다.
     - **Sorted Sets (or ZSets)**: 각 멤버가 연결된 스코어 값을 가지며, 스코어에 따라 정렬되는 set. `ZADD`, `ZRANGE` 등의 명령을 사용한다.

   - **Hashes**: 필드와 값을 가진 key-value 구조로, 한 key에 여러 필드를 저장할 수 있는 형태이다.

     - Redis의 key-value 내에 또 다른 key-value 구조를 가지는 데이터 타입. 

       작은 객체나 데이터 구조를 표현하는 데 유용하며, `HSET`, `HGET`, `HDEL` 등의 명령을 사용한다.

   - **Bitmaps**: 비트 수준에서 값을 다룰 수 있는 데이터 구조이다.

   - **HyperLogLogs**: 큰 데이터 세트에서 중복된 데이터를 처리하지 않고, 고유 항목의 근사치를 계산하는 데 사용된다.

   - **Streams**: Redis 5.0부터 지원하는 데이터 타입으로, **로그 기반 메시지 스트림**을 구현할 수 있다.

2. database, cache, message broker로 사용되며 인메모리 데이터 구조를 가진 저장소이다.

   redis는 빠른 속도를 자랑하지만 RAM의 용량문제와 휘발성 문제가 있다.

   - 휘발성이기 때문에 보조적인 수단으로 사용될 수 있다.
     - **Web APP cache**: 사용자 세션, 자주 조회되는 데이터(예: 상품 정보, 게시글 등)를 캐시하여 읽기 속도를 극대화한다.
     - **실시간 분석**: 실시간 로그 데이터나 사용자의 행동 패턴 분석에 Redis를 활용해 빠르게 데이터를 처리하고 분석할 수 있다.
     - **message queue**: Celery와 같은 비동기 작업 큐의 **브로커** 역할로 자주 사용된다. 실시간 처리가 필요한 이벤트나 작업을 효율적으로 분산 처리할 수 있

   - Redis는 휘발성 메모리 문제를 해결하기 위해 **데이터 영구성**을 제공하는 여러 기능을 갖추고 있다. 

     - **RDB (Redis DataBase)**: 특정 시점에 메모리의 모든 데이터를 **스냅샷(Snapshot)**으로 저장하는 방식이다. 

       사용자가 설정한 주기마다 데이터를 디스크에 저장하며, 서버 재시작 시 이를 불러온다.

     - **AOF (Append-Only File)**: 모든 쓰기 작업을 **로그 파일**에 순차적으로 기록하는 방식이다. 

       AOF는 데이터를 매우 자주 디스크에 기록하므로 RDB보다 더 높은 수준의 영속성을 제공한다. 

       Redis는 AOF 파일이 손상되었을 때 **자동 복구** 기능도 지원한다.

     RDB와 AOF를 동시에 사용하는 방식도 가능

3. Redis의 cluster와 sharding

   Redis 클러스터는 고가용성과 데이터 분산을 지원하며, 여러 Node 간에 데이터를 분산 저장할 수 있다. 

   - **샤딩(Sharding)**: Redis 클러스터는 데이터를 shard로 나눠 각 Node에 분배하여 저장한다. 이를 통해 데이터 용량을 늘리고 읽기 및 쓰기 성능을 확장할 수 있다.
   - **자동 페일오버(Auto-failover)**: 클러스터 모드에서는 마스터-슬레이브 구조에서 마스터 노드가 장애가 발생했을 때, 자동으로 슬레이브 노드가 마스터로 승격된다.

4. Lua scripting

   여러 명령어를 원자적으로 실행할 수 있는 기능을 지원한다.

5. **Pub/Sub**: 퍼블리셔/구독자 모델을 통해 실시간 메시지 전달 기능을 제공한다. 이를 통해 실시간 이벤트 시스템을 구축할 수 있다.





#### **Redis 사용에 주의할 점**

- 서버에 장애가 발생했을 경우 그에 대한 운영 플랜이 꼭 필요하다.
  인메모리 데이터 저장소의 특성상, 서버에 장애가 발생했을 경우 데이터 유실이 발생할 수 있다.









### install

[공식](https://redis.io/docs/getting-started/installation/install-redis-on-linux/)

**Prerequisites**

```
$ sudo apt install lsb-release curl gpg
```

```
$ curl -fsSL https://packages.redis.io/gpg | sudo gpg --dearmor -o /usr/share/keyrings/redis-archive-keyring.gpg

$ echo "deb [signed-by=/usr/share/keyrings/redis-archive-keyring.gpg] https://packages.redis.io/deb $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/redis.list

$ sudo apt-get update
$ sudo apt-get install redis
```



- 설치 확인

  ```
  $ redis-server --version
  ```




**start**

redis서버 실행

서버 실행에는 두 가지 방법이 있다.

1. ```
   $ systemctl start redis-server # 시작
   $ systemctl stop redis-server # 정지
   $ systemctl status redis-server # 상태 확인
   ```

2. ```
   $ redis-server &
   ```

   > `systemstl`을 사용하여 redis를 실행시키는 경우 celery에서 broker경로를 찾지 못할때가 있다.



해당 server에 접속

```
$ redis-cli
```

- ```
  not connected> 
  ```

  연결 실패한 경우 위 처럼 나옴

  `exit`입력으로 종료



**uninstall**

```
$ sudo apt remove redis-server
```



#### With Docker

- `alpine`: **Alpine Linux** 기반의 이미지를 의미

  **Alpine Linux**는 **경량** 운영체제로, 이미지의 크기가 매우 작고 빠르다. Redis의 기본 이미지를 **경량화**한 버전이므로 디스크 사용량을 최소화하려는 상황에서 유용하다.

  클라우드 환경, 도커 컨테이너를 많이 사용하는 마이크로서비스 아키텍처 등에서 메모리나 디스크 공간을 절약해야 하는 경우 적합하다.

- `bookworm`: **Debian 12 (Bookworm)** 기반의 이미지를 의미

  **Debian**은 안정성과 보안이 강조되는 리눅스 배포판으로, **Bookworm**은 Debian 12의 코드 이름이며 이는 일반적인 리눅스 시스템에 적합하다.

  안정성과 보안이 중요한 프로덕션 환경에서 사용된다. 메모리 절약보다는 안정성과 호환성에 더 집중할 때 적합하다.

- `No TagName`: 별다른 기반 없는 이미지는 **Redis의 최신 안정 버전**을 의미한다.



**docker-compose**

```
services:
  redis:
    image: 'redis:7.2.1-alpine'   
    container_name: 'redis'
    ports:
      - '6379:6379'
    volumes:
      - './redis-data:/data'  # 데이터를 보존하기 위해 호스트의 ./redis-data DIR을 컨테이너의 /data dir로 마운트

    
# docker-compose -f docker-compose_utils.yml up -d
```

