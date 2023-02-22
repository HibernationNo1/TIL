dhkdn?

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



## With VirtualBox

### set VirtualBox

1. Network 구성

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



2. VirtualBox 실행, 새로 만들기 

   종류 : Linux

   버전 : Ubuntu (64-bit)

   >  64bit가 보이지 않을 땐 PC의 BIOS에서 가상화(Virtualization, TV) 기능을 킬 것

   메모리 크기 : 전체 메모리의 4분의 1 정도

   `지금 새 가상 하드 디스크 만들기` : VDI, 동적 할당, 디스크 크기 원하는 만큼 할당



3. 설정

   - **port forwarding**

     만들어진 Ubuntu 선택 후 설정 - 네트워크 - 고급 - 포트 포워딩

     - web server port

       host port : `80`,  	gest port : `80`

       virtual machine안에서도 웹 서버를 자유롭게 이용할 수 있도록 설정

     - SSH port

       위 **Network 구성**의 port forwarding 과정에서 특정 OS port를 할당하지 않았을 때만 하기

       host port : `22`,  	gest port : `22`

       putty와 같은 원격 host protocol을 사용하여 virtual machine에 원격으로 접속할 수 있도록 설정

   - **system**

     만들어진 Ubuntu 선택 후 설정 - 시스템 

     - 마더보드 - 부팅 순서 - 플로피 해제

     - 프로세서 - 프로세서 개수 : 2개~원하는 만큼

   - **repository**(저장소)

     설정 - 저장소  - '저장 장치'의 `컨트롤러 : IDE`의 `비어있음` 클릭 후 우측 '속성'의 광학 드라이브에서 파란버튼 누른 후 `디스크에서 파일 선택` 에서 위 **Ubuntu 설치** 과정에서 다운받은 Ubuntu .iso 파일 선택

     > Ubuntu를 VirtualBox가 설치 된 드라이브(C 드라이브)에 넣은 것으로 이해하자.



### install ubuntu in VirtualBox

- 화면 크기

  가상 머신 선택 > 설정 > 디스플레이 > 크래픽 컨드롤러를 `VMSVGA` 에서 `VboxVGA`으로 선택 

  > 가상머신 창을 반응형으로 변경
  >
  > 이 때 ubuntu가 정상작동이 안되며 검은화면만 계속 될 경우 다시 `VMSVGA` 로 변경 >> 화면 크기 자동조절 됨





1. 시작

   시작 - 시동 디스크 선택 - **Ubuntu 설치** 과정에서 다운받은 Ubuntu .iso 파일 선택

   Ubuntu 설치 시작

   언어 선택 후 install ubuntu

   한국어 키보드 설정 > 계속하기

   updatas and other software 옵션은 default

   > 일반설치, ubuntu 설치 중 업데이트 다운로드 > 계속하기

   installation type 은 파티션을 나누는 부분. Erase disk and install ubuntu

   > 디스크를 지우고 Ubuntu설치 > 계속하기

   거주지 - seoul

2. 설치 완료

   컴퓨터 restart 버튼 누르면 ubuntu booting 
   `Please remove the installation medium, then press ENTER`  보이면 Enter

   > booting이 되지 않는다면 설정에 들어가서 위 **set VirtualBox**의 2.설정 part에서 `컨트롤러 : IDE` 을 비어있음으로 설정해서 제거해줘야함

3. 로그인

   Help improve Ubuntu - No  

   You're ready to go! 하며 설치 가능한 package를 보여준다.

   

4. 게스트 확장 설치 진행 (window10과 통신을 하기 위해)

   windows와 ubuntu사이의 붙여넣기가 적용되지 않는 경우

   실행중인 가상환경 창(Oracle VM VirtualBox)의 장치 탭 - 게스트 확장 CD 이미지 삽입 선택

   > cd룸에 cd넣은거라고 생각하면 됨
   >
   > - (VERR_PDM_MEDIA_LOCKED)에러 뜨면 이미 삽입되어있어서 락이 걸려있다는 내용 >> 다시 설정 필요함
   >
   >   해당 가상머신 종료 후 VirtualBox 메인화면의 가상머신 선택 > 설정 - 저장소 VBoxGuestAdditions.iso 가 있음 (꺼내가 다시 넣어야 인식됨)
   >
   > - 우측 속성칸 '광학 드라이브(D)' 의 선택버튼 옆 파란색 버튼 클릭 > `가상 드라이브에서 디스크 꺼내기` 클릭 
   >
   > - 다시 가상머신 on > 장치 > 게스트 확장 CD 이미지 삽입 선택, >> 실행 (인증 후 terminal 뜨고 진행하다 완료)

   창 뜨면 실행(run) 

    인증 후 terminal 뜨고 진행하다 완료

   터미널 마지막에 

   ```
   Press Return to close this window...
   ```

   뜨면 완료

   

