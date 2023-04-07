# Submodules

하나의 main repository안에서 다른 여러 repository를 포함하여 관리하는 경우 사용할 수 있다.

**ex)**

`main_module`이라는 repo와 `sub_module`이라는 repo가 있고,

`another_repo`라는 repo가 있는 상황에서



`main_module`안의 code중 `from sub_module`을 통해  sub_module의 **대부분의 기능을** import해야 하고

`another_repo`안의 code 또한 `from sub_module`을 통해  sub_module의 **부분적인 기능을** import해야 한다고 한다면,

`main_module`에 `sub_module`을 git으로 포함하되, repo는 분할하여 관리하는 것이 편리하다. 이럴 때

> `another_repo`에서는 `sub_module`을 git clone으로 불러와야 편리하고, 
>
> `main_module`에서는 `sub_module`을 포함하여 개발을 진행해야 편리하기 때문
>
> - `another_repo`에서 `main_module`을 git clone한 후 `sub_module`의 path를 명시하는 것 보다 효율적
> - `sub_module`를 pypi에 등록하여 package형식으로 관리하는 것 보다 효율적



### How to?

기존의 `main_module`의 dir map

```
.git
.gitignore
README.md
Dockerfile
main.py
```



`sub_module` 이라는 submodule 추가

```
$ git submodule add (sub_module의 repository주소)
```



이후  `main_module`의 dir map

```
.git(dir)
.gitignore
sub_module(dir)
.gitmodules
README.md
Dockerfile
main.py
```

- `.gitmodules`의 내용

  ```
  [submodule "sub_module"]
  	path = sub_module
  	url = https://github.com/username/sub_module.git
  ```

  

이제 `sub_module`은 `main_module`에 포함되지만, `main_module` dir에서 `git add`와 같은 명령어로는 `.git`에 의해 관리되지 않는다.

만일 `sub_module`에 대한 code update가 발생한다면, `sub_module`안의 `.git`에 의해 명확히 다른 repo로 분리되어 관리 받는다.



> 만일 submodule을 add했는데 dir만 추가됐고, user는 모든 code를 가져오고 싶을 때
>
>  `main_module` dir 위치에서
>
> 1. registered
>
>    ```
>    $ git submodule init {submodule 이름}
>    ```
>
>    - `submodule 이름`: `.gitmodules`안의 `[submodule "sub_module"]`에 `""` 로 명시된 이름.
>
> 2. update
>
>    ```
>    $ git submodule update
>    ```
>
>    registered 된 submodule을 전부 update한다. (현재 update된 최신 commit기준으로 가져온다.)







**update from remotes**

remote상에서 `sub_module`에 대한 code update가 있는 경우, 해당 update내용을 받아오는 두 가지 방법이 있다.

- `sub_module` dir안에서 `git pull`을 사용 (dir안으로 들어가든, vscode로 dir을 열든)

-  `main_module` dir 위치에서

  1. registered

     ```
     $ git submodule init {submodule 이름}
     ```

     - `submodule 이름`: `.gitmodules`안의 `[submodule "sub_module"]`에 `""` 로 명시된 이름.

  2. update from remote

     ```
     $ git submodule update --remote
     ```

     registered 된 submodule을 현재 update된 최신 commit기준으로 가져온다

     > 만일 submodule안에 또 다른 submodule이 있다면 `--recursive`를 추가하자.

  

  

