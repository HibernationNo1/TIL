# linux IP, network

{:toc}



### 사전 지식

- **network** 주소

  일반적으로 하나의 network를 통칭하기 위해 사용하는 주소

  >  특정 허브로 구성된 network 주소가 `192.168.1.0` 이라고 하면 이 network에 속할 수 있는 주소 범위는 `192.168.1.0`~`192.168.1.255` 이다.

- **netmask** 주소

  하나의 network를 여러개로 나누어 사용할 때에 나눠진 각각의 network를 구분하기 위해 사용하는 특수한 bit (Subnet mask라고 한다.)

  > 이를 통해 트래픽 부하를 줄일 수 있다.

- **Broadcast** 주소

  특정 network에 속하는 모든 host들이 듣게 되는 주소

  일반적으로 구성된 network에 할당된 주소 중 가장 마지막 주소를 사용한다.

  > 특정 허브로 구성된 network 주소가 `192.168.1.0` 이라고 하면 Broadcast 주소는 `192.168.1.255` 

- **gateway**

  서로 다른 network를 연결해주는 특정 장비나 특정 host

  router와 같은 장비나 linux system을 통해 다른 network를 연결해줄 수 있다.

  > ping을 통해 현재 PC에서 router에 연결이 잘 되어 있는지 확인할 수 있다.
  >
  > router의 중간 IP가 20이라고 할 때, network는 192.168.20.0이 된다.
  >
  > ```
  > $ping 192.168.20.0
  > ```

- **Domain Name Server(DNS)**

  domain 주소를 IP주소로 변경해주는 서버.

  일반적으로 가정집에서 쓰는 internet은 통신사(ISP)에서 제공하는 DNS를 사용한다.

  주로 아래 두 개의 주소를 사용한다.

  - `1.1.1.1` (Coudflare 사의 DNS)
  - `8.8.8.8` (google 사의 DNS)

  



#### ifconfig

`ifconfig` : network 구성 확인하는 명령어

```
$ sudo apt install net-tools
```

- 예시

  ```
  enp2s0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
          inet 192.168.0.208  netmask 255.255.255.0  broadcast 192.168.0.255
          inet6 fe80::b62e:99ff:fe3f:d966  prefixlen 64  scopeid 0x20<link>
          ether b4:2e:99:3f:d9:66  txqueuelen 1000  (Ethernet)
          RX packets 383381  bytes 39712163 (39.7 MB)
          RX errors 0  dropped 46526  overruns 0  frame 0
          TX packets 7354  bytes 593597 (593.5 KB)
          TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
          device memory 0x90400000-9047ffff
  ```

  - `enp2s0` : network interface
  - `flags` : network card의 상태 표시
  - `inet` : network interface에 할당된 IP주소
  - `netmask` : network interface에 할당된 netmask 주소
  - `broadcast` : 네트워크 인터페이스에 할당된 브로드캐스트 주소
  - `ether` : network interface의 hardware주소



`ifconfig -a` : 모든 network interface config확인

- 예시

  ```
  docker0: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
          inet 172.17.0.1  netmask 255.255.0.0  broadcast 172.17.255.255
          ether 02:42:1c:bf:98:63  txqueuelen 0  (Ethernet)
          RX packets 0  bytes 0 (0.0 B)
          RX errors 0  dropped 0  overruns 0  frame 0
          TX packets 0  bytes 0 (0.0 B)
          TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
  
  enp2s0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
          inet 192.168.0.208  netmask 255.255.255.0  broadcast 192.168.0.255
          inet6 fe80::b62e:99ff:fe3f:d966  prefixlen 64  scopeid 0x20<link>
          ether b4:2e:99:3f:d9:66  txqueuelen 1000  (Ethernet)
          RX packets 383381  bytes 39712163 (39.7 MB)
          RX errors 0  dropped 46526  overruns 0  frame 0
          TX packets 7354  bytes 593597 (593.5 KB)
          TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
          device memory 0x90400000-9047ffff
  
  enp3s0: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
          ether b4:2e:99:3f:d9:67  txqueuelen 1000  (Ethernet)
          RX packets 0  bytes 0 (0.0 B)
          RX errors 0  dropped 0  overruns 0  frame 0
          TX packets 0  bytes 0 (0.0 B)
          TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
          device memory 0x90300000-9037ffff
  
  lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
          inet 127.0.0.1  netmask 255.0.0.0
          inet6 ::1  prefixlen 128  scopeid 0x10<host>
          loop  txqueuelen 1000  (Local Loopback)
          RX packets 414  bytes 30262 (30.2 KB)
          RX errors 0  dropped 0  overruns 0  frame 0
          TX packets 414  bytes 30262 (30.2 KB)
          TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
  ```

  - `docker0`  : 도커를 사용하기 위해 설치된 interface

  - `enp2s0`, `enp3s0` : 랜선 입력 포트에 대한 interface

    > 컴퓨터에 사용 가능한 랜선 입력 포트 개수만큼 나온다.

  - `lo` : 시스템이 자기 자신과의 통신을 하기 위한 가상 이더넷장치