3. 언어팩 설치

   한글 언어팩 설치 안될경우만 해당

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
   # update-locale LANG=ko_KR.UTF-8 LC_MESSAGES=POSIX
   ```

   > en_US.UTF-8 에서 ko_KR.UTF-8로 변환

   이후 MV logout후 다시 login

   

   **추가**

   virtualBox에서 가상머신의 설정 -> 일반 -> 고급 의

   - 클립보드 공유, 드래그 앤 드롭 을 **양방향** 으로 해야 window에서 복사한거 ubuntu안에서 붙여넣기 가능



4. 한글 입력 키 설정( fcitx-hangul 설치)

   `Ctrl + space`  으로 한글 전환이 안될 경우(기본적으로 `Ctrl + space` 만 가능)

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





네트워크 구성

1. 네트워크 연결

   우측상단 화살표 클릭 - 설정 - 네트워크 - 설정모양 아이콘 클릭

   IP주소 확인 가능(local의 사용 가능한 ip대역대 안에서 사용 가능한 ip가 자동으로 할당되어있음)

   이 때 static IP를 설정할 경우(위 **set VirtualBox**의 `Network 구성` 과정에서 결정한 특정 IP를 할당할 경우)

   해당 창의 위 Tap중 IPv4에서 자동 > 수동으로 변경 후 

   주소 : 10.100.0.105 (위에서 예시로 결정한 것)

   네트마스크 : 24 (CIDR값)

   게이트웨이 : 10.100.0.1 (`Network 구성` 과정에서 설정한 대역값 10.100.0.105 의 가장 앞 번호 )

   네임 서버(DNS) : 10.100.0.1 (게이트웨이와 동일)

   적용 후 연결됨을 껏다 키면 바뀐거 확인 가능

2. host

   1. 터미널에서 host name확인

      ```
      $ host name
      ```

   2. host name 변경

      편집기 열어서

      ```
      $ sudo vi /etc/hostname
      ```

      pull conneted name으로 바꾸자

      ```
      hibernation-ubuntu.example.com
      ```

      > :wq 으로 저장까지

   3. hosts file에 등록

      ```
      $ sudo vi /etc/hosts 
      ```

      여기서 

      ```
      127.0.0.1 	hibernation-ubuntu.example.com	# 을
      10.100.0.105 	hibernation-ubuntu.example.com # 으로 변경
      ```



network check

- 외부 network와 통신이 잘 되는지 확인

  ```
  $ ping -c 3 8.8.8.8
  ```






## Desktop

### set initial Ubuntu

1. root 계정 설정

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
      > password updata successfully 뜰 거임  녀애 

   



3. 언어팩 설치

   1. 전체 system을 한글로 변경하는 경우
   
      1. `Settings` > `Regions & Language` 의 상단 Language칸을 클릭 후 Korean선택 > **`Korean(101/104 key compatible)` 말고 `Korean` 선택** 후 add
   
      2. `Settings` > `Regions & Language` 의 하단 `Manage Installed Languages` 칸 선택 > 한글 언어팩이 추가되었기 때문에 install진행

      3. 이후 reboot
   
   2. 한글 입력키만 변경하는 경우
   
      1. `Settings` > `Regions & Language` 의 하단 `Manage Installed Languages` 칸 선택 > 한글 언어팩이 추가되었기 때문에 install진행

         > 이미 한글 언어팩이 설치되어 있으면 이 과정은 pass

      2. `Settings` > `Regions & Language` 의 Input Sources 아래 `+` 칸 선택 > 언어 목록에서 `Korean` 선택
   
      3. `Korean(Hangul)` 선택
   
         > 만약 없다면 reboot

      4. 3번까지 진행한다면 `Settings` > `Regions & Language` 의 Input Sources에 `Korean(Hangul)`이 추가되어 있다. 이 칸의 톱니바퀴 아이콘 클릭
   
         새롭게 나온 창의 Hangul Toggle Key의 Add 후 `한/영` 키 누르면 `Hangul`이 추가됨. 적용 후 desktop화면 우측 상단 한/en에서 직접 입력 선택하고나면 그 다음부터는 한/영 키로 toggle변경 가능 
   
      

      
   
      



4. 한글 입력 키 설정





5. 네트워크 구성

   1. 네트워크 연결

      우측상단 화살표 클릭 - 설정 - 네트워크 - 설정모양 아이콘 클릭

      IP주소 확인 가능(local의 사용 가능한 ip대역대 안에서 사용 가능한 ip가 자동으로 할당되어있음)

      이 때 static IP를 설정할 경우(위 **set VirtualBox**의 `Network 구성` 과정에서 결정한 특정 IP를 할당할 경우)

      해당 창의 위 Tap중 IPv4에서 자동 > 수동으로 변경 후 

      주소 : 10.100.0.105 (위에서 예시로 결정한 것)

      네트마스크 : 24 (CIDR값)

      게이트웨이 : 10.100.0.1 (`Network 구성` 과정에서 설정한 대역값 10.100.0.105 의 가장 앞 번호 )

      네임 서버(DNS) : 10.100.0.1 (게이트웨이와 동일)

      적용 후 연결됨을 껏다 키면 바뀐거 확인 가능

   2. host

      1. 터미널에서 host name확인

         ```
         $ host name
         ```

      2. host name 변경

         편집기 열어서

         ```
         $ sudo vi /etc/hostname
         ```

         pull conneted name으로 바꾸자

         ```
         hibernation-ubuntu.example.com
         ```

         > :wq 으로 저장까지

      3. hosts file에 등록

         ```
         $ sudo vi /etc/hosts 
         ```

         여기서 

         ```
         127.0.0.1 	hibernation-ubuntu.example.com	# 을
         10.100.0.105 	hibernation-ubuntu.example.com # 으로 변경
         ```

   

   network check

   - 외부 network와 통신이 잘 되는지 확인

     ```
     $ ping -c 3 8.8.8.8
     ```

     




### check resource

1. cpu

   ```
   $ lscpu
   ```

2. memory

   ```
   $ free -h
   ```

3. GPU

   ```
   $ sudo lshw -C display
   ```

   

   



### install  



#### Nvidia

사전에 설치되어있는 Nvidia, cuda를 전부 삭제하고 싶을 땐

```
$ sudo apt-get --purge remove "*cublas*" "cuda*" "*nvidia*"

