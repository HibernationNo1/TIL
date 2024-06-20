# Master Node

각 프로젝트의 CI/CD, monitering을 관리하는 Master Node를 구성하는 방법을 기록한 README입니다.

**사용하는 도구**

- **grafana**: 각 server 또는 service의 상태 또는 요청 수행시간을 모니터링합니다.
- **jenkins**: 각 project의 CI/CD를 관리합니다.





#### install

**1. install java** 

```
$ sudo apt update
$ sudo apt install openjdk-11-jdk
```

확인

```
$ java -version
```

**2. install docker, docker-compose**

- docker

- docker-compose

  ```
  $ sudo curl -L https://github.com/docker/compose/releases/latest/download/docker-compose-$(uname -s)-$(uname -m) -o /usr/local/bin/docker-compose
  ```

  ```
  $ sudo chmod +x /usr/local/bin/docker-compose
  ```

  check

  ```
  $ docker-compose --version
  ```


**3. start command**

```
$ set_master_cluster.sh
```





## initial setting

`start command`에 의해 모든 tool이 실행된 상태에서 세팅하는 방법입니다.

### Jenkins

**1. set jenkins**

1. `http://{master_node_IP}:8081/` 접속

   Administrator password: docker container의 log를 통해 확인 가능

   ```
   $ docker logs enliple_jenkins
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

2. plugin 설치

   접속 후 `Select plugins to install` 선택

   - `ssh-agent`: ssh-Credentials를 사용하기 위해 반드시 설치 필요

   - `GitLab`: git-lab 사용시 반드시 필요

     > Select plugins to install 단계에서 `ssh-agent` 설치 시 제대로 동작하지 않는 문제점 확인
     >
     > `ssh-agent` 는 jenkins login 후  jenkins관리 > Plugins > Available plugins > `ssh-agent` 검색 과정으로 설치하자

3. Create First Admin User (모든 항목이 필수)

   - 계정명: `enliple`
   - 암호: `ai1234`
   - 이름: `AI_lab`
   - 이메일 주소: `teno@enliple.com`

4. Instance Configuration

   jenkins URL 결정

   `http://{jenkins가 설치된 server의 IP}:{jenkins 사용 port}/{route path}`

   > 예시: `http://192.168.110.103:8081/`

   항상 defualt로 합니다.

**2. add credentails**

추가해야하는 credentials list

- GitLab의 계정에 대한 **API token credentials** (본인 계정)
- 각 프로젝트별 agent node에 대한 **ssh credentials**

> credentails을 추가하는 방법은 notion에서 확인



**3. add node**

추가해야하는 node

- 각 프로젝트별 build 및 test를 위한 stage agent
- 각 프로젝트별 deploy를 위한 live agent

> node를 추가하는 방법은 notion에서 확인



**4. add pipeline**

추가해야하는 pipeline

- 각 프로젝트별 CI/CD를 위한 pipeline

> pipeline을 추가하고 구성하는 추가하는 방법은 notion에서 확인





### Grafana

**1. connect grafana**

- `localhost:3000` 으로 접속

  최초 ID/PW : `admin`/`admin`



**2. Add new connection**

추가해야하는 connection

- 각 worker node에 대한 connection (port: 9090)
- 각 프로젝트가 배포되는 live server에 대한 connection (port: proejct마다 prometheus의 설정 확인)

> connection을 추가하는 방법은 notion에서 확인



**3. Add or import dashboard**

- import bash board

  - Node Exporter: CPU 사용량, 메모리 사용량, 디스크 I/O,네트워크 통계, 시스템 로드와 같은 중요한 서버 수준의 정보를 모니터링을 가능하게 하는 도구

    (ID: 1860)

  - NVIDIA_DCGM Exporter:  GPU 사용량, 메모리 사용량과 같이 서버 수준의 GPU 정보를 모니터링을 가능하게 하는 도구

    (ID: 12239)

  - hwmon Exporter: 리눅스에서 하드웨어 센서(예: 온도, 전압, 팬 속도)의 정보를 읽기 위한 인터페이스를 제공하는 도구

    (ID: 12950)

- add dashboard

> dashboard를 추가하는 방법은 notion에서 확인



**4. Set Alert**

각 dashboard에 대한 알람 설정 (필요시)