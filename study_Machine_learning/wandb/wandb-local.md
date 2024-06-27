# Wandb_local

local 환경에서 wandb를 구성하기 위한 설정



### Dockerfile

```
FROM wandb/local:0.52.2

# root 사용자로 변경
USER root

# 필요한 도구 설치
RUN apt-get update && \
    apt-get install -y git wget vim lsof sudo && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# wandb 사용자에게 sudo 권한 부여
RUN echo 'wandb ALL=(ALL) NOPASSWD:ALL' > /etc/sudoers.d/wandb

# wandb 사용자의 비밀번호 설정
RUN echo 'wandb:wandb_local' | chpasswd

# 다시 wandb 사용자로 변경
USER wandb
```

- container 내부에서 원하는 동작을 수행하기 위해 sudo 명령어를 사용할 경우를 대비, `wandb`사용자에 sudo권한 부여



### docker-compose.yml

```
version: '3'
services:
  wandb-local:          
    build :
      context : ./
      dockerfile: Dockerfile
    image: 'wandb-local:0.1'
    container_name: 'wandb-local'    
    ipc : "host"
    stdin_open: true # docker 유지
    tty: true # docker 유지
    volumes:
      - /etc/localtime:/etc/localtime:ro
      - /home/ai/Data/04.Storage/wandb_storage:/vol		# wandb로 관리할 data의 위치 mount
    ports:
      - "9595:8080" # 호스트의 9595 포트를 컨테이너의 8080 포트에 매핑
    environment:
      - HOST=http://192.168.0.4:9595 	# web page에 접속하기 위한 port 
      - LOCAL_RESTORE=true

# docker-compose -f docker-compose.yml up -d
```

- wandb로 관리할 data의 위치는 **wandb-local container** 뿐만 아니라 **experience container**에도 동일하게 mount되어있어야 한다.



### Set wandb-local container

1. **W&B 계정 생성**

   wandb-local 서버에서 사용할 계정을 생성한다. `http://{서버 IP}:{사용할 port}/signup` 에 접속하여 계정 생성

2. **라이센스키 생성 및 추가**

   1. W&B Deply Manager 사이트에 접속 https://deploy.wandb.ai

   2. 라이센스키 생성

      > Limitations 30 day trial 을 클릭 해제

      생성된 라이센스키는 [https://deploy.wandb.ai](https://deploy.wandb.ai/) 에서 확인할 수 있다.

   3. `http://{서버 IP}:{사용할 port}/system-admin/ ` 에 접속하여 복사한 라이센스키 입력

      ex) `http://192.168.0.4:9595/system-admin`

3. **프로젝트에서 local W&B 로그인**

   1. wandb 로그인

      ```
      $ wandb login --host=http://{서버 IP}:{사용할 port}
      ```

      > `wandb login --host=http://192.168.0.4:9595`

   2. 만일, 이미 로그인이 되어있다면, `relogin` flag를 추가

      ```
      $ wandb login --relogin --host=http://{서버 IP}:{사용할 port}
      ```

   3. wandb-local API key 붙여넣기

      `http://{서버 IP}:{사용할 port}/authorize` 에 접속하여 API key를 복사한 뒤 붙여넣으면 된다.

4. **mysql 에 `log_table` 이라는 이름의 table 구성**

   1. container 접속

      ```
      $ docker exec -it wandb-local /bin/bash 
      ```

   2. mysql접속

      ```
      container # mysql -u wandb_local -p
      ```

      PW: `wandb_local`

   3. table 생성

      ```
      mysql > CREATE TABLE wandb_local.log_table (
          user VARCHAR(255),
          timestamp DATETIME,
          action VARCHAR(100)
      );
      ```

   해당 table을 생성해야만 `wandb sync` 명령어 실행 시 mysql의 insert가 정상적으로 이루어진다.



## wandb sycn

### map

