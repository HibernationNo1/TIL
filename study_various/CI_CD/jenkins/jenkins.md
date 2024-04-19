# jenkins 

Jenkins는 오픈 소스 자동화 서버로서, 지속적 통합(CI) 및 지속적 배포(CD) 프로세스를 자동화하는 데 널리 사용된다.

Java로 개발되었으며, 소프트웨어 개발의 빌드, 테스트, 배포 단계를 자동화하여 개발 효율성을 높이고, 배포 주기를 단축하는 데 기여한다.

- **오픈 소스**: Jenkins는 MIT 라이선스 하에 배포되며, 무료로 사용 가능

- **플러그인 생태계**: 1,000개 이상의 플러그인을 지원하여 다양한 개발, 테스트, 배포 도구와 통합할 수 있다.

- **마스터-슬레이브 아키텍처**: 분산 빌드 환경을 지원하여, 여러 서버에 걸쳐 작업 부하를 분산시킬 수 있다.

  이를 통해 대규모 프로젝트와 조직에서 효율적으로 리소스를 관리할 수 있다.

- **파이프라인**: `Jenkinsfile`을 통해 파이프라인을 코드로 정의할 수 있으며, 복잡한 CI/CD 워크플로우를 구성할 수 있다.

  이를 통해 빌드, 테스트, 배포 과정을 자동화하고 재현 가능한 방식으로 관리할 수 있다.

**기능**

- **지속적 통합(CI)**: 소스 코드 저장소에 새로운 변경사항이 푸시될 때마다 자동으로 빌드와 테스트를 실행하여, 개발 초기 단계에서 문제를 식별하고 해결할 수 있도록 지원
- **지속적 배포(CD)**: 테스트를 통과한 코드를 자동으로 스테이징 또는 프로덕션 환경에 배포하여, 소프트웨어 배포 프로세스를 자동화
- **모니터링 및 로깅**: 빌드 과정과 결과를 자세히 모니터링하고 로그를 기록하여, 문제 해결 및 성능 최적화에 필요한 정보를 제공
- **알림**: 빌드 실패, 성공 등의 중요한 이벤트에 대해 이메일, Slack 등을 통해 알림을 받을 수 있다.



## Configure CI/CD

jenkins을 사용해서 CI/CD를 구성하는 순서

1. install jenkins (== set master node)
2. credentials 추가
   - gitlab의 계정에 대한 API token credentials
   - agent node에 대한 ssh credentials
3. agent node 추가
4. pipeline 구성 (and `git webhooks` 설정)





## install 

### install jenkins 

1. docker compose를 사용한 jenkins 설치 

   `docker-compose.yml`

   ```
   version: "3"
   services:
     jenkins: 
       image: 'jenkins/jenkins:2.448'
       container_name: 'jenkins'
       ports:
         - '8081:8080'     # jenkins의 기본 port
         - '50000:50000'   # agent node와 연결하기 위한 port(필요시 사용) Jenkins master와 agent 간의 통신시 사용
   ```

2. `http://localhost:8081/` 접속

   Administrator password: docker container의 log를 통해 확인 가능

   ```
   $ docker logs jenkins
   ```

   ```
   *************************************************************
   
   Jenkins initial setup is required. An admin user has been created and a password generated.
   Please use the following password to proceed to installation:
   
   412c66f7dd2e422a8463d19dd8d129dd
   
   This may also be found at: /var/jenkins_home/secrets/initialAdminPassword
   
   *************************************************************
   ```

   `412c66f7dd2e422a8463d19dd8d129dd` 이것이 password

3. plugin 설치

   >  예시: GitLab  plugin 설치
   >
   > 접속 후 `Select plugins to install` > 'GitLab' 검색 > install 

   필수 설치 목록:

   - `ssh-agent`: ssh-Credentials를 사용하기 위해 반드시 설치 필요

   - `GitLab`: git-lab 사용시 반드시 필요

     > Select plugins to install 단계에서 `ssh-agent` 설치 시 제대로 동작하지 않는 문제점 확인
     >
     > `ssh-agent` 는 jenkins login 후  jenkins관리 > Plugins > Available plugins > `ssh-agent` 검색 과정으로 설치하자

4. Create First Admin User (모든 항목이 필수)

   - 계정명: teno
   - 암호: ai1234
   - 이름: taeuk noh
   - 이메일 주소: `teno@enliple.com`

5. Instance Configuration

   jenkins URL 결정

   `http://{jenkins가 설치된 server의 IP}:{jenkins 사용 port}/{route path}`

   > 예시: `http://192.168.110.18:8081/`



## job

Jenkins에서 실행할 수 있는 작업의 단위로, 빌드, 테스트, 배포 등의 자동화된 작업을 정의하고 수행한다.

Job은 Jenkins의 기본 작업 단위이며, 사용자가 구성할 수 있는 다양한 작업(빌드 작업)을 포함한다.

**종류**

- **freestyle project**

  가장 일반적이고 범용적인 Job 유형으로, 복잡한 스크립팅 없이 GUI를 통해 쉽게 구성

  다양한 SCM, 빌드 트리거, 빌드 후 조치 등을 설정할 수 있어, 간단한 빌드 작업부터 시작하여 중간 복잡도의 작업에 적합

- **pipeline**

  코드로서의 인프라(IaC) 접근 방식을 사용하여 build, test 및 배포 pipeline을 정의할 수 있다.

  `Jenkinsfile`을 사용하여 파이프라인을 저장소와 함께 버전 관리할 수 있으며, 복잡한 워크플로우와 지속적인 통합/지속적인 배포(CI/CD)를 구현하는 데 유용

- **Multibranch Pipeline**

  코드 저장소 내의 여러 브랜치를 자동으로 검색하고, 각 브랜치에 대해 별도의 파이프라인을 설정할 수 있는 Pipeline의 확장 유형

  `Jenkinsfile`이 포함된 각 브랜치에 대해 자동으로 파이프라인 Job을 생성하고 관리

- **Maven Project**

  Java 기반 프로젝트에 대한 빌드 프로세스를 자동화하는 데 특화된 Job 유형

- **External Job**

  Jenkins UI 내에서 외부 프로세스의 실행 상태를 추적하고 기록하는데 사용



**freestyle project** vs **pipeline**

ipeline을 통해 정의된 자동화 작업은 단순한 Freestyle Job보다 더 많은 제어와 유연성을 제공

Pipeline Job은 `Jenkinsfile`을 통해 코드 형태로 pipeline인 로직을 정의하며, 이를 통해 복잡한 CI/CD 워크플로우를 구현할 수 있다.





