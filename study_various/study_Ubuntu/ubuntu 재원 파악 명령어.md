  





- CPU

  ```
  $ lscpu
  ```

  - `Socket(s)`: CPU 개수

  - `Core(s) per socket`: CPU에 포함된 core개수

  - `Thread(s) per core`: CPU code당 사용하는 Thread

  - `CPU(s)`: CPU core개수

    실제 프로세스 위치에서 인식하는 CPU core의 개수: `Core(s) per socket` x `Thread(s) per core` == `CPU(s)`

- GPU 

  ```
  $ nvidia-smi --query | fgrep 'Product Name'
  ```

- DISK

  ```
  $ sudo parted -l
  ```

  모델 명 끝에

  -  `scsi` : HDD
  - `nvme`: SSD

  

