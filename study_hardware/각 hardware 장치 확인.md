# 각 hardware 장치 확인



## linux

### CPU

```
$ lscpu
```

- `Socket(s)`: CPU 개수

- `Core(s) per socket`: CPU에 포함된 core개수

- `Thread(s) per core`: CPU core당 사용하는 Thread

- `CPU(s)`: CPU core개수

  실제 프로세스 위치에서 인식하는 CPU core의 개수: `Core(s) per socket` x `Thread(s) per core` == `CPU(s)`

### GPU

```
$ nvidia-smi --query | fgrep 'Product Name' &&   nvidia-smi --query-gpu=memory.total,memory.used --format=csv
```

### DISK

```
$ sudo parted -l
```

위 명령어로도 HDD, SSD 구별이 불가능하면

```
$ lsblk -o NAME,FSTYPE,SIZE,MOUNTPOINT,TYPE,MODEL
```

위 명령어로 device 이름을 확보 후 아래 명령어 실행



#### RAID controller

```
$ lsblk -o NAME,SIZE,MODEL
```

**위 명령어에 의한 출력이 아래와 같이 disk 모델명이 동일한데 용량이 다를 경우, virtual drive가 구성되어 있는지 확인해야됨**

```
NAME     SIZE MODEL
sda    893.8G SMC3108         
├─sda1   400M 
├─sda2    16G 
├─sda3   400M 
├─sda4     1K 
└─sda5   877G 
sdb      1.8T SMC3108         
└─sdb1   1.8T
```

위와 같이 구성된 경우는 RAID controller 로 구성되었을 가능성이 크다.

1. MegaCLI 설치

   1. 필요 패키지 설치

      ```
      sudo apt-get update
      sudo apt install unzip -y
      sudo apt-get install libncurses5 -y
      sudo apt-get install alien -y
      ```

   2. MegaCLI 다운로드

      ```
      $ wget https://docs.broadcom.com/docs-and-downloads/raid-controllers/raid-controllers-common-files/8-07-14_MegaCLI.zip
      $ unzip 8-07-14_MegaCLI.zip
      ```

   3. MegaCLI 설치

      alien 를 사용해서 ubuntu에서 megacli을 사용하기 위해 rpm을 deb 으로 변환

      ```jsx
      $ sudo alien Linux/MegaCli-8.07.14-1.noarch.rpm
      $ sudo dpkg -i megacli_8.07.14-2_all.deb
      ```

2. 명령어 실행

   - 물리적 drive 상태 명령어

     ```
     $ sudo /opt/MegaRAID/MegaCli/MegaCli64 -PDList -aAll
     ```

   - RAID 구성 확인 명령어

     ```
     $ sudo /opt/MegaRAID/MegaCli/MegaCli64 -CfgDsply -aAll
     ```

   - RAID 어댑터에 연결된 모든 가상 드라이브(Virtual Drive, VD)의 상세 정보를 출력하는 명령어

     ```
     $ sudo /opt/MegaRAID/MegaCli/MegaCli64 -LDInfo -Lall -aAll
     ```

     RAID Level에 아래와 같이 출력된 경우

     ```
     RAID Level          : Primary-0, Secondary-0, RAID Level Qualifier-0
     ```

     -  `Primary-0`: RAID 0을 사용하고 있단 의미.  Primary-1 은 RAID 1 사용 
     
   - 논리적 드라이브 확인 명령어
   
     ```
     $ sudo megacli -LDInfo -Lall -aAll
     ```
   
     



#### RAID software

```
$ lsblk -o NAME,SIZE,MODEL
```

**위 명령어에 의한 출력이 아래와 같이 drive이름이 `md127` 과 같이 구성되어 있는 경우**

```
NAME          SIZE MODEL
loop0           4K 
...
loop22       11.9M 
nvme0n1       3.6T Seagate FireCuda 530 ZP4000GM30013
└─nvme0n1p1   3.6T 
nvme1n1       3.6T Seagate FireCuda 530 ZP4000GM30013
├─nvme1n1p1     1G 
├─nvme1n1p2   512G 
└─nvme1n1p3   3.1T 
nvme2n1       3.6T Seagate FireCuda 530 ZP4000GM30013
└─md127       3.6T 
nvme3n1       3.6T Seagate FireCuda 530 ZP4000GM30013
└─md127       3.6T
```

