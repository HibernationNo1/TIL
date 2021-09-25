# Initial setting



## Anaconda 설치

[여기](https://www.anaconda.com/products/individual-d) 에서 설치

## pip 설치

[링크](https://bootstrap.pypa.io/get-pip.py)를 저장 후 해당 위치에서 명령어

```
$ python get-pip.py
```

```
pip install tensorflow
pip install numpy
pip install opencv-python
```

```python
import tensorflow as tf
import tensorflow.keras as tk
import numpy as np
import pandas as pd
import cv2
import scipy

print(tf.__version__)
print(tk.__version__)
print(np.__version__)
print(pd.__version__)
print(cv2.__version__)
print(scipy.__version__)
```





## GPU_CUDA설치

### 1. check GPU

NVIDIA GTX-1060 3GB 기준

- 그래픽카드 확인

  장치관리자 > 디스플레이 어뎁터

- CUDA core 수 확인

  ![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2F49t3X%2FbtqyEA98R9n%2FxTxNRuRsrJeB8yW2UgHb10%2Fimg.png)

  NVIDIA GTX-1060 3GB는 코어 1152임을 확인

  CUDA Cores = **1152**

- 성능 확인

  [여기](https://www.wikiwand.com/en/CUDA) 서 ctrl + f로 `1060` 검색  (또는 [여기](https://en.wikipedia.org/wiki/CUDA))

  6.1임을 확인

  ![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2F0b42E%2FbtqyGmpmz1S%2FCoqplHiiDHOyphS9sBOVe0%2Fimg.png)

  CUDA Compute Capability = **6.1**



### 2. graphic driver 설치

 [여기](https://www.nvidia.co.kr/Download/index.aspx?lang=kr) 에서 graphic driver를 설치

> 제품유형 : GeForce
>
> 시리즈 : GeForce 10 Series
>
> 계열 : GeForce GTX 1060
>
> windows 10 64-bit
>
> 다운로드 타입 : Game -Ready 드라이버 : 일반 사용자용,  sutido 드라이버 : 작업툴에서 성능발휘



### 3. Download CUDA

- 쿠다 version 확인

  ![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbeO6bC%2FbtqyGvNswxK%2FNDZCW4KvK2zKZp2ejkkuH0%2Fimg.png)

  CUDA Compute Capability = **6.1** 이기에 SDK = 10.0~10.1 임을 확인



- 자신의 version에 맞게 다운

  [여기](https://developer.nvidia.com/cuda-toolkit-archive)서 알맞는 version 선택![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fzq3zP%2FbtqyFZ2v0R5%2FpUShfkRCyKo3NvMuc8p2W0%2Fimg.png)

  - network는 internet을 통해 여러 번 다운받는 것
  - local은 한 번에 받는 것 (internet이 일정하게 문제 없다면 이걸로 받기)

  visual studio가 설치되어 있어야함

  [여기](https://visualstudio.microsoft.com/ko/thank-you-downloading-visual-studio/?sku=Community&rel=16) 에서 community 2019다운

- 경로 지정 후 설치 (default로 지정함)

  `C:\Users\마이노\AppData\Local\Temp\CUDA`

- 환경 변수 추가 및 확인

  경로를 default로 했으면 환경 변수 자동으로 추가됨

  시스템 환경 변수 > 환경 변수

  `cudart64_100.dll` 가 있는 path
  
  `C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v10.0\bin`



### 4. Download cuDNN

cuDNN는 회원가입을 해야 다운로드 가능

[여기](https://developer.nvidia.com/cudnn)에서 로그인 후 다운로드

다운받은 file(`bin`, `include`, `lib`)을 

`C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.4` 에 옮긴다.