$ sudo apt-get clean
$ sudo apt-get autoremove

$ sudo apt-get update
$ sudo apt-get upgrade
```



##### NVIDIA driver

1. check driver

   ```
   $ nvidia-smi
   ```

   없다고 뜨면

   ```
   $ ubuntu-drivers devices
   ```

   ```
   == /sys/devices/pci0000:00/0000:00:01.0/0000:01:00.0 ==
   modalias : pci:v000010DEd00001E07sv000019DAsd00005513bc03sc00i00
   vendor   : NVIDIA Corporation
   model    : TU102 [GeForce RTX 2080 Ti Rev. A]
   driver   : nvidia-driver-470-server - distro non-free
   driver   : nvidia-driver-450-server - distro non-free
   driver   : nvidia-driver-515-server - distro non-free
   driver   : nvidia-driver-470 - distro non-free
   driver   : nvidia-driver-510 - distro non-free
   driver   : nvidia-driver-515 - distro non-free recommended
   driver   : nvidia-driver-510-server - distro non-free
   driver   : nvidia-driver-418-server - distro non-free
   driver   : xserver-xorg-video-nouveau - distro free builtin
   ```

   위 권장 driver중에서 선택

   ```
   $ sudo apt install nvidia-driver-470
   ```

2. NVIDIA kernel module의 load를 도와주는 `modprobe` package를 install

   ```
   $ sudo apt-get install dkms nvidia-modprobe
   ```

   ```
   $ sudo apt update
   $ sudo apt upgrade
   
   $ sudo reboot
   ```

   reboot 후 

   ```
   $ nvidia-smi
   ```

##### CUDA toolkit

[여기](https://developer.nvidia.com/cuda-toolkit-archive) 에서 원하는 version선택한 후 `Installer Type` 은 runfile(local) 선택하여 나오는 명령어 복사

> `linux`, `x86_64`, `Ubuntu`, `20.04`, `runfile(local)`

```
$ wget https://developer.download.nvidia.com/compute/cuda/11.3.0/local_installers/cuda_11.3.0_465.19.01_linux.run
$ sudo sh cuda_11.3.0_465.19.01_linux.run
```

`Continue` 선택 후 `accept`입력, Driver은 선택 해제(X자 사라지게) 후 `install` 선택

install 완료시 출력 

```
Driver:   Not Selected
Toolkit:  Installed in /usr/local/cuda-11.3/
Samples:  Installed in /home/ainsoft/

Please make sure that
 -   PATH includes /usr/local/cuda-11.3/bin
 -   LD_LIBRARY_PATH includes /usr/local/cuda-11.3/lib64, or, add /usr/local/cuda-11.3/lib64 to /etc/ld.so.conf and run ldconfig as root

To uninstall the CUDA Toolkit, run cuda-uninstaller in /usr/local/cuda-11.3/bin
***WARNING: Incomplete installation! This installation did not install the CUDA Driver. A driver of version at least 465.00 is required for CUDA 11.3 functionality to work.
To install the driver using this installer, run the following command, replacing <CudaInstaller> with the name of this run file:
    sudo <CudaInstaller>.run --silent --driver

Logfile is /var/log/cuda-installer.log
```



이후 path설정

```
$ sudo vi ~/.bashrc
```

맨 아래 두 줄 입력

```
export PATH=/usr/local/cuda-11.3/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda-11.3/lib64:$LD_LIBRARY_PATH
```

활성화

```
$ source ~/.bashrc
```



check

```
$nvcc -V
```





#### chrome

```
$ wget https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
$ sudo apt install ./google-chrome-stable_current_amd64.deb
```



#### vscode 

1. [홈페이지](https://code.visualstudio.com/download)에서 알맞는 모델 다운

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

**또는**

```
$ sudo sh -c 'curl https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > /etc/apt/trusted.gpg.d/microsoft.gpg'
```

> Curl있어야함

```
$ sudo sh -c 'echo "deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main" > /etc/apt/sources.list.d/vscode.list'
$ sudo apt update
```

```
$ sudo apt install code
```





#### typora 

```
$ wget -qO - https://typora.io/linux/public-key.asc | sudo apt-key add -
$ sudo add-apt-repository 'deb https://typora.io/linux ./'
$ sudo apt -y install typora
```



#### curl, vim

```
$ sudo apt-get install -y curl vim		# Ubuntu
```

> 다른 text편집할때 vim으로 하려면 반드시 설치



#### git 

```
$ sudo apt-get install git				
$ git --version

