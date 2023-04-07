# branch 활용 방법

###  branch 기본 명령어

`git branch, git branch --list` : 현재 repository의 branch 목록을 확인할 수 있다.

`git branch name` : name 이라는 branch  생성.

`git switch name` : HEAD가 name이라는 branch로 이동

`git switch -c name`: name 이라는 branch  생성 후 해당 branch로 이동

`git checkout name`:  git switch name 와 같다.

`git checkout '특정 commit의 해쉬번호'`: 특정 commit 된 지점으로 HEAD 이동

`git push / pull origin name`: name 이라는 branch를 remote에 push한다. (remote 와 merge한다.)

`git push origin  master`: name 이라는 branch를 master branch와 merge한다.  // 협업에서는 하지 말 것.

`git merge name`: name이라는 branch를 master branch에 합친다.

`git branch -d name`:  name이라는 branch를  지움

`git branch -D name`:  name이라는 branch를  강제로 지움

`git log`: 현재 존재하는 branch와 commit의 상태를 보여줌

` git log --pretty=format:"%h %s" --graph`: git log를 깔끔하게 보여줌



#### +

- `git log --all --decorate --oneline --gragh` : 모든 banch의 log를 확인하는 명령어



### banch 병합

#### merge branch 

merge할 branch와 main branch의 모든 내용을 적용한다.



main branch에 exam이라는 sub branch를 merge할 경우

```
$ git merge exam
```



**충돌시**

같은 파일에 다른 내용이 입력되는 경우 branch간 병합 시 충돌이 일어나게 된다.

이 때 `Automatic merge failed;`라는 문구와 함께 `MEARGING`상태로 돌입하게 되며, 각 변경된 부분마다 vscode로 확인하면 아래 4개의 선택을 할 수 있다.

- `Accept Cureent Change`
- `Accept Incomming Chagne`
- `Accept Both Changes`
- `Compare Change` 



>merge가 안되겠다 하는 경우: merge를 중단하는 경우
>
>```
>$ git merge --abort
>```



#### rebase branch

rebase할 branch의 commit들을 main branch의 최신 commit뒤에 이어 붙인다. 

단, branch에 대한 history를 남기지 않는다.(모든 history가 main에 추가되게 된다.)



main branch에 exam이라는 sub branch를 rebase할 경우

```
```





**충돌시**

rebase 할 branch의 **commit 하나 하나**마다 merge형태로 조치를 취해줘야 한다.

rebase 할 branch의 commit이 3번이 있었다고 한다면

- 각 변경된 부분마다 vscode로 확인하면 아래 4개의 선택을 할 수 있다. 

  - `Accept Cureent Change`
  - `Accept Incomming Chagne`
  - `Accept Both Changes`
  - `Compare Change` 

  이후 

  ```
  $ git add .		
  $ git rebase --continue
  >> wq
  ```

  > `git add` 까지만 진행, commit까지는 진행하지 않고 `git rebase --continue`를 실행해야 한다.

위와 같은 동작을 각 commit마다 진행

이후

```
$ git switch main
$ git merge exam
```





> rebase가 안되겠다 하는 경우: rebase를 중단하는 경우
>
> ```
> $ git rebase --abort
> ```





### remote branch관리

remote branch확인하는 명령어

1. 원격에서 remote상에 존재하는 branch를 추적하는 정보를 최신화

   ```
   $ git fetch --prune origin
   ```

2. remote상의 branch확인

   ```
   $ git branch -r
   ```

3. local과 remote상의 branch비교

   ```
   $ git branch -a
   ```

   





- remote 에는 있지만 local에는 없는 `remote-branch`라는 branch가 있는 경우

  remote의 branch를 local로 받아온다.

  ```
  $ git swith -t origin/remote-branch
  ```

  이후 pull까지 진행해본다면

  ```
  $ git swith remote-branch
  $ git pull
  ```

  

- local에는 있지만 remote에는 없는 `local-branch`라는 branch가 있는 경우

  - local의 branch를 remote에도 올리는 경우

    local의 branch에서 commit후 push를 할 때 `--set-upstream`으로 local의 branch명 명시
  
    ```
    $ git push -u origin local-branch
    ```
  
    > - `-u` : `--set-upstream`의 축약문구
  
  - remote에서 삭제된 것 처럼 local에도 branch를 삭제하려는 경우
  
    변경사항이 반영 되었다면 local에서 그냥 삭제해도 안전하다
  
    

