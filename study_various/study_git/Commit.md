# commit

### type

commit시 type명시

- `feat`: 새로운 기능 추가
- `fix`: 버그 수정
- `docs` : 문서 수정
- `style`: 공백, 세미콜론 등 스타일 수정
- `refactor`: 코드 리팩토링
- `perf`: 성능 개선
- `test` : test추가
- `chore`: 빌드 과정 또는 보조 기능(문서 생성기능 등) 수정

ex)

```
feat: add eveluation
```



더 자세한 commit설명이 필요한 경우 commit message작성 mode활성화

```
$ git commit 
```

> `git commit -m "commit msg"`를 사용하는 것 보다 더 직접적으로, 자세하게 적을 수 있다.

ex)

```
feat: add eveluation
# 한 칸 띄고
add compute rule as custom 
- divide slice iou
- mAP calculation implementation
...
# 한 칸 띄고

>>: wq
```



- ```
  $ git commit -v
  ```

  commit message작성 mode활성화 시 변경사항까지 확인이 가능하다.



### hunk

`git add`를 사용할 때 하나의 file안에서도 부분마다 따로따로 적용할 수 있다.

하나의 문서당 하나의 변경 부분마다 hunk로 칭하며, 이를 하나하나 확인하면 staging할 수 있다.

```
$ git add -p
```

> hunk별로 탐색 mode시작

- `y`: stage this hunk
- `n`: do not stage this huck
- `q`: quit



1. 만일 하나의 파일에 변경점 중 부분적으로만 add를 하고 `git status`로 확인을 하면, 하나의 file이 staging되었고 동시에 staging되지 않았다는 상태를 확인할 수 있다.
2. 만일 file의 생성 후  첫 add라면 `-p`옵션 사용이 불가능하다.(파일 자체를 add해야 한다.)





## stash

- 기존 작업을 하는 도중 급하게 작은 `fix`요청이 들어왔을 때, 그리고 하던 작업을 commit하기엔 애매할 때 가상의 공간에 치워두고 급한 용무보토 볼 때 사용하는 기능

- commit하기 애매한 변화를 잠시 git의 가상 공간에 저장하는 기능 



1. 변경 사항이 있는 경우 add

   stash는 staging된 사항에 대해서만 적용된다.

   ```
   $ git add sum_file.py
   ```

2. stash

   ```
   $ git stash
   ```

   staging상태의 변경 부분을 stash라는 git의 어느 한 공간에 보관

   이는 source tree에서 확인이 가능하다.

3. stash list

   `list`: stash에 보관된 list를 확인할 수 있다.

   ```
   $ git stash list
   ```

   ```
   stash@{0}: ...
   stash@{1}: ...
   ```

   stash에 대한 number를 확인할 수 있다. 

4. apply

   ```
   $ git stash apply stash@{0}
   ```

   `stash@{0}`에 보관된 staging내용을 가져올 수 있다.

   > 이는 A라는 branch에서 stash를 실행했어도, B라는 branch에서 그대로 가져올 수 있다.

   - pop

     바로이전에 stash에 넣어두었던 staging내용을 가져온다.

     ```
     $ git stash pop
     ```

     > `stash drop`도 함께 동작하게 된다.

5. drop

   ```
   $ git stash grop stash@{0}
   ```

   list에서 특정 stash를 지운다.



또는

```
$ git stash branch exam-branch
```

exam-branch라는 branch를 만들고, staging된 내용을 해당 branch에 apply한 후 drop까지 완료한다.

왜? stash를 한 내용 중 이후 apply를 했을 때 충돌이 일어날 수 있다고 판단되는 경우 새 branch를 생성해서 그곳에 옮겨 담아놓는다.  





**options**

- `-p`: add의 patch기능과 같이, 하나의 file에서 원하는 부분에 stash에 보관이 가능하다.

  ```
  $ git stash -p
  ```

- `-m`: stash에 대한 message를 남길 수 있다.

  ```
  $ git stash -m "msg"
  ```

  



## edit commit

### amend

- 바로 직전에 commit했던 message를 수정할 수 있다.

  ```
  $ git command --amend
  ```

  commit msg를 수정할 수 있는 editer가 열리게 된다.

  - 만일 이전 commit msg가 한 줄(title)로만 이루어져 있다면 아래 한 줄 명령으로 가능

    ```
    $ git commit --amend -m 'fix commit msg'
    ```

    

- 바로 직전의 commit에 변경 사항을 추가할 수 있다.

  1. 추가 할 변경사항을 staging에 추가

     ```
     $ git add .
     ```

  2. 마지막 commit에 해당 내용 추가

     ```
     $ git commit --amend
     ```

     

  



### rebase

과거 commit내역을 다양한 방법으로 수정할 때 사용할 수 있다.

```
$ git rebase -i {수정하고자 하는 commit의 바로 이전 commit의 hash}
```

위 명령어를 입력하면 아래와 같은 editer화면이 실행된다.

```
pick 1c788ad commit msg 1		# 수정하고자 하는 commit
pick ff00ad9 commit msg 2
pick slfm442 commit msg 3
pick 59b43f3 commit msg 4		# 가장 최근에 했던 commit

# Rebase ...
...
```

