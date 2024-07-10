#!/bin/bash

# 환경변수가 설정되지 않았을 경우 기본값을 공백으로 설정
CONTAINER_NAME=${CONTAINER_NAME:-}

# 파일 경로 생성
MASTER_PID_FILE="logs/${CONTAINER_NAME}/gunicorn_master.pid"
WORKER_PID_FILE="logs/${CONTAINER_NAME}/gunicorn_worker.pid"

# 마스터 프로세스 종료
if [ -f "$MASTER_PID_FILE" ]; then
    kill -9 `cat "$MASTER_PID_FILE"`
    rm -rf "$MASTER_PID_FILE"
else
    echo "Master PID file not found: $MASTER_PID_FILE"
fi

# 워커 프로세스 종료
if [ -f "$WORKER_PID_FILE" ]; then
    kill -9 `cat "$WORKER_PID_FILE"`
    rm -rf "$WORKER_PID_FILE"
else
    echo "Worker PID file not found: $WORKER_PID_FILE"
fi