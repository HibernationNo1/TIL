# elasticsearch & Kibana

해당 문서는 local에서 1개의 node로 cluster를 구성하여 사용하는 경우에 해당된다.





elasticsearch와 Kibana는 version을 일치시켜서 install해야 한다.



## host

### install



- elasticsearch

  download file

  https://www.elastic.co/kr/downloads/past-releases/elasticsearch-7-13-0

  ```
  $ tar -zxvf elasticsearch-7.13.0-linux-x86_64.tar.gz
  ```

  `elasticsearch-7.13.0` 라는 dir이 생성됨을 확인

  install java

  ```
  $ sudo apt-get update 
  $ sudo apt-get install openjdk-8-jdk
  ```

  copy java file

  ```
  $ cd elasticsearch-7.13.0/
  $ sudo cp -r /usr/lib/jvm/java-1.8.0-openjdk-amd64/* jdk/
  $ sudo cp -r /usr/lib/jvm/java-8-openjdk-amd64/* jdk/
  ```

  

- kibana

  download file

  https://www.elastic.co/kr/downloads/past-releases/kibana-7-13-0

  ```
  $ tar -zxvf kibana-7.13.0-linux-x86_64.tar.gz
  ```

  `kibana-7.13.0-linux-x86_64  ` 라는 dir이 생성됨을 확인

### uninstall

- elasticsearch

  ```
  $ sudo dpkg --purge --force-all elasticsearch
  ```

  - `dpkg`: Debian package관리자.		`.deb` 패키지를 설치, 제거 및 관리할때 사용
  - `--purge`: package를 제거하는 것 외에도 해당 package의 설정 파일도 제거
  - `--force-all`: 모든 강제 option을 활성화

  ```
  $ rm -rf elasticsearch-7.13.0-linux-x86_64
  ```

  dir도 지워야 한다

- kibana

  ```
  $ rm -rf kibana-7.13.0-linux-x86_64
  ```





### start

local에서 구성되어있는 cluster에 접속하고자 한다면

local에서 elasticsearch를 설치해야 cluster에 접속한 후 색인(data 저장)/검색/삭제를 수행할 수 있다.

local에서 kibana를 설치해야 cluster에 접속한 후 깔끔한 UI을 활용할 수 있다.

#### command

항상 background에서 실행됨

- elasticsearch

  ```
  $ ./elasticsearch-7.13.0/bin/elasticsearch
  ```

  > ```
  > Active license is now [BASIC]; Security is disabled
  > 
  > Elasticsearch built-in security features are not enabled. Without authentication, your cluster could be accessible to anyone. See https://www.elastic.co/guide/en/elasticsearch/reference/7.13/security-minimal-setup.html to enable security.
  > 
  > ```
  >
  > Elasticsearch에서 보안 기능을 활성화하지 않았다는 메시지
  >
  > Elasticsearch를 실행하는데는 문제가 없다.

  server연결 확인

  ```
  $ curl http://localhost:9200
  ```

  ```
  {
    "name" : "teno",
    "cluster_name" : "elasticsearch",
    "cluster_uuid" : "c8q5FZ4gTCKKI9bn_sjCTg",
    "version" : {
      "number" : "7.13.0",
      "build_flavor" : "default",
      "build_type" : "tar",
      "build_hash" : "5ca8591c6fcdb1260ce95b08a8e023559635c6f3",
      "build_date" : "2021-05-19T22:22:26.081971330Z",
      "build_snapshot" : false,
      "lucene_version" : "8.8.2",
      "minimum_wire_compatibility_version" : "6.8.0",
      "minimum_index_compatibility_version" : "6.0.0-beta1"
    },
    "tagline" : "You Know, for Search"
  }
  ```

  

  - 어느 위치에서든 아래 명령어를 사용하면 elasticsearch를 시작할 수 있다.

    ```
    $ cd $(find ~ -name elasticsearch-7.13.0 2>/dev/null -print -quit) && ./bin/elasticsearch
    ```

    - `find ~ -name elasticsearch-7.13.0 2>/dev/null -print -quit`: elasticsearch-7.13.0의 위치를 찾는다

      - `2>/dev/null`: 허가 거부 skip
      - `-print -quit`: 결과가 출력되면 바로 종료

    - `./bin/elasticsearch` : elasticsearch 실행

      

    

    

