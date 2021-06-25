# Ubuntu 설치

1. VirtualBox 설치

   https://www.virtualbox.org/wiki/Downloads

   > VirtualBox 란 **컴퓨터 가상화 프로그램**으로, 현존하는 대부분의 OS를 가상 공간에 설치해서 사용할 수 있게 해 준다. 
   >
   > 설치 위치를 D드라이브로 설정하면 가상머신을 만든 후 시작 단계에서 오류가 발생할 수 있음

2. PuTTY 다운받아서 실행

   https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html 에서 putty.exe 

   >PuTTY 란 **원격 접속 프로그램**으로, 가장 많이 사용되는 프로토콜인 SSH, Telnet, Serial 등을 지원한다.
   >
   >- Secure SHell, **SSH** : 네트워크 상의 다른 컴퓨터에 로그인하거나 원격 시스템에서 명령을 실행하고 다른 시스템으로 파일을 복사할 수 있도록 해 주는 프로토콜. 기본적으로 22번 포트를 사용

3. Ubuntu 설치

   https://ubuntu.com/#download

   > Desktop용 또는 Server용



### set VirtualBox

1. 가상머신 만들기

   VirtualBox 실행, 새로 만들기 
   
   > 종류 : Linux
   >
   > 버전 : Ubuntu (64-bit)
   >
   > - 64bit가 보이지 않을 땐 PC의 BIOS에서 가상화(Virtualization, TV) 기능을 킬 것
   >
   > 메모리 크기 : 전체 메모리의 4분의 1 정도
   >
   > VDI
   >
   > 동적 할당
   
2. 설정

   - 파일 - 환경설정 - 입력 - 가상머신 - 단축키 (호스트 키 조합의 단축키 `Right Control`을 `F11`로 변경)

     > Linux에서 마우스가 못빠져나올때 F11누르면 해결되도록 설정

   - 설정 - 저장소  - '저장 장치'의 `컨트롤러 : IDE`의 `비어있음` 클릭 후 우측 '속성'의 광학 드라이브에서 파란버튼 누른 후 `디스크에서 파일 선택` 에서 위 **Ubuntu 설치** 과정에서 다운받은 Ubuntu .iso 파일 선택

     > Ubuntu를 VirtualBox가 설치 된 드라이브(C 드라이브)에 넣은 것으로 이해하자.

   - 설정 - 네트워크 - 고급 - `포트 포워딩` - 우측의 녹색 `+` 버튼 - 호스트 버튼 게스트 포트 두 값이 같게 22번, 80번 두 개 추가 후 확인

     > 네트워크 설정. 
     >
     > 22번 : ssh포트
     >
     > 80번 : 웹 서버 포트

### install ubuntu in VirtualBox

1. 시작

   시동 - 디스크 선택 - **Ubuntu 설치** 과정에서 다운받은 Ubuntu .iso 파일 선택

   Ubuntu 설치 시작

   언어 선택 후 install ubuntu

   updatas and other software 옵션은 default

   installation type 은 파티션을 나누는 부분. Erase disk and install ubuntu

   거주지 - seoul

2. 설치 완료

   컴퓨터 restart 버튼 누르면 ubuntu booting 
   `Please remove the installation medium, then press ENTER`  보이면 Enter

   > booting이 되지 않는다면 설정에 들어가서 위 **set VirtualBox**의 2.설정 part에서 `컨트롤러 : IDE` 을 비어있음으로 설정해서 제거해줘야함

3. 로그인

   Help improve Ubuntu - No  

   You're ready to go! 하며 설치 가능한 package를 보여준다.



### set initial Ubuntu

