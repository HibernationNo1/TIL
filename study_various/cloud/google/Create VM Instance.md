

create project 완료되었다 가정



## Create VM Instance 

1. VM 스펙 결정

   > virtual machine 유형
   >
   > - E2
   >
   >   

   ```
   Master Node
   - 1개
   - 리눅스 우분투 20.04 LTS
   - e2-medium(cpu2, 4GB)
   ```



 [N1 type](https://cloud.google.com/compute/docs/general-purpose-machines?hl=ko#n1_machines) 또는 [A2 type](https://cloud.google.com/compute/docs/accelerator-optimized-machines?hl=ko#a2_machines)를 사용하는 VM에만 GPU를 연결할 수 있다.(그 외 type은 GPU사용 불가)

|                            | [N1+GPU](https://cloud.google.com/compute/docs/gpus?hl=ko) | [A2](https://cloud.google.com/compute/docs/accelerator-optimized-machines?hl=ko#a2_vms) |
| :------------------------- | :--------------------------------------------------------- | :----------------------------------------------------------- |
|                            |                                                            |                                                              |
|                            |                                                            |                                                              |
| **워크로드 유형**          | 가속기 최적화                                              | 가속기 최적화                                                |
| **CPU 유형**               | Skylake, Broadwell, Haswell,Sandy Bridge, Ivy Bridge       | Cascade Lake                                                 |
| **아키텍처**               | x86                                                        | x86                                                          |
| **vCPU**                   | 1~96                                                       | 12~96                                                        |
| **vCPU 정의**              | Thread                                                     | Thread                                                       |
| **메모리**                 | 3.75~624GB                                                 | 85~1360GB                                                    |
| **확장 메모리**            | O                                                          | X                                                            |
| **단독 테넌시**            | O                                                          | X                                                            |
| **중첩된 가상화**          | O                                                          | X                                                            |
| **커스텀 VM 형태**         | O                                                          | X                                                            |
| **컨피덴셜 컴퓨팅**        | X                                                          | X                                                            |
| **디스크 인터페이스 유형** | SCSI, NVMe                                                 | SCSI, NVMe                                                   |
| **로컬 SSD**               | O                                                          | O                                                            |
| **최대 로컬 SSD**          | 9TB                                                        | 3TB                                                          |
| **표준 PD**                | 영역 및 리전                                               | 영역                                                         |
| **균형 있는 PD**           | 영역 및 리전                                               | 영역                                                         |
| **SSD PD**                 | 영역 및 리전                                               | 영역                                                         |
| **익스트림 PD**            | X                                                          | X                                                            |
| **네트워크 인터페이스**    | gVNIC, VirtIO-Net                                          | gVNIC, VirtIO-Net                                            |
| **네트워크 성능**          | 2~32Gbps                                                   | 24~100Gbps                                                   |
| **고대역폭 네트워크**      | X                                                          | 50~100Gbps                                                   |
| **최대 GPU 수**            | 8                                                          | 16                                                           |
| **할인**                   | CUD, Spot                                                  | CUD, Spot                                                    |
| **Coremark 점수(1vCPU)**   | X                                                          | X                                                            |



- 비용:  vCPU, GPU, GB 단위 메모리의 최소 요금은 **1분**부터 시작