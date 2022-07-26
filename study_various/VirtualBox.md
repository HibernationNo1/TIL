# VirtualBox

**Virtual Machine** : 하드웨어를 소프트웨어적으로 구현해서 그 위에서 운영체제가 작동하도록하는 기술

VirtualBox 란 **컴퓨터 가상화 프로그램**으로, 현존하는 대부분의 OS를 가상 공간에 설치해서 사용할 수 있게 해 준다. 



### install

https://www.virtualbox.org/wiki/Downloads

> 설치 위치를 D드라이브로 설정하면 가상머신을 만든 후 시작 단계에서 오류가 발생할 수 있음





### setting

- **Right Control**

  파일 - 환경설정 - 입력 - 가상머신 - 단축키 (호스트 키 조합의 단축키 `Right Control`을 `F11`로 변경)

  > Linux에서 마우스가 못빠져나올때 F11누르면 해결되도록 설정

- **Network 구성**

  Network추가하기 : 설정 - 네트워크 - 우측의 녹색 `+` 버튼

  - Network이름 : 자유롭게

  - Network CIDR : 10.0.2.0/24 그대로 (또는 10.100.0.0/24)

  - IPv6지원 체크

  - **port forwarding**

    설치된 가상 운영체제 중 원하는 운영체제에 원격으로 접속할 수 있도록 설정

    > 가상 OS에서 사용할 IP를 생각해두거나, defual로 그냥 사용

    만들어진 Network의 `포트 포워딩`에서

    - 특정 OS port

      host port : `105`,  	gest port : `22`

      local에서 105번 port로 접속하면 해당 OS로 접속할 수 있도록 설정

      이름 : (자유롭게 설정)

      프로토콜 : TCP

      호스트IP : `127.0.0.1` (local에서 연결할 때)

      게스트 IP : `10.0.2.15 ` (또는 나중에 OS에서 설정할 IP)  

      > 하나 더 만든다고 할 때 
      >
      > host port만  `106`으로 만들어 추가 
      >
      > 단, port는 본체 OS에서 사용하지 않는 port인지 확인할 것 

    

    

### chreate virtual machine

VirtualBox 실행, 새로 만들기 

