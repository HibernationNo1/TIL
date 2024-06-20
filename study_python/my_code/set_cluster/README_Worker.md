# Worker Node

각 server의 hardware의 상태를 master cluster에게 전송하고 CI의 test를 수행하기 위해 사용되는 Worker Node를 구성하는 방법을 기록한 README입니다.

Worker Node 는 `live worker node`와 `stage worker node` 로 나뉩니다.

- `live worker node` : 실제 service를 실행하고 있는 server(IDC server)
- `stage worker node`: stage server(연구소 내부 server)



**사용하는 도구**

- **prometheus**: server의 상태에 관련된 metrics를 수집합니다.
- **node-exporter**: CPU, Memory, Disk 등의 hardware의 상태 data를 수집합니다.
- **dcgm_exporter**: GPU상태와 관련된 data를 수집합니다.
- **java**: jenkens의 worker(agent) node로 사용하기 위해 설치합니다.





#### install

**1. install java** 

```
$ sudo apt update
$ sudo apt install openjdk-11-jdk
```

확인

```
$ java -version
```

> master cluster에 설치된 java 와 연동이 가능한 version이 설치되어야 함

**2. install docker, docker-compose**

- docker

- docker-compose

  ```
  $ sudo curl -L https://github.com/docker/compose/releases/latest/download/docker-compose-$(uname -s)-$(uname -m) -o /usr/local/bin/docker-compose
  ```

  ```
  $ sudo chmod +x /usr/local/bin/docker-compose
  ```

  check

  ```
  $ docker-compose --version
  ```


**3. start command**

```
$ sh set_worker_cluster.sh
```




