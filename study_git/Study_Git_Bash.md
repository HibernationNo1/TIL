### Git Bash 명령어 정리

#### 1. 기본적인 명령어

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

#### 2. 깃 커밋 명령어

- `git init`: 현재 디렉토리를 git으로 버전관리 시작하기

- `git remote add origin github_repository주소`: git으로 버전관리 되는 디렉토리에서 명령 실행 시 gib hub와 연동

  - ex) `git remote add origin https://github.com/HibernationNo1/TIL.git`

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

- `git push`: Local Repository에서 Remote Repository(github)로 업로드. 즉, 기본적으로 현재 분기를 추적 원격 지점으로 푸시

  -  `git push origin master`:  변경 내용을 `origin` 원격 저장소로 명시 적으로 푸시

    >rejected가 나오면 remote에 나한테 없는 정보가 있기 때문임. 
    >
    >즉,  `git pull origin master`  로 받아서 내가 push 하려 했던 정보와 합친 다음에 push해야한다.
    >
    >추가 정보 : [Study_branch](https://github.com/HibernationNo1/TIL/blob/master/study_git/Study_branch.md)

- `git fetch`: Remote Repository에서 Local Repository로 파일 정보 전달

- `git merge`: Local repository에서 Working Directory로 업로드

- `git pull`: 'git fetch'와 'git merge'가 한 번에 이루어짐

  

- `git restore 파일명`: 이전 변경사항 취소
  
  - 파일 내용을 추가했다가 해당 명령어 사용해서 잃어버린 내용은 복구 불가능
  - 가능하면 파일을 실수로 지워버렸을 때 되찾는 용도로 활용할 것
  
- `git --amend`: 명령어를 잘 못 입력했을 때 해당 내용을 수정 



#####  git init 이전에 `git touch .gitignore` 을 통해 내 프로젝트의 최 상단 repository에 gitignore 파일을 만든다.  (사실 순서는 크게 상관없음)

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

3. git init => add => commit...





######  summary

> 해당 파일은 아래 정보를 정리한 파일임
>
> - git bash 명령어 
>
> - 처음 프로젝트 시작할 때 tip