- `pick`: commit 수정 mode 선택 창(기본적으로 pick으로 선택되어 있는 것임)

  commit 수정 mode의 type

  - `pick`: commit그대로 두기
  - `reword`: commit의 message만 변경
  - `edit`: commit의 수정을 위해 정지
  - `drop`: commit 삭제
  - `squash` : 이전 commit에 합침

- `1c788ad` : 해당 commit의 hash값 앞 6자리

- `commit msg 3` : 해당 commit의 message



특정 commit의 mode를 수정했을 때(mode의 type을 수정 후 `:wq`입력 시 동작)

- `pick` : 그대로 둔다.

- `reword` : commit mssage를 수정하는 editer가 실행된다.

- `drop` : 해당 commit이 삭제된다.

- `squash`: 두 commit을 하나로 합치는 editer가 실행된다.

  ex) `slfm442`의 mode를 `squash`로 변경했을 경우

  ```
  ...
  # This is the 1st commit message:
  
  commit msg 3
  
  # This is the 1st commit message #2:
  
  commit msg 4
  
  ...
  ```

  위를 아래처럼 바꾼다.

  ```
  ...
  # This is the 1st commit message:
  
  commit msg 3 - squash
  
  # This is the 1st commit message #2:
  
  ...
  ```

  이렇게 하면 `slfm442`의 commit message가 `commit msg 3 - squash`으로 바뀌게 되고, 두 commit은 합쳐진다.

- `edit`: 해당 commit이 이루어진 시점으로 이동하게 된다.

  이후 

  1. reset을 통해 commit을 되돌린다

     ```
     $ git reset --mixed HEAD^
     ```

     `--mixed` option을 사용해 working diretory상태(unstaging상태)로 돌려놓는다.

  2. 변경 사항을 적용하고 git add, commit을 실행한다

     이 과정에서 1개였던 commit이 필요시 두개, 그 이상이 될 수도 있다.

  3. 모든 edit사항이 끝난 경우

     ```
     $ git rebase --continue
     ```

  > 어떻게 이것이 가능한가?
  >
  > 수정하고자 하는 commit에서 임의의 새 branch를 만들고, 수정사항이 있는 해당 commit 이후의 모든 commit에 수정사항이 반영되게 하여 commit이 자동으로 이루어지게 한다.
  >
  > 이후 rebase의 동작을 통해 기존에 있던 branch에 이어 붙여지게 되는 것이다.





### restore

원래는 staging상태를 working directory상태로 되돌리거나, working directory상태를 변경사항 이전의 상태로 되돌리는데 사용되지만

특정 file을 commit의 변경 없이 과거의 특정 commit상태로 되돌릴때 사용할 수도 있다.

```
$ git restore --source={hash of commit} {filename}
```

`file name`의 내용을 `hash of commit`이라는 hash의 commit일 당시의 상태로 되돌린다.

다시 현재 commit상태로 되돌리려면

```
$ git restore .
```





### reflog

git으로 입력한 모든 명령어의 log를 확인할 수 있다. (내가 사용한 git 명령어 기준)



reset으로 인해 지워버린 commit을 복구할때도 사용할 수 있다.

ex)

```
$ git reflog
```

```
2bce4f7 (HEAD -> main) HEAD@{0}: reset: moving to HEAD~2
...
```

- `2bce4f7`: 해당 명령어에 대한 hash값
- `reset: moving to HEAD~2` : 해당 명령어와, 그로인해 진행된 동작 

여기서 해당 명령어 자체를 reset으로 지워버리면(reset했던 명령을 지워버리면) 다시 복구가 되는 원리이다.

```
$ git reset --hard 2bce4f7
```





## tag

commit에 tag달기

- 특정 시점을 kward로 저장하고 싶을 때

- commit에 대한 version 정보를 붙이고자 할 때

  main branch의 주 point가 되는 시점에 tag를 달아서 표시하는 등





1. 마지막 commit에 tag를 다는 경우

   ```
   $ git tag v0.0.1
   ```

2. 현존하는 tag확인

   ```
   $ git tag
   ```

3. 특정 tag가 달린 commit에 어떤 변화가 있었는지 확인

   ```
   $ git show v0.0.1
   ```

4. tag삭제

   ```
   $ git tag -d v0.0.1
   ```



**+**

- tag에도 annation정보(message)를 추가할 수 있다.

  ```
  $ git tag v0.0.2 -m "update ann dataset:board"
  ```

- 원하는 commit에 tag를 달 수 있다.

  ```
  $ git tag v0.0.3 {hash of commit} -m "message"
  ```

- 원하는 tag의 commit으로 checkout

  ```
  $ git checkout v0.0.2
  ```

  

**tag on remotes**

- push

  local에서 달았던 tag를 remotes환경에 올리기

  ```
  $ git push {name of remote} {name of tag}
  ```

  - local의 모든 tag를 한번에 올릴 때

    ```
    $ git push --tags
    ```




- clone

  ```
  $ git clone -b {tag} {git URL}
  ```

  

  

- delete

  특정 tag를 remote에서 삭제

  ```
  $ git push --delete {name of remote} {name of tag}
  ```



**releases**

직접 dowload를 할 때 특정 tag를 target으로 할 수 있도록 하는 기능

remote상에서 repository의 tags클릭 > 각 tag의 우측에 위치한 `...` 클릭 > `Create release` 클릭 > 제목과 내용(markdown형식)으로 작성