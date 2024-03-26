# Credentials

plugin  중에 `ssh-agent` 설치가 필수



## add Credentials

"Manage Jenkins" > "Security" > "Credentials" 

- `store`: Credentials이 저장되는 위치  Global, Project 두 종류가 있음

  > Global: 시스템 전체에 적용됨
  >
  > Project: 프로젝트(또는 dir)에 국한되어 적용됨

  - **`Add Domain`**: Domain을 생성하여, 특정 조건이나 범위를 가지는 Credentials 그룹을 정의

- `domains`: Store 내에서 Credentials을 더 세분화하여 그룹화하는 단위

  - **`add Credentials`**: Store 또는 Domain 내에 새로운 Credentials을 추가





#### Username with password

사용자 이름과 비밀번호를 함께 저장하는 데 사용

Jenkins에서 소프트웨어 저장소, 데이터베이스, API, 원격 서버 접속 등 다양한 외부 시스템에 접근할 때 사용된다.



#### GitLab API token

GitLab에서 제공하는 개인 액세스 토큰(PAT)

GitLab과의 통신을 위해 사용 

GitLab 프로젝트 내의 코드를 체크아웃하거나, merge request를 생성하고 관리하는 등의 작업에 사용된다.

- Scope

  token이 접근할 수 있는 GitLab API의 범위를 정의

  - `Global(jenkins, nodes, items, all child items, etc)`  

    enkins의 모든 작업(job), 노드(nodes), 아이템(items), 그리고 하위 아이템들에서 해당 자격 증명을 참조할 수 있다는 의미

  - `system(jenkins and nodes only)`

    주로 Jenkins 자체의 설정이나 시스템 레벨의 작업에 사용되며, 일반적인 빌드 작업이나 파이프라인에서는 사용할 수 없음

- API token

  GitLab에서 제공하는 개인 액세스 토큰(PAT)

  > gitlab에서
  >
  > 사용자 설정 > 좌측 탭 중 `Access Tokens` > api 선택 후 만료날짜, 이름 결정 > `Create personal access token` 클릭
  >
  > **Your New Personal Access Token**  이 새로 만들어진 token이다.

- ID

  job 및 기타 구성에서 자격 증명을 식별하는 내부 고유 ID



#### SSH Username with private key

사용자 이름과 해당 사용자의 개인 키(Private Key)를 저장

개인 키와 함께 사용되는 공개 키(Public Key)는 대상 시스템에 등록되어야 한다.

- Scope

- ID

  > 예시: `Jenkins-agent-ssh`

  Credentials의 고유 식별자

  자동으로 생성될 수 있지만, 사용자가 직접 명확한 식별을 위해 지정할 경우 명시

  > `An internal error occurred during form field validation (HTTP 403). Please reload the page and if the problem persists, ask the administrator for help.` 가 뜰 시 새로고침

- Username

  SSH 접속에 사용될 사용자 이름을 입력

  > `ssh {username}@{IP}` 에서 username부분

- Treat username as secret

  사용자 이름도 비밀번호나 개인 키처럼 기밀 정보로 취급하여 보관하는 option

- Private Key 

  SSH 접속에 사용될 개인 키를 입력하는 부분

  1. master에서 slave 로 접속할 때 사용하려면, master의 개인 키를 입력해야 한다.

  2. id_rsa.pub 이 아닌, id_rsa의 내용을 사용해야 한다.

  3. 반드시 전체 내용을 복사해야 한다. —-BEGIN 내용 포함

     ```
     ----BEGIN OPENSSH PRIVATE KEY-----
     ...
     -----END OPENSSH PRIVATE KEY-----
     ```

  - Enter directly

    텍스트 필드에 개인 키를 직접 붙여넣을 수 있는 option

- Passphrase

   개인 키에 추가적인 보안 계층으로 패스프레이즈가 설정되어 있는 경우, 여기에 그 패스프레이즈를 입력

  패스프레이즈 없이 키를 사용하는 경우 이 필드는 비워 둘 수 있다.





