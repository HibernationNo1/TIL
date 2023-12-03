# DVC

Data Version Control

dataset을 version화 하여 관리할 수 있도록 하는 tool

- 대부분의 스토리지와 호환(amazon s3, google drive, ...)
- github외의 gitlab, bitbucket등의 대부분의 git 호스팅 서버와 연동
- data pipeline을 관리



#### install

[공식](https://dvc.org/doc/install)

가상환경 권장

```
$ pip install dvc[all]
```

> - storage중에서 s3만 사용할거면 
>
>   ```
>   $ pip install dvc[s3]
>   ```
>
> - SSH를 사용할거면
>
>   ```
>   $ pip install dvc[ssh]
>   ```
>
> - local dir을 storage로 사용할거면
>
>   ```
>   $ pip install dvc
>   ```



check

```
$ dvc --version
```



## Data Management

### 1. DVC init setting 

1. **init**

   git과 dvc모두 init

   ```
   $ git init
   $ dvc init
   ```

2. **git repository에 연결**

   ```
   $ vi README.md
   $ git commit -m "first commit"
   $ git remote add origin <주소>
   $ git push
   ```

   > 필요시  `git push --set-upstream origin master` 
   >
   > dvc의 여러 정보를 git repository로 관리

3. **add datset**

   관리할 dataset을 dir째로 위치한다.

   ```
   $ mkdir {dir_name}
   ```

   >현재 위치에 있는 data를 바로 upload할 수 없다. 1개 이상의 dir이 있는 구조가 필요
   >
   >```
   >dir - .git
   >	- .dvc
   >	- dataset_1(dir)
   >	- dataset_2(dir)
   >```

4. **dvc add**

   해당 dir을 dvc로 tracking (`dvc status`를 하면 modified상태 확인 가능)

   ```
   $ dvc add {dir_name}/
   ```

   ```
   To track the changes with git, run:                                             
   	
   	git add {dir_name}.dvc .gitignore 
   ```

   > dvc push는 remote storage에 연결 후 진행

5. **해당 변경 내용 git으로 관리**

   ```
   $ git add {dir_name}.dvc .gitignore 
   ```

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

   그 외에도 add할 사항이 있다면 git add 실행

   

   이후 git commit까지

   ```
   $ git commit -m "dataset_0.0.1"
   ```



### 2. **add remote storage**

remote storage는 cloud storage가 될 수도 있고, local에 특정 dir이 될 수도 있다.

#### google drive

1. google drive에 가서 dir새로 만들기  >> url ID복사

   ```
   https://drive.google.com/drive/folders/1ZJExBQjJp2VJRBtB-U8IUffJL0q5WBgN
   ```

   일 때 url ID는 아래와 같다

   ```
   1ZJExBQjJp2VJRBtB-U8IUffJL0q5WBgN  
   ```

2. dvc add

   ```
   $ dvc remote add -d storage gdrive://1ZJExBQjJp2VJRBtB-U8IUffJL0q5WBgN
   ```

   > `gdrive` : google drive라는 뜻

   ```
   Setting 'storage' as a default remote.          
   ```

   > default remote storage로 setting되었음을 의미

#### google storage

1. google cloud storage에서 bucket생성

   [여기](https://console.cloud.google.com/welcome?project=adroit-producer-358501)에서 storage bucket 만들기 > 

   - 객체 엑세스 제어 : 균일한 엑세스
   - 객체 데이터 보호하는 방법 : 객체 버전 관리 (객체당 치대 버전 수 3, 다음 날짜 7)

   > bucket세부정보에서 bucket name확보

2. dvc add

   ```
   $ dvc remote add -d remote_name gs://{bucket name}
   ```



#### aws S3

1. aws에 가입 후 bucket만든 후, bucket안에서 1개의 directory생성 후 해당 dir의 URL복사

   ```
   s3://{my_bucket}/{dir_name}/
   ```

2. dvc add

   ```
   $ dvc remote add -d remote_name s3://{my_bucket}/{dir_name}/
   ```

   > ```
   > Setting 'storage' as a default remote.
   > ```



#### ssh

192.168.0.101의 서버의 `/var/services/homes/dvc` 의 위치를 remote directory로 결정

1. SSH연결

   ```
   $  dvc remote add -d remote_name ssh://teno@192.168.0.101:/DATA/01.Data/dvc_test_folder
   ```

2. port설정 (기본값 22이 아닌, 2323인 경우)

   ```
   $ dvc remote modify remote_name port 2323
   ```

   - Nas에 연결하는 경우 

     1. `제어판` > `FTP` > `SFTP서비스 활성화`

        해당 port는 sftp의 포트번호 기입

     2. 원격 서버의 `/etc/ssh/sshd_config` 의 아래 내용 수정

        ```
        # override default of no subsystems
        # Subsystem sftp    /usr/libexec/sftp-server
        Subsystem   sftp    internal-sftp -f DAEMON -u 000		# 활성화 되어있어야 함
        ```

3. remote에 ssh개인 키 등록

   ```
   $ dvc remote modify remote_name keyfile ~/.ssh/id_rsa
   ```

   



#### local dir

1. storage path결정

   ```
   $ dvc remote add -d remote_name local/dir/path
   ```








### 3. dvc push



#### google drive

```
Go to the following link in your browser:

    https://accounts.google.com/o/oauth2/auth?client_id=710796635688-iivsgbgsb6uv1fap6635dhvuei09o66c.apps.googleusercontent.com&redirect_uri=urn%3Aietf%3Awg%3Aoauth%3A2.0%3Aoob&scope=https%3A%2F%2Fwww.googleapis.com%2Fauth%2Fdrive+https%3A%2F%2Fwww.googleapis.com%2Fauth%2Fdrive.appdata&access_type=offline&response_type=code&approval_prompt=force

Enter verification code:
```

위 출력이 나오며 인증 과정이 필요. 해당 주소로 이동하여 google login을 통해 수행.

인증을 수행하는 과정에 code가 보임

```
4/1AdQt8qgp7fYSoMCqitgBxY7BOOgrbDqZJ8m6o06Lqu3oRgCdJwjBB7zMdgc
```

이를 `Enter verification code:` 에 입력

```
Authentication successful.
```

이후 google drive에 들어가보면 random한 이름으로 file들이 생김. 이것들은 git add-commit으로 업로드 한 file들.



#### google storage

1. `client_secrets.json` 다운로드

   service account의 정보 중 `작업` > `key 관리` > `add key` : `'Json' format`

   -> json형식의 secret key가 local에 저장됨

   이걸 `client_secrets.json` 으로 이름 변경

2. GCP credentials

   1. export

      ```
      $ export GOOGLE_APPLICATION_CREDENTIALS='{path of client_secrets.json}'
      ```

      > 위 명령어를 입력하는 위치에 `client_secrets.json` 가 있으면
      >
      > `export GOOGLE_APPLICATION_CREDENTIALS=client_secrets.json`

   2. remote modify

      ```
      dvc remote modify --local remote_name credentialpath '{path of client_secrets.json}'
      ```

   3. dvc push 

      ```
      $ dvc push
      ```



#### aws S3

S3인 경우 해당 device에 user의 acssess key와 secret를 등록해놓아야 한다.

1. `aws configure` 사용

   ```
   $ aws configure
   ```

   ```
   AWS Access Key ID [****************xxxx]: 
   AWS Secret Access Key [****************xxxx]: 
   ```

2. `dvc remote modify --local bikes` 사용

   ```
   $ dvc remote modify --local remote_name access_key_id 'mykey' 
   $ dvc remote modify --local remote_name secret_access_key 'mysecret'
   ```

acssess key와 secret등록이 완료되면 push

```
$ dvc push
```

> ```
> 19 files pushed
> ```
>
> 19개 file정상적으로 pushed



#### ssh, local dir

```
$ dvc push
```





---





### download data

1. git init, dvc init을 한 dir위치에서 dvc pull을 할 때 (`.dvc` dir안에 ceche가 있는 경우)

   data를 remote storage로부터 download

   1. data를 받을 dir결정

      ```
      $ cd {dir_name}
      ```

      > `{dir_name}` : **`.div(dir)`과 `{dir_name}.dvc` 가 있어야함.**

   2. dvc pull

      data를 remote storage로부터 download받을 수 있는 명령어

      위의 `{dir_name}` 의 dir안의 data를 전부 지운 후 

      ```
      $ dvc pull
      ```

      을 하면 지워진 data가 google drive로부터 down받아진것을 확인할 수 있다.

2. 전혀 새로운 환경에서 dvc pull을 할 때 (`.dvc` dir안에 ceche가 없는 경우)

   1. S3 

      `.dvc(dir)`와  `{dir_name}.dvc` file이 있는 repo를 가져온다

      ```
      $ git clone
      ```

      access key입력

      ```
      $ dvc remote modify --local remote_name access_key_id 'mykey' 
      $ dvc remote modify --local remote_name secret_access_key 'mysecret'
      ```

      ```
      $ dvc pull
      ```

   2. google cloud storage

      `.dvc(dir)`와  `{dir_name}.dvc` file이 있는 repo를 가져온다

      ```
      $ git pull 		
      ```

      set remote

      ```
      $ dvc remote add -d -f remote_name gs://{bucket name}
      ```

      set client secrets

      ```
      $ export GOOGLE_APPLICATION_CREDENTIALS='client_secrets_path'
      ```

      - `client_secrets_path` : client_secrets.json의 위치

      ```
      $ dvc pull
      ```

      



### data checkout

#### modify dataset

1. dvc status

   `git init`, `dvc init` 가 된 dir의 하위 dir중에 수정이 있는 경우

   ```
   $ dvc status
   ```
   
   ```
   {dir_name}.dvc:
           changed outs:
                   modified:           {dir_name}
   ```
   
1. dvc add

   수정사항이 있는 dir은 

   ```
   $ dvc add {dir_name}/
   ```
   
1. data push

   data가 변경될 경우`dvc-storage` 의 위치의 `{dir_name}.dvc` 가 바뀌게 되는데, 이를 push

   1. git push

      ```
      $ git add {dir_name}.dvc
      ```

   2. git cummit

      ```
      $ git commit -m "dataset_1.0.1"
      ```

      > commit을 하지 않아도 push가 가능하지만, commit을 함으로써 log를 남겨 나중에 rollback이 가능하도록 한다.

   3. dvc push, git push
   
      ```
      $ dvc push
      ```
   
      > git repository가 있는 사람은 git push까지
      >
      > ```
      > $ git push
      > ```
   
   google drive에 변경 된 `{dir_name}.dvc`가 업로드 됨 



#### rollback dataset

1. data rollback

   이전 version의 data를 받기

   1. check log

      ```
      $ git log --oneline
      ```

      ```
      a102af5 (HEAD -> master) updata dataset
      3b550fa add remote storage
      df161ec Add test data
      ```

   2. git checkout

      ```
      $ git checkout df161ec {dir_name}.dvc
      ```

      > dvc file이 `test data` 로 commit했던 version으로 변경

   3. dvc checkout

      ```
      $ dvc checkout
      ```

      > `test data` commit했던 version의 data를 받는다.

   

