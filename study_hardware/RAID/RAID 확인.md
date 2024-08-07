# RAID 확인

RAID 구성을 확인하기 위해 MegaCLI을 설치해야 한다.

### **MegaCLI 설치**

1. 필요 패키지 설치

   ```
   $ sudo apt-get update
   $ sudo apt install unzip -y
   $ sudo apt-get install libncurses5 -y
   $ sudo apt-get install alien -y
   ```

2. MegaCLI 다운로드

   ```
   $ wget <https://docs.broadcom.com/docs-and-downloads/raid-controllers/raid-controllers-common-files/8-07-14_MegaCLI.zip>
   $ unzip 8-07-14_MegaCLI.zip
   ```

3. MegaCLI 설치

   alien 를 사용해서 ubuntu에서 megacli을 사용하기 위해 rpm을 deb 으로 변환

   ```
   $ sudo alien Linux/MegaCli-8.07.14-1.noarch.rpm
   $ sudo dpkg -i megacli_8.07.14-2_all.deb
   ```

   



#### 명령어 실행

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

  ```
  Adapter 0 -- Virtual Drive Information:
  Virtual Drive: 0 (Target Id: 0)
  Name                :
  RAID Level          : Primary-0, Secondary-0, RAID Level Qualifier-0        # RAID Level 0 사용
  Size                : 2.180 TB
  Sector Size         : 512
  Is VD emulated      : No
  Parity Size         : 0
  State               : Optimal
  Strip Size          : 256 KB
  Number Of Drives    : 5             # 드라이브 5개 사용
  Span Depth          : 1
  Default Cache Policy: WriteBack, ReadAhead, Direct, No Write Cache if Bad BBU
  Current Cache Policy: WriteThrough, ReadAhead, Direct, No Write Cache if Bad BBU
  Default Access Policy: Read/Write
  Current Access Policy: Read/Write
  Disk Cache Policy   : Disk's Default
  Encryption Type     : None
  PI type: No PI
  
  Is VD Cached: No
  
  
  
  Exit Code: 0x00
  
  ```

  