- kibana

  ```
  ./kibana-7.13.0-linux-x86_64/bin/kibana
  ```

  항상 background에서 실행됨

  server연결 확인

  ```
  http://localhost:5601
  ```

  - 어느 위치에서든 아래 명령어를 사용하면 kibana를 시작할 수 있다.

    ```
    $ cd $(find ~ -name kibana-7.13.0-linux-x86_64 2>/dev/null -print -quit) && ./bin/kibana 
    ```

    

#### stop

- elasticsearch

  ```
  $ ps -aux | grep elasticsearch
  $ kill -9 PID
  ```

- kibana

  ```
  $ ps -aux | grep kibana
  $ kill -9 PID
  ```









## docker(compose)





### Elasticsearch

Elasticsearch는 메모리 매핑된 파일을 많이 사용하므로, `vm.max_map_count`라는 커널 매개변수의 값이 충분히 크지 않으면 container 실행 중에 오류가 발생한다.

때문에 `/etc/sysctl.conf` 에 `vm.max_map_count=262144` 이 문구를 추가해야한다.



`set.sh`

```
#!/bin/bash

## ES container를 사용하기 위한 설정
# Check if vm.max_map_count is already set in /etc/sysctl.conf
grep -q "^vm.max_map_count=" /etc/sysctl.conf

# If the setting is not found, append it to the file
if [ $? -ne 0 ]; then
    echo "vm.max_map_count=262144" | sudo tee -a /etc/sysctl.conf
    echo "vm.max_map_count=262144 added to /etc/sysctl.conf"
else
    echo "vm.max_map_count is already set in /etc/sysctl.conf"
fi

# Apply the changes
sudo sysctl -p

echo "vm.max_map_count value has been applied."

## container 배포
docker network create --subnet=172.200.10.0/20 network_name || true
docker-compose -f ./docker/docker-compose.yml up -d
```





### Kibana

ES와 연결

1. Kibana 배포 후 웹으로 접근하면 Enrollment token 를 요구한다.

   ```
   $ docker exec -it es_container_name /bin/bash
   in container >> bin/elasticsearch-create-enrollment-token -s kibana 
   ```

   아래 출력 확인

   ```
   WARNING: Owner of file [/usr/share/elasticsearch/config/users] used to be [root], but now is [elasticsearch]
   WARNING: Owner of file [/usr/share/elasticsearch/config/users_roles] used to be [root], but now is [elasticsearch]
   eyJ2ZXIiOiI4LjE0LjAiLCJhZHIiOlsiMTcyLjE4LjAuNDo5MjAwIl0sImZnciI6IjRlNTVmZDNlOGEwNzFmMDZjNTk0ZmU5Yzc5Yjg4YjQzODcwYzIxNGIwM2U3OTk5MDdkMDQxYmM1MjdkZDQ3NjkiLCJrZXkiOiJJQUhEbTVFQjNaWjNYU0RKV1dSVDo4bjF2bmVpTVNTR2x4UjhzbXFjWF93In0=
   ```

2. Kibana 를 처음 설정할 때 Verification code 를 요구한다.

   `Verification required Copy the code from the Kibana server or run bin/kibana-verification-code to retrieve it.` 라는 물음에

   ```
   $ docker exec -it kibana_container_name /bin/bash
    in container >> bin/kibana-verification-code
   ```

   아래 출력 확인

   ```
   Kibana is currently running with legacy OpenSSL providers enabled! For details and instructions on how to disable see https://www.elastic.co/guide/en/kibana/8.15/production.html#openssl-legacy-provider
   Your verification code is:  672 616 
   ```

3. 최초 비밀번호 설정

   ```
   $ docker exec -it es_container_name /bin/bash
   in container >> bin/elasticsearch-reset-password -u elastic
   ```

   아래 출력 확인

   ```
   This tool will reset the password of the [elastic] user to an autogenerated value.
   The password will be printed in the console.
   Please confirm that you would like to continue [y/N]y
   
   
   Password for the [elastic] user successfully reset.
   New value: rrx8oa8vCGJgDY1RXWIS
   ```

   최초 **ID**: `elastic`, **PW**: `rrx8oa8vCGJgDY1RXWIS`

