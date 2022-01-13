

{:toc}





## 1. install

### CUDA Toolkit 

#### windows

**1.  check GPU**

1. 그래픽카드 확인

   장치관리자 > 디스플레이 어뎁터

2. [여기](https://www.studio1productions.com/Articles/NVidia-GPU-Chart.htm)서 CUDA core 수 확인

   > 예시
   >
   > ![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2F49t3X%2FbtqyEA98R9n%2FxTxNRuRsrJeB8yW2UgHb10%2Fimg.png)
   >
   > NVIDIA GTX-1060 3GB는 코어 1152임을 확인
   >
   > CUDA Cores = **1152**

3. 성능 확인

   GPU이름으로 검색 후 CUDA Compute Capability확인

   > NVIDIA GTX-1060이라면 
   >
   > [여기](https://www.wikiwand.com/en/CUDA) 서 ctrl + f로 `1060` 검색  (또는 [여기](https://en.wikipedia.org/wiki/CUDA))
   >
   > ![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2F0b42E%2FbtqyGmpmz1S%2FCoqplHiiDHOyphS9sBOVe0%2Fimg.png)
   >
   > CUDA Compute Capability = **6.1**

**2. graphic driver 설치**

1.  [여기](https://www.nvidia.co.kr/Download/index.aspx?lang=kr) 에서 graphic driver를 설치

   > 제품유형 : GeForce
   >
   > 시리즈 : GeForce 10 Series
   >
   > 계열 : GeForce GTX 1060
   >
   > windows 10 64-bit
   >
   > 다운로드 타입 : Game -Ready 드라이버 : 일반 사용자용,  sutido 드라이버 : 작업툴에서 성능발휘

**3. Download CUDA**

1. 쿠다 version 확인

   > NVIDIA GTX-1060이라면
   >
   > ![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbeO6bC%2FbtqyGvNswxK%2FNDZCW4KvK2zKZp2ejkkuH0%2Fimg.png)
   >
   > CUDA Compute Capability = **6.1** 이기에 SDK = 10.0~10.1 임을 확인

2. 자신의 version에 맞게 다운

   [여기](https://developer.nvidia.com/cuda-toolkit-archive)서 알맞는 version 선택

   > ![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fzq3zP%2FbtqyFZ2v0R5%2FpUShfkRCyKo3NvMuc8p2W0%2Fimg.png)
   >
   > - network는 internet을 통해 여러 번 다운받는 것
   > - local은 한 번에 받는 것 (internet이 일정하게 문제 없다면 이걸로 받기)
   >
   > visual studio가 설치되어 있어야함
   >
   > [여기](https://visualstudio.microsoft.com/ko/thank-you-downloading-visual-studio/?sku=Community&rel=16) 에서 community 2019다운

3. 경로 지정 후 설치 (default로 지정함)

   > `C:\Users\마이노\AppData\Local\Temp\CUDA`

4. 환경 변수 추가 및 확인

   경로를 default로 했으면 환경 변수 자동으로 추가됨

   시스템 환경 변수 > 환경 변수

   `cudart64_100.dll` 가 있는 path

   `C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v10.0\bin`

#### linux

1. GPU확인

   ```
   $ nvidia-smi -L
   ```

   [여기](https://www.studio1productions.com/Articles/NVidia-GPU-Chart.htm)서 CUDA core 수 확인  (4352)

2. CUDA Compute Capability확인

   [여기](https://www.wikiwand.com/en/CUDA) (7.5)

3. graphic driver 설치

   1. 사용 가능한 graphic driver확인

      ```
      $ ubuntu-drivers devices
      ```

   2. 사용 가능한 driver중 하나 설치

      ```
      $ sudo apt install nvidia-driver-460		# 예시임
      ```

   3. 확인

      ```
      nvidia-smi
      ```

      `Diver Version`: 확인. 적용 안되어있으면 `sudo reboot`

4. download cuda coolkit

   [여기](https://developer.nvidia.com/cuda-toolkit-archive)서 알맞는 version 선택

   선택하면 명령어를 알려줌. 따라서 설치

   1. install과정에서 `Abort`와 `Continue` 선택은 `Continue` 선택

   2. 다음과 같은 error가 난다면 gcc가 설치 안된 상태

      ```
       Failed to verify gcc version. See log at /var/log/cuda-installer.log for details.
      ```

      이럴땐 필수 프로그램 install

      ```
      $ sudo apt-get install build-essential 
      ```

   3. `accept/declin/quit` 뜨면 accept입력

   4. CUDA Installer에서 

      `Driver`에서 체크 해제 후 `install`에서 엔터

5. CUDA Toolkit 환경 변수 추가 

   ```
   $ sudo sh -c "echo 'export PATH=$PATH:/usr/local/cuda-11.2/bin' >> /etc/profile"
   $ sudo sh -c "echo 'export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda-11.2/lib64' >> /etc/profile"
   $ sudo sh -c "echo 'export CUDADIR=/usr/local/cuda-11.2' >> /etc/profile"
   $ source /etc/profile
   ```

   > cuda version 잘 확인할 것

6. check 

   ```
   nvcc -V
   ```

   

- remove CUDA

  ```
  $ sudo rm -rf /usr/local/cuda*
  $ export PATH=$PATH:/usr/local/cuda-11.0/bin
  $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda-11.0/lib64
  $ export CUDADIR=/usr/local/cuda-11.0
  
  ```

  

  

### cuDNN

#### windows

**Download cuDNN**

cuDNN는 회원가입을 해야 다운로드 가능

[여기](https://developer.nvidia.com/cudnn)에서 로그인 후 다운로드

다운받은 file(`bin`, `include`, `lib`)을 

`C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.4` 에 옮긴다.

#### linux

[여기](https://developer.nvidia.com/cudnn)에서 로그인 후 다운로드

```
$ cd 다운로드 위치
```



1. 압축 풀어서 파일 복사

   ```
   $ tar xvzf cudnn-11.2-linux-x64-v8.1.0.77.tgz
   ```

   > `cudnn-11.2-linux-x64-v8.1.0.77.tgz` 을 다운받았을 때의 명령어

   ```
   $ sudo cp cuda/include/cudnn* /usr/local/cuda/include
   $ sudo cp cuda/lib64/libcudnn* /usr/local/cuda/lib64
   $ sudo chmod a+r /usr/local/cuda/include/cudnn.h /usr/local/cuda/lib64/libcudnn*
   ```

2. link 할당

   ```
   $ sudo ln -sf /usr/local/cuda-11.2/targets/x86_64-linux/lib/libcudnn_adv_train.so.8.1.0 /usr/local/cuda-11.2/targets/x86_64-linux/lib/libcudnn_adv_train.so.8
   $ sudo ln -sf /usr/local/cuda-11.2/targets/x86_64-linux/lib/libcudnn_ops_infer.so.8.1.0  /usr/local/cuda-11.2/targets/x86_64-linux/lib/libcudnn_ops_infer.so.8
   $ sudo ln -sf /usr/local/cuda-11.2/targets/x86_64-linux/lib/libcudnn_ops_infer.so.8.1.0  /usr/local/cuda-11.2/targets/x86_64-linux/lib/libcudnn_ops_infer.so.8
   $ sudo ln -sf /usr/local/cuda-11.2/targets/x86_64-linux/lib/libcudnn_ops_infer.so.8.1.0  /usr/local/cuda-11.2/targets/x86_64-linux/lib/libcudnn_ops_infer.so.8
   $ sudo ln -sf /usr/local/cuda-11.2/targets/x86_64-linux/lib/libcudnn_ops_infer.so.8.1.0  /usr/local/cuda-11.2/targets/x86_64-linux/lib/libcudnn_ops_infer.so.8
   $ sudo ln -sf /usr/local/cuda-11.2/targets/x86_64-linux/lib/libcudnn_ops_infer.so.8.1.0  /usr/local/cuda-11.2/targets/x86_64-linux/lib/libcudnn_ops_infer.so.8
   ```

3. 새로 추가된 library를 system에서 찾을 수 있도록 설정

   ```
   $ sudo idconfig
   ```

4. 확인

   1. root dir로 이동

      ```
      cd ~
      ```

   2. ```
      ldconfig -N -v $(sed 's/:/ /' <<< $LD_LIBRARY_PATH) 2>/dev/null | grep libcudnn
      ```

      아래처럼 알맞는 version이 보여야 함

      ```
      libcudnn_adv_train.so.8 -> libcudnn_adv_train.so.8.1.0
      libcudnn_adv_infer.so.8 -> libcudnn_adv_infer.so.8.1.0
      libcudnn_ops_infer.so.8 -> libcudnn_ops_infer.so.8.1.0
      libcudnn.so.8 -> libcudnn.so.8.1.0
      libcudnn_ops_train.so.8 -> libcudnn_ops_train.so.8.1.0
      libcudnn_cnn_train.so.8 -> libcudnn_cnn_train.so.8.1.0
      libcudnn_cnn_infer.so.8 -> libcudnn_cnn_infer.so.8.1.0
      ```

      > 예시는 8.1.0임

   





## 2. check GPU

#### nvidia-smi

```
$ nvidia-smi
```



**첫째 줄** : version설명

- `Driver Version` : 현재 설치되어 있는 nvidia driver version

- `CUDA Version` : 현재 설치되어 있는 driver version과 맞는 추천 cuda version

  > 설치된 version이 아님

**둘째 줄** : 셋째 줄 에 대한 명칭. GPU상태 및 설정을 명시한다.

- `GPU` : GPU사용 정도를 나타낸다.

- `Fan` : fan사용정도를 나타낸다.

  > N/A이면 fan이 없는 Tesla모델
  >
  > 44% : fan이 44%의 효율로 돌아가고 있음

- `Name` : GPU의 이름

- `Temp` : 현재 온도

- `Perf` : P0부터 P12까지 존재하며, P0에 가까울수록 GPU의 performance가 좋다.

- `Pwr: Usage/Cap` : 현재 전력사용량과 최대 용량을 나타낸다.

- `Bus-Id` : 서버 제조사의 메인보드마다 가지고 있는 PCI slot에 부여된 BUS-ID이다.

  > 이것을 참고로 하여 사용하는 GPU number와 메인보드의 PCI 슬롯을 매칭 시켜 확인할 수 있다.

- `Disp.A` : RTX나 Quadro계열의 GPU에서 사용된다.

  > 모니터를 연결한 출력 포트의 GPU는 on상태

- `Memory-Usage` : 현재 사용하는 GPU 메모리 / 총 GPU 메모리

- `Voltaile GPU-Util` : GPU의 총사용량이다.

  > GPU는 메모리로만 동작하지 않고 SMs와 같은 프로세서도 존재한다.

- `Uncorr. ECC` : default값은 ECC ON 상태이며, ECC count가 생기면 숫자 0이 1,2.. 이상으로 변경된다.

  > - ECC ON 상태에서 count가 계속 발생하면 시스템 Hang이 발생한다. 
  >
  >   현재 작업중인 job에 문제가 생길 수 있다는 의미.
  >
  > -  Hang을 예방하기 위해 Off 시켜 놓고 작업하는 곳이 많으며, ECC Off를 하게 되면 놀랍게도 GPU Memory 총량이 늘어나게 된다
  >
  >   ECC Off 명령어 : `nvidia-smi -e 0`

- `Compute M.` : Compute Mode의 모드이다.

  > 0 - default
  >
  > 1 - exclusive_thread
  >
  > 2 - prohibited
  >
  > 3 - exclusive_process

- `MIG M` : Multi Instance GPU기능. GPU를 Slice 하는 기능이다. 

  > Default는 Disabled가 되어 있지만 옵션을 통해 Enable 하여 사용한다.

**Processes**

현재 사용중인 GPU에 대한 정보들이 나와있다.



#### nvcc --version

- `nvcc` : 어떤 compiler driver가 설치되어 있는지 보여준다.

- `Cuda compilation tools, release 11.2, V11.2.67`

  cuda 11.2 version을 사용하고 있음을 알 수 있다.





### nvidia-smi Options

##### -q -d memory

```
$ nvidia-smi -q -d memory
```

GPU에 memory에 대한 정보를 출력

- `-i` 옵션을 통해 필요한 GPU만 선택하여 간략하게 볼 수 있다.

  ```
  $ nvidia-smi -q -d memory -i 0,3
  ```

  > 0, 3번 GPU만 선택하여 본다.



##### -L

```
$ nvidia-smi -L
```

GPU List를 보여주지만 단순하게 보여주는 것이 아니라 UUID값을 보여주는 옵션이다.



##### -e 

```
$ nvidia-smi -e 0
```

ECC ON/Off 명령어

**0은 Disabled, 1은 Enabled이다.** 반드시 리부팅 후 적용이 된다.







## 3. Multi GPU

GPU를 분산으로 사용하는 것에는 두 가지 방법이 있다.

1. GPU여러개를 사용하는 경우: source code를 분산 code로 설계하여 진행 (Multi GPU)
2. GPU한개를 여러 instance로 분할하여 사용 : MIG(Multi Instance GPU)기능을 지원하는 GPU(A100)를 사용하여 진행



Multi GPU는 GPU여러개를 사용하는 경우이다.







자세한 것은 [여기](https://medium.com/daangn/pytorch-multi-gpu-%ED%95%99%EC%8A%B5-%EC%A0%9C%EB%8C%80%EB%A1%9C-%ED%95%98%EA%B8%B0-27270617936b) - pytorch

+  [+여기](https://wooono.tistory.com/331)



## 4. Multi Instance GPU

Multi Instance GPU :  CUDA 애플리케이션을 위한 최대 7의 개별 GPU 인스턴스로 안전하게 분할하여 최적의 GPU 활용을 위해 사용자에게 별도의 GPU 리소스를 제공한다.  이러한 분할 mode를 **A100 MIG** mode라고 한다.

- MIG 기능은 CUDA 11.0 / R450 release부터 NVIDIA GPU 드라이버의 일부로 제공되며, NVIDIA DRIVER는 450.82 이상 사용가능하다.
- MIG 기능은 **A100** GPU에서만 가능하다.



**A100 MIG mode 사용 시 참고사항**

- GPU-GPU P2P 지원되지 않는다.
- 그래픽 API가 지원되지 않는다.
- CUDA 애플리션은 컴퓨팅 인스턴스와 상위 GPU 인스턴스를 단일 CUDA 장치로 취급한다.
- GPU 인스턴스 간의 CUDA IPC는 지원되지 않으며, Compute 인스턴스에서 CUDA IPC가 지원된다.
- CUDA 디버깅 및 메모리 / race checking 지원됨.
- GPU 인스턴스에서 사용될 때 GPUDirect RDMA가 지원됨.
- CUDA MPS는 MIG 위에 지원되며, 유일한 제한은 최대 클라이언트 수(48)가 컴퓨팅 인스턴스 크기에 비례하여 낮아진다.

**주요 용어**

- **GPU Context** : 고유 한 주소 공간, 메모리 할당 등을 포함하여 GPU에서 작업을 실행하는 데 필요한 모든 리소스를 캡슐화한다.

  > CPU 프로세서와 유사

- **GPU Engine** : GPU 엔진은 GPU에서 작업을 실행하는 것이다. 

  각 엔진들은 독립적으로 예약할 수 있으며 다른 GPU Context에 대해 작업을 실행할 수 있다.

  > - 컴퓨팅 / 그래픽 엔진 : 가장 일반적으로 사용되는 엔진. 컴퓨터 명령을 실행
  > - NVENC : 비디오 인코딩을 담당
  > - NVDEC  : 비디오 디코딩을 담당
  > - CE : DMA 수행을 담당

  

- **GPU Memory Slice** : GPU 메모리 슬라이스는 해당 메모리 컨트롤러 및 캐시를 포함하여 A100 GPU 메모리의 가장 작은 부분이다.

  GPU 메모리 슬라이스는 용량과 대역폭을 모두 포함하여 GPU 메모리 리소스의 1/8이다.

- **GPU SM Slice** : GPU SM 슬라이스는 A100 GPU에서 SM 중 가장 작은 부분이며, GPU SM 슬라이스는 MIG 모드에서 구성할 때 A100에서 사용할 수 있는 총 SM수의 1/7이다.

- **GPU Slice** : GPU 슬라이스는 단일 GPU 메모리 슬라이스와 GPU SM 슬라이스를 결합한 A100 GPU의 가장 작은 부분이다.

- **GPU Instance(GI)** : GPU 인스턴스는 GPU 슬라이스와 GPU 엔진 (DMA, NVDEC 등)의 조합이다. 

  GPU 인스턴스 내의 모든 것은 항상 모든 GPU 메모리 슬라이스 및 기타 GPU 엔진을 공유한다.

- **Compute Instance(CI)** : GPU 인스턴스는 여러 컴퓨팅 인스턴스로 세분화 될 수 있다. 

  컴퓨팅 인스턴스(CI)에는 상위 GPU 인스턴스의 SM 슬라이스 및 기타 GPU 엔진(DMA, NVDEC 등)의 하위 집합이 포함되며, CI는 메모리와 엔진을 공유한다.



**MIG를 사용하기 전에는 GPU 인스턴스 프로필과 유효한 GPU 인스턴스 조합등을 상세히 알아보고 익혀 둘 필요가 있다.**

- GPU Instance Profiles

  | Profile Name | Fraction of Memory | Fraction of SMs | Hardware Units | Number of Instances Available |
  | ------------ | ------------------ | --------------- | -------------- | ----------------------------- |
  | MIG 1g.5gb   | 1/8                | 1/7             | 0 NVDECs       | 7                             |
  | MIG 2g.10gb  | 2/8                | 2/7             | 1 NVDECs       | 3                             |
  | MIG 3g.20gb  | 4/8                | 3/7             | 2 NVDECs       | 2                             |
  | MIG 4g.20gb  | 4/8                | 4/7             | 2 NVDECs       | 1                             |
  | MIG 7g.40gb  | Full               | 7/7             | 5 NVDECs       | 1                             |

  `MIG 1g.5gb` : 1ea SMs + 5GB memory

  `MIG 2g.10gb` : 2ea SMs + 10GB memory

  `MIG 3g.20gb` : 3ea SMs + 20GB memory

  `MIG 4g.20gb` : 4ea SMs + 20GB memory

  `MIG 7g.40gb` : 7ea SMs + 40GB memory

- 유효한 GPU 인스턴스 조합

  ![](https://blog.kakaocdn.net/dn/b7LBrq/btqQlLe96oZ/ZoRy4jZMFkfPKmqFs8kuA0/img.png)

  - [1 memory, 1 compute] : `MIG 1g.5gb` 프로필을 의미한다.  `GPU Instance ID` : 19
  - [2 memory, 2 compute] : `MIG 2g.10gb` 프로필을 의미한다.  `GPU Instance ID` : 14
  - [4 memory, 3 compute] : `MIG 3g.20gb` 프로필을 의미한다.  `GPU Instance ID` : 9
  - [1 memory, 1 compute] : `MIG 4g.20gb` 프로필을 의미한다.  `GPU Instance ID` : 5
  - [1 memory, 1 compute] : `MIG 7g.40gb` 프로필을 의미한다.  `GPU Instance ID` : 0

  두 개의 프로필이 수직으로 겹치지 않도록 왼쪽의 instance 프로필로 시작하여 오른쪽으로 이동할 때 다른 instance 프로필과 결합하여 유요한 조합을 만들 수 있다.

  ![](https://blog.kakaocdn.net/dn/bQz28o/btqQptYXr8A/DSR1OCCij7KQ8G3aqm3iE1/img.png)

  단, [4 memory, 4 compute] + [4 memory, 3 compute] 프로필은 예외로 불가능하다.  





#### toggle MIG mode

```
$ nvidia-smi
```

```
+-----------------------------------------------------------------------------+
| NVIDIA-SMI 472.12       Driver Version: 472.12       CUDA Version: 11.4     |
|-------------------------------+----------------------+----------------------+
| GPU  Name            TCC/WDDM | Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
|                               |                      |               MIG M. |
|===============================+======================+======================|
|   0  NVIDIA GeForce ... WDDM  | 00000000:01:00.0  On |                  N/A |
| 44%   33C    P8    10W / 125W |    290MiB /  6144MiB |      1%      Default |
|                               |                      |                  N/A |
+-------------------------------+----------------------+----------------------+

+-----------------------------------------------------------------------------+
| Processes:                                                                  |
|  GPU   GI   CI        PID   Type   Process name                  GPU Memory |
|        ID   ID                                                   Usage      |
|=============================================================================|
|    0   N/A  N/A     26916    C+G   Insufficient Permissions        N/A      |
+-----------------------------------------------------------------------------+
```

여기서 `MIG M` 을 보면 기본 Disabled되어 있는 MIG 모드를 명령어를 통해 Enabled를 시켜주면 된다.

```
$ nvidia-smi -mig 1
```

> - 만일 GPU가 여러개이고, 특정 GPU만들 MIG mode로 사용한다면 아래 명령어를 입력한다.
>
>   ```
>   $ nvidia-smi -i 0,1 -mig 1
>   ```
>
>   0, 1번 GPU만 MIG mode로 활성화
>
> - 만일 MIG M이 N/A이면 A100 GPU가 아님



#### create GPU Instance

```
$ nvidia-smi mig -cgi {GPU Instance ID} -C
```

> `-cgi` : --create-gpu-instance
>
> `C` : --default-compute-instance

이제 조합을 해 보자.

**e.g.**

- `MIG 1g.5gb` 프로필 7개로 조합하는 경우

  ```
  $ nvidia-smi mig -cgi 19,19,19,19,19,19,19 -C
  ```

- `MIG 2g.10gb`, `MIG 2g.10gb`, `MIG 1g.5gb` , `MIG 1g.5gb` , `MIG 1g.5gb`  로 조합하는 경우

  ```
  $ nvidia-smi mig -cgi 14,14,19,19,19 -C
  ```

- `MIG 4g.20gb`, `MIG 2g.10gb`, `MIG 1g.5gb` 로 조합하는 경우

  ```
  $ nvidia-smi mig -cgi 5,14,19 -C
  ```

