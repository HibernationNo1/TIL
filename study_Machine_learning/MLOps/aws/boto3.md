# boto3

aws storage(S3) python SDK

[공식](https://boto3.amazonaws.com/v1/documentation/api/latest/guide/quickstart.html)





#### install 

- Requirements : `boto3`, `tqdm`

```
$ pip install boto3 tqdm
```



boto3에서 s3에 접근하는 방법은 `client`, `resource`, `Session` 세 가지가 있다.

- `client`
  - low-level interface
  - service description에 의해 만들어짐
  - AWS CLI와 boto3의 기초가 되는 라이브러리인 botocore 수준의 client를 공개
  - 가끔 botocore의 API를 찾아봐야하는 경우가 있기도 함
  - **모든 AWS 서비스 API와 1:1 매핑**됨
  - 메소드가 스네이크 케이스로 정의되어 있음
- `resource`
  - boto3.client를 wrapping한 high-level, 객체지향적 interface
  - 높은 수준의 추상화
  - resource description에 의해 만들어짐
  - Identifiers
    - 특정 리소스를 고유하게 식별하는 데 사용되는 고유한 값
    - bucket_name과 key가 있음
  - Attributes
    - 리소스 속성에 액세스. load() 메소드를 통해 로드되므로 처음 액세스 시 느리게 로드 됨
    - accept_ranges, metadata, last_modified 등 👉 [공식 문서 참고](https://boto3.amazonaws.com/v1/documentation/api/latest/reference/services/s3.html#S3.Object)
  - Actions
    - 리소스에 대한 작업 호출. 식별자와 일부 특성으로부터 인수 전달을 자동으로 처리 가능
    - copy(), delete(), get(), download_file(), upload_file() 등 👉 [공식 문서 참고](https://boto3.amazonaws.com/v1/documentation/api/latest/reference/services/s3.html#S3.Object)
  - 자원에 대한 조작 위주 → 직관적, 사용 편리
  - AWS 서비스와 상호작용할 때 기본 디테일에 대한 고민이 많이 필요하지 않아 boto3 사용에서 권장됨
  - boto3.client의 모든 기능을 wrapping한 것이 아니라서 필요하다면 boto3.client 혹은 boto3.resource.meta.client를 사용해야 함
- `Session`
  - configure를 저장
  - service `client` 및 `resource`를 만들 수 있다.



## Session

configure을 저장하고  client & resource 서비스를 생성하기 위한 권한을 부여

```python
import boto3

AWS_ACCESS_KEY_ID ="..."
AWS_SECRET_ACCESS_KEY = "..."

session = boto3.Session(
    aws_access_key_id=AWS_ACCESS_KEY_ID,
    aws_secret_access_key=AWS_SECRET_ACCESS_KEY
)
s3 = session.resource('s3')  # s3에 대한 권한 및 상태를 s3(변수)에 저장

print(f"s3 : {s3}")
for bucket in s3.buckets.all():
    print(bucket.name)
```





## client

`AWS_ACCESS_KEY_ID`, `AWS_SECRET_ACCESS_KEY` 을 사용하여 AWS의 특정 사용자에 접속

```python
import boto3

AWS_ACCESS_KEY_ID ="AKIAXZX44242X6XXYK7K"
AWS_SECRET_ACCESS_KEY = "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"
client = boto3.client('s3',
                      aws_access_key_id=AWS_ACCESS_KEY_ID,
                      aws_secret_access_key=AWS_SECRET_ACCESS_KEY
                      )
```

> AWS_ACCESS_KEY_ID : AWS에 추가한 사용자 중 하나의 ACCESS_KEY
>
> AWS_SECRET_ACCESS_KEY : AWS에 추가한 사용자 중 하나의 SECRET_ACCESS_KEY





## resource

```python
import boto3

AWS_ACCESS_KEY_ID ="..."
AWS_SECRET_ACCESS_KEY = "..."

s3 = boto3.resource('s3',
                      aws_access_key_id=AWS_ACCESS_KEY_ID,
                      aws_secret_access_key=AWS_SECRET_ACCESS_KEY
                      )
```





### Bucket

```python
bucket = s3.Bucket('bucket_name')
```

- `bucket_name` : s3에 존재하는, 접근하고자 하는 bucket의 name

  

#### download_file

```python
bucket.download_file('file_path', 'download_file_path')
```

- `file_path` : 특정 bucket에 있는 file의 path (fotmat을 포함한 name)
- `download_file_path` : down받고자 하는 file을 save할 path



#### upload_file

```python
bucket.upload_file('upload_file_path', 'file_path')
```

- `upload_file_path` : upload할 file의 path
- `file_path` : 특정 bucket에 저장할 file의 name (format 포함)