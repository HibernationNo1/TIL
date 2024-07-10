#!/bin/bash
CONTAINER_PORT=$1

# predict POST 요청
checkAPI() {
  local port=$1
  local img=$3

  response=$(curl -s -w "%{http_code}" -X POST \
    -H "Content-Type:application/json" \
    -d \
    "{\"file_path\": \"$img\"
    }"\
    "http://localhost:$port/api/predict")

  status_code=$(echo "$response" | tail -n 1)


  # 응답 상태 코드가 200이 아닌 경우
  if [ "$status_code" -ne 200 ]; then
    echo "Error: The request failed with status code $status_code"
    echo "Response Body: $response"
    exit 1    # 1 상태로 종료하면 비정상종료임을 의미함
  fi

  echo "The request 'create banner' was successful with status code $status_code"
  echo "Response Body: $response"
}

checkAPI $CONTAINER_PORT /sample/sample_1.jpg
checkAPI $CONTAINER_PORT /sample/sample_2.jpg
checkAPI $CONTAINER_PORT /sample/sample_3.jpg

# sh test_code/test.sh 20001
# sh test_code/test.sh 20000