

# pipeline 구성

### General

- **Do not allow concurrent builds**

  이 옵션을 활성화하면, 해당 pipeline의 동시 실행을 방지

  pipeline이 이미 실행 중인 경우, 새로운 실행 요청이 들어와도 pending 상태에 머물게 되며, 현재 실행 중인 build가 완료된 후에야 다음 build가 시작

  - Abort previous builds

    새 빌드가 시작되면 이전에 실행 중이던 같은 파이프라인의 빌드를 자동으로 중단(abort)

- **Do not allow the pipeline to resume if the controller restarts**

  이 옵션을 활성화하면, Jenkins 컨트롤러가 재시작되어도 pipeline이 이전 상태에서 자동으로 재개되지 않음

  jenkins에서 pipeline의 상태를 일시적으로 저장하고, Jenkins controller(서버)가 재시작한 후에 이를 다시 시작하는 것이 defualt임

  > pipeline이 특정 환경이나 상태에 의존적인 경우, 불안정하거나 예측할 수 없는 동작을 방지하기 위해 사용

- **GitHub project**

  파이프라인과 관련된 GitHub 프로젝트의 URL을 지정

  이는 파이프라인 구성 요소와 GitHub 저장소 간의 연결을 명시적으로 설정

- **GitLab Connection**

  Jenkins 프로젝트에서 GitLab 서버와의 연동을 위해 사용되는 설정

- **Use alternative credential**

  작업을 수행할 때 기본 Credentials(`Username with password`) 대신 다른 인증 정보를 사용하고 싶을 때 활성화

  gitlab에서 만든 API Access Token 을 사용할 수 있다.

  > gitlab에서
  >
  > 사용자 설정 > 좌측 탭 중 `Access Tokens` > api 선택 후 만료날짜, 이름 결정 > `Create personal access token` 클릭
  >
  > **Your New Personal Access Token**  이 새로 만들어진 token이다.

- **Pipeline speed/durability override**

  Pipeline의 로깅과 내부 데이터 저장 방식을 조정하여, 성능과 내구성 사이의 균형을 맞추는 설정

  Pipeline의 실행 속도와 장애 복구 능력 사이에서 적절한 수준을 선택

  - `Maximum durability but slowest`

    모든 파이프라인 관련 데이터를 Jenkins 마스터에 저장하여, Jenkins 재시작 후에도 Pipeline 상태를 복구할 수 있는 최대한의 내구성을 제공

    데이터 저장 및 logging 작업으로 인해 Pipeline인 실행 속도가 느려질 수 있다.

  - `Less durability, a bit faster`

    일부 중요한 Pipeline 데이터는 저장하되, 모든 데이터를 저장하지는 않아 Pipeline인 실행 속도가 Maximum보다는 빠르다.

  - `preformance-optimized: much faster`

    재시작 후 Pipeline 상태 복구가 최소한으로 진행되기 때문에 내구성을 최소화하여 Pipeline의 실행 속도를 크게 향상

    대규모 파이프라인이나 높은 성능이 요구되는 환경에서 유용

    > 장애 발생 시 대부분의 파이프라인 진행 상황을 잃을 수 있음

- **Preserve stashes from completed builds**

  Pipeline에서 `stash`와 `unstash` 단계를 사용

  - `stash`: 주로 파이프라인의 한 부분에서 생성된 파일이나 디렉토리를 임시적으로 저장
  - `unstash`:  `stash`를 통해 저장된 파일이나 디렉토리를 다시 꺼내 쓸 때 사용

  일시적으로 파일을 저장했다가 필요 시 다시 꺼내 쓸 때, 완료된 build의 stash 파일을 보존하도록 설정

  여러 build 또는 Pipeline 간에 파일을 공유하고 싶을 때 유용

  - `Keep this many of the most recent builds' stashes`

    보존할 최근 빌드의 stash 파일 수를 지정

    이 값에 따라, 지정된 수의 최근 빌드에서 생성된 stash만이 보존되며, 그 이외의 빌드에서 생성된 stash 파일은 삭제

- **Throttle builds**

  동시에 실행되는 build의 수를 제한

  resource 사용량을 제어하고, 서버에 overloading이 발생하는 것을 방지

  - `Number of builds`: 허용하는 동시 실행 build수
  - `Time period`: 빌드의 최대 실행 횟수를 허용하는 특정 시간을 결정

