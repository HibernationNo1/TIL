# WSL

WSL이란? `리눅스용 윈도우 하위 시스템(Windows Subsystem for Linux, WSL)`은 윈도우 10에서 네이티브로 리눅스 실행 파일(ELF)을 실행하기 위한 호환성 계층. 윈도우에서 리눅스를 사용하기 위한 도구이다.



## install

windows 10 version : 20H1, 20H2, 21H1 혹은 그 이상이여야 함



1. windows pawershell을 관리자 권한으로 실행

2. DISM 명령어로 Microsoft-Windows-Subsystem-Linux 기능 활성화

   ```
   $ dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
   ```

3.  dism 명령어로 `VirtualMachinePlatform` 기능을 활성화

   ```
   $ dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
   ```

   정상적으로 완료되었다면 재부팅

4. WSL설치

   ```
   $ wsl --install
   ```

   ['정식 설치 가이드'](https://docs.microsoft.com/ko-kr/windows/wsl/install#step-4---download-the-linux-kernel-update-package) 에서 wsl_update_x64.msi 다운

5. 기본적으로 사용할 WSL 버전을 2로 변경

   ```
   $ wsl --set-default-version 2
   ```

6. 마이크로소프트 스토어(Microsoft Store) 앱을 열고 Ubuntu설치

   설치가 끝나고앱이 실행되면 터미널이 하나 열리고 설치가 자동적으로 진행 >> 끄지 말고 기다릴 것

   > 설치 간 터미널창에 `Installing. this may take few minutes…` 라고 뜸
   >
   > 설치 후 사용할 user name과 password를 지정하는 입력창이 나타남
   >
   > 앱이 자동으로 실행되지 않는다면 windows + S키 입력 후 ubuntu를 검색해서 실행

7. 우분투 실행

   1. 계정 정보 입력
      - user name
      - passward

8. 터미널에서 wsl명령어 사용 가능

   ```
   $ wsl -l -v
   ```

   현재 설치된 linux확인

   > VERSION이 1로 나오면 아래 명령어 실행
   >
   > ```
   > $ wsl --set-version Ubuntu 2
   > ```





## tip

현재 사용중인 Ubuntu version출력

```
$ wsl cat /etc/lsb-release
```





bash shell 실행

```
$ wsl bash
```

실행 후 부터는 WSL2 Linux shell 프롬프트



### Vmmem

docker기반 WSL을 사용하면 Vmmem이라는 prosses가 메모리를 과점유하는 경우가 있다.

- 방법 1. 

  Vmmem의 memory점유 최대치 설정

  `c:\User\SOMEUSER` 에서

  `.wslconfig` file 생성

  ```
  [wsl2] 
  memory=4GB 
  swap=0 
  localhostForwarding=true
  ```

  - memory : 허용하는 momry점유 최대치

  