4. User 추가  (**ID**:enliple,  **PW**:ai1234)

   좌측 탭 중 `Stack Management` > `Users` 화면에 접속 (이 화면에서 기본적으로 제공되는 계정들을 확인할 수 있다.)

   화면 우측 상단 Create user 선택

   User roles

   - **editor**: 데이터와 관련된 편집 작업을 수행할 수 있는 권한을 제공

     Elasticsearch 인덱스에 문서를 추가하거나, 업데이트하고 삭제하는 등의 작업 권한

   - **enrich_user**:  Enrich Processor와 관련된 작업을 수행할 수 있는 역할

     Enrich Processor는 Enrich Policy를 사용하여 문서를 풍부하게 만드 작업 권한

   - **inference_user**: 기계 학습 모델의 추론 작업을 수행할 수 있는 권한을 제공

     학습된 모델을 기반으로 데이터에 대한 예측 수행 기능을 사용

   - **machine_learcning_user**: Elasticsearch의 기계 학습 기능을 사용할 수 있는 권한

     작업을 생성하고, 관리하며, 결과를 볼 수 있다.

   - **monitoring_user**: Elasticsearch 클러스터의 모니터링 데이터를 조회할 수 있는 역할

     클러스터, 노드, 인덱스의 상태와 성능 메트릭을 볼 수 있다.

   - **remote_monitoring_agent**: 원격 모니터링 데이터를 수집하고 Elasticsearch에 전송하는 역할을 가진 에이전트에게 부여되는 역할.
     이 역할은 Beats 또는 Logstash와 같은 데이터를 수집하는 도구와 자주 사용된다.

   - **remote_monitoring_collector**: 원격 모니터링 데이터를 수집하는 역할을 가진 사용자를 위한 역할

   - **rollup_user**: Rollup 작업을 수행할 수 있는 권한을 부여

     Rollup은 오래된 데이터를 압축하여 저장하고, 저장소를 절약하는 기능이다.

   - **snapshot_user**: Elasticsearch의 스냅샷 및 복원 기능을 사용할 수 있는 권한을 부여

     사용자는 인덱스 또는 클러스터의 스냅샷을 만들고, 복원할 수 있다.

   - **transform_user**: Elasticsearch에서 데이터를 변환하는 Transform 작업을 수행할 수 있는 권한을 부여

     Transform은 데이터를 한 형태에서 다른 형태로 변환하는 데 사용된다.

   - **transport_client**: Elasticsearch 클러스터에 Transport 프로토콜을 통해 연결할 수 있는 권한을 부여

     Transport는 주로 노드 간 통신에 사용된다.

   - **viewer**: 데이터에 대한 읽기 전용 권한을 부여한다. 

     사용자는 데이터를 조회할 수 있지만, 수정, 삭제 또는 추가 작업은 수행할 수 없다.

   - **watch_user**: Elasticsearch Watcher 기능을 사용하는 사용자를 위한 역할

     Watcher는 데이터를 모니터링하고 알림을 트리거하는 데 사용된다.

   - **apm_user(default)**: APM (Application Performance Monitoring) 데이터를 볼 수 있는 권한을 부여

     APM은 애플리케이션의 성능을 모니터링하고 분석하는 데 사용한다.

   - **data_frame_transtorms_admin(default)**: 데이터 프레임 변환을 관리하는 사용자를 위한 역할

     Elasticsearch에서 데이터 변환 작업을 생성, 관리, 삭제할 수 있는 권한을 부여한다.

   - **data_frame_transtorms_user(default)**: 데이터 프레임 변환 작업을 실행할 수 있는 사용자를 위한 역할

     관리 권한은 없고, 실행 권한만 있다.

   - **reporting_user(default)**:Kibana에서 보고서를 생성할 수 있는 권한을 부여

     대시보드 또는 시각화의 보고서를 생성하고 다운로드할 수 있다.





```
https://juhpark.tistory.com/50
```

