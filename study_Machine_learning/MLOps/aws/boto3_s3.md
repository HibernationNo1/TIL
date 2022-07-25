# boto3_s3

## Introduction

Simple Storage Service의 약자로 파일 서버의 역할을 하는 서비스다. 일반적인 파일서버는 트래픽이 증가함에 따라서 장비를 증설하는 작업을 해야 하는데 S3는 이와 같은 것을 대행한다. 트래픽에 따른 시스템적인 문제는 걱정할 필요가 없어진다. 또 파일에 대한 접근 권한을 지정 할 수 있어서 서비스를 호스팅 용도로 사용하는 것을 방지 할 수 있다.



**AWS S3(Simple Storage Service의 특징**

- 많은 사용자가 접속을 해도 이를 감당하기 위해서 시스템적인 작업을 하지 않아도 된다.
- 저장할 수 있는 파일 수의 제한이 없다.
- 최소 1바이트에서 최대 5TB의 데이터를 저장하고 서비스 할 수 있다.
- 파일에 인증을 붙여서 무단으로 엑세스 하지 못하도록 할 수 있다.
- HTTP와 BitTorrent 프로토콜을 지원한다.
- REST, SOAP 인터페이스를 제공한다.
- 데이터를 여러 시설에서 중복으로 저장해 데이터의 손실이 발생할 경우 자동으로 복원한다.
- 버전관리 기능을 통해서 사용자에 의한 실수도 복원이 가능하다.
- 정보의 중요도에 따라서 보호 수준을 차등 할 수 있고, 이에 따라서 비용을 절감 할 수 있다. (RSS)



**용어**

- 객체 - object, AWS는 S3에 저장된 데이터 하나 하나를 객체라고 명명하는데, 하나 하나의 파일이라고 생각하면 된다.
- 버킷 - bucket, 객체가 파일이라면 버킷은 연관된 객체들을 그룹핑한 최상위 디렉토리라고 할 수 있다. 버킷 단위로 지역(region)을 지정 할 수 있고, 또 버킷에 포함된 모든 객체에 대해서 일괄적으로 인증과 접속 제한을 걸 수 있다.
- 버전관리 - S3에 저장된 객체들의 변화를 저장. 예를들어 A라는 객체를 사용자가 삭제하거나 변경해도 각각의 변화를 모두 기록하기 때문에 실수를 만회할 수 있다.
- RSS - Reduced Redundancy Storage의 약자로 일반 S3 객체에 비해서 데이터가 손실될 확률이 높은 형태의 저장 방식. 대신에 가력이 저렴하기 때문에 복원이 가능한 데이터, 이를테면 섬네일 이미지와 같은 것을 저장하는데 적합하다. 그럼에도 불구하고 물리적인 하드 디스크 대비 400배 가량 안전하다는 것이 아마존의 주장
- Glacier - 영어로는 빙하라는 뜻으로 매우 저렴한 가격으로 데이터를 저장 할 수 있는 아마존의 스토리지 서비스





1. 회원가입

2. 버킷 만들기

   1. 일반 구성

      버킷 이름 : 임의의 이름 (hibernationproject)

      AWS 리전 : 아시아 태평양(서울)ap-northeast-2 검색

   2. 객체 소유권

      권장사항

   3. 엑세스 차단 설정 (1, 2번째것만 해제)

      - **새 ACL(액세스 제어 목록)을 통해 부여된 버킷 및 객체에 대한 퍼블릭 액세스 차단**

        공개 설정으로 해둔 파일을 업로드 할 때, 업로드가 거절된다.

        지정된 ACL이 퍼블릭이거나, 요청에 퍼블릭 ACL이 포함되어 있으면 PUT 요청을 거절한다.

        (권장 : 해제)

      - **임의의 ACL(액세스 제어 목록)을 통해 부여된 버킷 및 객체에 대한 퍼블릭 액세스 차단**

        버킷의 모든 퍼블릭 ACL과 그 안에 포함된 모든 Object를 무시하고, 퍼블릭 ACL를 포함하는 PUT 요청은 허용한다. (권장 : 해제)

      - 새 퍼블릭 버킷 또는 액세스 지점 정책을 통해 부여된 버킷 및 객체에 대한 퍼블릭 액세스 차단

        지정된 버킷 정책이 퍼블릭이면 PUT 요청을 거절한다. 이 설정을 체크하면 버킷 및 객체에 대한 퍼블릭 액세스를 차단하고 사용자가 버킷 정책을 관리할 수 있으며, 이 설정 활성화는 기존 버킷 정책에 영향을 주지 않는다.

      - **임의의 퍼블릭 버킷 또는 액세스 지점 정책을 통해 부여된 버킷 및 객체에 대한 퍼블릭 액세스 차단**

        퍼블릭 정책이 있는 버킷에 대한 액세스가 권한이 있는 사용자와 AWS 서비스로만 제한되며, 이 설정 활성화는 기존 버킷 정책에 영향을 주지 않는다.

   4. 버킷 버전 관리

      활성화 : 파일이 수정되었어도 그 과거 내용이 보존

   5. 기본 암호화

      서버측 암호화를 활성화 하면, Object를 암호화된 상태로 안전하게 보관할 수 있다. (비활성화 했음)

   6. 고급 설정

      객체 잠금 : 객체 잠금을 활성화 하면 객체의 삭제 및 덮어쓰임을 방지할 수 있다. (비활성화 했음)



관련 python SDK는 boto3라는 package로 사용 가능하다.



aws storage(S3) python SDK

[공식](https://boto3.amazonaws.com/v1/documentation/api/latest/guide/quickstart.html)



## SDK

#### install 

- Requirements : `boto3`, `tqdm`

```
$ pip install boto3 tqdm
```



check

```python
import boto3
print(boto3.__version__) 
```

> 1.24.2

source code [공식](https://boto3.amazonaws.com/v1/documentation/api/latest/index.html)



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



### Session

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





### client

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





### resource

```python
import boto3

AWS_ACCESS_KEY_ID ="..."
AWS_SECRET_ACCESS_KEY = "..."

s3 = boto3.resource('s3',
                      aws_access_key_id=AWS_ACCESS_KEY_ID,
                      aws_secret_access_key=AWS_SECRET_ACCESS_KEY
                      )
```





#### Bucket

```python
bucket = s3.Bucket('bucket_name')
```

- `bucket_name` : s3에 존재하는, 접근하고자 하는 bucket의 name

  

##### download_file

```python
bucket.download_file('file_path_in_storage', 'file_path_to_download')
```

- `file_path_in_storage` : 특정 bucket에 있는 file의 path (fotmat을 포함한 name)
- `file_path_to_download` : down받고자 하는 file을 save할 path



##### upload_file

```python
bucket.upload_file('file_path_to_upload', 'file_path_in_storage')
```

- `file_path_to_upload` : upload할 file의 path
- `file_path_in_storage` : 특정 bucket에 저장할 file의 name (format 포함)



**예시**

```python
import boto3
import os


AWS_ACCESS_KEY_ID ="AKIAXZX44242SIJNTR5O"
AWS_SECRET_ACCESS_KEY = "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"
bucket_name = "hibernationproject"
file_path_in_storage = 'requirements.txt'
file_path_to_upload = os.path.join(os.getcwd(), "exam.txt")

s3 = boto3.resource('s3',
                      aws_access_key_id=AWS_ACCESS_KEY_ID,
                      aws_secret_access_key=AWS_SECRET_ACCESS_KEY
                      )



bucket = s3.Bucket(bucket_name)

bucket.upload_file(file_path_to_upload, file_path_in_storage)
```

