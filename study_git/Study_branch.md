# branch 활용 방법

branch는 firsh commit이 반드시 있어야 한다.

HEAD: 내가 화면으로 보고있는 위치

master branch: 시초의 branch 

---

## git flow

- main branch : 프로젝트가 끝날 때 까지 항상 유지되는 branch

  - master : 제품으로 출시(Launching)할 수 있는 branch

    > branch name은 master/v 0.0.0 이런 식

  - develop: 개발 brach. 여기서 feature, release가 분기되고 병합된다.

    > branch name은 develop/v 0.0.0 이런 식

- sub branch : 필요할때만 사용되고 소멸되는 branch

  - feature : develop로 부터 분기되어 개별 기능을 개발하는 branch. 기능이 완료되면 다시 develop으로 병합된다.

    > branch name은 feature - ~~~ 또는 feature/ 이런 식

  - release: 기능 개발이 완료되어 출시 버전을 준비하는 branch. 주로 주석을 정리하거나 gitignore에 등록하고 readme를 정리하는 작업 등을 한다.

    > branch name은 release/ v 0.0.0 이런 식

  - hofix : 출시 버전에서 발생한 bug를 fix하는 branch로 유일하게 mastger에서 분기된다.

    > branch name은 hofix/v 0.0.0 이런 식



### model 구성

