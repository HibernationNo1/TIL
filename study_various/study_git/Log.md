# Git log

여러 가지 방법으로 git의 수행 과정을 확인하는 방법



## log

log를 보는 기본적인 명령어

```
$ git log
```



**options**

- `-p`

  ```
  $ git log -p
  ```

  각 commit마다 변경사항 보기

  

- `-{갯수}`

  ```
  $ git log -3
  ```

  최근 log 3개만 보기

  

- `--stat`

  ```
  $ git log --stat 
  ```

  통계와 함께 보기

  

- `--oneline`

  ```
  $ git log --oneline
  ```

   log 한 출로 보기

  

- `--all`

  ```
  $ git log --all 
  ```

  모든 branch에 대한 commit log확인

  

- `--decorate`

  ```
  $ git log --decorate
  ```

  branch, tag등 모든 reference표시





**search**

- `-S {검색어}`

  ```
  $ git log -S python
  ```

  변경사항 내 내용 중 `python`가 포함된 log출력

  

- `-grep`

  ```
  $ git log -grep fix
  ```

  commit msg중에 `fix`라는 단어가 포함된 log출력

  

**자주 사용되는 조합**

- ```
  $ git log --all --decorate --oneline --graph
  ```

  - `--all`: 모든 branch에 대해서 보기
  - `--graph` : graph로 표현

  > 이것보다 source tree로 보는 것이 더 눈이 편하다



## diff

working diretory의 변경사항을 확인하는데 사용된다. (add로 staging으로 올리기 전 상태의 변경사항)

```
$ git diff
```



**options**

- `--name-only`

  ```
  $ git diff --name-only
  ```

  변경된 file명만 확인

  

- `--staged`

  ```
  $ git diff --staged
  ```

  `git add`로 인해 staging된 변경사항을 확인할 수 있다.



**commit간의 변경사항 차이 확인**

```
$ git diff {commit hash_1} {commit hash_2}
```

commit hash 또는 HEAD번호로 commit구분

> commit hash를 1개만 입력하면 현재 커밋과의 내용 비교가 진행된다.

- HEAD로 구분할 때

  ```
  $ git diff HEAD~~  HEAD~3
  ```

  지금 HEAD의 두 번째 전 commit과 세 번째 전 commit을 비교





**branch간의 변경사항 차이 확인**

```
$ git diff {name of branch_1} {name of branch_2}
```





## blame

git commit 수행자 확인

```
$ git blame {파일명}
```

line별로 누가 작성했는지 확인할 수 있다.



특정 부분 지정해서 작성자 확인

```
$ git blame -L {시작 line} {끝 line 또는 `시작 line+줄 수`} {파일 명}
```



**각 line별로 바로바로 확인하는 가장 쉬운 방법**: vscode에서 확장 프로그램 `gitlens`를 설치한다.