1. 게스트 확장 설치 진행 (window10과 통신을 하기 위해)

   Oracle VM VirtualBox의 장치 - 게스트 확장 CD 이미지 삽입 - ps 입력 - 설치 완료

   > cd룸에 cd넣은거라고 생각하면 됨

   ubuntu 바탕화면의 왼쪽에 cv아이콘 누른 후 VBoxLinuxAdditions.run 실행

   > VBoxLinuxAdditions.run은 VirtualBox 크기에 맞춰 Ubuntu 화면도 크기가 조절되게 해주는 file
   >
   > `gcc make perl dkms` 이 없어서 설치가 되지 않는다면
   >
   > ```
   > $ sudo apt-get update
   > $ sudo apt-get install build-essential gcc make perl dkms
   > ```
   >
   > sudo로 gcc설치 후 
   >
   > ```
   > sudo ./VBoxLinuxAdditions.run
   > ```
   >
   > 파일 위치에서 직접 실행, 이후 reboot

   apt과정에서 오류가 발생한다면 

   ```
   # apt -get updata
   ```

   

2. root 계정 설정

   Linux에는 두 개의 계정이 있다.
   
   - 시스템 관리자(root)
   
     ```
     #  
     ```

   - 일반 사용자

     ```
     $
     ```

     

   > ubuntu는 사용자가 설정한 계정과 패스워드로 로그인을 하게 되는데, 이는 개별 계정으로 여러 제한사항이 있다.
   >
   > - apt-get으로 소프트웨어 package를 설치 불가
   > - file에 access 권한이 없는 directory가 존재
   > - 개별 권한으로 실행을 못하는 app가 있음
   >
   > 이런 권한을 획득하기 위해 'Super User Do'의 줄임말인 sudo 명령을 통해서 위 모든 권한을 가진 root계정으로 전환할 수 있음
   
   1. **root 계정으로 전환**
   
      ```
      $ sudo -i
      ```
   
      > 이후부턴 `$`가 아닌, `root@computer'sname:~#`  으로 시작함
   
   2. 최초 root 계정 암호 설정, password 입력 
   
      ```
      root@ ~~~ :~# passwd
      ```
   
      > new password : 설정할 root 비밀번호입력
      >
      > password updata successfully 뜰 거임  
   
   
   
3. 언어팩 설치

   ```
   # nl /etc/default/locale
   ```

   을 입력하면 각 기능에 어떤 언어가 사용되어 표현되는지 확인할 수 있다.

   > en_US.UTF-8 : 영어 
   >
   > ko_KR.UTF-8 : 한글

   위 언어를 다른 언어로 바꾸려면 해당 언어팩이 있어야 한다.

   1. 한글 언어팩

      ```
      # apt -y install language-pack-ko
      ```

   2. 영어 언어팩

      ```
      # apt -y install language-pack-en
      ```

   언어 변환

   ```
   # updata-locale LANG=ko_KR.UTF-8 LC_MESSAGES=POSIX
   ```

   > en_US.UTF-8 에서 ko_KR.UTF-8로 변환

   **추가**

   virtualBox에서 os의 설정 -> 일반 -> 고급 의

   - 클립보드 공유, 드래그 앤 드롭 을 **양방향** 으로 해야 window에서 복사한거 ubuntu안에서 붙여넣기 가능



4. 한글 입력 키 설정( fcitx-hangul 설치)

   1. fcitx-hangul 설치

      ```
      sudo apt-get update
      sudo apt-get install fcitx-hangul
      ```

   2. 설정

      setting(설정) -> Region & Language -> 

      - input source에 korean 설정 후 해당 language setting의 keyboard input method system을 fcitx로 변경

      또는

      - input source에 korean 설정 후 manage installed Languages누른 후 install 진행
      - 오른쪽 상탄 tap의 키보드 아이콘 클릭 후 현재 입력기 설정
      - 입력 방법 : 한국어 추가
      - 전역 설정 : Ctrl + space : hangul