$ git config --global user.name "HibernationNo1"
$ git config --global user.email "winter4958@gmail.com"
```



#### anaconda

[여기](https://repo.anaconda.com/archive/) 에서 아래 버전 선택해서 다운

[Anaconda3-2021.05-Linux-x86_64.sh](https://repo.anaconda.com/archive/Anaconda3-2021.05-Linux-x86_64.sh)

- download 

  ```
  $ wget https://repo.anaconda.com/archive/Anaconda3-2021.05-Linux-x86_64.sh
  ```

  > 년도에 따라 version 알맞게 사용. 	21.05가 현재까진 범용적

- start install process

  ```
  $ sudo bash Anaconda3-2021.05-Linux-x86_64.sh
  ```

  ```
  Please, press ENTER to continue
  >>> 
  뜨면 Enter하고 다 읽어내린 후 
  ```

  ```
  Do you accept the license terms? [yes|no]
  Please answer 'yes' or 'no':'
  >>> 
  뜨면 yes 입력 후 Enter
  ```

  ```
  Anaconda3 will now be installed into this location:
  /home/hibernation/anaconda3
  
    - Press ENTER to confirm the location
    - Press CTRL-C to abort the installation
    - Or specify a different location below
  
  [/home/{user_name}/anaconda3] >>> 		/home/ainsoft/anaconda3
  뜨면 새롭게 만들 directory의 name을 입력 (걍 anaconda3으로 )
  # 이 때 입력 후 바로 뜨는 문구 `PREFIX=/home/ainsoft/anaconda3` 를 아래 기억★★★
  
  ```

  > 만약 [/root/anaconda3] >>>  으로 뜨면 root에 설치된다는 뜻.
  >
  > `/home/username`의 위치에서 anaconda install을 진행할 때 발생한다. 
  >
  > 위 path가 보이는 경우 install이후에도 anaconda3가 작동하지 않을 수 있기 때문에
  >
  > `/home/username` 에서 `$ mkdir workspace` 와 같이 새 dir을 만든 후 그 안에서 anaconda설치를 진행해야 한다.

  ```
  Do you wish the installer to initialize Anaconda3
  by running conda init? [yes|no]
  
  no를 입력하면 콘다는 쉘 스크립트를 수정하지 못한다. yes를 누른다
  ```

- path추가

  ```
  $ sudo vi ~/.bashrc
  ```

  text 편집기가 열리면 맨 아래줄에 추가
  
  ```
  export PATH="~/anaconda3/bin:~/anaconda3/condabin:$PATH"
  ```

  > 예시로, `home/hibernation/workspace/tmp` 의 위치에서 `$ bash Anaconda3-2021.05-Linux-x86_64.sh` 를 했어도 위 명령어 그대로 입력
  
  
  
  
  
- 설치 확인

  bashrc 실행

  ```
  $ sudo source ~/.bashrc
  ```

  > (base)뜨는지 확인
  >
  > 안뜨면 `conda init`을 해야 함 (그 전에 `conda -V`을 통해 `conda : command not found` 가 뜨는지 확인)
  >
  > ```
  > $ conda init bash
  > ```
  >
  > bash사용
  >
  > > (base) 없애려면 ` $ conda deactivate`

  check version
  
  ```
  $ conda -V 
  ```
  
  > 만일 `conda : command not found` 가 뜨면
  >



#### docker

[공식 문서](https://docs.docker.com/engine/install/ubuntu/)

**Install using the repository**

1. install docker의 prerequisite packge

   ```
   $ sudo apt-get install \
       ca-certificates \
       curl \
       gnupg \
       lsb-release
   ```

2. GPH key추가

   ```
   $ sudo mkdir -p /etc/apt/keyrings
   $ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
   ```

3. repository를 follow하도록 설정

   ```
   $ echo \
     "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
     $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
   ```

   > arm기반의 cpu인 경우 위 명령어 대신 다른 명령어 사용(검색하기)
   >
   > - dpkg-buildpackage: command not found
   >
   >   ```
   >   sudo apt-get install dpkg-dev
   >   ```
   >
   >   

4. install Docker Engine (최신 version)

   ```
   $ sudo apt-get update
   $ sudo apt-get install docker-ce docker-ce-cli containerd.io docker-compose-plugin
   ```

   > 특정 version의 docker engine을 install하고자 한다면 공식 문서 참고
   >
   > - uninstall
   >
   >   ```
   >   $ sudo apt-get remove docker docker-ce docker-ce-cli containerd.io docker-compose-plugin
   >   ```
   >
   >   

5. check

   ```
   $ sudo docker run hello-world
   ```

   `Hello from Docker!` 이 포함된 출력문이 나오면 된것

6. 권한 설정

   root user가 아닌, host의 기본 user에게도 권한을 주기 위해 

   새로운 터미널 띄운 후 

   ```
   $ sudo usermod -a -G docker $USER
   $ sudo service docker restart
   ```

   이후 MV logout후 다시 login

   ```
   $ docker ps
   ```

   > 출력 확인
   >
   > ```
   > CONTAINER ID   IMAGE     COMMAND   CREATED   STATUS    PORTS     NAMES
   > ```

7. docker 실행 설정

   system이 재시작 되더라도 docker 자동 실행

   ```
   $ sudo systemctl enable docker
   ```

   



#### Kubernetes

##### minikube

- minikube

  [공식](https://minikube.sigs.k8s.io/docs/start/)

  CPU 2core 이상, Memory 2GB이상, Disk : 20GB이상

  ```
  $ curl -LO https://storage.googleapis.com/minikube/releases/latest/minikube-linux-amd64
  $ sudo install minikube-linux-amd64 /usr/local/bin/minikube
  ```

  check

  ```
  $ minikube version
  ```

- kubectl

  [공식](https://kubernetes.io/ko/docs/tasks/tools/install-kubectl-linux/)

  - 최신 릴리스 다운로드 (**최신 릴리스는 연동 안되는 tools이 많다.)**

    ```
    $ curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl"
    ```

    바이너리 검증(optional)

    ```
    $ curl -LO "https://dl.k8s.io/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl.sha256"
    $ echo "$(<kubectl.sha256)  kubectl" | sha256sum --check
    ```

    > 검증 성공시 아래처럼 출력
    >
    > ```
    > kubectl: OK
    > ```

  - 특정 version download
    
    ```
    $ sudo curl -LO https://dl.k8s.io/release/v1.19.3/bin/linux/amd64/kubectl
    ```

    > `v1.19.3` 가 추후 kubeflow를 위해 좋다
    
    바이너리 검증(optional)
    
    ```
    $ curl -LO "https://dl.k8s.io/v1.19.3/bin/linux/amd64/kubectl.sha256"
    $ echo "$(<kubectl.sha256)  kubectl" | sha256sum --check
    ```
    
  
  install kubectl
  
  ```
  $ sudo install -o root -g root -m 0755 kubectl /usr/bin/local/kubectl
  ```
  
  
  
  check
  
  ```
  $ kubectl version --client
  ```
  
  > ```
  > Client Version: version.Info{Major:"1", Minor:"24", GitVersion:"v1.24.2", GitCommit:"f66044f4361b9f1f96f0053dd46cb7dce5e990a8", GitTreeState:"clean", BuildDate:"2022-06-15T14:22:29Z", GoVersion:"go1.18.3", Compiler:"gc", Platform:"linux/amd64"}
  > ```
  >
  > 위 처럼 떠도 정상 (kubenetes server와 client의 version이 모두 출력하는 과정에서, host에서 kubenetes server를 생성하지 않았기 때문에 뜨는 문구)
  >
  > 이를 해결하기 위해 minukube 를 실행하여 kubenetes server를 설치
  >
  > - error
  >
  >   ```
  >   bash: /usr/bin/kubectl: No such file or directory
  >   ```
  >
  >   라고 뜨면
  >
  >   ```
  >   $ sudo install -o root -g root -m 0755 kubectl /usr/bin/kubectl
  >   ```
  >
  >   install root다시 정의
  
- kubenetes server

  ```
  $ minikube start --driver=docker
  ```

  check

  ```
  $ minikube status
  ```

  ```
  minikube
  type: Control Plane
  host: Running
  kubelet: Running
  apiserver: Running
  kubeconfig: Configured
  ```

  여기서 다시 아래 명령어를 입력하면

  ```
  $ kubectl version 
  ```

  ```
  Client Version: version.Info{Major:"1", Minor:"24", GitVersion:"v1.24.2", GitCommit:"f66044f4361b9f1f96f0053dd46cb7dce5e990a8", GitTreeState:"clean", BuildDate:"2022-06-15T14:22:29Z", GoVersion:"go1.18.3", Compiler:"gc", Platform:"linux/amd64"}
  Kustomize Version: v4.5.4
  Server Version: version.Info{Major:"1", Minor:"24", GitVersion:"v1.24.1", GitCommit:"3ddd0f45aa91e2f30c70734b175631bec5b5825a", GitTreeState:"clean", BuildDate:"2022-05-24T12:18:48Z", GoVersion:"go1.18.2", Compiler:"gc", Platform:"linux/amd64"}
  
  ```

  minikube 내부에 default로 생성되는 pod들이 정상적으로 생성됐는지 확인

  ```
  $ kubectl get pod -n kube-system
  ```

   

- uninstall minikube

  ```
  $ minikube delete
  ```

- uninstall k8s(kubernetes)

  ```
  $ sudo rm /usr/local/bin/kubectl
  ```



##### kubeadm

###### master

1. **check**

   ```
   $ sudo apt-get update
   ```

   ```
   $ systemctl status docker
   ```

   `Active: active (running)` 확인

   

2. **swapoff**

   ```
   $ sudo swapoff –a
   ```

   > ```
   > swapoff: –a: swapoff failed: No such file or directory
   > ```
   >
   > 위 문구가 출력되면 아래 명령어로 check
   >
   > 아예 영구적으로 사용 안할 시 fstab file에서 swap을 주석 처리
   >
   > ```
   > $ sudo sed -i 's/\/swap/\#/swap/' /etc/fstab
   > ```

   

   check

   ```
   $ free -m
   ```

3. **load kernel module, set sysctl parameters**

   load module

   ```
   $ sudo modprobe overlay
   $ sudo modprobe br_netfilter
   ```

   

   set config file

   ```
   $ cat <<EOF | sudo tee /etc/modules-load.d/k8s.conf
   overlay
   br_netfilter
   EOF
   ```

   

   set sysctl parameters

   ```
   $ cat <<EOF | sudo tee /etc/sysctl.d/k8s.conf
   net.bridge.bridge-nf-call-ip6tables = 1
   net.bridge.bridge-nf-call-iptables = 1
   net.ipv4.ip_forward = 1
   EOF
   ```

   ```
   $ sysctl --system
   ```

   

4. **install docekr runtime**

   ```
   $ cat <<EOF | sudo tee /etc/docker/daemon.json
   {
     "exec-opts": ["native.cgroupdriver=systemd"],
     "log-driver": "json-file",
     "log-opts": {
       "max-size": "100m"
     },
     "storage-driver": "overlay2"
   }
   EOF
   ```

   ```
   $ systemctl daemon-reload
   $ systemctl restart docker
   $ systemctl restart kubelet
   ```

   

5. **add kubernetes signing key**

   kubernetes공개 key download

   ```
   $ curl -s https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add
   ```

   

6. **Add Software Repositories**

   ```
   $ sudo apt-add-repository "deb http://apt.kubernetes.io/ kubernetes-xenial main"
   ```

    

7. **install kubeadm kubelet kubectl**

   ```
   $ sudo apt-get update
   $ sudo apt-get install kubeadm kubelet kubectl
   ```

   > ```
   > $ kubeadm version
   > $ kubelet version
   > $ kubectl version
   > ```

   

   activate kubelet

    ```
    $ systemctl start kubelet && systemctl enable kubelet
    ```

   

   apt-mark hold

   ```
   $ sudo apt-mark hold kubelet kubeadm kubectl
   ```

   

8. **Assign Unique cluster name** 

   ```
   $ sudo vi /etc/hosts
   ```

   맨 아래 ip와 hostname추가 (node name)

   ```
   192.168.0.107 myCluster
   ```

   

9. **Initialize Kubernetes on Master Node**

   ```
   $ sudo kubeadm init --apiserver-advertise-address 192.168.0.107 --pod-network-cidr=192.168.1.0/24
   ```

   - error

     `[ERROR CRI]` 발생 시

     ```
     $ sudo rm /etc/containerd/config.toml
     $ sudo systemctl restart containerd
     ```

   출력 확인

   ```
   To start using your cluster, you need to run the following as a regular user:
   
     mkdir -p $HOME/.kube
     sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
     sudo chown $(id -u):$(id -g) $HOME/.kube/config
   
   Alternatively, if you are the root user, you can run:
   
     export KUBECONFIG=/etc/kubernetes/admin.conf
   
   You should now deploy a pod network to the cluster.
   Run "kubectl apply -f [podnetwork].yaml" with one of the options listed at:
     https://kubernetes.io/docs/concepts/cluster-administration/addons/
   
   Then you can join any number of worker nodes by running the following on each as root:
   
   kubeadm join 192.168.0.107:6443 --token xop2oi.vyv8qv9zxi34tzpm \
           --discovery-token-ca-cert-hash sha256:a393c710216abf0ce4badb8c31d3e3c21622677cb948ec9efc269f0d622516bc
   ```

   cluster를 사용하기 위해 위 출력에 따라 아래 명령어 입력(해당 명령어를 수행해야 root가 아닌 계정으로도 cluster를 사용 = kubectl명령어를 수행할 수 있다.)

   ```
   $ mkdir -p $HOME/.kube
   $ sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
   $ sudo chown $(id -u):$(id -g) $HOME/.kube/config
   ```

   

   다른 device에서 worker node를 만들어 해당 master node(cluster)에 join할 때 위 출력에 있는 명령어 입력

   ```
   kubeadm join 192.168.0.107:6443 --token xop2oi.vyv8qv9zxi34tzpm \
           --discovery-token-ca-cert-hash sha256:a393c710216abf0ce4badb8c31d3e3c21622677cb948ec9efc269f0d622516bc
   ```

   

10. **Deploy Pod Network to Cluster**(install network add-on)

    add-on에는 여러가지가 있다.

    그 중 가장 보편적인 flannel 가상 network사용 (가장 최신 flannel manifast download)

    ````
    $ wget https://raw.githubusercontent.com/coreos/flannel/master/Documentation/kube-flannel.yml
    ````

    > 아래 명령어로 kubectl를 통해 바로 apply를 적용할 수 있다.
    >
    > ```
    > $ sudo kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/master/Documentation/kube-flannel.yml
    > ```
    >
    > 이 경우 `kube-flannel-cfg` 는 namespace : `kube-flannel ` 에 위치함

    

    

    verify
    
    ```
    $ kubectl get node
    ```
    
    ```
    NAME          STATUS   ROLES           AGE     VERSION
    master-node   Ready    control-plane   2m59s   v1.24.3
    ```

    
    
    ```
    $ kubectl get pods --all-namespaces
    ```
    
    ```
    NAMESPACE      NAME                                  READY   STATUS    RESTARTS   AGE
    kube-flannel   kube-flannel-ds-xvvn2                 1/1     Running   0          46s
    kube-system    coredns-6d4b75cb6d-2p695              1/1     Running   0          3m6s
    kube-system    coredns-6d4b75cb6d-zmqkw              1/1     Running   0          3m6s
    kube-system    etcd-master-node                      1/1     Running   0          3m20s
    kube-system    kube-apiserver-master-node            1/1     Running   0          3m20s
    kube-system    kube-controller-manager-master-node   1/1     Running   0          3m20s
    kube-system    kube-proxy-zvt2t                      1/1     Running   0          3m6s
    kube-system    kube-scheduler-master-node            1/1     Running   0          3m21s
    ```
    
    전부 Running인지 확인. 아니면 reset해야할때도 있음



**reset**

```
$ sudo kubeadm reset
```

```
$ rm $HOME/.kube/config
```



###### worker

위 master node 구축의 1번~8번까지 실행



이후 사전에 구축된 master node(cluster)의 join명령어 확인

```
kubeadm join 192.168.0.107:6443 --token xop2oi.vyv8qv9zxi34tzpm \
        --discovery-token-ca-cert-hash sha256:a393c710216abf0ce4badb8c31d3e3c21622677cb948ec9efc269f0d622516bc