![](https://media.vlpt.us/images/cos/post/57fa6718-f327-4ae8-b789-26259632e4fe/Simplified-version-of-the-gitflow-branching-model-adapted-from-8.png)









## branch

###  branch 명령어

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



###  branch 경우의 수

#### - master branch를 사용하면서 프로젝트를 진행할 때

1. first commit 이후 branch가 1개만 생성되어 몇 번의 commit 후 merge

   > 해당 브랜치가 master가 된다.
   >
   > > fast forward 라고 함

2. first commit 이후 2개 이상의 branch가 생성되어 몇 번의 commit 후 merge

   2 -1.중복되는 메모리에 서로 다른 정보가 있다면?

   >수동으로 바꿔달라고 한다. 
   >
   >그 동안은 MERGING상태. merge가 완료된 것이 아님.
   >
   >>이 때는 commit이 불가능

2 -2.그 외

>이거 괜찮냐? 라고 물어보며 vim이 실행되지만 그대로 저장하면 merge 진행됨
   >
   >> automatic merge 라고 함

- 병합이 성공적으로 되면 master가 아닌 branch는 병합 이전의 commit에서 멈추고, master가 병합된 마지막 commit의 주인임

##### branch 경우의 수 예제

1. 의 경우

>`$ touch word.md`				// master branch에 word라는 파일 생성
>
>`$ vim about.md`  를 통해 첫 번째 줄에 2라는 내용 저장
>
>`$ git commit - m "commit1"` 	//  commit1 이라는 commit 실행
>
>`$ git switch - c home`				// home 이라는 branch 생성 후 해당 branch로 HEAD 이동
>
>`$ touch alphabet.md	`				// home branch에 alphabet라는 파일 생성
>
>`$ git commit - m "commit2"` 	//  commit2 이라는 commit 실행
>
>`$ git switch master` 				// master branch 로 HEAD 이동
>
>현재까지 branch 갯수 2개(master, home)
>
>현재 log
>
>branch 2개 (master, home)
>
>> master branch에서 실행된 commit 1회 (commit 1)
>>
>> - commit1: word.md 의 첫 번째 줄에 1이라는 내용 추가
>
>>  home branch에서 실행된 commit 2회 (commit 1, commit 2)
>>
>> - commit1:  위의 commit1과 같은 commit임
>> - commit2: alphabet라는 파일 생성
>
>`$ git merge home`
>
>master가 commit2 위치로 이동 . fast forward 라고 함



2-1. 의 경우

>`$ touch word.md`				// master branch에 word라는 파일 생성
>
>`$ vim about.md`  를 통해 3 번째 줄에 1이라는 내용 입력 후 저장
>
>`$ git commit - m "commit1"` 	//  commit1 이라는 commit 실행
>
>`$ git switch - c home`				// home 이라는 branch 생성 후 해당 branch로 HEAD 이동
>
>`$ touch alphabet.md	`				// home branch에 alphabet라는 파일 생성
>
>`$ git commit - m "commit2"` 	//  commit2 이라는 commit 실행
>
>`$ git switch master` 				// master branch 로 HEAD 이동
>
>`$ vim about.md`  를 통해 3 번째 줄에 1이라는 내용을 2로 수정 후 저장
>
>`$ git commit - m "commit3"` 	//  commit3 이라는 commit 실행
>
>`$ git switch home` 				// home branch 로 HEAD 이동
>
>> 현재 log
>>
>> branch 2개 (master, home)
>>
>> > master branch에서 실행된 commit 2회 (commit 1, commit 3)
>> >
>> > - commit1: word.md 의 3 번째 줄에 1이라는 내용 추가
>> >
>> > - commit3: word.md 의 3 번째 줄에 1이라는 내용을 2로 변경
>>
>> >  home branch에서 실행된 commit 2회 (commit 1, commit 2)
>> >
>> > - commit1:  위의 commit1과 같은 commit임
>> > - commit2: alphabet라는 파일 생성
>
>`$ git merge home`  // 두 branch 안에 있는 같은 파일인 word.md 안의 같은 줄( 3 번째 줄) 내용이 다르기 때문에 수동으로 고쳐군 다음에 merge 해야 한다.
>
>- 방법 1.  home branch 안에 있는 word.md의 내용 또는 master branch 안에 있는 word.md 내용 둘 중에 하나를 결정하고 남기면 된다.
>
>md파일 열어서 해결 가능
>
>- 방법 2.  vscode로word.md를 연다면, 합칠 수 있는 경우의 수를 보여준다.
>
>`$ git merge home`   // 변경 후 다시 merge
>
>master가 commit3 위치로 이동 (commit 2과 3이 합쳐짐)
>
>내용을 변경하기 전에 `$ git add .`  하면 master|MASGING 라며 마징이 진행중이라고 뜬다.
>
>내용을 변경한 후에 `$ git add .`  하면 commit이 가능해진다.

2 -2. 의 경우

>`$ touch word.md`				// master branch에 word라는 파일 생성
>
>`$ vim about.md`  를 통해 3 번째 줄에 1이라는 내용 입력 후 저장
>
>`$ git commit - m "commit1"` 	//  commit1 이라는 commit 실행
>
>`$ git switch - c home`				// home 이라는 branch 생성 후 해당 branch로 HEAD 이동
>
>`$ touch alphabet.md	`				// home branch에 alphabet라는 파일 생성
>
>`$ git commit - m "commit2"` 	//  commit2 이라는 commit 실행
>
>`$ git switch master` 				// master branch 로 HEAD 이동
>
>`$ vim about.md`  를 통해 4 번째 줄에 2라는 내용 추가 저장
>
>`$ git commit - m "commit3"` 	//  commit3 이라는 commit 실행
>
>`$ git switch home` 				// home branch 로 HEAD 이동
>
>현재 log
>
>branch 2개 (master, home)
>
>> master branch에서 실행된 commit 2회 (commit 1, commit 3)
>>
>> - commit1: word.md 의 3 번째 줄에 1이라는 내용 추가
>>
>> - commit3: word.md 의 4 번째 줄에 2라는 내용 추가
>
>>  home branch에서 실행된 commit 2회 (commit 1, commit 2)
>>
>> - commit1:  위의 commit1과 같은 commit임
>> - commit2: alphabet라는 파일 생성
>
>`$ git merge home `   // 두 branch 성공적으로 merge
>
>master가 commit3 위치로 이동 (commit 2과 3이 합쳐짐)

#### - master branch는 구현 branch로만 활용해서 프로젝트를 진행할 때

1. 각자 브랜치에서 작업함 (commit)

2. branch push도 종종함.

3. 적절한 시점에 remote/master와 merge 함.

4. 이 때, Pull Request 를 통해서 리모트(깃허브)에서 원격으로 merge 진행함.

   > git hub에서  repository에 compate & pull request  >> create pull request  >> 승인과정이 이루어져야 merge됨. >> 승인은 본인도, 함께 협업하는 사람도 모두 가능.
   >
   > >단, 본인이 pull request 올리고 승인까지 다 해버리면 협업하는 사람은 
   > >
   > >깃허브 상에서 수동 merge을 진행해야 함 

5. 리모트 merge 종료 이후, 로컬에서 master 브랜치로 origin / master 를 pull 함.(git pull origin master)

   > 배포했거나 배포할 코드만 master 브랜치에 merge 해서 안정 버전의 코드만 master 브랜치에 둔다.

6. pull 이후에 바로 다른 브랜치 생성 => 다시 위의 작업 반복