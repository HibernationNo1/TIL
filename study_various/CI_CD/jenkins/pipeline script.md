# pipeline script

실제 작업 프로세스를 정의하는 Groovy 기반 스크립트

언적 또는 스크립트 방식으로 작성할 수 있으며, 파이프라인의 각 단계, 실행 환경, 조건 분기 등을 코드로 명시한다.

pipeline script 기본 예시

```groovy
pipeline {
    agent { label 'test' } 

    stages {
    	stage('Checkout Code') { 	
    		steps {
   			....
            }
   
        }
        
        stage('Build') { 
            steps {
			....
            }
        }
    ....
    }
    
    
    post {
        always {
            ...
        }
    }
    
}
```

### agent

agent를 지정한다

- 전체 pipeline에 대한 agent 적용

  ```
  pipeline {
  	agent { label 'test' } 
  	...
  ```

- 각 stage에 대한 개별 agent 적용

  ```
  pipeline {
  	agent none  // 전체 파이프라인에 대한 기본 에이전트를 지정하지 않음
  	stages {
          stage('Build') {
              agent { label 'build-agent' }
              steps { ... }
          }
          stage('Test') {
              agent { label 'test-agent' }
              steps { ... }
          }
      }
      ...
  ```

  전체 pipeline에 대한 agent 적용 후, 각 stage에 대한 개별 agent를 적용하면

  최종적으론 각 stage에 적용된 agent에서 각 stage 동작이 수행된다.

- docker 사용

  ```
  agent {
      label 'node_1' // 이 스테이지를 실행할 에이전트 노드의 라벨 지정
      docker {
          image 'node:12-alpine' 					// 사용할 Docker 이미지 지정
          args '-v /home/jenkins:/home/jenkins' 	// 필요한 경우 Docker 실행 옵션 추가
      }
  }
  ```

- none 지정

  전체 파이프라인에 대한 기본 에이전트를 지정하지 않을 경우에 사용

  





### stages

```
stages {
    stage('stage_name') 
    ...
```

- `stage_name`: 사용자 마음대로 naming가능



**stage**

stages 내부에 정의된, 동작을 구성하는 부분

```
stages {
    stage('Deploy') {
        agent { label 'build-agent' }
        when { branch 'master' }
        environment {
            ...
        }
        steps {
            echo 'Deploying...'
            ...
        }
        post {
            ...
        }
    }
    ...
}
```

- `agent`: 현재 스테이지를 실행할 에이전트를 지정한다.  (필수 아님)
- `when`: 스테이지 실행 여부를 결정하는 조건을 지정한다. (필수 아님)
- `environment`: 스테이지에서 사용할 환경 변수를 지정한다. (필수 아님)
- `steps`: 실제 실행할 작업 명령을 정의한다. (필수)
- `post`: 스테이지 실행 후 실행할 조건별 작업을 정의한다. (필수 아님)



### post

파이프라인의 `stages` 또는 `stages.stage.steps` 후에 실행되는 단계를 정의하는 섹션

- **`always`**: 파이프라인이나 스테이지의 실행 결과와 상관없이 항상 실행한다. 

  성공, 실패, 중단 등 모든 상황에서 수행할 작업을 정의할 때 사용

- **`success`**: 파이프라인이나 스테이지가 성공적으로 완료되었을 때만 실행한다. 

  성공적인 빌드 후 정리 작업이나 알림을 보내는 등의 작업을 정의할 때 사용

- **`failure`**: 파이프라인이나 스테이지가 실패했을 때만 실행한다. 

  실패한 경우에만 수행해야 하는 작업, 예를 들어 에러 로그 수집, 실패 알림 전송 등을 정의할 때 사용

- **`unstable`**: 파이프라인이나 스테이지의 실행 결과가 불안정(unstable)한 경우 실행한다. 

  테스트 실패와 같이 빌드가 성공적으로 완료되었으나, 일부 경고나 문제가 보고된 경우에 해당된다.

- **`changed`**: 이전 빌드 또는 스테이지와 비교했을 때 실행 결과가 변경되었을 경우 실행한다. 

  성공에서 실패로, 또는 실패에서 성공으로 상태가 변화했을 때 유용하게 사용할 수 있다.

- **`aborted`**: 파이프라인이나 스테이지가 중단되었을 때 실행한다. 

  사용자에 의해 빌드가 취소되거나 시스템 문제로 인해 중단된 경우에 해당하는 작업을 정의할 때 사용.

- **`fixed`**: 이전에 실패했던 파이프라인이나 스테이지가 현재 빌드에서 성공적으로 완료되었을 때 실행한다.

- **`regression`**: 이전 빌드가 성공했으나 현재 빌드에서 실패한 경우 실행한다. 



### 예시

```
pipeline {
	agent { label 'stage' }		// pipeline을 실행할 node 지정.

    stages {
    	stage('Checkout Code') { 		// checkout code
    	    // work_space에 해당 project가 없는 경우: work_space/{pipeline_name}/ 의 위치에 clone.
    		// 이미 work_space에 해당 project가 있는 경우: 명시된 branch로 checkout
            steps {
                git url: 'ssh://git@192.168.0.101:30001/fusion_research/utils/teno_test.git', branch: 'stage'
            }
        }
        
        stage('Build') { 
            steps {
                sh 'docker network create test_network || true'		// 이미 존재하는 경우를 고려하여 오류 무시.
                sh 'docker-compose -f docker/docker-compose.yml up -d'
            }
        }
        
        stage('Test') { 
            steps {
				// test cript 실행
                sh 'sh sh/test_health_check.sh'
                sh 'sh sh/test_curl_1.sh'
                sh 'sh sh/test_curl_raise_error.sh'
            }
        }       
        
        stage('Deploy') { 
        	agent { label 'live' }
            steps {
                git url: 'ssh://git@192.168.0.101:30001/fusion_research/utils/teno_test.git', branch: 'live'
				sh 'docker network create test_network || true'	
				sh 'docker-compose -f docker/docker-compose.yml up -d'
				
                sh 'sh sh/test_health_check.sh'
                sh 'sh sh/test_curl_1.sh'
                sh 'sh sh/test_curl_raise_error.sh'
            }
        }
    }
    
    post {
        always {
        	// Docker container, nerwork, image 자원을 정리
            sh 'docker-compose -f docker/docker-compose.yml down --rmi all' 
        }
    }
    
}
```