- ifconfig [interface name ] up  : interface끄기

- ifconfig [interface name ] down : interface켜기



### Set IP

- **dhcp 방식** :  IP를 자동으로 랜덤하게 설정하는 방법
- **static 방식** : 사용자가 해당 PC의 IP를 고정시키는 방법 



#### Ubuntu

- 18.04

  ```
  $ sudo vi /etc/network/interfaces
  ```
  
  > 192.168.110.0 network에 속하며, 107번으로 IP를 고정시킬 경우
  
  ```
  # The primary network interface
  # This file describes the network interfaces available on your system
  # and how to activate them. For more information, see interfaces(5).
  # The loopback network interface
  auto lo
  iface lo inet loopback
  
  # The primary network interface
  auto eth0
  iface eth0 inet static
  address 192.168.110.107
  netmask 255.255.255.0
  gateway 192.168.110.1
  dns-nameservers 8.8.8.8
  ```
  
  
  
- 20.04

  ubuntu에서 network interface IP를 설정하는 파일은 `/etc/netplan` 위치에 `01-netcfg.yaml` 이름으로 있다. (없다면 만들자.)

  ```
  $ cat /etc/netplan/01-netcfg.yaml
  ```
  
  `01-netcfg.yaml` 파일을 통해 고정 IP를 설정하는 경우
  
  - 예시 
  
    > 192.168.0.0 network에 속하며, 208번으로 IP를 고정시킬 경우
  
    ```
    network:
        version: 2
        renderer: networkd
        ethernets:
            enp2s0:
                dhcp4: no
                addresses: [192.168.0.208/24]
                gateway4: 192.168.0.1
                nameservers:
                    addresses: [1.1.1.1,8.8.8.8]
    ainsoft@nonggiwon:/etc/netplan$
    ```

    `enp2s0` : interface name

    > `ifconfig`를 통해 확인할 것. 

    `dhcp4` : true 면 dhcp4방식, no면 static방식

    `addresses` : IP주소
  
    `gateway4` : gateway주소

    `nameservers` : DNS주소

    
  
    값 세팅 후
  
    ```
    $ systemctl restart network
    ```
  
    
  
  

#### SentOS

SentOS에서 network interface IP를 설정하는 파일은 `/etc/sysconfig/network-scripts/` 에 위치해 있다.

ifconfig를 통해 확인했을 때 `eno5`, `eno6`, `eno7`, `eno8` 4개의 IP할당이 가능한 PC라고 할 때 

`etc/sysconfig/network-scripts/` 에 `ifcfg-eno5` , `ifcfg-eno6`,  `ifcfg-eno7` , `ifcfg-eno8` 라는 이름의 파일이 각각 존재한다.

이 중  `eno5` 라는 interface에 고정 IP를 설정한다면, \

```
$ sudo vi ifcfg-eno5
```

```
TYPE=Ethernet
PROXY_METHOD=none
BROWSER_ONLY=no
BOOTPROTO=none
DEFROUTE=yes
IPV4_FAILURE_FATAL=no
IPV6INIT=yes
IPV6_AUTOCONF=yes
IPV6_DEFROUTE=yes
IPV6_FAILURE_FATAL=no
IPV6_ADDR_GEN_MODE=stable-privacy
NAME=eno5
UUID=b755eda7-7b06-48ba-ac6e-7d5c9d897041
DEVICE=eno5
ONBOOT=yes
IPADDR=192.168.0.167
PREFIX=24
GATEWAY=192.168.0.1
DNS1=168.126.63.1
DNS2=8.8.8.8
```

- `DEVICE, NAME` : interface name

- `BOOTPROTO` : dhcp, static 방식 중 어떤 방식을 사용할것인지 결정

  > `BOOTPROTO = "dhcp"` 이면 dhcp 방식
  >
  > `BOOTPROTO = "none"` 이면 static 방식

- `ONBOOT` : system booting시 활성화 할 것인지 결정

  > 사용하는 interface가 아니면 no, 사용하는거면 yes

- `IPADDR` : 고정하고자 하는 IP주소

- `GATEWAY` : gateway주소

- `DNS1, DNS2` : DNS주소

  

  static으로 IP설정 시 아래 값은 반드시 설정

  ```
  BOOTPROTO=none
  DEVICE=eno5
  ONBOOT=yes
  IPADDR=192.168.0.167
  GATEWAY=192.168.0.1
  DNS1=168.126.63.1
  DNS2=8.8.8.8
  ```

  

  값 세팅 후 

  ```
  $ systemctl restart network
  ```

  