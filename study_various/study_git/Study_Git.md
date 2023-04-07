# Study Git



## installation

#### 1. install git 

- for windows

  https://git-scm.com/

  >  git bash는 반드시 포함해서 설치 진행

check installation

```
$ git --version
```



**setting**

- ```
  $ git config --global core.autocrlf true
  ```

  협업시 windows와 mac에서 enter방식 차이로 인한 오류를 방지

  

- ```
  $ git config --global user.name "{username}"
  $ git config --global user.email "useremail"
  ```

  이 설정은 Github계정과는 별개로, 협업시 다른 팀원들에게 보이는 정보이다.

  

- ```
  $ git config --global init.defaultBranch main
  ```

  master branch의 name을 main으로 변경

  

- ```
  $ git config --global core.editor "vim"
  ```

  git 편집 에디터 설정
  
  
  
- ```
  $ git config --global push.default current
  ```

  git push를 진행할 때 local의 branch와 같은 name의 branch가 remote상에 있다면, 해당 branch로 바로push를 진행

  > ```
  > $ git push -u origin sub-branch
  > ```
  >
  > 위 처럼 -u옵션으로 항상 명시하지 않아도 된다.

  



#### 2. install sourcetree

https://www.sourcetreeapp.com/

> github를 사용시 Bitbucket server, Bitbucket을 선택하는 한계는 건너뛰기

project의 상태를 git상에서 자세히 살펴볼 때 주로 사용함. 

git관련 명령어는 CLI환경에서 진행



#### 3. install vscode

https://code.visualstudio.com/ 



**setting**

- terminal을 git bash로 설정
  1. vs code에서 `ctrl` + `shift` + `p` 으로 설정 검색 창 open
  2. `Select Default Profile`검색
  3. Git Bash선택



## terminology

### HEAD

현재 속한 branch의 가장 최신 commit을 의미한다

`git switch` 를 사용할 때마다 각 branch의 HEAD에 위치하게 된다



## command

### for bash

리눅스의 기초 명령어와 동일

- `Ctrl + L`: 화면 초기화
- `LS`: 목록 보기
- `cat 파일이름`: 파일의 내용 보기
  - cat Git_Bash
-  `grep`: 특정 문자를 검색
  - 추후 공부할 예정
- `cd 디렉터리 이름`: 해당 디렉터리로 이동
  - `cd ..`: 상위 디렉터리로 이동
  - `cd ~`:  홈 디렉터리로 이동
- `md 이름` 또는 `mkdir 이름`:  '이름' 의 디렉터리 생성
- `rm 이름`: 파일 또는 디렉터리 삭제 (파일은 확장자까지 입력)
- `touch 파일 이름`: 파일 생성
- `vim 파일이름`: 해당 파일 내용 편집
- `start 파일이름`: 파일을 GUI 환경에서 열기
- `start .`: 현재 위치 폴더 GUI 환경에서 열기
- `Ctrl + Insert`: 복사하기
- `Shift + Insert`: 붙여넣기
- `이전에 사용한 명령어의 첫 문자 + Tap`: 이전에 사용한 명령어 자동완성

- `mv 파일이름.확장자 name`: 해당 파일을 name이라는 폴더로 이동

  

### for flow

#### init, remote, clone

- `git init`: 현재 디렉토리를 git으로 버전관리 시작하기
- `git remote add origin github_repository주소`: git으로 버전관리 되는 디렉토리에서 명령 실행 시 gib hub와 연동

  - ex) `git remote add origin https://github.com/HibernationNo1/menual-function.git`
- `git clone github_repository주소`:  

  - 로컬에서의 git init에 해당되는 명령어
  - `git remote add origin URL` 은 내가 직접 사용하는 내 계정의 URL을 관리할때 사용
  - `git clone Url` 은 남이 하는 프로젝트를 이어받거나 내가 잠시 사용할때(또는 다른 PC에서 내 URL을 사용할때) 사용 



#### status, add, commit, push

- `git status`: Working Directory 버전관리 상태 확인하기

- `git add 파일명`: Working Directory에서 Staging Area로 이동

  - `git add Study_Git_bash.md` 파일 형식도 써야함

- `git commit` : Staging Area에 있는 데이터만 Local Repository로 commit

  - 실제 사용 -> `git commit -m "커밋 내용"`

