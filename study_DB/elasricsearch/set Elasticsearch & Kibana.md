# elasticsearch & Kibana



## install

elasticsearch와 Kibana는 version을 일치시켜서 install해야 한다.



- elasticsearch

  download file

  https://www.elastic.co/kr/downloads/past-releases/elasticsearch-7-13-0

  ```
  $ tar -zxvf elasticsearch-7.13.0-linux-x86_64.tar.gz
  ```

  

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

  







## start

local에서 구성되어있는 cluster에 접속하고자 한다면

local에서 elasticsearch를 설치해야 cluster에 접속한 후 색인(data 저장)/검색/삭제를 수행할 수 있다.

local에서 kibana를 설치해야 cluster에 접속한 후 깔끔한 UI을 활용할 수 있다.

### command

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
  
  - 어느 위치에서든 아래 명령어를 사용하면 elasticsearch를 시작할 수 있다.
  
    ```
    $ cd $(find ~ -name kibana-7.13.0-linux-x86_64 2>/dev/null -print -quit) && ./bin/kibana 
    ```
  
    






## set

### index

#### settings

elasticsearch는 정형화된 data를 저장하는 database이다.

이러한 data의 모음에서 특정 data를 parsing할 때는 특정 방법을 활용하면 더욱 효율적으로 검색할 수 있다.

특정 index의 data를 search하기 위한 효율적인 방법을 구성해 놓은 것을 `settings`라고 한다.

>  settings은 각 index마다 설정한다.

#### mappings

index에 저장되는 document의 규칙을 설정하는 것을 `mappings`이라 한다.

document는 각 field와 value의 type등 구조를 결정해놓은 data만 저장할 수 있다.

>  mapping은 각 index마다 설정한다.
