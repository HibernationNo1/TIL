# AWS CLI

##### install

- Linux

  ```
  $ sudo apt install awscli
  ```

- windows

  [여기](https://docs.aws.amazon.com/ko_kr/cli/latest/userguide/getting-started-install.html) 에서 다운로드

check

```
$ aws --version
```



##### set configure

access key발급은 [aws공식](https://us-east-1.console.aws.amazon.com/console/home?region=us-east-1#)에서 받는다. 자세한 방법은 [여기](https://docs.aws.amazon.com/ko_kr/IAM/latest/UserGuide/id_users_create.html)

1. 우측 상단에 IAM을 검색

2. 좌측 탭 중 `사용자` 선택 후 우측 `사용자 추가` 선택

3. 사용자 이름 입력 (hibernation_project)

   아래 **액세스 키 – 프로그래밍 방식 액세스** 선택

4. 권한 설정

   1. 그룹 만들기

   2. 그룹 이름(hibernation) 만들고 `AdministratorAccess` 선택

      > 관리자 권한을 해당 그룹에 부여

5. 키 확인

   - AWS 계정의 access key

   - AWS 계정의 secret key



민감한 자격 증명 정보를 홈 디렉터리의 `credentials`라는 폴더에 있는 `.aws`라는 로컬 파일에 저장

덜 민감한 구성 옵션은 `config`라는 로컬 파일에 저장되며, 홈 디렉터리의 `.aws` 폴더에 저장

```
$ aws configure
```

```
AWS Access Key ID [None]: AKIAXZX44242X6XXYK7K		# AWS 계정의 access key
AWS Secret Access Key [None]: YtM93B0DvThk+dcltXao32ZEGtOZYVSEkpsJrV9u		# AWS 계정의 secret key
Default region name [None]: ap-northeast-2 			# 
Default output format [None]: json 
```

configure 정보 변경은 **`aws configure set`** 사용(검색) 또는 `aws configure` 한번 더 실행해서 입력

> windows에서는 cmd 명령 프롬프트에서 해야됨

check configure

```
$ aws configure list
```