- **오래된 빌드 삭제**

  disk 공간을 절약하기 위해 일정 기간이 지난 build 기록을 삭제

  Strategy

  - `Build Age`: build가 생성된 지 일정 시간이 지난 후에 삭제
  - `Log Ratation`: 로그 파일의 크기나 수명을 기준으로 오래된 로그 파일을 자동으로 삭제

- **이 빌드는 매개변수가 있습니다**

  build를 실행할 때 사용자로부터 입력 받을 parameter를 정의할 수 있다.

  build시 다양한 option을 dynamically하게 지정할 수 있으며, build 과정을 flexible하게 제어할 수 있다. 

- **필요한 경우 concurrent 빌드 실행**

  기본적으로 jenkins는 동일 project의 build를 순차적으로 실행하지만, 이 option을 사용 시 같은 project에 대해 여러 build를 parallel하게 진행할 수 있다.



### Build Triggers

- **Build after other projects are built**

  현재 pipeline이나 project를 다른 project의 build가 성공적으로 완료된 후에 실행하도록 설정

  - `Trigger only if build is stable`

    앞서 실행된 project의 build가 "성공적(stable)"으로 마무리되었을 때만 현재 project의 build를 실행하도록 설정

  - `Trigger even if the build is unstable`

    앞선 project의 build가 "불안정(unstable)"한 상태여도 현재 project의 build를 실행

  - `Trigger even if the build fails`

    앞서 실행된 project의 build가 실패(fail)한 경우에도 현재 project의 build를 실행

  - `Always trigger, even if the build is aborted`

    앞선 project의 build가 어떤 이유로 중단(aborted)되었을지라도, 조건에 상관없이 항상 현재 project의 build를 실행

  > **Do not allow concurrent builds** 와의 차이점
  >
  > - **Do not allow concurrent builds**: 하나의 프로젝트 또는 pipeline 내에서 동시에 여러 빌드가 실행되는 것을 방지
  >
  >   단일 proejct 내에서 동시 build 실행을 제어
  >
  > - **Build after other projects are built**: 현재 프로젝트 또는 pipeline의 build를 다른 특정 project의 build가 완료된 후에만 실행되도록 구성
  >
  >   다른 project의 build 상태를 기반으로 현재 프로젝트의 build를 trigger

- **Build periodically**

  cron 표현식을 사용하여 정해진 스케줄에 따라 주기적으로 빌드를 실행하도록 설정

  매일 야간에 빌드를 실행하거나, 매주 특정 요일에 테스트를 수행하는 등의 시나리오에 적합

  **Schedule 구성 예시**

  - 기본 형식

    ```
    분(0-59) 시간(0-23) 일(1-31) 월(1-12 또는 JAN-DEC) 요일(0-7 또는 SUN-SAT)
    ```

  - 매일 자정에 build 실행

    ```
    0 0 * * *
    ```

  - 매일 오후 6시에 build 실행

    ```
    0 18 * * *
    ```

  - 매주 월요일 오전 9시에 build 실행

    ```
    0 9 * * 1
    ```

  - 매월 1일 자정에 build 실행

    ```
    0 0 1 * *
    ```

  - 주중(월요일부터 금요일) 매일 오전 8시에 build 실행

    ```
    0 8 * * 1-5
    ```

