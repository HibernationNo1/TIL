## ADD Node(Agent)

CI에 대한 build, test등을 수행한 agent node를 추가하는 방법



## prerequisite

**1. install java**

agent로 삼고자 하는 server에 java가 설치되어 있어야 한다.

자바 설치

- Ubuntu

  ```
  $ sudo apt update
  $ sudo apt install default-jdk
  ```

- Centos

  ```
  $ sudo yum update
  $ sudo yum install java-11-openjdk-devel
  ```



##### 2. ssh copy

master node에서 agent로 삼고자 하는 server에 공개 key를 복사해야 한다.

> 예시 192.168.110.104 서버의 sirs라는 user에 공개 key를 복사하고자 할 때
>
> (credentials 를 생성할 때 `Username`에 sirs라고 등록했어야 함)
>
> ```
> $ ssh-copy-id sirs@192.168.110.104
> ```

만일 jenkins를 docker container로 띄웠다면 

build시 ssh 파일들을 전부 volume mount를 하거나, container 내부에서 copy명령어 실행할 것.



##### 3. docker 사용시 permission 부여

docker를 사용하는 proejct라면 permission에 의해 build과정이 중지될 수 있기 때문에, 미리 권한 추가할 것.

1. ```
   $ sudo usermod -aG docker ${USER}
   ```

   docker 실행 시 sudo명령어 없이 실행하도록 설정

2. ```
   $ sudo chown -R sirs:sirs /home/sirs/.docker
   ```

   docker image build시 생성되는 cache path 에 대한 소유권을 설정.

   이 설정을 하지 않으면 root 권한으로 path(dir)가 생성되며, pipeline script에 docker 또는 docker-compose를 사용한 build가 불가능하다.

   > (credentials 를 생성할 때 `Username`에 sirs라고 등록했어야 함)





## New node

"Manage Jenkins" > "System Configuration" > "Nodes" > `+ New node`

- Permanent Agent

  Jenkins에서 빌드 작업을 지속적으로 처리하기 위해 설정하는 에이전트 유형임을 명시

  이 에이전트가 지속적으로 존재하며, 다양한 빌드 작업에 재사용될 수 있음을 의미한다.



### 설정

- **Number of executors**

  해당 node에서 동시에 실행할 수 있는 build작업의 최대 개수

- **Remote root directory**

  stage서버에서 Jenkins 관련 파일(빌드 로그, 아티팩트 등)을 저장할 dir의 경로를 지정

  > 예시:  `/var/jenkins/agent` 로 입력하고자 한다면
  >
  > ```
  > $ sudo mkdir /var/jenkins					# 경로 생성
  > $ sudo chown username:username /var/jenkins -R		# 권한 부여
  > ```

- **Labels**

  node에 할당할 label. 

  node의 용도나 지원하는 환경을 표시한다.

  > `linux`, `docker`, `stage` 또는 아예 이름처럼 `project_stage_server`

  pipeline 구성 시 agent를 지정할 때 이름이 아닌 lable기준으로 지정하기 때문에 이를 고려해서 labeling 하기.

- **Usage**

  해당 node가 어떤 빌드 작업에 사용될지를 결정

  - use this node as much as possible

    label과 관계없이 모든 종류의 build 작업을 실행하는 node라는것을 명시

  - only build jobs with label expressions matching this node

    Jenkins가 오직 이 node에 할당된 label과 일치하는 표현식을 가진 작업들만 이 node에서 실행

