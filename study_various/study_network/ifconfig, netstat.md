### ifconfig

interface 구성 모니터링 명렁어

- **install** 

  linux에서 ifconfig명령어가 설치되어 있지 않은 경우 install `net-tools` 

  **sentOS**

  ```
  # sudo yum install net-tools
  ```

  

  **Ubuntu**

  ```
  # sudo apt-get install net-tools
  ```

  



인수가 없는 ifconfig명령어 : 활성화된 interface의 세부 사항을 표시

`ifconfig`

```
$ ifconfig eth0
eth0      Link encap:Ethernet  HWaddr 00:1e:4f:c8:43:fc
          inet addr:192.168.0.6  Bcast:192.168.0.255  Mask:255.255.255.0
          inet6 addr: fe80::b44b:bdb6:2527:6ae9/64 Scope:Link
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
          RX packets:60474 errors:0 dropped:0 overruns:0 frame:0
          TX packets:33463 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000
          RX bytes:43922053 (43.9 MB)  TX bytes:4000460 (4.0 MB)
          Interrupt:21 Memory:fe9e0000-fea00000
    
lo        Link encap:Local Loopback
          inet addr:127.0.0.1  Mask:255.0.0.0
          inet6 addr: ::1/128 Scope:Host
          UP LOOPBACK RUNNING  MTU:65536  Metric:1
          RX packets:2255 errors:0 dropped:0 overruns:0 frame:0
          TX packets:2255 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1
          RX bytes:223063 (223.0 KB)  TX bytes:223063 (223.0 KB)
```

- **[eth0] :** network interface 이름

  > **lo** : localhost의 interface (loofback interface라고도 한다.)

- **[flags] :** 네트워크 카드의 상태 표시

- **[mtu] :** 네트워크 인터페이스의 최대 전송 단위(Maximum Transfer Unit)

- **[inet] :** 네트워크 인터페이스에 할당된 IP 주소

- **[netmask] :** 네트워크 인터페이스에 할당된 넷마스크 주소

- **[broadcast] :** 네트워크 인터페이스에 할당된 브로드캐스트 주소

- **[inet6] :** 네트워크 인터페이스에 할당된 IPv6 주소

- **[prefixlen] :** IP 주소에서 서브 넷 마스크로 사용될 비트 수

- **[scopeid] :** IPv6의 범위. LOOPBACK / LINKLOCAL / SITELOCAL / COMPATv4 / GLOBAL

- **[ether] :** 네트워크 인터페이스의 하드웨어 주소

- **[RX packets] :** 받은 패킷 정보

- **[TX packets] :** 보낸 패킷 정보

- **[collision] :** 충돌된 패킷 수

- **[Interrupt] :** 네트워크 인터페이스가 사용하는 인터럽트 번호

- **[UP]** : network interface가 켜져 있음을 의미한다.



##### **up, down**

- ifconfig [interface name ] up  : interface끄기

- ifconfig [interface name ] down : interface켜기



### netstat

전송 제어 프로토콜, 라우팅 테이블, 수많은 네트워크 인터페이스(네트워크 인터페이스 컨트롤러 또는 소프트웨어 정의 네트워크 인터페이스), 네트워크 프로토콜 통계를 위한 네트워크 연결을 보여주는 명령 줄 도구이다.

| 옵션        | 기능                                                     |
| ----------- | -------------------------------------------------------- |
| -a          | 모든 연결 및 수신 대기 포트를 표시한다.                  |
| -c          | 현재 실행 명령을 매 초마다 실행한다.                     |
| -l          | LISTEN 하고 있는 포트를 보여 준다.                       |
| -t          | TCP 로 연결된 포트를 보여 준다.                          |
| -u          | UDP 로 연결된 포트를 보여 준다.                          |
| -n          | 주소나 포트 형식을 숫자로 표현한다.                      |
| -p 프로토콜 | 해당 프로세스를 사용하고 있는 프로그램 이름을 보여 준다. |
| -r          | 라우팅 테이블을 보여 준다.                               |