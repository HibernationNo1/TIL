# Git Bash 명령어 정리

### 1. 기본적인 명령어

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
- 

### 2. 깃 커밋 명령어

- `git init`: 현재 디렉토리를 git으로 버전관리 시작하기

- `git remote add origin github_repository주소`: git으로 버전관리 되는 디렉토리에서 명령 실행 시 gib hub와 연동

  - ex) `git remote add origin https://github.com/HibernationNo1/menual-function.git`

- `git clone github_repository주소`:  
  
  - 로컬에서의 git init에 해당되는 명령어
  - `git remote add origin URL` 은 내가 직접 사용하는 내 계정의 URL을 관리할때 사용
  - `git clone Url` 은 남이 하는 프로젝트를 이어받거나 내가 잠시 사용할때(또는 다른 PC에서 내 URL을 사용할때) 사용 
  
- `git status`: Working Directory 버전관리 상태 확인하기

- `git add 파일명`: Working Directory에서 Staging Area로 이동

  - `git add Study_Git_bash.md` 파일 형식도 써야함

- `git commit` : Staging Area에 있는 데이터만 Local Repository로 commit

  - 실제 사용 -> `git commit -m "커밋 내용"`
- `git reset 파일명`: Staging Area에서 제외시키는 명령어
  - `git log`: 커밋을 포함한,  Remote Repository(github)로 업로드에 관한 모든 로그를 보여준다.

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

  

- `git restore 파일명`: 이전 변경사항 취소
  
  - 파일 내용을 추가했다가 해당 명령어 사용해서 잃어버린 내용은 복구 불가능
  - 가능하면 파일을 실수로 지워버렸을 때 되찾는 용도로 활용할 것
  
- `git --amend`: 명령어를 잘 못 입력했을 때 해당 내용을 수정 



git init 이전에 `touch .gitignore` 을 통해 내 프로젝트의 최 상단 repository에 gitignore 파일을 만든다.  (사실 순서는 크게 상관없음)

> 이 파일 안에 '파일이름.확장자' 또는  '폴더명/'를 입력하면 git add 에서 제외돼서 git 버전관리에서 제외된다.
>
> gitignore 파일 안에 어떤 파일을 포함시켜야 할까?
>
> >[gitignore](https://gitignore.io)  해당 링크로 가서   // 링크 원본 https://gitignore.io
> >
> >검색창에 내가 쓰는 프로그램들 다 태크한 후 검색해서 나온 모든 파일명을 .gitignore 파일 안에 붙여넣자.

#####  project 생성할 때 순서

1. touch .gitignore
2. touch README.md

3. git init => remote =>  add => commit...



### 3. 깃 추가 내용

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