- **Launch method**

  Jenkins 마스터가 노드를 어떻게 시작할지를 결정한다.

  - Launch agent by connection it to the controller

    이 방식은 agent(node)가 액티브하게 Jenkins controller(master)에 연결을 시도한다.

    사용자는 Jenkins controller에서 제공하는 JNLP 파일을 다운로드하여 에이전트 컴퓨터에서 실행함으로써 agent를 시작하게 된다.

  - **Launch agent via SSH**

    Jenkins 컨트롤러가 SSH를 통해 노드에 원격으로 접속하여 agent 프로세스를 시작한다.

    - Host

      agent node의 IP주소

    - Credentials

      Jenkins controller가 agent에 접속할 때 사용할 인증 정보(사용자 이름 및 비밀번호 또는 SSH 키)를 선택. 

      Jenkins는 저장된 Credentials 목록에서 선택할 수 있으며, 이를 통해 안전한 방식으로 접속 정보를 관리할 수 있다.

    - Host Key Verification Strategy

      SSH 접속 시 호스트 키 검증 방식을 설정

      - Known hosts file Verification Strategy

        Jenkins(master) 서버의 `known_hosts` 파일에 저장된 호스트 키 정보를 사용하여 에이전트의 호스트 키를 검증

      - Manually provided key Verification strategy

        jenkins 설정 과정에서 agent 호스트키를 수동으로 입력

        보안상 안전한 방법이지만, 호스트 키가 변경될 경우 Jenkins 설정도 업데이트해야 하는 번거로움이 있음

        > HOST KEY를 입력해야 한다. 공개 키(public key)로 하면 연결 안됨
        >
        > - host key 확인 방법 (`ecdsa` 형식의 host key 확인. `rsa`형식의 host key는 Manually provided key Verification strategy 의 입력 알고리즘 조건에 맞지 않음)
        >
        >   ```
        >   $ ssh-keyscan -t ecdsa 192.168.110.104
        >   ```
        >
        >   ```
        >   # 192.168.110.104:22 SSH-2.0-OpenSSH_7.6p1 Ubuntu-4ubuntu0.7
        >   192.168.110.104 ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBFPNY+H3v54UR4Cv/xsg8Z9KRN2seQ1L+NqJNh+QkZMupYAvzcGzmSRYLyo7lZskJYTMROgTF5u3bmK7FQ0d+5Q=
        >   ```
        >
        >   여기서 
        >
        >   ```
        >   ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBFPNY+H3v54UR4Cv/xsg8Z9KRN2seQ1L+NqJNh+QkZMupYAvzcGzmSRYLyo7lZskJYTMROgTF5u3bmK7FQ0d+5Q=
        >   ```
        >
        >   이 부분이 host key임
        >
        > - 만일 `ecdsa` 형식의 host key가 없다면, 생성하기
        >
        >   ```
        >   $ ssh-keygen -t ecdsa -b 256
        >   ```

      - Manually trusted key verification strategy

        agent에 처음 접속할 때 호스트 키를 수동으로 검증하고 신뢰할지 결정하는 과정을 포함한다. 

        이 옵션을 선택하면, 처음 접속 시 Jenkins 사용자는 호스트 키가 신뢰할 수 있는지를 수동으로 확인하고 승인해야 한다.

        - require manual verification of inital connection

          처음 접속 시 호스트 키를 수동으로 검증하고 신뢰하는 과정이 추가된다.

      - Non verifying Verification strategy

         SSH 접속 시 호스트 키 검증 과정을 생략

    - **advance option**

      - `JavaPath`

        java 실팽 파일의 경로를 지정

        ```
        $ which java
        ```

        위 명령어로 위치를 알 수 있다.

      - `JVM Options`

        Jenkins agent를 시작할 때 Java 가상 머신(JVM)에 전달할 추가 옵션을 지정

        메모리 할당량을 조정하거나 시스템 속성을 설정하는 등의 JVM 관련 설정을 이곳에 추가할 수 있다.

      - `refix Start Agent Command`

        agent 시작 명령어 앞에 추가할 커맨드 또는 스크립트를 지정

        agent 실행 전에 필요한 사전 조건을 설정하거나 초기화 작업을 수행할 수 있다.

      - `Suffix Start Agent Command`

        agent 시작 명령어 뒤에 추가할 커맨드 또는 스크립트를 지정

        agent 실행 후 추가적인 작업이 필요할 때 사용된다.

      - `Connection Timeout in Seconds`

         SSH 접속 시도 시 연결이 성립되기를 기다리는 최대 시간(초)을 지정

      - `Maximum Number of Retries`

        SSH 접속 시도가 실패할 경우 재시도할 최대 횟수를 지정

        default: 10회

      - `Seconds To Wait Between Retries`

        재접속 시도 간 대기할 시간(초)을 지정

        재시도 간의 딜레이를 추가하여 네트워크 문제 등이 해결될 시간을 제공할때 사용한다.

      - `Use TCP_NODELAY flag on the SSH connection`

        SSH 연결 시 TCP_NODELAY 플래그를 사용하는 option.

        네트워크 지연을 줄이고 데이터 패킷의 즉각적인 전송을 가능하게 하여 성능을 개선할 수 있다.

      - `Remoting Work directory`

        enkins 에이전트의 작업 dir을 지정한다.

        agent가 작업을 수행하면서 사용할 임시 파일이나 캐시 등을 저장하는 위치로 사용된다.

        주로 pipeline의 build를 수행하기 위해 git clone을 하여 code를 가져올때 사용한다.

        > 예시  `/var/jenkins/agent/workdir`

        Remote root directory 와의 차이점: Remote root directory는 빌드 아티팩트, 로그 파일, 임시 파일 등을 저장

