# google.cloud

## install google CIL





## Syncing Data to GCP Storage Buckets

### set Storage

1. project만들기

2. bucket만들기

   [여기](https://console.cloud.google.com/welcome?project=adroit-producer-358501)에서 storage bucket 만들기 > 

   - 객체 엑세스 제어 : 균일한 엑세스
   - 객체 데이터 보호하는 방법 : 객체 버전 관리 (객체당 최대 버전 수 3, 다음 날짜 7)

   > bucket세부정보에서 bucket name확보

3. credentials 얻기

   IAM & Admin > Service Accounts > create Service Accounts

   1. 서비스 계정 세부 정보

      > service account e-mail확보

   2. 프로젝트에 대한 엑세스 권한 부여

      역할 : 소유자

   3. 서비스 계정에 대한 엑세스 권한 부여

      서비스 계정 사용자 역할 : `service account e-mail`

      서비스 계정 관리자 역할 :  `service account e-mail`

      > `service account e-mail` : 위 1단계에서 얻은 e-mail

      > OAuth 2 client ID확보

   4. service account의 정보 중 `작업` > `key 관리` > `add key` : `'Json' format`

      -> json형식의 secret key가 local에 저장됨

      > 해당 file에 저장된 information
      >
      > `type`
      >
      > `project_id`
      >
      > `private_key_id`
      >
      > `private_key`
      >
      > `client_email`
      >
      > `client_id`
      >
      > `auth_uri`
      >
      > `token_uri`
      >
      > `auth_provider_x509_cert_url`
      >
      > `client_x509_cert_url`

      이건 `client_secrets.json` 으로 이름 변경 후 관리



### DVC

#### set remote

##### init

1. dvc init

   ```
   $ dvc init
   $ dvc remote add -d {remote name} gs://{bucket name}
   ```

   > remote name : remote 이름은 자유
   >
   > `.dvc/config` 에 remote정보가 추가된다.

2. GCP credentials

   1. export

      ```
      $ export GOOGLE_APPLICATION_CREDENTIALS='{path of client_secrets.json}'
      ```

      > 위 명령어를 입력하는 위치에 `client_secrets.json` 가 있으면
      >
      > `export GOOGLE_APPLICATION_CREDENTIALS=client_secrets.json`

   2. set credentialpath

      ```
      dvc remote modify --local {remote name} credentialpath '{path of client_secrets.json}'
      ```




##### modify remote

기존의 storage가 아닌, 다른 storage에 연결하는 경우

- 다른 storage가 새롭게 생성된 storage인 경우

  ```
  dvc remote add -d {remote name} gs://{bucket name}
  ```

- 다른 storage가 기존에 있던 storage인 경우

  `.dvc/config`를 살펴보면 아래와 같이 되어있다.

  ```
  [core]
      remote = remote_name_1
  ['remote "remote_name_1"']
      url = url_exam_1
  ['remote "remote_name_2"']
      url = url_exam_2
  ['remote "remote_name_3"']
      url = url_exam_3
  ```

  > 현재 remote가 `remote_name_1`을 가리키고 있다.
  >
  > 이를 `remote_name_2` 또는 `remote_name_3`으로(원하는 remote로) 변경해준다.



이후 GCP credentials 진행

export

```
$ export GOOGLE_APPLICATION_CREDENTIALS='{path of client_secrets.json}'
```

> 위 명령어를 입력하는 위치에 `client_secrets.json` 가 있으면
>
> `export GOOGLE_APPLICATION_CREDENTIALS=client_secrets.json`



set credentialpath

```
dvc remote modify --local {remote name} credentialpath '{path of client_secrets.json}'
```

> 현재 위치에 client_secrets.json 가 있다면 `path of client_secrets.json` =`client_secrets.json`



#### add data

##### add info to git

data를 저장할 dir을 생성 후 그 안에 data를 위치시킨다.

```
$ mkdir {dir_name}
```

> 현재 위치에 있는 data를 바로 upload할 수 없다. 1개 이상의 dir이 있는 구조가 필요
>
> ```
> dir - .git
> 	- .dvc
> 	- dataset_1(dir)
> 	- dataset_2(dir)
> ```

해당 dir을 dvc로 tracking (`dvc status`를 하면 modified상태 확인 가능)

```
$ dvc add {dir_name}/
```

```
To track the changes with git, run:                                             
	
	git add {dir_name}.dvc .gitignore 
```

위에서 뜬 안내메시지 실행 (git에서 version관리를 할 수 있도록 해줌)

```
$ git add {dir_name}.dvc 
```

- check

  위 명령어를 수행한 위치에 `{dir_name}.dvc` file이 생겼음을 확인할 수 있다.

  이 file은 {dir_name}안의 dataset에 대한 meta data를 가진 file이다.

  git은 바로  이 .dvc file 관리하게 된다.

  > 이 때 `.gitignore `는 아래의 내용이 담겼으며 `.dvc`안에 위치해있다.
  >
  > ```
  > /config.local
  > /tmp
  > /cache
  > ```
  >
  > 기존의 `.gitignore`과 별개임

해당 data에 대한 정보를 commit, push

```
$ git commit -m "dataset_0.0.1"
$ git push
```





#### data upload

실제 data를 storage에 push한다.

```
$ dvc push
```



#### download data

- 전혀 새로운 곳에서 data를 받고자 할 때

  download하고자 하는 dataset에 대한 정보를 가진 `{dataset dir name}.dvc`가 있어야 한다.

  ```
  $ git pull
  ```

  > 또는 `git clone`

  이후  GCP credentials 진행

- `{dataset dir name}.dvc`가 있는 경우

  pass

```
$ dvc pull
```









## SDK

[공식](https://cloud.google.com/python/docs/reference/storage/latest/google.cloud.storage.blob.Blob)

```
$ pip google-cloud-storage
```

> dvc를 같이 사용한다면 아래 명령어
>
> ```
> $ pip install 'dvc[gs]'
> ```
>



### storage

```python
from google.cloud import storage
import os
os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = client_secrets_path
```

- `client_secrets_path` : google cloud IAM secret key(json format)

 

#### Client

```python
from google.cloud import storage

storage_client = storage.Client()
```



#####  get_bucket, blob

return bucket instance

```python
storage_client = storage.Client()
bucket = storage_client.get_bucket(BUCKET_NAME)
blob = bucket.blob(BLOB_PATH)
```

- `BUCKET_NAME` :  interact할 bucket name
- `BLOB_PATH` : storage내 bucket에 upload (or download)할 file의 path



###### upload_from_filename

```python
blob.upload_from_filename(local_file_path)
```

- `local_file_path` : upload할 file의 path



###### download_to_filename

```python
blob.download_to_filename(local_file_path)
```

- `local_file_path` : file을 download할 path