# git flow

## Introduce

git flow를 이용해 만들 수 있는 branch는 6종류가 있다.

1. master
2. develop
3. feature 
4. release
5. hotfix 
6. support



- main branch : 프로젝트가 끝날 때 까지 항상 유지되는 branch

  - master : 제품으로 출시(Launching)할 수 있는 branch

    > branch name은 master/v 0.0.0 이런 식

  - develop: 개발 brach. 여기서 feature, release가 분기되고 병합된다.

    > branch name은 develop/v 0.0.0 이런 식

- sub branch : 필요할때만 사용되고 소멸되는 branch

  - feature : develop로 부터 분기되어 개별 기능을 개발하는 branch. 기능이 완료되면 다시 develop으로 병합된다.

    > branch name은 feature - ~~~ 또는 feature/ 이런 식

  - release: 여러 버그가 고쳐지거나 기능에 변경이 생겼을 때, README가 변경되었을 때 사용

    > branch name은 release/ v 0.0.0 이런 식

  - hotfix : 출시전 version에서 발생한 bug를 fix하는 branch로, 유일하게 mastger에서 분기된다. (또는 긴급 bug를 fix하기 위해서 주로 사용)

    > branch name은 hofix/v 0.0.0 이런 식

  - support : 버전 호환성 문제를 처리하기 위한 branch



### model 구성

![](https://media.vlpt.us/images/cos/post/57fa6718-f327-4ae8-b789-26259632e4fe/Simplified-version-of-the-gitflow-branching-model-adapted-from-8.png)



### GitKraken

1. develop 에서 feature 만든 후 code 변경. 

2. 변경된 code를 up stage한 후 commit

3. finish feature (변경사항)

4. develop 에서 release 만든 후 주석 변경.  

   > 각 release는  feature개당 1개씩
   >
   > finish feature (변경사항) 이후에 release해야함

5. 변경된 주석을 up stage한 후 commit

6. finish release (v 0.0.0)

   >  release 만든 후 바로 변경사항 없이 finish release 해도 됨

7. master에서 push

   > finish release 안하면 develop에서 master로 marge가 안됨

같은 파일의 내용에 대해서 각각의 feature 또는 release를 진행하면, 변경된 두 경우 중 어떤 경우를 marge할건지 물어본다. 그렇기 때문에 가능하면 각 branch마다 다른 file에 대해서 개발하자.



## Getting Started

#### Install

- Linux

  ```
  $ apt-get install git-flow
  ```

  

#### initialize

기존 git repository에서 초기화 하는 것으로 git-flow의 사용을 시작 할 수 있다.

```
$ git flow init -d
```

> `git flow init` 을 실행하면 process별로 사용할 branch의 name을 결정하라고 한다. `-d` option으로 default로 가자



### Feature

**start**

develop branch에서 feature branch가 하나 만들어지며 자동으로 해당 branch로 checkout된다.

```
$ git flow feature start {branch name}
```



**finish**

작업이 완료된다면 feature finish

```
$ git flow feature finish {branch name}
```

> feature finish가 실행되면 자동으로 develop branch로 checkout한 후 
>
> feature branch의 변경 내용을 develop branch에 merge하고
>
> 작업이 긑난 feature branch를 삭제한다.



**publish**

해당 feature branch를 여러 개발자와 공동으로 개발하고 싶다면 원격 서버에 게시하면 된다.

```
$ git flow feature publish {branch name}
```



**delete without merge**

```
$ git branch -D {branch name}
```



### Release

**start**

develop branch의 내용을 기반으로 release branch가 하나 만들어지며 자동으로 해당 branch로 checkout된다.

```
$ git flow release start {version}
```



**finish**

release 를 위한 점검이 끝나면 finish를 한다.

```
$ git flow release finish {version}
```

> release finish 명령이 실행되면 release branch 의 변경사항을 master branch에 merge한 후 
>
> release의 이름으로 tag를 등록, 
>
> release의 변경 사항을 develop branch로 재병한 후 release branch를 삭제한다.



### example

- 항상 `git branch`와 `git log`(`git log --pretty=format:"%h %s" --graph`) 를 통해 현재 위치와 log를 확인하고 `git switch`를 활용하자.

1. feature start

   ```
   $ git flow feature start {branch name}
   ```

2. code 작업 후 commit

   ```
   $ git add {file name.type}
   $ git commit -m "commit title"
   $ git push origin feature/{branch name}
   ```

3. feature finish

   ```
   $ git flow feature finish {code}
   ```

4. release start

   ```
   $ git flow release start {version}
   ```

5. release 작업 후 commit

   ```
   $ git add {file name.type}
   $ git commit -m "commit title"
   $ git push origin release/{version}
   ```

6. release finish

   ```
   $ git flow release finish {version}
   ```

7. master에서 push

   ```
   $ git push origin master
   ```

   > github에 올라간걸 확인할 수 있다.

