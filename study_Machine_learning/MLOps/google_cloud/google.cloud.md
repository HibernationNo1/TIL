# google.cloud

## install google CIL





## Syncing Data to GCP Storage Buckets

1. project만들기

2. bucket만들기

   [여기](https://console.cloud.google.com/welcome?project=adroit-producer-358501)에서 storage bucket 만들기 > 

   - 객체 엑세스 제어 : 균일한 엑세스
   - 객체 데이터 보호하는 방법 : 객체 버전 관리 (객체당 치대 버전 수 3, 다음 날짜 7)

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

4. set DVC

   1. dvc init

      ```
      $ dvc init
      $ dvc remote add -d bikes gs://{bucket name}
      ```

      > remote 이름 : bikes 로 만든것임. remote 이름은 자유

   2. GCP credentials

      ```
      $ export GOOGLE_APPLICATION_CREDENTIALS='{path of client_secrets.json}'
      ```

   3. dvc push 

      ```
      $ dvc push
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