Linux 소프트웨어 RAID (또는 mdadm)에서 사용되는 장치를 나타낸다. 즉, RAID software에 의한 RAID 구성이 되어있는 것이다.



```
$ sudo mdadm --detail /dev/md127
```

```
/dev/md127:
           Version : 1.2
     Creation Time : Thu Jun 30 10:12:40 2022
        Raid Level : raid1
        Array Size : 3906886464 (3.64 TiB 4.00 TB)
     Used Dev Size : 3906886464 (3.64 TiB 4.00 TB)
      Raid Devices : 2
     Total Devices : 2
       Persistence : Superblock is persistent

     Intent Bitmap : Internal

       Update Time : Mon Aug  5 10:14:17 2024
             State : clean 
    Active Devices : 2
   Working Devices : 2
    Failed Devices : 0
     Spare Devices : 0

Consistency Policy : bitmap

              Name : user-M12SWA-TF:1  (local to host user-M12SWA-TF)
              UUID : 4771a9aa:f9cfc267:43201f9f:177a89e3
            Events : 3536

    Number   Major   Minor   RaidDevice State
       0     259        6        0      active sync   /dev/nvme2n1
       1     259        7        1      active sync   /dev/nvme3n1
```

- `/dev/nvme2n1`, `/dev/nvme3n1` 는 각각 disk 슬롯을 의미한다.
- `Raid Level : raid1`: RAID 1 로 구성되어 있음을 의미한다.

즉, 2개의 `Seagate FireCuda 530 ZP4000GM30013` 에 의해 RAID 1이 구성되어 있는 virtual drive임을 알 수 있다.



> `/dev/nvme2n1`, `/dev/nvme3n1`가 `md127` 에 할당되러 RAID를 구성했다면
>
> `$ sudo parted -l` 명령어를 입력했을 때 아래와 같이 나올 수 있다.
>
> ```
> 오류: /dev/nvme2n1: 인식할 수 없는 디스크 레이블
> ...
> 오류: /dev/nvme3n1: 인식할 수 없는 디스크 레이블
> ```
>
> 하지만 정상 동작하는 것임



#### LOGICAL VOLUME

```
$ sudo parted -l
```

**위 명령어에 의한 출력이 아래와 같이 `HPE LOGICAL VOLUME`를 포함하고 있다면, HPE의 Smart Array 컨트롤러에 의해 생성된 논리 드라이브인 것이다.**

```
Model: HPE LOGICAL VOLUME (scsi)
Disk /dev/sda: 960GB
Sector size (logical/physical): 512B/4096B
Partition Table: gpt
Disk Flags: 

Number  Start   End     Size    File system     Name                  Flags
 1      1049kB  420MB   419MB   fat16           EFI System Partition  boot
 2      420MB   840MB   419MB   xfs
 3      840MB   18.0GB  17.2GB  linux-swap(v1)
 4      18.0GB  960GB   942GB   xfs
```



- HPE Smart Storage Administrator CLI (`ssacli`) 설치 및 사용

  ```
  $ sudo yum install ssacli
  ```

  - 만일 위 명령어만으로 설치가 안된다면

    1. `/etc/yum.repos.d/hpe-mcp.repo` 에 내용 추가

       ```
       $ sudo vim /etc/yum.repos.d/hpe-mcp.repo
       
       [hpe-mcp]
       name=Management Component Pack
       baseurl=http://downloads.linux.hpe.com/repo/mcp/dist/dist_ver/arch/project_ver
       enabled=1
       gpgcheck=0
       gpgkey=file:///etc/pki/rpm-gpg/GPG-KEY-mcp
       ```

    2. 이후 설치

       ```
       $  sudo yum install ssacli
       ```



- 모든 논리 드라이브 확인

  ```
  $ sudo ssacli controller all show
  ```

  ```
  HPE Smart Array P408i-a SR Gen10 in Slot 0 (Embedded)  (sn: PEYHC0DRHD13L5)
  ```

  

