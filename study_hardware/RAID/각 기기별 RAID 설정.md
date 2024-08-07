# RAID 설정



## NVIDIA DGX V100 

- mainboard: `NVIDIA - DGX-1 with V100-32`



**1. RAID 설정 창으로 접근 ** 

1.  `F2` 또는 `DEL` 키를 입력하여 BIOS 진입
2. Advanced > `AVAGO Mefa RAID <AVAGO MegaRAID SAS PCI Express ROMB> Configuration Utility`  선택
3. Configure 선택



- **1-1**. drive를 사용 가능한 상태로 변경

  Advanced > `AVAGO Mefa RAID <AVAGO MegaRAID SAS PCI Express ROMB> Configuration Utility` > `View Server Profile` > `Drive management`  경로에 각 drive의 상태를 확인할 수 있다.

  만일 상태가 `Unconfigured Bad ` 라면  해당 드라이브가 인식되지만 사용할 수 없거나 결함이 있는 상태를 의미한다.

  복구방법:

  1. 특정 drive 선택 

  2. Operation 변경

     - **select operation**: 사용자가 수행할 수 있는 작업을 선택할 수 있도록 메뉴를 표시

       drive가 정상상태라면 해당 옵션 선택

     - **start locate**: 선택된 디스크를 물리적으로 식별할 수 있도록 디스크의 LED를 깜빡이게 한다.

     - **stop locate**: "Start Locate" 명령을 취소. 즉, 깜빡이는 LED를 끔

     - **make unconfigured good**: 현재 "Unconfigured Bad" 상태인 드라이브를 "Unconfigured Good" 상태로 변경. 

       이 작업은 드라이브가 실제로 물리적으로 문제가 없는 경우에만 수행해야 한다.



**2. RAID를 할당하기 위한 Virtual Drive 생성**

1. **`Create Virtual Drive`** 선택
2. Select RAID Level : RAID 레벨 선택

3. Select Drives: Drive 선택

   - `Select Media Type`: SSH, HDD, BOTH 중에 선택

     선택한대로 아래에 고를 수 있는 drives가 출력된다.

4. Drive 선택

   list에서 사용하고자 하는 drive 선택 후 `Disabled`상태에서 `Enabled` 로 상태 변경






- **2-1. 특정 Virtual Drive 삭제**

  1.  `F2` 또는 `DEL` 키를 입력하여 BIOS 진입
  2.  Advanced > `AVAGO Mefa RAID <AVAGO MegaRAID SAS PCI Express ROMB> Configuration Utility`  선택
  3.  `View Server Profile` > `Virtual Drive Management` > 삭제하고자 하는 Virtual Drive 선택
  4.  Operation 에서 `-` 를 눌러 `[Delete Virtual Drive]` 으로 전환 > `Go` 선택

- **2-2. 모든 Virtual Drive 삭제**

  option화면에서 Clear Virtual Drive 실행
  
  



**3. RAID 설정**

- **Select Drives From**

  - `Unconfigured Capacity`: RAID 컨트롤러에 연결되어 있지만 아직 RAID 배열에 할당되지 않은 드라이브를 선택할 수 있다.

    새로운 RAID 배열을 만들거나 기존 배열을 확장할 때 사용

  - `Configured Capacity`: 이미 RAID 배열에 포함된 드라이브의 용량을 나타낸다.

- **Strip Szie**: RAID 배열에서 데이터를 분할하여 여러 디스크에 저장할 때 각 디스크에 저장되는 데이터의 블록 크기 설정

  작은 스트라이프 크기는 작은 파일을 처리할 때 유리하고, 큰 스트라이프 크기는 대용량 파일을 처리할 때 유리하다.

- **Read Policy**: RAID 컨트롤러가 데이터를 읽을 때 사용하는 방법을 설정

  - `No Read Ahead`: 요청된 데이터만 읽는다. 

    시스템이 데이터 요구를 예측하지 않고 필요한 데이터만 읽기 때문에 일반적으로 작은 파일에 적합

  - `Read Ahead`: 예상되는 다음 데이터를 미리 읽어 메모리에 저장한다.

    대용량 연속 데이터 읽기 작업에 유리하다.

- **Write Policy**: RAID 컨트롤러가 데이터를 디스크에 쓸 때 사용하는 방법을 설정

  - `Write Through`: 데이터가 디스크에 완전히 쓰여질 때까지 쓰기 작업을 완료하지 않는다. 이 방법은 안전하지만 성능이 낮다.
  - `Write Back`: 데이터를 먼저 캐시에 쓰고, 이후에 디스크에 쓴다. 캐시가 데이터를 유지하므로 성능이 높지만, 전력 손실 시 데이터 손실 위험이 있다.
  - `Always Write Back`: 항상 Write Back 정책을 사용한다. 전원 장애 시 배터리 백업 캐시를 사용하여 데이터 손실을 방지할 수 있다.

- **I/O Policy**: 데이터 입출력 시 캐시를 사용할지 여부를 설정
  - `Direct`: 데이터 입출력이 직접 디스크에 이루어진다. 캐시를 사용하지 않아 데이터 무결성이 높다.
  - `Cached`: 데이터 입출력이 먼저 캐시를 통해 이루어진다. 성능이 높지만, 데이터 무결성은 다소 떨어질 수 있다.
- **Access Policy**: RAID 배열에 대한 접근 권한을 설정
  - `Read/Write`: RAID 배열에 대한 읽기 및 쓰기 접근 권한을 모두 허용
  - `Read Only`: RAID 배열에 대한 읽기 접근 권한만 허용하고, 쓰기는 차단한다. 데이터 보호를 위해 사용된다.
  - `Blocked`: RAID 배열에 대한 모든 접근을 차단한다. 주로 유지 보수 또는 데이터 보호를 위해 사용된다.



설정 완료 후 가장 하단에 Save Configuration 선택



**4. Boot device 결정**

boot시 사용할 가상 device를 결정. 

OS를 설치할 가상 device를 결정한다.

1. Advanced > `AVAGO Mefa RAID <AVAGO MegaRAID SAS PCI Express ROMB> Configuration Utility`  선택

2. `Configure` > `View server Profile` > `Controller Management`

3. `Select Boot Device` > 사용하고자 할 Virtual Drive의 이름을 선택 

   