`wandb sync` 라는 명령어 실행 시 아래 그림의 순서대로 동작이 이루어진다.

wandb_local 그림 삽입

1. **experience container**에서 `wandb sync` 명령어 실행 시 wandb package code에 의해 **wandb-local container** 의 Nginx로 post, get 요청이 보내진다.

   **url**: `http://192.168.0.4:9292/graphql`

2. Nginx는 받은 요청의 주소를 **wandb-local container**에서 실행되고 있는 gorilla 프로그램으로 routing하고있다.

3. gorilla가 요청을 받으면 외부의 비공개 code를 실행하는 trigger가 실행된다.

4. gorilla의 trigger에 의해  **wandb-local container** 의

   - minio의 위치(volume mount)에 data가 복사된다.

     이때 minio의 event 데이터는 redis에 저장된다.

   - mysql의 `wandb_local.files`와 `wandb_local.run` 에 data가 insert된다.

   >  container내부의 `/var/log/gorilla.log`를 확인하여 유추



### mysql

wandb 의 데이터를 sync하고나서 wep page에서 확인하기 위해서는 mysql에 data가 존재해야 한다.

**확인방법**

- ```
  container# mysql -u wandb_local -p -h localhost
  # passwd : wandb_local
  ```

  ```
  mysql > use wandb_local;
  ```

  ```
  mysql > Select count(*) from runs WHERE name='run_name';
  mysql > Select count(*) from files WHERE run_name='run_name';
  ```

**임의로 sync를 해제하는 방법**

- ```
  container# mysql -u wandb_local -p -h localhost
  # passwd : wandb_local
  ```

  ```
  mysql > use wandb_local;
  ```

  ```
  mysql > DELETE FROM runs WHERE name="run_name";
  mysql > DELETE FROM files WHERE run_name='run_name';
  ```

- `{mount_path}/minio/local-files/{minio_path}/run_name` 삭제



**임의로 mysql에 데이터를 insert하는 code**

