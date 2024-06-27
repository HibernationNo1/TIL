# Multi-Instance GPU(MIG)



### Activate MIG mode 

> 아래 예시는 A100으로 수행했음



**1. 현재 GPU에서 실행중인 프로세스 전부 삭제**

> 필수 프로세스라도, GPU를 다른 프로세스에서 사용중이라면 아래 출력이 나온다. 이런 경우 제대로 된 MIG적용이 안될 수 있으니 모든 프로세스를 종료하거나 reboot한 후 다시 시도할 것. 
>
> ```
> Warning: MIG mode is in pending enable state for GPU 00000000:01:00.0:In use by another client
> 00000000:01:00.0 is currently being used by one or more other processes (e.g. CUDA application or a monitoring application such as another instance of nvidia-smi). Please first kill all processes using the device and retry the command or reboot the system to make MIG mode effective.
> All done.
> ```

1. 현재 GPU에서 실행중인 프로세스 확인

   ```
   $ sudo fuser -v /dev/nvidia*
   ```

   아래는 A100 DGX station 예시

   ```
                        USER        PID ACCESS COMMAND
   /dev/nvidia0:        root       2180 F.... nv-hostengine
                        root       2284 F.... nvsm_core
                        nvidia-persistenced   2890 F.... nvidia-persiste
                        gdm        3392 F...m Xorg
                        gdm        3461 F...m gnome-shell
   /dev/nvidia1:        root       2180 F.... nv-hostengine
                        root       2284 F.... nvsm_core
                        nvidia-persistenced   2890 F.... nvidia-persiste
                        gdm        3392 F...m Xorg
                        gdm        3461 F...m gnome-shell
   /dev/nvidia2:        root       2180 F.... nv-hostengine
                        root       2284 F.... nvsm_core
                        nvidia-persistenced   2890 F.... nvidia-persiste
                        gdm        3392 F...m Xorg
                        gdm        3461 F...m gnome-shell
   /dev/nvidia3:        root       2180 F.... nv-hostengine
                        root       2284 F.... nvsm_core
                        nvidia-persistenced   2890 F.... nvidia-persiste
                        gdm        3392 F...m Xorg
   /dev/nvidiactl:      root       2180 F.... nv-hostengine
                        root       2284 F.... nvsm_core
                        nvidia-persistenced   2890 F.... nvidia-persiste
                        gdm        3392 F...m Xorg
                        gdm        3461 F...m gnome-shell
   /dev/nvidia-modeset: nvidia-persistenced   2890 F.... nvidia-persiste
                        gdm        3392 F.... Xorg
                        gdm        3461 F.... gnome-shell
   /dev/nvidia-uvm:     root       2180 F.... nv-hostengine
                        root       2284 F.... nvsm_core
   
   ```

2. GPU에 실행중인 아래 프로세스 종료 ( kill 로 죽이는건 소용없음)

   ```
   nv-hostengine	# GPU의 상태를 모니터링하고 관리				# sudo systemctl stop nvidia-dcgm
   nvsm_core		# GPU 및 시스템 하드웨어의 상태를 모니터링        # sudo systemctl stop nvsm
   Xorg			# GUI환경을 복구하기 위해 설치했던 패키지. 		  # sudo systemctl stop gdm
   gnome-shell		# GUI환경을 복구하기 위해 설치했던 패키지. 
   ```

   ```
   $ sudo systemctl stop nvidia-dcgm
   $ sudo systemctl stop nvsm
   $ sudo systemctl stop gdm
   ```

   



**2.  Persistence Mode 활성화**

1. 모든 GPU에 대해 Persistence Mode 활성화

   ```
   $ sudo nvidia-persistenced
   ```

   GPU 드라이버가 GPU의 전력 상태를 유지하여 초기화 시간을 줄이고, GPU가 재부팅 없이 연속적으로 사용될 수 있도록 한다.

   

   - 계속해서 아래와 같은 출력이 나온다면

     ```
     nvidia-persistenced failed to initialize. Check syslog for more details.
     ```

      MIG를 활성화 할 GPU에만  Persistence Mode 활성화

     ```
     $ sudo nvidia-smi -i 0 -pm 1
     ```

     - `-i 0`: 0번 GPU에 대해 명령어 실행 (예시 0번)
     - `-pm 1`: Persistence Mode 활성화 (값 `0` 은 비활성화)

     ```
     Enabled persistence mode for GPU 00000000:01:00.0.
     All done.
     ```

     

   

   

   

   

