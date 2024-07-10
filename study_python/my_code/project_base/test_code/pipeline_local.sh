#! bin/bash
# local에서 CI pipeline 을 test하기 위한 shell script


# 함수 정의: 명령 실행 후 종료 상태 확인
check_command() {
  "$@"
  local status=$?
  if [ $status -ne 0 ]; then
    echo "Error with $1" >&2
    exit 1
  fi
  return $status
}


# 네트워크 생성
docker network create --subnet=172.200.0.0/20 network_name || true

echo '-----project_1 build and test-----'
check_command docker rm -f project_1 || true
check_command docker-compose -f docker/docker-compose_stage.yml up -d project_1
sleep 5
check_command sh test_code/test.sh 20001

echo '-----project_2 build and test-----'
check_command docker rm -f project_2 || true
check_command docker-compose -f docker/docker-compose_stage.yml up -d project_2
sleep 5
check_command sh test_code/test.sh 20002

echo '-----project_3 build and test-----'
check_command docker rm -f project_3 || true
check_command docker-compose -f docker/docker-compose_stage.yml up -d project_3
sleep 5
check_command sh test_code/test.sh 20003

echo '-----Utils container build and test-----'
check_command docker-compose -f docker/docker-compose_stage.yml up -d nginx_kakao prometheus_kakao health_check_kakao

check_command sh test_code/health_check.sh
check_command sh test_code/test.sh 5004


# sh test_code/pipeline_local.sh 5004