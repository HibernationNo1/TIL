#!/bin/bash

echo "Waiting for 10 seconds..."
sleep 10

### 1. 각 tool이 제대로 build되고 online상태인지 확인하기 위한 script
# http의 response status-code 를 검사하는 함수 정의
checkHttpResponseCode() {
  local url=$1
  local serviceName=$2
  responseCode=$(curl -o /dev/null -s -w "%{http_code}" "$url")
  
  if [ "$responseCode" != "200" ]; then
    # HTTP response code가 200이 아닌 경우 스크립트 종료 코드를 1로 설정 
    echo "Error: $serviceName HTTP response code is $responseCode"
    exit 1
  else
    echo "$serviceName is online with HTTP response code $responseCode"
  fi
}

# Prometheus에 대한 health check
checkHttpResponseCode 'http://localhost:9092/-/healthy' 'Prometheus'

# Nginx에 대한 health check
checkHttpResponseCode 'http://localhost:8089' 'Nginx'


### 2. 특정 process가 제대로 실행중인지 확인하는 script
checkPsauxGrepCode() {
  # "python health_check.py" 와 같이 띄어쓰기는 하나의 local 변수로 받기에서 error발생
  local script_type=$1
  local process_name=$2

  # 프로세스 검색 및 그 결과의 라인 수 계산
  process_count=$(ps -aux | grep "$script_type $process_name" | grep -v grep | wc -l)

  if [ "$process_count" -eq 0 ]; then
      # process가 실행 중이지 않으면 스크립트 종료 코드를 1로 설정
      echo "Error: Process '$process_name' is not running."
      exit 1
  else
      echo "Success: Process '$process_name' is running."
  fi
}

checkPsauxGrepCode 'python' 'health_check.py'

# sh test_code/health_check.sh