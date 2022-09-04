## Make a backup

1. Ubuntu version check

   ```
   $ lsb_release -a
   ```

   ```
   No LSB modules are available.
   Distributor ID: Ubuntu
   Description:    Ubuntu 18.04.6 LTS
   Release:        18.04
   Codename:       bionic
   ```

   

2. Linux 커널 버전 check 

   ```
   $ uname -mrs
   ```

   ```
   Linux 4.20.17-042017-generic x86_64
   ```





## Upgrade all installed packages, remove all unused old kernels

1. Upgrade all installed packages of Ubuntu version 18.04

   ```
   $ sudo apt update && sudo apt upgrade && sudo apt dist-upgrade
   ```

   > - ```
   >   A new version (/tmp/fileedWd9c) of configuration file /etc/ssh/sshd_config is available, but the version installed currently has been locally modified. │ │ │ │ What do you want to do about modified configuration file sshd_config?
   >   ```
   >
   >   뜨면 
   >
   >   ```
   >   install the package maintainer's version    
   >   ```
   >
   >   선택
   >
   >   
   >
   > - ```
   >   0 upgraded, 0 newly installed, 0 to remove and 2 not upgraded.
   >   ```
   >
   >   2개의 upgrade가 잘 이루어지지 않았다는 의미
   >
   >   아래 명령어로 2개가 어떤것인지 확인
   >
   >   ```
   >   $ apt list --upgradable 
   >   ```
   >
   >   ```
   >   cuda/unknown 11.7.1-1 amd64 [upgradable from: 10.2.89-1]
   >   ```
   >
   >   위와 같이 upgrade가 불가능한 package가 있다면,  해당 package삭제(나중에 다시 install)
   >
   >   ```
   >   $ sudo apt-get --purge -y remove 'cuda*'
   >   ```
   >
   >   다시
   >
   >   ```
   >   $ apt list --upgradable 
   >   ```
   >
   >   ```
   >   Listing... Done
   >   ```

   

2. reboot

   ```
   sudo reboot
   ```

   

3. remove all unused old kernels

   ```
   sudo apt --purge autoremove
   ```

   



## Upgrade Ubuntu Linux to latest LTS

1. install update-manager-core package

   ```
   $ sudo apt install update-manager-core
   ```

   

2. check config of erlease-upgrades

   ```
   $ sudo vi /etc/update-manager/release-upgrades
   ```

   `Prompt=lts` 으로 설정되어있는지 확인

   

3. Upgrade Ubuntu Linux to latest LTS

   만약 ssh를 통해 방화벽을 업그레이드하고 컴퓨터에서 실행하려면 임시로 포트를 열고 진행해야 한다.

   ```
   $ sudo iptables -I INPUT -p tcp --dport 1022 -j ACCEPT
   ```

   

   ```
   $ sudo do-release-upgrade
   ```

   > 아래 문구 나올 시
   >
   > ```
   > Please install all available updates for your release before upgrading.
   > ```
   >
   > 무언가가 upgrade가 안되었다.
   >
   > [Upgrade all installed packages, remove all unused old kernels ](#Upgrade all installed packages, remove all unused old kernels)로 가서 다시 

   - ```
     LXD snap track 
     ```

     `4.0` 선택

    

4. verification

   ```
   $ lsb_release -a
   ```

   ```
   No LSB modules are available.
   Distributor ID: Ubuntu
   Description:    Ubuntu 20.04.5 LTS
   Release:        20.04
   Codename:       focal
   ```

   