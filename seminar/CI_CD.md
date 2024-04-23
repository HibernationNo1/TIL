

# CI CD

- **CI** :continuous integration

  지속적 통합

  - 동작: 소스 코드 저장소에 새로운 변경사항이 푸시될 때마다 자동으로 빌드와 테스트, 통합을 실행
  - 목적: 개발 초기 단계에서 문제를 식별하고 해결할 수 있도록 한다.

- **CD**: continuous deployment

  지속적인 배포

  - 동작: 테스트를 통과한 코드를 자동으로 stage 또는 live환경에 배포
  - 목적: 소프트웨어 배포 프로세스를 자동화한다.

![](https://github.com/HibernationNo1/TIL/blob/master/seminar/images/CI_CD/CI_CD_1.png?raw=true)

- **Build**

  현재 AI연구소는 대부분의 server를 구동할 때 docker-compose 명령어를 사용한다.

  build 과정에서는, docker compose와 같은 명령어를 사용하도록 설정하여 code가 동작하도록 하는 과정이 이루어진다.

  1. git clone
  2. git checkout
  3. Run command (docker compose)

- **Test**

  동작중인 service가 의도한대로 제대로 동작하는지 확인하는 과정이다.

  image검수는 DB로부터 data를 가져와 처리하고, pomission은 request로부터 data를 받아 처리한다.

  이와 같이 각각의 프로젝트는 그 목적에 따라 data가 필요한데, 이러한 data를 임의로 구성해서 build된 service에 request를 보내는 방식 등으로 test를 진행한다.

- **Merge**

  Test 동작이 문제 없이 완료되었다면, branch 끼리 merge하는 과정이 이루어진다.

  **`stage`** branch에 대해 build와 test가 문제 없이 완료된다면, **`live`** branch 에 자동으로 merge되도록 구성할 수 있다.

  이를 통해 제대로 동작하지 않는 code가 live branch로 merge되는 것을 예방할 수 있으며, branch의 관리를 철저하고 용이하게 할 수 있다.

  > 이 기능은 GitLab Webhooks 라는 기능을 사용해야 하는데, 현재 GitLab이 설치된 Main Nas가 DMZ 네트워크에 소속되어 있고
  >
  > merge 기능을 활성화 하기 위한 jenkins의 master node를 내부 네트워크에 소속된 서버에 설치했기 때문에
  >
  > 사용이 불가능한 상태이다.

- **Deploy**

  CI 과정이 문제 없이 완료되었다면, 해당 code를 배포하는 과정이다.

  이 과정에서 live server에서 **Build**와 **Test**를 한 번에 수행한다.

  이를 통해 아래와 같은 장점을 가지게 된다.

  - server에 code가 유실되었을 경우 빠르게 복구할 수 있다.
  - 이미 동작하는 code를 배포하기 때문에 안정적이고 빠르게 배포를 완료할 수 있다.

보통 CI과정은 stage server에서 수행하고, CD과정은 live server에서 수행한다.

**CI/CD의 장점**

- 무중단 배포를 구성해놓았다면 Build - Test - Merge - Deploy 과정을 commit 이 이루어질때마다 자동적으로 수행할 수 있게 구성할 수 있다.
- 커다란 프로젝트(다수의 사람이 개발에 참여하는)인 경우, 여러 branch에 의해 merge되는 과정에서도 꼬임 없이 안정적인 개발이 가능하다.
- 설정된 Git 리포지토리의 변경 사항을 감지하고 자동으로 CI/CD가 수행되도록 적용하여 지속적으로 동기화를 유지할 수 있다.
- CI 에 강력한 도구 따로, CD에 강력한 도구 따로 구성할 수 있다.

## **가장 많이 쓰이는 CI/CD 도구 5가지**

### **1. Buddy**

- 사용자 친화적인 UI를 제공하며, 설정이 쉬워 개발자들도 접근하기 편하다.
- 실행 속도가 다른 CI/CD 도구보다 빠르다.
- AWS, Google, DigitalOcean, Azure, Shopify, WordPress 과 같은 여러 cloud 서비스와 통합이 가능하다.
- 간단한 프로젝트에 용이하며, 대규모 개발이 필요한 프로젝트에는 제한적.

![](https://github.com/HibernationNo1/TIL/blob/master/seminar/images/CI_CD/buddy_1.jpg?raw=true)

### **2. Jenkins**

- 하나의 Master Node와 다수의 Worker Node를 구성하는 cluster를 구축하여 여러 프로젝트에 관한 CI/CD pipeline을 한 번에 관리한다.
- Linux, Mac OS, Windows 를 모두 지원한다.
- 인증을 구성해야만 GitLab, Worker Node와 통합할 수 있기 때문에 보안적이다.
- 구성이 까다롭지만 그만큼 디테일한 작업을 제어할 수 있기 때문에 거의 모든 종류의 프로젝트에 맞게 조정할 수 있다.
- 오픈 소스 CI/CD 도구이며, 확장 가능한 플러그인을 검색하고 설치하는 방식을 지원하기 때문에 많이 알수록 더욱 강력하게 사용할 수 있다.

![](https://github.com/HibernationNo1/TIL/blob/master/seminar/images/CI_CD/jenkins-view.png?raw=true)

### **3. Gitlab CI**

- GitLab 리포지토리 관리 시스템에 내장된 CI/CD 도구.
- worker node로 Docker의 container, kubernetes의 pod 와 같은 환경을 지정할 수 있다.
- pipeline구성 파일 외의 다른 동작(pipeline의 동시 실행 방지)을 제어할 수 없다.
- GitLab 외의 다른 코드 저장소와의 통합이 제한적임.
- custom 구성에 제한적인 부분이 많다.

![](https://github.com/HibernationNo1/TIL/blob/master/seminar/images/CI_CD/gitlab_CICD.png?raw=true)

### **4. Github Action**

- GitHub 리포지토리 관리 시스템에 내장된 CI/CD 도구.
- 다양한 GitHub 이벤트(예: 푸시, 풀 요청, 이슈 코멘트 등)에 따라 워크플로우를 자동으로 트리거할 수 있다.
- 매우 다양한 워크플로우를 쉽게 구성할 수 있으며, custom action을 생성하여 공유할 수도 있다.
- GitHub의 다른 기능들(Full request, issue tracker 등)과 원활하게 통합되어 프로젝트 관리가 용이하다.
- 무료로 사용하기에 제한적인 사항이 많음...

![](https://github.com/HibernationNo1/TIL/blob/master/seminar/images/CI_CD/github_CICD.png?raw=true)

### **5. ArgoCD**

- Kubernetes를 위한 CI/CD 도구
- 여러 Kubernetes 클러스터를 중앙에서 관리할 수 있다. (jenkins와 비슷)
- CLI 를 제공하여 ArgoCD의 다양한 기능과 설정을 직접 조작하고 관리할 수 있어 구성 방법에 제한이 없다. (나만의 자동화, 모니터링 가능)
- 디테일한 작업을 제어할 수 있기 때문에 거의 모든 종류의 프로젝트에 맞게 조정할 수 있다.
- 현재 클러스터에 배포된 애플리케이션의 목록, 각 애플리케이션의 상태, 최근 동기화 정보 등을 한 눈에 볼 수 있는 web UI를 제공한다.
- grafana와 연동되어 cluster 모니터링이 가능하다.

![](https://github.com/HibernationNo1/TIL/blob/master/seminar/images/CI_CD/argoCD.png?raw=true)