- `git reset log_id`: Staging Area에서 제외시키는 명령어

  - `git log`: 커밋을 포함한,  Remote Repository(github)로 업로드에 관한 모든 로그를 보여준다.

  > **git commit 이후 (push 이전) 해당 commit을 취소하고자 할 때**
  >
  > ```
  > $ git log
  > ```
  >
  > log를 보며 commit id를 확인한다.
  >
  > ```
  > commit 4c8b92a082c2a05d6b6ff42e03ce385b19c6c519
  > Author: HibernationNo1 <winter4958@gmail.com>
  > Date:   Sun Oct 3 20:23:04 2021 +0900
  > 
  >     add image
  >     
  > 이런식으로 나옴
  > ```
  >
  > ```
  > $ git reset --hard 4c8b92a082c2a05d6b6ff42e03ce385b19c6c519
  > ```
  >
  > add image 라는 commit이 취소됨
  >
  > 단, 바로 이전의 commit이 아닌, 더욱 이전의 commit을 취소한다면 뒤의 commit까지 전부 취소된다.

- `git push`: Local Repository에서 Remote Repository(github)로 업로드. 즉, 기본적으로 현재 분기를 추적 원격 지점으로 푸시

  -  `git push origin master`:  변경 내용을 `origin` 원격 저장소로 명시 적으로 푸시

    >rejected가 나오면 remote에 나한테 없는 정보가 있기 때문임. 
    >
    >즉,  `git pull origin master`  로 받아서 내가 push 하려 했던 정보와 합친 다음에 push해야한다.
    >
    >추가 정보 : [Study_branch](https://github.com/HibernationNo1/TIL/blob/master/study_git/Study_branch.md)
    
  -  Remote Repository(github)를 `git clone`으로 가져왔을 경우 `git push`만 해도 되지만, `git remote`로 가져왔다면 최초 `git push`는 Repository 이름과 branch명을 명시해야 한다. `git push origin master` <<이것 처럼

     > 단, `git push -u origin master` 처럼 -u 옵션을 사용한다면, 이후부터 `git push` 만 입력해도 된다.
     
  -  `git push --set-upstream origin master`: commit은 정상인데, push가 안될때 사용

- `git fetch`: Remote Repository에서 Local Repository로 파일 정보 전달

- `git merge`: Local repository에서 Working Directory로 업로드

- `git pull`: 'git fetch'와 'git merge'가 한 번에 이루어짐

  > `git pull` 을 해도 `Already up to data` 라고 뜨지만 working directory 는 안가져 올 때
  >
  > ```
  > $ git fetch --all 
  > $ git reset --hard 
  > ```

- `git restore 파일명`: 이전 변경사항 취소

  - 파일 내용을 추가했다가 해당 명령어 사용해서 잃어버린 내용은 복구 불가능
  - 가능하면 파일을 실수로 지워버렸을 때 되찾는 용도로 활용할 것

- `git --amend`: 명령어를 잘 못 입력했을 때 해당 내용을 수정 





#### reset, revert, restore

stage 또는 commit 상태의 file을 되돌리는 명령어



전제조건:

1. `exam.txt`라는 file생성

   ```
   $ vi exam.txt
   >> reset test
   >> :wq
   ```

   `git status`로 확인

   ```
   $ git status
   ```

   ```
   On branch master
   Your branch is up to date with 'origin/master'.
   
   Untracked files:
     (use "git add <file>..." to include in what will be committed)
           exam.txt
   
   nothing added to commit but untracked files present (use "git add" to track)
   ```

   > stage상태는 아님

2. add 진행

   ```
   $ git add exam.txt
   ```

   ```
   $ git status
   ```

   ```
   On branch master
   Your branch is up to date with 'origin/master'.
   
   Changes to be committed:
     (use "git restore --staged <file>..." to unstage)
           new file:   exam.txt
   ```

   > stage상태

3. commit 진행

   ```
   $ git commit -m "test commit"
   ```

   log확인

   ```
   $ git log
   ```

   ```
   commit b038eb07af80fc5685f16c05ebd8628c9e4e2a8f (HEAD -> master)
   Author: hibernation <taeuk4958@gmail.com>
   Date:   Tue Apr 4 10:22:52 2023 +0900
   
       test commit
   ```

   > hash `b038eb07af80fc5685f16c05ebd8628c9e4e2a8f`확인



```
git reset --hard b038eb07af80fc5685f16c05ebd8628c9e4e2a8f^ 에서 끝에 `^`를 붙이는 이유가 뭐지? `^`를 붙이지 않으면 명령어가 진행되지 않나?
```



**reset**

돌아가고자 하는 commit시점으로 돌아간 후, 이후의 진행됐던 commit은 삭제

- `hard`

  commit했던 변경사항 자체가 local에서 완전히 지워지게 된다. 

  ```
  $ git reset --hard b038eb07af80fc5685f16c05ebd8628c9e4e2a8f^
  ```

  > `^` 를 끝에 붙이는 이유: 
  >
  > ````
  > $ git reset --hard b038eb07af80fc5685f16c05ebd8628c9e4e2a8f
  > ````
  >
  > 를 실행하면 `b038eb07af80fc5685f16c05ebd8628c9e4e2a8f`라는 hash까지 남기고 이후의 commit은 삭제된다.
  >
  > `b038eb07af80fc5685f16c05ebd8628c9e4e2a8f`라는 hash까지 삭제하려면 `^`을 붙인다.
  >
  > `b038eb07af80fc5685f16c05ebd8628c9e4e2a8f`라는 hash의 이전 commit까지 삭제하려면 `^^`을 붙인다. (개수에 따라 조절됨)

- `mixed`

  commit했던 변경사항이 working directory(add이전)상태가 된다.

  ```
  $ git reset --mixed b038eb07af80fc5685f16c05ebd8628c9e4e2a8f^
  ```

  ```
  $ git status
  On branch master
  Your branch is up to date with 'origin/master'.
  
  Untracked files:
    (use "git add <file>..." to include in what will be committed)
          exam.txt
  
  nothing added to commit but untracked files present (use "git add" to track)
  ```

- `soft`

  commit했던 변경사항이 staging area(add이후)상태가 된다.

  ```
  $ git reset --soft b038eb07af80fc5685f16c05ebd8628c9e4e2a8f^
  ```



**revert**

- `revert`: 돌아가고자 하는 commit시점부터 지금까지 진행 된 commit을 거꾸로 다시 commit해가며 돌아가는 것.

  되돌리고자 하는 commit만 변경하고, 그 외의 commit은 유지할 수 있기 때문에 협업에서 사용된다.

  1. log를 확인해서 hash값 확보

     ```
     $ git log
     ```

     ```
     commit 099a1ad904851ee4777d1ab23a452ec1fd51ef17
     ...
     
     ```

  2. git revert

     ```
     $ git revert 099a1ad904851ee4777d1ab23a452ec1fd51ef17
     ```

     해당 commit의 변경점만 취소하는(변경되기 전으로 되돌리는) commit이 한 개 추가된다.

     만일 해당 commit의 변경점을 취소하는 과정에서 이후 commit과의 관계성(연계된 code라던가)때문에 수동적으로 결정해야 하는 부분이 있다면 `REVERING`상태로 진입하게 된다.

  3. REVERING

     REVERING과정에서 `git add`, `git rm` 등으로 변경부분을 성공적으로 fix했다면 `git revert --continue`를 통해 REVERING상태를 종료하고 revert를 완교한다.

     ```
     $ git revert --continue
     >> wq (저장)
     ```




**restore**

staging상태를 working diretory상태로 되돌린다. (변경 사항을 되돌리는것이 아님)

```
$ git restore --staged {file_name}
```

> `file_name`은 staging상태여야 함



또는 working diretory상태에서 변경사항이 없던 상태로 (변경사항이 전부 사라지는)되돌린다.

```
$ git restore {file_name}
```





#### push, pull

항상 무언가를 push하기 전에는 pull을 먼저 해서 최신 commit을 가져오거나, 비교해야 한다.

push할 것이 있을 시 pull하는 두 가지 방법

1. merge방식

   ```
   $ git pull --no-rebase
   ```

   local의 main branch와 원격 상의 main branch를 다른 branch로 인식한 후, 원격의 main branch를 local의 main branch에 merge하는 방식이다.

   

2. rebase방식

   ```
   $ git pull --rebase
   ```

   원격 상의 main branch의 최종 commit뒤에, local의 main branch의 진행된 commit을 이어서 붙인다.

   > 협업시 사용

이후에 push진행

```
$ git push
```



+ 원격상의 branch가 잘못되어 local의 branch로 강제로 맞춰야 할 경우

  ```
  git push --force
  ```

  > 협업시에는 사용하지 말자



- local에는 sub branch가 있지만, 원격에는 sub branch가 없는 경우 push를 하게 되면

  ```
  $ git switch -c sub-branch
  $ git push
  ```

  fatal과 함께 `use  git push --set-upstream origin sub-branch` 이라는 메시지가 출력된다.

  > `origin`이라는 원격에  `sub-branch`라는 branch를 명시 해서 push하라는 의미

  이런 경우 명확히 branch를 명시해서 push해 주어야 한다.

  ```
  $ git push -u origin sub-branch
  ```

  > - `-u` : `--set-upstream`의 축약문구



#### fetch

remote에서 어떠한 변경점이 있는 경우, local에서 `fetch`를 진행하면 현재 branch의 HEAD에서 가상의 branch를 만든 후 remote branch로부터 가져온다. (단 merge 또는 rebase하지 않는다.)

때문에 `fetch`는 pull(merge, rebase하기 전)하기 전에 remote상의 변경점과 local상의 변경점을 비교하여 살펴보는 용도로 사용된다.

1. `git fetch`

   변경점이 있다면 commit msg와 hash를 확인할 수 있다.

   ```
   $ git fetch
   ```

   ```
   8294dff..8d28c85 main 		-> origin/main
   ```

   - `8294dff..8d28c85` : commit의 hash값

   - `origin/main`: remote name/ branch name

     여기서 가상의 branch는 따로 이름이 있는것이 아니라 `origin/main`으로 명시된다.

2. git checkout

   `fetch`로 만들어진 가상의 branch로 이동하여 변경점 확인

   ```
   $ git checkout origin/main
   ```

   변경점 확인 후 다시 local의 main branch로 회귀

   ```
   $ git switch main
   ```

3. git pull

   merge해도 괜찮겠다 판단되면 merge 진행

   ```
   $ git pull
   ```

   





#### error

**warning: CRLF will be replaced by LF in some/file.file.**

터미널에 `git add` 를 입력했는데 다음과 같은 에러가 뜨는 경우가 있다.

```
warning: CRLF will be replaced by LF in some/file.file.
The file will have its original line endings in your working directory.
```

이는 맥 또는 리눅스를 쓰는 개발자와 윈도우 쓰는 개발자가 Git으로 협업할 때 발생하는 **Whitespace** 에러다. 유닉스 시스템에서는 한 줄의 끝이 **LF(Line Feed)**로 이루어지는 반면, 윈도우에서는 줄 하나가 **CR(Carriage Return)**와 **LF(Line Feed)**, 즉 **CRLF**로 이루어지기 때문이다. 따라서 어느 한 쪽을 선택할지 Git에게 혼란이 온 것이다.

유닉스 OS을 쓰고 있다면 `CRLF will be replaced by LF in…` 에러 메시지가 뜰 것이고, 윈도우를 사용하고 있다면 `LF will be replaced by CRLF in…` 에러 메시지가 뜰 것이다.

해답은 `core.autocrlf` 를 켜는 것!

> 둘 중 뭐든간에 해결 방법은 같다. Git은 똑똑해서 이를 자동 변환해주는 `core.autocrlf` 라는 기능을 가지고 있는데, 이 기능을 켜주기만 하면 된다.
>
> 이 기능은 개발자가 git에 코드를 추가했을 때 (예컨대 커밋할 때)에는 CRLF를 LF로 변환해주고, git의 코드를 개발자가 조회할 때 (예컨대 clone한다거나 할 때)에는 LF를 CRLF로 변환해준다.

그러므로 **윈도우 사용자**의 경우 이러한 변환이 항상 실행되도록 다음과 같은 명령어를 입력한다. 물론 시스템 전체가 아닌 해당 프로젝트에만 적용하고 싶다면 `—global` 을 빼주면 된다.

```
git config --global core.autocrlf true
```

**리눅스나 맥을 사용**하고 있는 경우, 조회할 때 LF를 CRLF를 변환하는 것은 원하지 않을 것이다. 따라서 뒤에 `input`이라는 명령어를 추가해줌으로써 단방향으로만 변환이 이루어지도록 설정한다.

```
git config --global core.autocrlf true input
```

혹은 이러한 변환 기능을 원하지 않고, 그냥 **에러 메시지 끄고 알아서 작업하고 싶은 경우**에는 아래 명령어로 경고메시지 기능인 `core.safecrlf`를 꺼주면 된다.

```
git config --global core.safecrlf false
```



**remote: Support for password authentication was removed on August**

git push과정에서 

```
Username for 'https://github.com': HibernationNo1
Password for 'https://HibernationNo1@github.com':
```

password입력 시 아래와 같은 메시지를 만날 경우

```
remote: Support for password authentication was removed on August 13, 2021.
```

개인 access key가 만료되었다는 뜻

github계정에서 setting > 좌측 하단  Developer settings > Personal access tokens

Note : access key의 이름

발급시 `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` 와 같은 key(Password)를 받을 수 있다.



만일 이미 clone된 repository에 새로 발급한 personal-access-token을 적용하고 싶다면 아래 명령어

```
git remote set-url origin https://<your-username>:<your-personal-access-token>@github.com/<your-username>/<your-repo>.git
```