2. 상태 확인

   ```
   $ sudo systemctl status nvidia-persistenced
   ```

   ```
   ● nvidia-persistenced.service - NVIDIA Persistence Daemon
        Loaded: loaded (/lib/systemd/system/nvidia-persistenced.service; enabled; vendor preset: enabled)
       Drop-In: /etc/systemd/system/nvidia-persistenced.service.d
                └─nv-persistence-override.conf
        Active: active (running) since Tue 2024-06-25 17:16:09 KST; 4s ago
       Process: 40015 ExecStartPre=/usr/bin/nvidia-smi (code=exited, status=0/SUCCESS)
       Process: 40031 ExecStart=/usr/bin/nvidia-persistenced --user nvidia-persistenced --persistence-mode >
      Main PID: 40032 (nvidia-persiste)
         Tasks: 1 (limit: 618759)
        Memory: 3.0M
        CGroup: /system.slice/nvidia-persistenced.service
                └─40032 /usr/bin/nvidia-persistenced --user nvidia-persistenced --persistence-mode --verbose
   
   
   ```

   `Active: active (running)` 확인

   - 만일 active상태가 아니라면 아래 명령어로 프로세스 재실행

     ```
     $ sudo systemctl enable nvidia-persistenced
     $ sudo systemctl start nvidia-persistenced
     ```

     

**3. MIG모드 활성화**

1. 0번 GPU에 MIG모드 활성화

   ```
   $ sudo nvidia-smi -i 0 -mig 1
   ```

   ```
   Enabled MIG Mode for GPU 00000000:01:00.0
   All done.
   ```

   > 해당 GPU를 다른 프로세스에서 사용중이라면 아래 출력이 나온다. 이런 경우 제대로 된 MIG적용이 안될 수 있으니 모든 프로세스를 종료하거나 reboot한 후 다시 시도할 것. 
   >
   > ```
   > Warning: MIG mode is in pending enable state for GPU 00000000:01:00.0:In use by another client
   > 00000000:01:00.0 is currently being used by one or more other processes (e.g. CUDA application or a monitoring application such as another instance of nvidia-smi). Please first kill all processes using the device and retry the command or reboot the system to make MIG mode effective.
   > All done.
   > ```

2. 0번 GPU에 대해서 MIG 모드 활성화 확인

   ```
   $ nvidia-smi -i 0 -q | grep -A 2 -i "MIG Mode"
   ```

   ```
       MIG Mode
           Current                           : Enabled
           Pending                           : Enabled
   ```

   Current, Pending 모두 Enabled 상태여야 한다.

3. 원래 gpu에 할당되었던 프로세스들 다시 start

   ```
   $ sudo systemctl start nvidia-dcgm
   $ sudo systemctl start nvsm
   $ sudo systemctl start gdm
   ```

   

**4. instance 생성**

1. 예시) 1g.5gb instance 7개 생성

   ```
   $ sudo nvidia-smi mig -cgi 19,19,19,19,19,19,19 -C
   ```

   - `-cgi`: "Create GPU Instances"의 약자로, GPU 인스턴스를 생성한다.
   - `19,19,19,19,19,19,19`: 7개의 GPU 인스턴스를 생성하며, 각각의 인스턴스가 1g.5gb 유형을 나타낸다.
   - `-C`: 명령어를 실행하여 인스턴스를 생성한다.

2. 생성된 instance의 device 확인

   ```
   $ nvidia-smi -L
   ```

   ```
   GPU 0: NVIDIA A100-SXM4-80GB (UUID: GPU-9434a402-0d94-4ef8-93d0-0528ee662e9c)
     MIG 1g.10gb     Device  0: (UUID: MIG-e138a708-679d-5075-ab88-ba8e298ec5d3)
     MIG 1g.10gb     Device  1: (UUID: MIG-ae9a37c7-4e38-5a4c-8229-7f07dc126721)
     MIG 1g.10gb     Device  2: (UUID: MIG-788dbffa-1d55-5ea9-a591-40d9575812f9)
     MIG 1g.10gb     Device  3: (UUID: MIG-557c3eba-c526-520d-b50f-a5e73a5507fc)
     MIG 1g.10gb     Device  4: (UUID: MIG-fd5674fe-5f31-5006-b6c3-05ca43b4ac42)
     MIG 1g.10gb     Device  5: (UUID: MIG-23738dbe-fdf9-55bb-b44f-50d31fce3c53)
     MIG 1g.10gb     Device  6: (UUID: MIG-9b1ad31d-c893-5aba-a20b-8cc97bed5f40)
   GPU 1: NVIDIA A100-SXM4-80GB (UUID: GPU-0e28d4e1-04b2-1d52-1352-827618fb6373)
   GPU 2: NVIDIA DGX Display (UUID: GPU-a072e8f4-1f50-8158-39cd-12d80ffcbeed)
   GPU 3: NVIDIA A100-SXM4-80GB (UUID: GPU-af6294b0-350e-25de-b043-bdc16ea66283)
   ```

   0번 GPU가 7개로 쪼개진 것을 확인할 수 있다.

