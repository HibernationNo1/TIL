### MegaCLI 설치

Ubuntu에사 RAID 구성을 확인하기 위해 MegaCLI을 설치해야 한다.

1. 필요 패키지 설치

   ```
   $ sudo apt-get update
   $ sudo apt install unzip -y
   $ sudo apt-get install libncurses5 -y
   $ udo apt-get install alien -y
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

  



