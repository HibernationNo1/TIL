## freestyle project 구성

jenkins에서 "new item"  > "freestyle project" 

- GitLab Connection

  Jenkins 프로젝트에서 GitLab 서버와의 연동을 위해 사용되는 설정

- other options

  - Use alternative credential

    작업을 수행할 때 기본 Credentials(`Username with password`) 대신 다른 인증 정보를 사용하고 싶을 때 활성화

    gitlab에서 만든 API Access Token 을 사용할 수 있다.

    > gitlab에서
    >
    > 사용자 설정 > 좌측 탭 중 `Access Tokens` > api 선택 후 만료날짜, 이름 결정 > `Create personal access token` 클릭
    >
    > **Your New Personal Access Token**  이 새로 만들어진 token이다.
    >
    > 1ZiuY69VQWS5hc5_tNG9

  - Throttle builds

    동시에 실행되는 build의 수를 제한

    resource 사용량을 제어하고, 서버에 overloading이 발생하는 것을 방지

  - 오래된 빌드 삭제

    disk 공간을 절약하기 위해 일정 기간이 지난 build 기록을 삭제

  - 이 빌드는 매개변수가 있습니다

    build를 실행할 때 사용자로부터 입력 받을 parameter를 정의할 수 있다.

    build시 다양한 option을 dynamically하게 지정할 수 있으며, build 과정을 flexible하게 제어할 수 있다. 

  - 필요한 경우 concurrent 빌드 실행

    기본적으로 jenkins는 동일 project의 build를 순차적으로 실행하지만, 이 option을 사용 시 같은 project에 대해 여러 build를 parallel하게 진행할 수 있다.

  - 고급

    - Quiet period

      build trgger가 발생한 후 실제로 빌드가 시작되기까지의 대기 시간 

      이 대기시간동안 추가적인 trigger 발생 시, 모든 trigger가 하나의 build로 통합된다.

      불필요한 build를 줄이고 여러 변경사항을 하나의 build로 처리하기 위해 사용

    - 재시도 횟수

       network 문제나 임시적인 문제로 인해 build가 실패할 경우, 지정된 횟수만큼 자동으로 다시 시도

      일시적인 문제로 인한 빌드 실패를 자동으로 복구하기위해 사용

    - 업스트림, 다운스트림 프로젝트가 빌드하는 동안 빌드 멈춤

      현재 프로젝트에 의해 트리거되는 업스트림( or 다운스트림)프로젝트의 빌드가 진행 중일 때 현재 프로젝트의 빌드를 일시적으로 멈추게 하는 설정

       의존성이 있는 프로젝트 간의 빌드 충돌 방지

    - 사용자 빌드 경로 사용

      jenkins는 기본적으로 각 프로젝트의 build 결과를 자체적으로 정의된 경로에 저장한다. 

      이 option을 사용 시 사용자가 지정한 경로에 build 결과를 저장할 수 있다.

    - 표시 이름

      프로젝트 또는 빌드의 표시 이름을 사용자 정의

    - Keep the build logs of dependencies

      현재 프로젝트에 의존성이 있는 다른 프로젝트의 빌드 로그를 보관하고자 할 때 사용

- 소스 코드 관리 (Git)

  - Repositories

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

  - Additional Behaviours

    체크아웃 과정에서 Git에 적용할 추가적인 설정이나 동작을 정의

    예시

    - `Sparse Checkout paths`: 특정 폴더나 파일만을 체크아웃하고 싶을 때 사용

    - `Clean before checkout`: 체크아웃을 수행하기 전에 작업 directory 내부의 모든 변경사항을 제거

      "작업 directory"는 Jenkins Job이 실행되는 동안 코드가 체크아웃되고 빌드가 수행되는 로컬 디렉토리를 의미