- **Build when a change is pushed to GitLab**

  GitLab 저장소에 변경사항이 푸시될 때마다 빌드를 실행하도록 설정

  이를 위해 GitLab 저장소에 Jenkins의 Webhook URL을 설정하고, 코드 변경 시 Jenkins가 자동으로 build를 시작하도록 설정

  > GitLab webhook URL: `http://localhost:8081/project/{pipeline_name}`
  >
  > 과 같이 gitLab webhook을 구성할때 입력할 URL을 제공한다

  - `Push Events`

    GitLab 저장소에 코드가 푸시되었을 때 빌드를 트리거

  - `Push Events in case of branch delete`

    브랜치가 삭제되었을 때도 빌드를 트리거할지 여부를 설정

    브랜치 삭제는 종종 코드베이스 정리나 머지 작업의 일환으로 발생할 수 있기 때문에 사용됨

  - `Opened Merge Request Events`

    머지 리퀘스트가 새로 생성되었을 때 빌드를 트리거

  - `build only if new commits were pushed to Merge Request`

    머지 리퀘스트에 새로운 커밋이 푸시된 경우에만 빌드를 트리거

  - `Accepted Merge Request Events`

    머지 리퀘스트가 승인되고 머지까지 되었을 때 빌드를 트리거

  - `Closed Merge Request Events`

    머지 리퀘스트가 닫혔을 때(머지되지 않고 종료됨) 빌드를 트리거

  - `Rebuild open Merge Requests `

    이미 열려 있는 머지 리퀘스트에 대해 특정 조건하에서 빌드를 재실행

    - On push to source branch

      머지 리퀘스트의 소스 브랜치(변경사항을 제안하는 브랜치)에 새로운 커밋이 푸시될 때마다 Jenkins가 해당 머지 리퀘스트의 빌드를 재실행

      소스 브랜치에 추가된 변경사항을 바탕으로 머지 리퀘스트가 여전히 기대하는 대로 동작하는지 검증하고자 할 때 유용하다.

    - On push to source or target branch

      소스 브랜치뿐만 아니라 타겟 브랜치(변경사항이 머지될 목표 브랜치)에 대한 커밋 푸시도 머지 리퀘스트의 빌드를 재실행

      소스 브랜치의 변경사항 뿐만 아니라 타겟 브랜치의 최신 상태도 함께 고려하여 머지 리퀘스트의 빌드를 실행하고자 할 때 사용된다.

  - `Approved Merge Requests (EE-only)`

    GitLab Enterprise Edition에서 제공하는 기능

    머지 리퀘스트가 승인된 후에(머지까진 안되더라도) 빌드를 트리거

    코드 리뷰와 승인 과정을 거쳐 최종적으로 승인된 변경사항에 대해서만 빌드와 테스트를 실행하고자 할 때 유용

    > 이 옵션은 GitLab의 EE(Enterprise Edition)에서만 사용 가능

  - `Comments`

    머지 리퀘스트나 커밋에 특정 comment가 달렸을 때 빌드를 트리거

  - `Comment (regex) for triggering a buil`

    comment 내용이 지정된 정규 표현식과 일치할 때 빌드를 트리거

    > `Jenkins please retry a build` 으로 입력 시
    >
    > "Jenkins please retry a build"와 같은 특정 문구를 comment로 작성하면, 해당 조건과 일치하는 comment가 감지될 때마다 자동으로 Jenkins 빌드를 실행

  - **`Advanced settings`**

    - `Enable [ci-skip]`

      커밋 메시지에 `[ci-skip]` 또는 `[skip ci]` 태그가 포함된 경우, 해당 커밋에 대한 빌드를 실행하지 않음

       특정 커밋이 코드 변경과 관련 없거나 빌드를 필요로 하지 않는 경우 유용하게 사용

      commit message가 `Update README.md [skip ci]` 와 같을 경우엔 해당 commit에 대한 build를 실행하지 않음

    - `Ignore WIP Merge Requests`

      Work In Progress(WIP) 상태의 머지 리퀘스트를 무시하고 빌드를 실행하지 않도록 설정

      > WIP 머지 리퀘스트는 아직 검토나 병합을 위해 완전히 준비되지 않은 상태를 의미

    - `Labels that launch a build if they are added (comma-separated)`

      특정 label이 머지 리퀘스트에 추가될 때 빌드를 실행하도록 설정

      - label: merge request에 추가할 수 있는 tag나 maker

    - `Set build description to build cause (eg. Merge request or Git Push)`

      빌드 설명을 빌드의 원인(예: 머지 리퀘스트나 Git 푸시)으로 설정하도록하는 기능

    - `Build on successful pipeline events`

      GitLab CI/CD pipeline의 성공적인 실행 결과에 대한 event를 감지하여 빌드를 실행하도록 설정

      GitLab의 파이프라인이 성공적으로 완료된 후에 후속 작업이나 배포 과정을 자동으로 진행하고자 할 때 유용하게 사용

    - `Pending build name for pipeline`

      파이프라인에 대해 진행 중인(or 대기 중인) 빌드의 이름을 지정

    - `Cancel pending merge request builds on update`

      머지 리퀘스트에 대한 새로운 업데이트가 발생할 때 기존에 대기 중인 빌드를 자동으로 취소

    - `Allowed branches`

      - Allow all branches to trigger this job

        repository의 모든 브랜치로부터 발생하는 변경사항에 대해 빌드를 트리거

        특정 브랜치에 대한 제한 없이 광범위한 변경사항을 모니터링하고자 할 때 사용

      - Filter branches by name

        특정 이름을 가진 브랜치로부터 발생하는 변경사항에 대해서만 빌드를 트리거

        > `Rebuild open Merge Requests`에 `On push to source branch`을 설정하고, 동시에 `Allowed branches`에서 `Filter branches by name` 설정을 통해 source branch를 exclude(제외)하도록 설정하면? >> 설정 간의 충돌 발생.  정상적인 동작 X

      - Filter branches by regex

        정규 표현식을 사용하여 브랜치 이름을 필터링하고, 해당 조건에 맞는 브랜치로부터 발생하는 변경사항에 대해서만 빌드를 트리거

    - `Filter merge request by label`

      머지 리퀘스트에 특정 라벨이 추가되었을 때만 빌드를 트리거

    - `Secret token`

      Jenkins와 GitLab 간의 Webhook 통신을 보호하기 위한 비밀 토큰

      Generate 를 통해 만들 수 있는 이 token은 GitLab에서 Webhook을 설정할 때 사용된다.

