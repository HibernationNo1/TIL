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
$ pip install dvc[all]==2.6.4
```

> 특정 version download



check

```
$ dvc --version
```



## Data Management

### DVC storage setting

1. make directory

   ```
   $ mkdir dvc-storage && cd dvc-storage
   ```

2. git init

   ```
   $ git init
   ```

3. dvc init

   ```
   $ dvc init
   ```

   ```
   Initialized DVC repository.
   ```

4. save data

   data를 저장할 dir을 생성 후 그 안에 data를 save

   ```
   $ mkdir {dir_name}
   ```

   해당 dir을 dvc로 tracking

   ```
   $ dvc add {dir_name}/
   ```

   ```
   To track the changes with git, run:                                             
   
   	git add {dir_name}.dvc .gitignore
   ```

   위에서 뜬 안내메시지 실행 (git에서 version관리를 할 수 있도록 해줌)

   ```
   $ git add {dir_name}.dvc .gitignore
   ```

   

   - check

     위 명령어를 수행한 위치에 `{dir_name}.dvc` file이 생겼음을 확인할 수 있다.

     이 file은 {dir_name}안의 dataset에 대한 meta data를 가진 file이다.

     git은 바로  이 .dvc file 관리하게 된다.

5. commit

   ```
   $ git commit -m "Add test data"
   ```

6. set remote storage

   data가 실제로 저장될 remote storage를 세팅 (google drive에 저장)

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

7. git add, commit dvc config

   ```
   $ git add .dvc/config
   $ git commit -m "add remote storage"
   ```

   > 변경된 사항을 git에서 관리할 수 있도록 함

8. dvc push

   ```
   $ dvc push
   ```

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



### data download

data를 remote storage로부터 download

1. data를 받을 dir결정

   ```
   $ cd {dir_name}
   ```

   > `{dir_name}` : 위에서 git, dvc로 init된 dir

2. dvc pull

   data를 remote storage로부터 download받을 수 있는 명령어

   위의 `{dir_name}` 의 dir안의 data를 전부 지운 후 

   ```
   $ dvc pull
   ```

   을 하면 지워진 data가 google drive로부터 down받아진것을 확인할 수 있다.

   

### data checkout

1. data push

   data가 변경될 경우`dvc-storage` 의 위치의 `{dir_name}.dvc` 가 바뀌게 되는데, 이를 push

   1. git push

      ```
      $ git add data.dvc
      ```

   2. dvc push

      ```
      $ dvc push
      ```

      > git repository가 있는 사람은 git push까지

   google drive에 변경 된 `{dir_name}.dvc`가 업로드 됨 



2. data rollback

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