- `slot=0`인 논리 드라이브 정보 확인:

  ```
  $ sudo ssacli controller slot=0 logicaldrive all show
  ```

  ```
  HPE Smart Array P408i-a SR Gen10 in Slot 0 (Embedded)
  
     Array A
  
        logicaldrive 1 (279.37 GB, RAID 1, OK)
  
     Array B
  
        logicaldrive 2 (419.16 GB, RAID 1, OK)
  
     Array C
  
        logicaldrive 3 (894.22 GB, RAID 1, OK)
  
  ```

  모든 logical drive가 RAID 1로 구성되어있음을 알 수 있다.

- 물리 드라이브 정보 확인:

  ```
  $ sudo ssacli controller slot=0 physicaldrive all show
  ```

  ```
  HPE Smart Array P408i-a SR Gen10 in Slot 0 (Embedded)
  
     Array A
  
        physicaldrive 1I:1:1 (port 1I:box 1:bay 1, SATA SSD, 960 GB, OK)
        physicaldrive 1I:1:2 (port 1I:box 1:bay 2, SATA SSD, 960 GB, OK)
  ```

  2개의 SSD 로 구성되어있음을 알 수 있다.

  이제 `1I:1:1`, `1I:1:2` 정보로 물리 드라이브의 세부 정보를 확인이 가능하다.

  ```
  $ sudo ssacli controller slot=0 physicaldrive 1I:1:1 show detail
  ```



### MainBoard

```
$ sudo dmidecode -t baseboard
```

```
Base Board Information
        Manufacturer: ASRock
        Product Name: B365M Pro4
        Version:
        Serial Number: M80-CB003901138
        Asset Tag:
        Features:
                Board is a hosting board
                Board is replaceable
        Location In Chassis:
        Chassis Handle: 0x0003
        Type: Motherboard
        Contained Object Handles: 0
```

- 예시: `ASRock B635M PRO4 에즈윈`

  **Manufacturer**: 제조사

  **Product Name**: 제품명

- RAM

  ```
  $ sudo dmidecode -t memory
  ```

  ```
  Memory Device
          Array Handle: 0x000D
          Error Information Handle: Not Provided
          Total Width: 64 bits
          Data Width: 64 bits
          Size: 8192 MB
          Form Factor: DIMM
          Set: None
          Locator: ChannelA-DIMM0
          Bank Locator: BANK 0
          Type: DDR4
          Type Detail: Synchronous Unbuffered (Unregistered)
          Speed: 2667 MT/s
          Manufacturer: Samsung
          Serial Number: 3268A489
          Asset Tag: 9876543210
          Part Number: M378A1K43CB2-CTD
          Rank: 1
          Configured Memory Speed: 2667 MT/s
          Minimum Voltage: 1.2 V
          Maximum Voltage: 1.2 V
          Configured Voltage: 1.2 V
  ```

  - 예시: `삼성전자 DDR4 8G PC4-21300`

    **Manufacturer**: 제조사

    **Type**: RAM type

    **Size:** RAM size

    수량 2개일 시 위 출력이 두 개 있음

### LAN 카드

```
$ lshw -class network
```

```
*-network
       description: Ethernet interface
       product: RTL8111/8168/8411 PCI Express Gigabit Ethernet Controller
       vendor: Realtek Semiconductor Co., Ltd.
       physical id: 0
       bus info: pci@0000:03:00.0
       logical name: enp3s0
       version: 06
       serial: 00:e0:4c:ab:38:c7
       capacity: 1Gbit/s
       width: 64 bits
       clock: 33MHz
       capabilities: bus_master cap_list ethernet physical tp mii 10bt 10bt-fd 100bt 100bt-fd 1000bt 1000bt-fd autonegotiation
       configuration: autonegotiation=on broadcast=yes driver=r8169 driverversion=5.15.0-97-generic firmware=rtl8168e-3_0.0.4 03/27/12 latency=0 link=no multicast=yes port=twisted pair
       resources: irq:19 ioport:d000(size=256) memory:df200000-df200fff memory:d2100000-d2103fff
...
```

network 중에 `vendor` 항목이 있는 것이 LAN카드