- local에서 삭제한 branch는 remote에서도 삭제를 해야 한다.

  1. local에서 삭제

     ```
     $ git branch -d local-branch 
     ```

  2. remote에서도 삭제

     ```
     $ git push origin --delete local-branch
     ```

     

  

- **항상 remote에서 새 변경점이 있는지 확인하도록 한다.**

  1. 변경점 사전 확인

     ```
     $ git fetch
     ```

  2. local과 remote상의 branch비교

     ```
     $ git branch -a
     ```

  3. 변경점이 있다면 해당 branch로 이동 후 확인

     ```
     $ git checkout remote_name/branch_name
     ```

  4. 다시 local branch로 이동

     ```
     $ git switch local_branch_name
     ```

  5. 경우의 수에 따라 다른 동작

     - remote에 새로운 branch가 있는 경우: local에도 해당 branch가져오기

       ```
       $ git switch -t remote_name/new_branch_name
       ```

     - local에 있는 branch가 remote에 존재하는 경우: remote에 해당 branch삭제

       ```
       $ git push remote_name --delete local-branch
       ```

        





### HEAD운용

**`git switch`**

branch간 이동을 할 때 사용

git swith를 통해 branch간 이동 시 해당 branch의 최신 commit상태로 이동하게 되고, 그 자리가 HEAD의 위치다.



예시

```
$ git switch exam-1
```

`exam-1` 이라는 branch의 최신 commit으로 이동





**`git checkout`**

1개의 branch내에서 특정 commit으로 HEAD를 이동할 때 사용. (HEAD만 이동하기 때문에 commit의 history에는 변경이 없다.)

이 때 해당 branch내의 특정 commit에 임의의 branch를 만들어 최신 commit의 위치로 결정하고(HEAD의 정의처럼) 위치하게 된다. 때문에 해당 HEAD의 위치에서 새로운 commit을 진행하면 임의의 branch에 새 commit이 생기게 된다.



예시

- 현재 HEAD의 이전 commit으로 이동 

  ```
  $ git checkout HEAD^
  ```

  현재 HEAD의 두 번 전의 commit으로 이동

  ```
  $ git checkout HEAD^^
  ```

  

- 바로 이전의 HEAD의 위치로 이동

  ```
  $ git checkout -
  ```

   `git checkout -`은 이전 HEAD의 위치로 이동한는 것 외에는 동작하지 못한다. 

  때문에 특정 branch로 이동하고자 하면 `git switch`를 사용해야 한다.

  

- `git checkout` 으로 만들어진 임의의 branch에서 다른 branch로 이동할 때

  ```
  $ git switch branch-name
  ```

  







### example

#### case 1

branch만들고 이름 바꾸기

1. `exam-1`이라는 branch 추가

   ```
   $ git branch exam-1
   ```

2. 해당 branch로 이동

   ```
   $ git switch exam-1
   ```

   > ```
   > $ git switch -c exam-2
   > ```
   >
   > `exam-2`라는 branch를 새로 만들고 HEAD를 `exam-2`로 이동

3. branch 이름 바꾸기

   ```
   $ git branch -m exam-1 exam-2
   ```

   `exam-1`이라는 이름에서 `exam-2`로 이름 변경





#### case 2

두 개의 branch만들고 각각의 commit후 병합하기(**충돌 없음**)

1. branch 추가: `exam-1`

   ```
   $ git switch -c exam-1
   $ git add .
   $ git commut -m "exam-1 first commit"
   $ git switch main
   ```

2. branch 추가: `exam-2`

   ```
   $ git switch -c exam-2
   $ git add .
   $ git commut -m "exam-2 first commit"
   $ git switch main
   ```

3. branch `exam-1`을 main에 merge

   main branch에서 merge명령어 실행

   ```
   $ git merge exam-1
   ```

   > 병합된 branch를 삭제할 경우
   >
   > ```
   > $ git branch -d exam-1
   > ```

4. branch `exam-2`를 main에 rebase

   `exam-2`에서 rebase명령어 실행

   ```
   $ git swith exam-2
   $ git rebase main
   ```

   이후 main으로 이동하면 rebase되기 전 commit으로 이동하게 된다.

   ```
   $ git swith main
   ```

    merge까지 진행을 해 주어야 완전한 rebase가 진행되는 것

   ```
   $ git merge exam-2
   ```

   