- **GitHub hook trigger for GITScm polling**

  GitHub 저장소의 변경사항(커밋, 풀 리퀘스트 등)이 있을 때 Jenkins 빌드를 자동으로 트리거

  > GitHub에서 제공하는 Webhook 기능을 활용

- **Poll SCM**

  Jenkins가 주기적으로 소스 코드 관리 시스템(SCM)을 폴링하여 변경사항을 확인하고, 변경사항이 감지되면 자동으로 빌드를 시작

  - `chedule`

    cron 표현식을 사용하여 scheduling table 구성

  - `Ignore post-commit hooks`

    `post-commit hook`: Source Code Management(SCM) 시스템(Git)에서 커밋이 완료된 직후에 자동으로 실행되는 스크립트나 명령어

- **Quiet period**

  빌드 트리거가 발생한 후 실제 빌드를 시작하기 전까지 대기하는 시간(초 단위)을 설정

  이 기간 동안 추가적인 빌드 요청이 들어오면, 여러 요청을 하나의 빌드로 합칠 수 있다.

- **빌드를 원격으로 유발 (예: 스크립트 사용)**

  외부 시스템이나 스크립트에서 Jenkins 빌드를 원격으로 시작할 수 있도록 허용

  - `Authentication Token`: 원격 빌드를 유발할 때 보안을 위해 사용하는 토큰

    Jenkins 빌드 URL에 접근할 때 이 토큰을 파라미터로 제공해야 한다.

  - `다음 URL을 사용하여 원격 빌드 유발: ~~~` URL제공



### Advanced Project Options



### Pipeline

**Definition**

- `pipeline script`

  Groovy 언어를 사용하여 Jenkinsfile에 해당하는 파이프라인의 전체 코드를 직접 입력하는 방식

- `pipeline script from SCM`

   Source Code Management(SCM) 시스템(Git)에서 파이프라인 스크립트(Jenkinsfile)를 가져오도록 설정

  - Script Path

>  Groovy는 자바 가상 머신(JVM) 위에서 실행되는 동적 타이핑 언어로, Jenkins 파이프라인의 로직을 정의하는 데 사용된다.

- `Lightweight checkout`

  repository의 내용을 checkout하지 않고 `Jenkinsfile`만을 가져와 pipeline인 설정 적용.

  이 방식은 리소스 사용을 줄이고, 파이프라인 시작 시간을 단축시키는 데 도움이 된다.



#### **pipeline script from SCM**

**SCM**

- **None**