3. docker 에 GPU할당 예시 (**MIG를 활성화 한 0번 GPU의 첫 번째 instance를 할당**)

   ```
     exam_container:          
       build :
         context : ./
         dockerfile: Dockerfile.exam
       image: 'exam:0.1'
       container_name: 'exam_container'    
       environment:
         - NVIDIA_VISIBLE_DEVICES=MIG-e138a708-679d-5075-ab88-ba8e298ec5d3      # device number 확인 필요
       ports:
         - '10110:10010'
       volumes:
         - /etc/localtime:/etc/localtime:ro
       command: /bin/bash
       shm_size: 8G
       ipc : "host"
       runtime: "nvidia"
       stdin_open: true # docker 유지
       tty: true # docker 유지
   ```

   환경변수 `NVIDIA_VISIBLE_DEVICES`의 값에 할당하고자 하는 GPU의 UUID를 입력한다.



**5. MIG 비활성화 **

1. 0번 GPU의 모든 MIG instance 제거

   ```
   $ sudo nvidia-smi mig -i 0 -dci
   ```

   ```
   Successfully destroyed compute instance ID  0 from GPU  0 GPU instance ID  7
   Successfully destroyed compute instance ID  0 from GPU  0 GPU instance ID  8
   Successfully destroyed compute instance ID  0 from GPU  0 GPU instance ID  9
   Successfully destroyed compute instance ID  0 from GPU  0 GPU instance ID 11
   Successfully destroyed compute instance ID  0 from GPU  0 GPU instance ID 12
   Successfully destroyed compute instance ID  0 from GPU  0 GPU instance ID 13
   Successfully destroyed compute instance ID  0 from GPU  0 GPU instance ID 14
   ```

   - `-dci`: "Delete Compute Instances"의 약자로, 지정된 GPU의 모든 MIG 인스턴스를 삭제한다.

2. 0번 GPU의 MIG 모드 비활성화

   이번에도 관련 프로세스 전부 stop해야 함

   ```
   $ sudo systemctl stop nvidia-dcgm
   $ sudo systemctl stop nvsm
   $ sudo systemctl stop gdm
   ```

   이후 비활성화

   ```
   $ sudo nvidia-smi -i 0 -mig 0
   ```

3. 비활성화 확인

   ```
   $ nvidia-smi -i 0 -q | grep -A 2 -i "MIG Mode"
   ```

   ```
       MIG Mode
           Current                           : Disabled
           Pending                           : Disabled
   ```

   

### Intance type

- **1g.5gb**
  - Compute Instance: 19
  - GPU 메모리: 5GB
  - GPU 코어: 1/7
  - 명령어: `sudo nvidia-smi mig -cgi 19 -C`
- **2g.10gb**
  - Compute Instance: 14
  - GPU 메모리: 10GB
  - GPU 코어: 2/7
  - 명령어: `sudo nvidia-smi mig -cgi 14 -C`
- **3g.20gb**
  - Compute Instance: 9
  - GPU 메모리: 20GB
  - GPU 코어: 3/7
  - 명령어: `sudo nvidia-smi mig -cgi 9 -C`
- **4g.40gb**
  - Compute Instance: 5
  - GPU 메모리: 40GB
  - GPU 코어: 4/7
  - 명령어: `sudo nvidia-smi mig -cgi 5 -C`
- **7g.80gb**
  - Compute Instance: 0
  - GPU 메모리: 80GB (전체 GPU)
  - GPU 코어: 전체
  - 명령어: `sudo nvidia-smi mig -cgi 0 -C`



**여러 개의 instance 생성**

- `1g.5gb` 7개 생성  (코어 7/7 사용)

  ```
  $ sudo nvidia-smi mig -cgi 19,19,19,19,19,19,19 -C
  ```

- `2g.10gb` 2개 생성  (코어 4/7 사용)

  ```
  $ sudo nvidia-smi mig -cgi 14,14 -C
  ```

- `1g.5gb` 3개, `2g.10gb` 2개 생성  (코어 7/7 사용)

  ```
  $ sudo nvidia-smi mig -cgi 19,19,19, 14,14 -C
  ```

  다른 type의 instance를 동시에 생성할 수 있다.



