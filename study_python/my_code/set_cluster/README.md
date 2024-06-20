# Cluster

연구소에서 관리하는 모든 server와 project를 관리하기 위해 cluster를 구성하는 repository입니다.

기본적으로 모든 server의 `/workspace` 의 위치에 git clone하여 구성하기를 권장합니다.

Cluster는 1개의 Master Node, N개의 Worker Node로 구성

- **Master Node**: 각 프로젝트의 CI/CD, monitering을 관리

  - **grafana**: 각 server 또는 service의 상태 또는 요청 수행시간을 모니터링
  - **jenkins**: 각 project의 CI/CD를 관리

- **Worker Node**: 각 server의 hardware의 상태를 master cluster에게 전송하고 CI의 test를 수행하기 위해 사용

  - **prometheus**: server의 상태에 관련된 metrics를 수집
  - **node-exporter**: CPU, Memory, Disk 등의 hardware의 상태 data를 수집
  - **dcgm_exporter**: GPU상태와 관련된 data를 수집
  - **java**: jenkens의 worker(agent) node로 사용하기 위해 설치

  Worker Node 는 `live worker node`와 `stage worker node` 로 나뉩니다.

  - `live worker node` : 실제 service를 실행하고 있는 server(IDC server)
  - `stage worker node`: stage server(연구소 내부 server)







#### Node list






#### TODO

현 상황: prometheus와 그 외 exporter를 각각의 node에 설치 후 master node에서 worker node의 prometheus로부터 data를 받는 형식

개선 목표: prometheus를 master node에만 설치, 각각의 worker node에는 exporter만 설치한 후

prometheus의 설정 파일에서 여러 jog을 정의하여 data를 가져온다.

이를 위해 IDC server는 모든 exporter에 대한 port를 접근 가능하도록 방화벽 정책 요청이 필요함



**Warning**

- jenkins docker container를 지우면 그동안 추가한 credential, node 기록이 전부 삭제됨
