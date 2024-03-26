# pipeline 관리

Dashboard > {pipeline_name}

### Status 

현재 pipeline의 상태, 과거 build결과 등을 확인할 수 있다.





### {build_number} 

Dashboard > {pipeline_name} > {build_number}

pipeline으로 build를 수행하면 `#1`, `#2`와 같이 build가 수행된 순서대로 build_number가 할당된다. 

해당 build로 들어가면 build에 대한 결과를 확인하는 dashboard를 확인할 수 있다.

- **Status**

  빌드의 상태(성공, 실패, 진행 중 등)를 요약하여 확인할 수 있다.

- **Changes**

  이 빌드와 이전 빌드 사이에 발생한 소스 코드 변경 사항을 나열한다.

  소스 코드 관리 시스템(SCM)과 통합할 수 있다.

- **Console Output**

  빌드 프로세스 동안 생성된 콘솔 출력을 보여준다.

  오류 메시지, 경고, 사용자 스크립트의 출력 등이 포함된다.

- **Edit Build Information**

  빌드에 대한 정보(빌드 이름, 설명 등)를 편집할 수 있다.

- **timings**

  빌드의 각 단계가 실행된 시간을 확인할 수 있다.

- **Pipeline Overview**

  파이프라인의 전체적인 흐름과 각 스테이지의 상태를 graph형식으로 보여준다

- **Pipeline console**

  파이프라인 스크립트의 실행 동안 생성된 콘솔 출력을 특화된 형태로 보여준다.

- **Restart from Stage**

  파이프라인의 특정 스테이지부터 재실행할 수 있는 기능을 제공한다.

  실패한 스테이지부터 빌드를 다시 시작하려는 경우에 유용하다.

- **Replay**

  이전에 실행된 파이프라인 빌드를 같은 매개변수로 재실행한다.

  파이프라인 스크립트를 수정하여 테스트하고자 할 때 유용하다.

- **Pipeline Steps**

  파이프라인의 각 단계와 해당 단계에서 실행된 명령어 및 작업의 세부 정보를 확인할 수 있다.

- **Workspaces**

  빌드가 실행된 작업 공간(워크스페이스)에 대한 접근을 제공한다.

  빌드에 의해 생성되거나 사용된 파일을 확인할 수 있다.