- **Availability**

  노드가 언제 Jenkins 작업을 위해 사용될 수 있는지를 결정

  - Keep this agent online as much as possible

     Jenkins는 해당 node를 가능한 한 항상 온라인 상태로 유지하려고 시도한다.

  - Bring this agent online according to a schedule

    노드를 예약된 일정에 따라 온라인 및 오프라인 상태로 전환하도록 설정한다.

    - Startup Schedule

      node를 온라인 상태로 전환할 시간을 크론(Cron) 표현식으로 지정한다.

    - Scheduled Uptime

      node를 온라인 상태 전화 이후, 계속해서 유지할 시간을 지정한다. (단위: 분)

    - Keep online while builds are running

      build가 진행 중인 동안 Scheduled Uptime 시간을 넘어가도라도, node를 온라인 상태로 유지

  - Bring this agent online when in demand, and take offline when idle

    노드를 필요할 때만 온라인 상태로 전환하고, 일정 시간 동안 사용되지 않으면 자동으로 오프라인 상태로 전환하도록 설정

    - In demand delay

      작업이 할당되고 나서 노드를 온라인 상태로 전환하기까지의 지연 시간을 지정 (단위: 분)

    - Idel delay

      노드가 마지막 작업을 완료한 후 오프라인 상태로 전환되기까지 대기하는 시간을 지정 (단위: 분)

  > `offline`: Jenkins 관점에서 해당 노드가 작업을 받지 않도록 설정된 상태

- **Node Properties**

  - Disable deferred wipeout on this node

    선택한 노드에 대해 `deferred wipeout` 기능을 비활성화하고 즉시 삭제를 수행

    `deferred wipeout`: 작업 공간을 정리하여 파일 시스템의 부하를 줄이는 기능

  - Disk Space Monitoring Thresholds

    노드의 디스크 공간 사용 상황을 모니터링하고, 설정된 임계값에 도달하면 경고를 발생시키는 기능

    경고 알람은 jenkins에서 설정한 알람으로 받을 수 있다.

  - Environment variables

    노드별로 설정할 수 있는 환경 변수

    빌드 과정에서 사용될 수 있는 다양한 환경 설정값(예: PATH 환경 변수, 사용자 정의 변수 등)을 지정할 수 있다.

  - Tool Locations

    노드에서 사용되는 도구들(JDK, Git, Maven 등)의 위치를 지정할 수 있다.

    같은 도구가 여러 version이 설치되어 있어 하나의 version만 명시해야 하는 경우 또는

    도구가 표준 경로가 아닌 곳에 설치된 경우에 유용하다.