**[Ubuntu](https://ubuntu.com/#download) 예시**

종류 : Linux

버전 : Ubuntu (64-bit)

- 64bit가 보이지 않을 땐 PC의 BIOS에서 가상화(Virtualization, TV) 기능을 킬 것

메모리 크기 : 전체 메모리의 4분의 1 정도 (가능하면 8GB 이상)

`지금 새 가상 하드 디스크 만들기` : 10GB할당 (최소), VDI, 동적 할당, 디스크 크기 원하는 만큼 할당(10GB 이상)



iso는 [여기](https://releases.ubuntu.com/)서 다운 (가능하면 20.04)

시작 > 시동 디스크 선택 > 다운받은 iso 파일









#### setting

- **port forwarding**

  만들어진 Ubuntu 선택 후 설정 - 네트워크 - 고급 - 포트 포워딩

  - SSH port

    host port : `22`,  	gest port : `22`

    putty와 같은 원격 host protocol을 사용하여 virtual machine에 원격으로 접속할 수 있도록 설정

  - web server port

    host port : `80`,  	gest port : `80`

    virtual machine안에서도 웹 서버를 자유롭게 이용할 수 있도록 설정

- **system**

  만들어진 Ubuntu 선택 후 설정 - 시스템 

  - 마더보드 - 부팅 순서 - 플로피 해제

  - 프로세서 - 프로세서 개수 : 2개~원하는 만큼

- **repository**(저장소)

  설정 - 저장소  - '저장 장치'의 `컨트롤러 : IDE`의 `비어있음` 클릭 후 우측 '속성'의 광학 드라이브에서 파란버튼 누른 후 `디스크에서 파일 선택` 에서 위 **Ubuntu 설치** 과정에서 다운받은 Ubuntu .iso 파일 선택

  > Ubuntu를 VirtualBox가 설치 된 드라이브(C 드라이브)에 넣은 것으로 이해하자.

- **일반**

  만들어진 Ubuntu 선택 후 설정 - 일반 - 네트워크 어댑터 사용하기 - 다음에 연결됨

  `NAT`에서 `NAT 네트워크` 로 변경

  이름 - Network 구성의 port forwarding 과정에서 설정한 network중 사용하고자 하는 network 선택

  > Network 구성의 port forwarding 과정에서 설정한 특정 OS port를 사용하기 위함



#### snapshot

현재 Virtual machine의 상태(version 등)을 저장

Virtual machine의 세 줄 tap 클릭 - 스냅샷 - 상단 찍기 버튼



### manage Ubuntu

#### 1. 내보내기, 가져오기

VirtualBox의 내보내기, 가져오기를 통해 설치한 ubuntu를 여러개처럼 따로따로 사용할 수 있다.

1. 내보내기

   VirtualBox에서 ubuntu 전원 꺼짐 상태로, 파일 - 가상 시스템 내보내기 -  설치한 ubuntu 선택하고 다음 - 원하는 위치

2. 가져오기

   파일 - 가상 시스템 가져오기 -  이전에 내보내기 한 ubuntu 선택 



#### 2. 스펙 업그레이드

- CPU core개수 

  가상머신 > 설정 > 시스템 > 프로세서

  



Ubuntu 가상머신 저장소, 파티션 용량 늘리는 법

1. 가상머신 저장소 용량 늘리기

   1. Ubuntu, VirtureBox 종료

   2. modifyhd 명령어 실행

      `"버추얼박스가 설치된 위치(경로)" modifyhd "용량을 조절할 가상머신 파일 위치(경로).vid" --resize 용량`

      ```
      "C:\Program Files\Oracle\VirtualBox\VBoxManage.exe" modifyhd "C:\Users\마이노\VirtualBox VMs\Ubuntu-Desktop 1\Ubuntu-Desktop-inital-disk002.vdi" --resize 20480 
      ```

      > 버추얼박스가 설치된 위치(경로) : `C:\Program Files\Oracle\VirtualBox\VBoxManage.exe`
      >
      > 용량을 조절할 가상머신 파일 위치(경로) : `C:\Users\마이노\VirtualBox VMs\Ubuntu-Desktop\Ubuntu-Desktop.vdi`
      >
      > 늘릴 용량 : 10G `10240` -> 20G `20480`

2. 파티션 용량 늘리기

   가상머신 저장소 용량을 늘렸으면, Ubuntu에서 실제 사용 가능한 용량이 커질 수 있도록 해야 한다.

   1. **GParted** 라이브러리를 설치 (dist 파티션 설청 프로그램)

      ```
      sudo apt-get install gparted 
      ```

      > 불필요한 패키지가 설치되어 있어서 용량이 부족하다는 메시지 때문에 설치가 안되면 `sudo apt autoremove`

   2. GParted 실행 (검색해서 열자)

      main partition이 무엇인지 확인 후 resize하자

      (내꺼 partition은 /dev/sda5, file System = ex4 인 것을 resize했다)

      resize한 후 초록색 확인 버튼 눌러서 적용



#### 3. port forwarding

1. host 전용 어댑터 사용

   해당 가상 OS의 설정 > 네트워크 > 어댑터 1

   네트워크 어댑터 사용하기 체크, 호스트 전용 어댑터 (어댑터 1에는 NAT로 설정되어 있을 것임)

2. 가상 OS실행 후 IP확인(ifconfig)

   ```
   enp0s8: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
           inet 192.168.56.101  netmask 255.255.255.0  broadcast 192.168.56.255
           inet6 fe80::6f64:554f:332e:78c1  prefixlen 64  scopeid 0x20<link>
           ether 08:00:27:8c:3a:93  txqueuelen 1000  (Ethernet)
           RX packets 6  bytes 1549 (1.5 KB)
           RX errors 0  dropped 0  overruns 0  frame 0
           TX packets 46  bytes 5802 (5.8 KB)
           TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
   ```

   192.168.56.101 ~ 192.168.56.254 IP 대역으로 자동으로 할당 확인 (`192.168.56.101`)



#### 4. 원격 접속 확인

- ssh확인

  1. 가상 OS에서 

     check and install

     ```
     $ dpkg -l | grep openssh					# openssh-client 확인
     $ sudo apt-get install openssh-server		# openssh-server 설치
     ```

     start

     ```
     $ sudo service ssh start
     ```

     check port

     ```
     $ sudo netstat -anp|grep LISTEN|grep sshd
     ```

     > 변경시 
     >
     > ```
     > $ sudo vi /etc/ssh/ssh_config
     > ```

  2. 접속하고자 하는 OS에서

     IP통신 확인

     ```
     $ ping 192.168.56.101
     
     Ping 192.168.56.101 32바이트 데이터 사용:
     192.168.56.101의 응답: 바이트=32 시간<1ms TTL=64
     192.168.56.101의 응답: 바이트=32 시간<1ms TTL=64
     192.168.56.101의 응답: 바이트=32 시간<1ms TTL=64
     192.168.56.101의 응답: 바이트=32 시간<1ms TTL=64
     
     192.168.56.101에 대한 Ping 통계:
         패킷: 보냄 = 4, 받음 = 4, 손실 = 0 (0% 손실),
     왕복 시간(밀리초):
         최소 = 0ms, 최대 = 0ms, 평균 = 0ms
     ```

     접속

     `username@IP` :port 입력

- filezilla

  - host : `sftp://192.168.56.101`
  - user name : 
  - pw:
  - port : 22 (ssh와 동일)

- 

