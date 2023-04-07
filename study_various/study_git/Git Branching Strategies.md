# Git Branching Strategies



**tip)**

- 두 branch를 병합하는 경우 rebase보다는 merge를 사용하자. (history를 남길 수 있다.)

  ```
  $ git merge exam
  ```

  

- 원격 branch에 push를 하기 전, 원격의 상태를 항상 항상 꼭 하자.

  - 원격의  branch를 포함해서, 모든 branch의 이름을 확인

    ```
    $ git branch -a
    ```

  - 원격의 commit상태 확인

    ```
    $ git fetch
    ```

    

  이 때 `pull`을 해야 하는 경우, merge방식보다는, rebase방식을 사용하자.

  ```
  $ git pull --rebase
  ```

  





## Github Flow

GitHub에서 제공하는 `Pull Request`와 `코드 리뷰`기능을 적극적으로 활용한 방식. 

브랜치와 `Pull Request`(줄여서 PR)라는 개념을 사용한다.



### Getting Started

#### 1. create branch

Github-flow 전략은 기능 개발, 버그 픽스 등 어떤 이유로든 **새로운 브랜치를 생성**하는 것으로 시작된다.

> 이때 체계적인 분류 없이 브랜치 하나에 의존하게 되기 때문에 **브랜치 이름을 통해 의도를 명확하게** 드러내는 것이 매우 중요하다.

- master 브랜치는 항상 최신 상태며, stable 상태로 product에 배포되는 브랜치다. 이 브랜치에 대해서는 엄격한 role과 함께 사용한다
- **새로운 브랜치는 항상 master 브랜치에서 만든다**.
- Git-flow와는 다르게 feature 브랜치나 develop 브랜치가 존재하지 않는다.
- 그렇지만, 새로운 기능을 추가하거나 버그를 해결하기 위한 **브랜치 이름은 자세하게** 어떤 일을 하고 있는지에 대해서 작성해주도록 하자



#### 2. cummit and push

개발을 진행하면서 커밋을 남긴다.

- **커밋메시지를 명확하게 작성하자**
- 원격지 브랜치로 **수시로 push** 하자



#### 3. create PR(Pull Request)

피드백이나 도움이 필요할 때, 그리고 merge 준비가 완료되었을 때는 pull request를 생성한다

- pull request는 **코드 리뷰**를 도와주는 시스템
- 이것을 이용해 자신의 코드를 공유하고, 리뷰받는다.
- merge 준비가 완료되었다면 master 브랜치로 반영을 요구한다.



#### 4. code review

Pull-Request가 master 브랜치 쪽에 합쳐진다면 곧장 라이브 서버에 배포되는 것과 다름 없으므로, 상세한 리뷰와 토의가 이루어져야 한다.



#### 5. run test

리뷰와 토의가 끝났다면 해당 내용을 라이브 서버(혹은 테스트 환경)에 배포해본다.

배포시 문제가 발생한다면 곧장 master 브랜치의 내용을 다시 배포하여 초기화 시킨다.



#### 6. merge to master

라이브 서버(혹은 테스트 환경)에 배포했음에도 문제가 발견되지 않았다면 **그대로 master 브랜치에 푸시를 하고, 즉시 배포**를 진행한다.

대부분의 Github-flow 에선 master 브랜치를 최신 브랜치라고 가정하기 때문에 배포 자동화 도구를 이용해서 Merge 즉시 배포를 시킨다.

**master로 merge되고 push 되었을 때는, 즉시 배포되어야한다**

- GitHub-flow의 핵심
- master로 merge가 일어나면 자동으로 배포가 되도록 설정해놓는다. (CI / CD)







## Git flow

여러 version의 서비스를 제공하는 프로그램인 경우 사용되는 방식. 

 

### Introduce

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



#### model 구성

![](https://media.vlpt.us/images/cos/post/57fa6718-f327-4ae8-b789-26259632e4fe/Simplified-version-of-the-gitflow-branching-model-adapted-from-8.png)





### Getting Started

#### Install

- Linux

  ```
  $ apt-get install git-flow
  ```

  

##### initialize

기존 git repository에서 초기화 하는 것으로 git-flow의 사용을 시작 할 수 있다.

```
$ git flow init -d
```

> `git flow init` 을 실행하면 process별로 사용할 branch의 name을 결정하라고 한다. `-d` option으로 default로 가자



#### Feature

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



#### Release

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



#### example

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

