# nvidia-driver upgrade



## ubuntu

18.04



1. apt update, upgrade

   ```
   $ sudo apt update
   $ sudo apt upgrade
   ```

2. 설치 가능한 ubuntu driver 확인

   ```
   $ ubuntu-drivers devices
   ```

3. apt install

   - 필요시 기존 NVIDIA driver제거

     ```
     $ sudo apt-get remove --purge '^nvidia-.*'
     ```

   ```
   $ sudo apt install nvidia-driver-535
   ```

   > 문제를 바로잡을 수 없습니다. 망가진 고정 패키지가 있습니다. 
   >
   > 라는 문구가 뜨면 아래 명려엉 실행
   >
   > ```
   > $ sudo apt-get clean
   > $ sudo apt-get autoclean
   > $ sudo apt-get autoremove
   > ```

   이후 재시작

   ```
   $ sudo reboot now
   ```

4. 추가 package repository 설치(option)

   ```
   $ sudo add-apt-repository ppa:graphics-drivers/ppa
   $ sudo apt update
   ```

   때때로, 특정 드라이버 버전이 특정 소스에서만 사용 가능할 수 있다. NVIDIA 공식 PPA를 추가하는것 고려

5. 확인

   ```
   $ nvidia-smi
   ```

   - `Failed to initialize NVML: Driver/library version mismatch` 라는 문구 출력시 `sudo reboot now`

