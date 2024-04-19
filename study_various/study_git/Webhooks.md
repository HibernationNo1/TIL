# Webhooks

GitHub repository에서 발생하는 특정 이벤트(예: code push, add pull request, issue comments 등)에 대해 사용자 지정 callback URL로 HTTP POST 요청을 자동으로 보내는 메커니즘이다.

이를 통해 repository에서 발생한 이벤트에 대한 알림을 받거나, 해당 이벤트를 기반으로 외부 시스템에서 자동화된 작업을 실행할 수 있다.



### setting

#### URL

외부 시스템 서버의 HTTP 엔드포인트 URL

**url 구성**

보통 url은 webhooks을 사용하고자 하는 tool에서 제공해준다.

 제공받은 url이 `http://192.168.110.18:8081/project/pipeline_name` 과 같이 내부 IP주소(192.168.~~)인 경우, 이를 입력할 시 `Url is blocked: Requests to the local network are not allowed` 라는 error 가 발생한다. 

외부 시스템 서버가 내부 네트워크에 위치했다면, url 구성을 변경해야 한다.

1. host 변경

   git-lab이 설치된 PC에서 `/etc/hosts` 파일에 아래 내용 추가

   ```
   192.168.110.18       mypublicdomain.com
   ```

   - `192.168.110.18` : 엔드포인트 URL 에 포함된 내부 IP주소
   - `mypublicdomain.com`: 내부 IP주소로 인식하고자 하는 url

   위와 같이 설정하면 `mypublicdomain.com` 를 `192.168.110.18`으로 인식하게 된다.

2. url 변경

   1번과 같이 host를 변경했다면 url  또한 아래와 같이 변경하여 입력한다.

   ```
   http://mypublicdomain.com:8081/project/pipeline_name
   ```

   

**webhooks을 사용할 수 있는 tool 종류**

- Jenkins

  pipeline의 설정 중 `Build when a change is pushed to GitLab`에서 url을 확인할 수 있다.



#### 그 외 설정

**secret token**

Webhook 요청의 보안을 강화하기 위해 사용

- Jenkins

  pipeline의 설정 중  `Build when a change is pushed to GitLab`의 고급 설정 > `Secret token` 에서 생성할 수 있다.







- **Push events**

  repository에 code가 push될 때마다 해당 URL이 트리거

  ```
  Branch name or widcard pattern to trigger on (leave blank for all)
  
  ```

  - `Build when a change is pushed to GitLab`에서 겹치는 설정이 없는지 확인

- **Tag push events**

  repository에 새로운 tag가 push될 때마다 해당 URL이 트리거

- **Comments**

  issue, merge request 등에 누군가가 코멘트를 추가할 때 해당 URL이 트리거

- **Confidential Comments**

  기밀 issue에 누군가가 코멘트를 추가할 때 해당 URL이 트리거

- **Issues events**

  issue가 create, update, 또는 merge될 때 해당 URL이 트리거

- **Confidential Issues events**

  기밀 issue가 create, update, 또는 merge될 때 해당 URL이 트리거

- **Merge request events**

  merge request가 create, update, 또는 merge될 때 해당 URL이 트리거

  This URL will be triggered when a merge request is created/updated/merged

- **Job events**

  CI/CD 작업(Job)의 상태가 변경될 때 해당 URL이 트리거

  빌드 상태나 테스트 결과에 따른 알림 설정에 사용될 수 있

- **Pipeline events**

  This URL will be triggered when the pipeline status changes

  파이프라인의 상태가 변경될 때 해당 URL이 트리거

  - jenkins의 파이프라인 상태가 변경될때도 적용되나?

- **Wiki Page events**

  위키 페이지가 생성되거나 업데이트될 때 해당 URL이 트리거