5. vscode 설치

   1. 홈페이지에서 알맞는 모델 다운

      > default로 install하지 말고 file을 다운

   2. `.deb` file 실행

      ```
      $ cd ~/Downloads 
      $ sudo dpkg -i code*.deb
      ```

      완료
   
   > **consolas** font download in ubuntu
   >
   > Referance : https://gist.github.com/sigoden/d01ad118da677f796bab01781b7eae23
   >
   > 그대로 따라한 후 font setting에 `"YaHei Consolas Hybrid"` 추가



6. typora 설치

   ```
   $ wget -qO - https://typora.io/linux/public-key.asc | sudo apt-key add -
   $ sudo add-apt-repository 'deb https://typora.io/linux ./'
   $ sudo apt -y install typora
   ```

   



### start SSH

1. ssh 설치

   1. 방화벽 off

      ```
      root@ ~~~ :~# systemctl stop ufw
      ```

   2. ssh 시작

      ```
      root@ ~~~ :~# systemctl start ssh
      ```

      없다고 뜨면 설치

      ```
      root@ ~~~ :~# apt install ssh
      ```

      > `y` 

   3. ssh가 잘 설치되었는지 확인

      ```
      ps -ef | grep ssh
      ```

      `00:00:00 sshd: /usr/sbin/sshd -D [listener]` 가 보인다면 접속 가능

2. putty로 ssh 시작

   1. login

      window 10에서 putty 실행 후 ip에 127.0.0.1 입력 후 확인, accept 클릭

      `login as:` 가 뜨면 성공

      ```
      login as: hibernation
      password : winter4958
      ```

      > 아이디 비번 입력해서 접속

   2. VirtualBox와 양방향 setting

      VirtualBox에서 장치 - 클립보드 공유 - 양방향 으로 setting

      VirtualBox에서 장치 - 드래그 앤 드롭 - 양방향 으로 setting

   이제 window10에서 putty를 통해 ssh로 ubuntu에서 작업이 가능하다.









### manage Ubuntu

#### 1. 내보내기, 가져오기

VirtualBox의 내보내기, 가져오기를 통해 설치한 ubuntu를 여러개처럼 따로따로 사용할 수 있다.

1. 내보내기

   VirtualBox에서 ubuntu 전원 꺼짐 상태로, 파일 - 가상 시스템 내보내기 -  설치한 ubuntu 선택하고 다음 - 원하는 위치
   
2. 가져오기

   파일 - 가상 시스템 가져오기 -  이전에 내보내기 한 ubuntu 선택 



#### 2. 용량 늘리기

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

   1.  **GParted** 라이브러리를 설치 (dist 파티션 설청 프로그램)

      ```
      sudo apt-get install gparted 
      ```

      > 불필요한 패키지가 설치되어 있어서 용량이 부족하다는 메시지 때문에 설치가 안되면 `sudo apt autoremove`

   2.  GParted 실행 (검색해서 열자)

      main partition이 무엇인지 확인 후 resize하자

      (내꺼 partition은 /dev/sda5, file System = ex4 인 것을 resize했다)

      resize한 후 초록색 확인 버튼 눌러서 적용



### install Compiler

Ubuntu에선 python colpiler는 default로 설치되어 있지만, C, C++은 따로 설치를 해 주어야 한다.

- **python**

  python terminal실행 (Compiler 가 아니고 terminal임)

  ```
  $ python3
  ```

  > 끝낼때는 quit()

  python Compiler 실행 

  ```
  # vi filename.py
  ```

  > Compiler로 vim을 사용  `:wr`하면 저장 후 종료

  - install pip

    ```
    $ apt-get install python3-pip
    ```

    > `$ pip install numpy`

- **C, C++** install

  ```
  # apt -y install gcc g++
  ```

  C++ Compiler 실행

  ```
  # vi file_name.cpp
  ```

  > vim으로 실행하는 것이기 때문에 `:wr`하면 저장 후 종료

  code 작성 후 compile

  ```
  # g++
  ```

  > file_name.out 이라는 이름의 실행 파일이 만들어짐

  ```
  # file_name.out
  ```

  > 실행 파일 작동