- **Git** 

  Repositories

  - Repository URL

    접근 가능한 저장소의 URL이여야 함.

    만일 jenkins를 docker로 설치했다면 container내부에 ssh key를 만들고 git-lab 사용자의 계정에 추가해야함.

    > jenkins container에 sshkey 생성
    >
    > 1. docker 접속
    >
    >    ```
    >    $ docker exec -it jenkins /bin/bash 
    >    ```
    >
    > 2. ssh key 생성
    >
    >    ```
    >    $ ssh-keygen -t rsa -b 4096 -C "your_email@example.com"
    >    ```
    >
    > 3. ssh key확인
    >
    >    ```
    >    $ cat ~/.ssh/id_rsa.pub 
    >    ```
    >
    > 4. ssh key 등록
    >
    >    git-lab의 개인 계정 setting > 좌측 탭 중 `SSH Keys` > ssh key 등록

  - Credentials

    Jenkins에서 사용할 수 있는 주요 Credentials 유형 선택 (아래 유형만 선택 가능)

    - Username with password: 일반적인 사용자 이름과 비밀번호 조합입
    - SSH Username with private key: SSH 키 기반 인증
    - Secret file: 비밀번호나 인증 토큰과 같은 비밀 정보를 포함한 파일
    - Secret text: API 토큰이나 비밀번호와 같은 단일 문자열 정보

    위 유형 중 아무것도 만들어진 Credentials이 없을 경우 `-none-` 출력

    만일 위 유형이 아닌 다른 유형(gitlab에서 만든 API Access Token과 같은)을 사용한다면 `Use alternative credential`에 등록할것.

  - 고급

    - Name

      Git에서 브랜치, 태그, 또는 리비전을 지정할 때 사용하는 별칭.

      다양한 브랜치에 대해 다른 작업을 수행하고자 할 때, 이를 구분하기 위한 식별자로 사용

    - Refspec

      로컬과 원격 저장소 간에 데이터를 전송할 때 어떤 branch나 tag가 포함될지를 정의하는 규칙

      git fetch 동작을 제어하는데 사용된다.

      > 예시
      >
      > `refs/heads/main:refs/remotes/origin/main`: 원격 저장소의 `main` 브랜치를 로컬의 `origin/main`으로 fetch
      >
      > 아래 명령어와 같은 동작을 수행한다.
      >
      > ```
      > $ git fetch origin refs/heads/main:refs/remotes/origin/main
      > ```
      >
      > 자세한 패던은 `git refs` 검색

      1개의 branch에 대한 규칙만 정의할 수 있다.

  - Add repository

    Jenkins 프로젝트에서 여러 Git 저장소를 참조하고 싶을 때 사용

    소스 코드 저장소에 걸쳐 있는 의존성이 있거나, 여러 저장소로부터 코드를 가져와 빌드해야 할 경우에 유용

- branches to build

  Jenkins가 build를 위해 checkout해야 하는 branch를 지정

  특정 브랜치, 여러 브랜치, 또는 특정 패턴을 따르는 브랜치들을 지정할 수 있다.

  여러 브랜치를 지정한 경우, 지정된 브랜치 중 하나에서 변경사항을 감지하면 해당 브랜치에서 빌드를 실행

  예시로 `feature/*`를 지정하면, `feature/`로 시작하는 브랜치 중 변경사항이 있는 브랜치에 대해 빌드를 수행

- Repository browser

  Jenkins에서 source code repository의 browser를 설정하는 옵션

  Jenkins UI에서 직접적으로 소스 코드를 볼 수 있는 링크를 제공하여, 빌드에 관련된 커밋이나 변경사항을 쉽게 확인할 수 있다.

  - gitlab

    - URL: GitLab 저장소의 루트 URL

      > 예시: 사용자 이름이 "username"이고 저장소 이름이 "repository"인 GitLab 저장소의 경우
      >
      > ```
      > https://gitlab.com/username/repository/		# 또는
      > http://192.168.0.101:30000/path/repository_name
      > ```

    - Version: GitLab의 버전을 명시

      이 필드를 비워 둔다면, Jenkins는 GitLab의 최신 버전을 기준으로 작동

      9.1 이상의 version을 원할 시 `9.1`이라 입력

- Additional Behaviours

  체크아웃 과정에서 Git에 적용할 추가적인 설정이나 동작을 정의

  예시

  - `Sparse Checkout paths`: 특정 폴더나 파일만을 체크아웃하고 싶을 때 사용

  - `Clean before checkout`: 체크아웃을 수행하기 전에 작업 directory 내부의 모든 변경사항을 제거

    "작업 directory"는 Jenkins Job이 실행되는 동안 코드가 체크아웃되고 빌드가 수행되는 로컬 디렉토리를 의미



### pipeline script (Jenkinsfile)

Jenkinsfile은 Groovy 언어로 작성

예시

```groovy
pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                echo 'Building..'
                // 빌드 관련 명령어 실행
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
                // 테스트 스크립트 실행
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying..'
                // 배포 스크립트 실행
            }
        }
    }
}
```

- agent any

  Jenkins 파이프라인이 실행될 때 사용 가능한 어떤 build agent(node)에서도 파이프라인을 실행할 수 있도록 설정.

  enkins 환경에 여러 노드(물리적 또는 가상)가 구성되어 있을 경우, `agent any` 설정은 Jenkins 마스터가 현재 가용 상태인 임의의 build agent를 선택하여 파이프라인을 실행한다.

  > **build agent**
  >
  > 자동화된 빌드, 테스트, 배포 작업 등을 수행하는 서버나 환경
  >
  > build agent는 일반적으로 CI 서버(Jenkins 마스터)로부터 작업을 할당 받아 수행하며, 병렬 처리 능력을 확장하고 다양한 환경에서의 빌드를 지원하기 위해 사용된다.