```

- `--token` : token값

  token값은 24시간의 TTL이 있기 때문에 만료시 다시 생성이 필요하다

  ```
  $ sudo kubeadm token create
  ```

  check

  ```
  $ sudo kubeadm token list
  ```

- `--discovery-token-ca-cert-hash ` : join시 보안을 위해 hash값을 사용한다

  token의 hash값 얻는 법

  ```
  $ openssl x509 -pubkey -in /etc/kubernetes/pki/ca.crt | openssl rsa -pubin -outform der 2>/dev/null | openssl dgst -sha256 -hex | sed 's/^.* //'
  ```

- 아예 새 token 및 join 명령어 생성

  ```
  $ kubeadm token create --print-join-command
  ```

  

- 기본 문법

  ```
  $ kubeadm join [APISERVER_IP]:[APISERVER_PORT] --token [TOKEN] --discover-token-ca-cert-hash [CA_CERT]
  ```

  



#### kubeflow

[공식](https://www.kubeflow.org/docs/started/installing-kubeflow/), [github](https://github.com/kubeflow/manifests)

Prerequisites : `Kubernetes` (up to `1.21`) , `kustomize` (version `3.2.0`) 

**Install the Kubeflow Manifests manually**

kustomzie V3 기반으로  manifests file을 관리한다.

> kustomzie : helm과 비슷한 역할을 하며, 여러개의 yaml file을들 쉽게 관리하기 위한 도구이다.
>
> 여러 resource드르이 configuration을 템플릿과 커스터마이제션한 부분으로 나누어서 관리할 수 있다.

1. **kustomize** install

   [여기](https://github.com/kubernetes-sigs/kustomize/) 에서 현재 k8s version에 맞는 kustomize version을 확인하고 download binary

   ```
   $ kubectl version
   ```

   > kustomize 3.2.0에 알맞는 version확인

   [여기](https://github.com/kubernetes-sigs/kustomize/releases/tag/v3.2.0)의 **Asset** 아래 `kustomize_3.2.0_darwin_amd64` 의 링크 복사 (arm이면 arm꺼 복사)

   > 링크 없어지면 [releases](https://github.com/kubernetes-sigs/kustomize/releases?page) 에서 3.2.0 찾은 후 진행

   ```
   $ sudo wget https://github.com/kubernetes-sigs/kustomize/releases/download/v3.2.0/kustomize_3.2.0_linux_amd64
   ```

   > 만약`.tar.gz` format밖에 없다면 압축 풀고 진행
   >
   > ```
   > $ gzip -d kustomize_v3.2.0_linux_amd64.tar.gz
   > $ tar -xvf kustomize_v3.2.0_linux_amd64.tar
   > ```

   file의 mode 변경 (실행 가능하도록)

   ```
   $ sudo chmod +x kustomize_3.2.0_linux_amd64
   ```

   압축 풀고 file위치 변경

   ```
   $ sudo mv kustomize_3.2.0_linux_amd64 /usr/local/bin/kustomize
   ```

   check(새 terminal 열고)

   ```
   $ kustomize version
   ```

   ```
   Version: {KustomizeVersion:3.2.0 GitCommit:a3103f1e62ddb5b696daa3fd359bb6f2e8333b49 BuildDate:2019-09-18T16:26:36Z GoOs:linux GoArch:amd64}
   ```

   > uninstall : `sudo rm /usr/local/bin/kustomize`

2. start kubenetes 

   ```
   $ minikube start --driver=docker \
    --cpus='4' --memory='8g' \
    --kubernetes-version=v1.19.3 \
    --extra-config=apiserver.service-account-signing-key-file=/var/lib/minikube/certs/sa.key \
    --extra-config=apiserver.service-account-issuer=kubernetes.dafault.svc
   ```

   > `--extra-config` : token Request활성화 관련 설정
   >
   > `--kubernetes-version=v1.19.3` : version정확히 명시해야됨 `$ kubectl version` 으로 확인
   >
   > version잘못 명시하면 다시 install
   >
   > ```
   > $ minikube stop
   > $ minikube delete
   > $ minikube delete --all
   > ```

   check

   ```
   $ kubectl get sc
   ```

   ```
   NAME                 PROVISIONER                RECLAIMPOLICY   VOLUMEBINDINGMODE   ALLOWVOLUMEEXPANSION   AGE
   standard (default)   k8s.io/minikube-hostpath   Delete          Immediate           false                  15s
   
   ```

   

3. git clone [kubeflow/manifests](https://github.com/kubeflow/manifests)

   ```
   $ cd ~/minikube			# git clone할 임의의 위치
   $ git clone https://github.com/kubeflow/manifests.git
   $ cd manifests
   ```

   > ```
   > $ git checkout tags/v1.4.0 
   > ```
   >
   > 위 명령어를 통해 특정 version으로 checkout하면 `manifests/apps/pipeline/upstream/env/` 의 cert-manager dir이 사라지는  현상 발생 

   check

   ```
   $ git log
   ```

   > 마지막 commit확인

4. kubeflow의 individual components install ([github](https://github.com/kubeflow/manifests) 에 다 있음. 가능하면 해당 link에서 보고 install)

   > 각각 yaml file을 build이후 kubectl apply -f를 진행하게 되는, 이는 모두 순서대로 해야한다. 특정 kubeflow version을 설치한다면, 대한 version에 대한 tag로 이동하여 해당 version에 맞는 명령어를 입력해야 한다.

   1. cert-manager

      ```
      $ kustomize build common/cert-manager/cert-manager/base | kubectl apply -f -
      $ kustomize build common/cert-manager/kubeflow-issuer/base | kubectl apply -f -
      ```

      check

      ```
      $ kubectl get pod -n cert-manager
      ```

   2. istio

      ```
      $ kustomize build common/istio-1-14/istio-crds/base | kubectl apply -f -
      $ kustomize build common/istio-1-14/istio-namespace/base | kubectl apply -f -
      $ kustomize build common/istio-1-14/istio-install/base | kubectl apply -f -
      ```

      > kubeflow version에 따라 istio의 version이 다를 수 있으니 확인할 것

      ```
      $ kubectl get pod -n istio-system 
      ```

   3. Dex

      ```
      $ kustomize build common/dex/overlays/istio | kubectl apply -f -
      ```

   4. OIDC AuthService

      ```
      $ kustomize build common/oidc-authservice/base | kubectl apply -f -
      ```

   5. Knative

      > 설치 안됨 
      >
      > ```
      > unable to recognize "STDIN": no matches for kind "PodDisruptionBudget" in version "policy/v1"
      > unable to recognize "STDIN": no matches for kind "PodDisruptionBudget" in version "policy/v1"
      > ```
      >
      > 

      ```
      $ kustomize build common/knative/knative-serving/overlays/gateways | kubectl apply -f -
      $ kustomize build common/istio-1-14/cluster-local-gateway/base | kubectl apply -f -
      ```

   6. Kubeflow Namespace

      ```
      $ kustomize build common/kubeflow-namespace/base | kubectl apply -f -
      ```

      check

      ```
      $ kubectl get namespace   # Kubeflow라는 namespace생성되어야함
      ```

   7. Kubeflow Roles

      ```
      $ kustomize build common/kubeflow-roles/base | kubectl apply -f -
      ```

   8. Kubeflow Istio Resources

      ```
      $ kustomize build common/istio-1-14/kubeflow-istio-resources/base | kubectl apply -f -
      ```

      > kubeflow version에 따라 istio의 version이 다를 수 있으니 확인할 것

   9. Kubeflow Pipelines

      ```
      $ kustomize build apps/pipeline/upstream/env/cert-manager/platform-agnostic-multi-user | kubectl apply -f -
      ```

      > If your container runtime is not docker, use pns executor instead:
      >
      > ```
      > $ kustomize build apps/pipeline/upstream/env/platform-agnostic-multi-user-pns | kubectl apply -f -
      > ```

      만약 아래와 같은 error가 떳다면

      ```
      unable to recognize "STDIN": no matches for kind "CompositeController" in version "metacontroller.k8s.io/v1alpha1"
      ```

      위 설치 명령어 다시 입력

   10. KServe

       Install the KServe component

       ```
       $ kustomize build contrib/kserve/kserve | kubectl apply -f -
       ```

       > ```
       > anable to recognize "STDIN": no matches for kind "ClusterServingRuntime" in version "serving.kserve.io/v1alpha1"
       > ```
       >
       > 가 뜬다면 위 명령어 한번 더 입력

       Install the Models web app

       ```
       $ kustomize build contrib/kserve/models-web-app/overlays/kubeflow | kubectl apply -f -
       ```

   11. Katib

       ```
       $ kustomize build apps/katib/upstream/installs/katib-with-kubeflow | kubectl apply -f -
       ```

   12. Central Dashboard

       ```
       $ kustomize build apps/centraldashboard/upstream/overlays/kserve | kubectl apply -f -
       ```

   13. Admission Webhook

       ```
       $ kustomize build apps/admission-webhook/upstream/overlays/cert-manager | kubectl apply -f -
       ```

   14. Notebooks

       Install the Notebook Controller official Kubeflow component

       ```
       $ kustomize build apps/jupyter/notebook-controller/upstream/overlays/kubeflow | kubectl apply -f -
       ```

       Install the Jupyter Web App official Kubeflow component

       ```
       $ kustomize build apps/jupyter/jupyter-web-app/upstream/overlays/istio | kubectl apply -f -
       ```

   15. Profiles + KFAM

       ```
       $ kustomize build apps/profiles/upstream/overlays/kubeflow | kubectl apply -f -
       ```

   16. Volumes Web App

       ```
       $ kustomize build apps/volumes-web-app/upstream/overlays/istio | kubectl apply -f -
       ```

   17. Tensorboard

       Install the Tensorboards Web App official Kubeflow component

       ```
       $ kustomize build apps/tensorboard/tensorboards-web-app/upstream/overlays/istio | kubectl apply -f -
       ```

       Install the Tensorboard Controller official Kubeflow component

       ```
       $ kustomize build apps/tensorboard/tensorboard-controller/upstream/overlays/kubeflow | kubectl apply -f -
       ```

   18. training operator

       ```
       $ kustomize build apps/training-operator/upstream/overlays/kubeflow | kubectl apply -f -
       ```

   19. User Namespace

       ```
       $ kustomize build common/user-namespace/base | kubectl apply -f -
       ```

5. 모든 pod 구동

   ```
   $ kubectl get po -A -w
   ```

   > 길게는 몇십분까지 걸림

6. kubeflow 접속

   1. 새로운 terminal에서 port forwarding

      ```
      $ kubectl port-forward svc/istio-ingressgateway -n istio-system 8080:80
      ```

      > user 접속 정보 관련 설정을 변경하지 않는 경우의 default접속 정보는 아래와 같다
      >
      > - ID : user@example.com
      > - PW : 12341234

      이 terminal은 항상 열고있어야한다.

   2. 접속

      `localhost:8080` 으로 접속 후 login





#### pytorch

[여기](https://pytorch.org/) 에서 알맞는 설치법 명령어 복사하여 설치





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





