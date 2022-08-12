# minio



minio-service는 kubeflow namespace에 있다.

```
$ kubectl get svc -n kubeflow | grep minio-service 
```

```
minio-service                                               ClusterIP   10.97.174.20     <none>        9000/TCP            23d
```



```
$ kubectl -n kubeflow port-forward svc/minio-service 9000:9000
```

기본 `minio/minio123`







minio client 실행

> container안으로 들어가는거와 같다.

```
$ kubectl attach my-mc -c my-mc -i -t
```

```
mc: Configuration written to `/root/.mc/config.json`. Please update your access credentials.
mc: Successfully created `/root/.mc/share`.
mc: Initialized share uploads `/root/.mc/share/uploads.json` file.
mc: Initialized share downloads `/root/.mc/share/downloads.json` file.
```







```
[root@my-mc /]# mc config host ls
```

```
gcs  
  URL       : https://storage.googleapis.com
  AccessKey : YOUR-ACCESS-KEY-HERE
  SecretKey : YOUR-SECRET-KEY-HERE
  API       : S3v2
  Path      : dns

local
  URL       : http://localhost:9000
  AccessKey : 
  SecretKey : 
  API       : 
  Path      : auto

play 
  URL       : https://play.min.io
  AccessKey : Q3AM3UQ867SPQQA43P2F
  SecretKey : zuf+tfteSlswRu7BJ86wekitnifILbZam1KYY3TG
  API       : S3v4
  Path      : auto

s3   
  URL       : https://s3.amazonaws.com
  AccessKey : YOUR-ACCESS-KEY-HERE
  SecretKey : YOUR-SECRET-KEY-HERE
  API       : S3v4
  Path      : dns
```

- `gcs`  : google에서 제공하는storage service
- `ocal` : 사용자가 local에 직접 설정한 MinIO
- `play` : minop에서 제공하는 MinIO storage service
- `s3` : AWS에서 제공하는 S3 service





kubeflow의 minio-service client에 접속

Add a Cloud Storage Service

```
[root@my-mc /]# mc alias set exam http://minio-service.kubeflow:9000 minio minio123
```

```
Added `exam` successfully.
```

아래 host가 추가된다.

```
exam
  URL       : http://minio-service.kubeflow:9000
  AccessKey : minio
  SecretKey : minio123
  API       : s3v4
  Path      : auto
```





이제부터 storage에 이러저런 명령어 사용 가능

- bucket list

  ```
  $ mc ls exam
  ```

- play list

  ```
  $ mc ls play
  ```

  





```
from minio import Minio

client = Minio(
    "minio-service.kubeflow:9000",
    access_key="minio",
    secret_key="minio"
)


bucket_name = "mlpipeline"

if client.bucket_exists(bucket_name):
    print(f"{bucket_name} exists")
else:
    print(f"{bucket_name} does not exist")
    

```