```
import mysql.connector		# mysql-connector-python
import redis			# redis
import json
import os, os.path as osp
        

VOLUME_PATH = '/vol/minio/local-files'
PROEJCT_INFO = {                # project마다 id가 할당된다. 
    'VITON-HD_SegGan': dict(
        id = 1
    ),
    'VITON-HD_Synthesis': dict(
        id = 2
    ),
    'VITON-HD_GMM': dict(
        id = 3
    ),
    'VITON-HD_AFWM': dict(
        id = 4
    )
}

TARGET_RUN = 'ejf7lqvc' #  'vynp1kwh'     # ejf7lqvc

def get_data_for_insert_to_mysql(client, redis_key):
    target_project = None
    redis_data_list = client.lrange(redis_key, 0, -1)       
    data_list_for_insert = list()
    file_path_list = list()
    for data_list_bytes in redis_data_list:
        if isinstance(data_list_bytes, bytes):
            data_list = json.loads(data_list_bytes.decode('utf-8'))
        else:
            raise TypeError(f"'{type(data_list_bytes)}' is Unsupported type for decode data")
        
        for data in data_list: 
            if len(data['Event']) != 1: 
                raise KeyError(f"data['Event'] cannot contain more then 2 lens!")
            bucket_name = data['Event'][0]['s3']['bucket']['name']
            file_path = data['Event'][0]['s3']['object']['key'].replace("%2F", "/")
            local_file_path = osp.join(VOLUME_PATH, file_path)
            
            try:
                run_name = file_path.split('/')[2]
                project_name = file_path.split('/')[1]
            except:
                print(f"file_path; {file_path}")
                exit()
            if TARGET_RUN != run_name:
                # 목표로 하는 Run name에 대해서만 동작 수행
                continue
            if target_project is None: target_project = project_name

            
            if not osp.exists(local_file_path):
                # 실제로 존재하는 file인지 확인 (redis에는 중복되는 event가 많이 저장됨)
                raise OSError(f"Path '{osp.join(VOLUME_PATH, file_path)}' is not exist!")
            if local_file_path not in file_path_list:
                file_path_list.append(local_file_path)
            else:
                print(f"{local_file_path} is checked path before.")
                continue
            
            
            
            # wandb_local의 files 라는 table에 insert할 data구성
            data_list_for_insert.append(
                dict(
                    # CREATED_AT: Now
                    # UPDATED_AP: Now
                    # ID: auto_increment
                    NAME = file_path.split(f'{run_name}/')[-1],
                    MIMETYPE = "text/x-python; charset=utf-8",
                    PROJECT_ID = PROEJCT_INFO[project_name]['id'],
                    RUM_NAME = run_name,
                    META = json.dumps(dict(
                        md5 = "",
                        etag = data['Event'][0]['s3']['object']['eTag'],
                        size = data['Event'][0]['s3']['object']['size'],
                        name = file_path,
                        bucket = f"s3://{bucket_name}",
                        crc32c = "",
                        updated = data['Event'][0]['eventTime'],
                        generation = "null",
                        contentType = "text/x-python; charset=utf-8"
                    )),
                    STORAGE_BUCKET = f"s3://{bucket_name}",
                    SPECIAL = None,
                    ARCHIVED = None,
                    DELETED_AT = None,
                    STORAGE_ENTITY_NAME = file_path.split('/')[0],
                    STORAGE_PROJECT_NAME = project_name,
                    STORAGE_RUN_NAME = run_name,
                    STORAGE_FILE_NAME = file_path.split(f'{run_name}/')[-1]
                )
            )
    if len(file_path_list) != len(data_list_for_insert):
        # 실제 file의 개수와 mysql에 insert하고자 하는 data의 개수가 동일한지 확인
        raise ValueError(f"The number of files must be the same, but got ({len(file_path_list)}, {len(file_path_list)})")
    print(f"Project name: '{target_project}' \nRun name: '{TARGET_RUN}' \nNumber of data: '{len(data_list_for_insert)}'")
    return data_list_for_insert
            
            

def get_data_from_redis():
    try:
        # Redis에 연결
        client = redis.Redis(host='localhost', port=6379, db=0)
    except Exception as e:
        raise OSError(f"Failed connect to Redis")
        
    data_list_for_insert = None
    # 모든 키 조회
    redis_keys = client.keys('*')
    for redis_key in redis_keys:
        # 키의 유형 확인
        key_type = client.type(redis_key).decode('utf-8')
        
        if key_type == 'list':      # minio event에 대한 data는 redis에 list형태로 저장된다.
            # minio의 event에 대한 데이터만 주출하여 
            # mysql에 insert하기 위한 데이터로 구성
            data_list_for_insert = get_data_for_insert_to_mysql(client, redis_key)
            
        # # 유형에 따라 적절한 처리 수행
        # if key_type == 'string':
        #     value = client.get(redis_key)
        # elif key_type == 'set':
        #     value = client.smembers(redis_key)
        # elif key_type == 'hash':
        #     value = client.hgetall(redis_key)        
        # elif key_type == 'list':
        #     redis_data_list = client.lrange(redis_key, 0, -1)        
        # else:
        #     raise TypeError(f"'{type(redis_key)}' is Unsupported type for redis_key")
    return data_list_for_insert



def print_data(row):
    # 단순히 mysql의 값을 확인하기 위한 함수
    (created_at, updated_at, id, name, mimetype, project_id, run_name,
             meta, storage_bucket, special, archived, deleted_at, storage_entity_name, storage_project_name,
             storage_run_name, storage_file_name, digest)= row
    print(f"created_at: {created_at}")      # created_at: <class 'datetime.datetime'>
    print(f"updated_at: {updated_at}")      # updated_at: <class 'datetime.datetime'>
    print(f"id: {id}")                      # id: <class 'int'>
    print(f"name: {name}")                  # name: <class 'str'>
    print(f"mimetype: {mimetype}")          # mimetype: <class 'str'>
    print(f"project_id: {project_id}")      # project_id: <class 'int'
    print(f"run_name: {run_name}")          # run_name: <class 'str'>
    print(f"meta: {meta}")                  # meta: <class 'str'>
    print(f"storage_bucket: {storage_bucket}")      # storage_bucket: <class 'str'>
    print(f"special: {special}")                    # special: <class 'NoneType'>
    print(f"archived: {archived}")                  # archived: <class 'NoneType'>
    print(f"deleted_at: {deleted_at}")              # deleted_at: <class 'NoneType'>
    print(f"storage_entity_name: {storage_entity_name}")        # storage_entity_name: <class 'str'>
    print(f"storage_project_name: {storage_project_name}")      # storage_project_name: <class 'str'>
    print(f"storage_run_name: {storage_run_name}")              # storage_run_name: <class 'str'>
    print(f"storage_file_name: {storage_file_name}")            # storage_file_name: <class 'str'>
    print(f"digest: {digest}")          # digest: <class 'str'>
    print(f"\n\n")


def get_date(conn): 
    # mysql에 있는 데이터를 불러와 확인하기 위한 함수
    project_id_list = list()
    cursor = conn.cursor()
    query = "SELECT * FROM files;"     # WHERE run_name='ejf7lqvc'
    cursor.execute(query)
    results = cursor.fetchall()
    for row in results:
        (created_at, updated_at, id, name, mimetype, project_id, run_name,
            meta, storage_bucket, special, archived, deleted_at, storage_entity_name, storage_project_name,
            storage_run_name, storage_file_name, digest)= row
        # print_data(row)
        if project_id not in project_id_list:
            project_id_list.append(project_id)
            print(f"project_id: {project_id}")
            print(f"storage_project_name: {storage_project_name}\n")

    exit()
    
    
def insert_data(conn, data_list_for_insert):
    cursor = conn.cursor()

    for data_for_insert in data_list_for_insert:
        # insert하기 위한 query구성
        query = (
        "INSERT INTO files (created_at, updated_at, name, mimetype, project_id, run_name, "
                        "meta, storage_bucket, special, archived, deleted_at, "
                        "storage_entity_name, storage_project_name, storage_run_name, storage_file_name) "
                "VALUES (NOW(), NOW(), %s, %s, %s, %s, "
                        "%s, %s, %s, %s, %s, "
                        "%s, %s, %s, %s)"
        )
    
        values = (data_for_insert['NAME'],  data_for_insert['MIMETYPE'],  data_for_insert['PROJECT_ID'],  data_for_insert['RUM_NAME'],
                data_for_insert['META'], data_for_insert['STORAGE_BUCKET'], data_for_insert['SPECIAL'], data_for_insert['ARCHIVED'], data_for_insert['DELETED_AT'],
                data_for_insert['STORAGE_ENTITY_NAME'], data_for_insert['STORAGE_PROJECT_NAME'], data_for_insert['STORAGE_RUN_NAME'], data_for_insert['STORAGE_FILE_NAME'])
        cursor.execute(query, values)
        conn.commit()
        
        # test를 위하여 하나만 insert하도록 exit설정
        conn.close()
        cursor.close()
        exit()
    
    
def main():
    data_list_for_insert = get_data_from_redis()
    if data_list_for_insert is None:
        raise ValueError(f"Redis data deleted automatically. Run again `wandb sync`")
    exit()
    
    try:
        # MySQL 데이터베이스 연결
        conn = mysql.connector.connect(
            host='localhost',
            user='wandb_local',
            password='wandb_local',  
            database='wandb_local' 
        )
    except Exception as e:
        raise OSError(f"Failed connect to Mysql")

    insert_data(conn, data_list_for_insert)

    if conn.is_connected():
        conn.close()
        

main()
```

