# NVIDIA GPU

GPU란 무엇인가?

![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/CPUvsGPU.jpg?raw=true)

**CPU**

- 범용적인 명령어를 해석하고 실행하는 데 최적화되어 있다.
- 하나 또는 소수의 코어를 가지며, 각 코어는 고속으로 단일 작업을 처리할 수 있다.
- 시스템 메모리(RAM)와 직접적으로 상호작용하며, 빠른 메모리 접근을 위해 캐시를 사용한다.

**GPU**

- 비디오 렌더링, 이미지 처리, 딥러닝 연산 등 고도의 병렬 처리를 위한 명령어를 해석하고 실행하는 데 최적화되어 있다.

- 많은 수의 코어를 가지고 있어, 대량의 데이터를 동시에 처리할 수 있다.

- 자체 메모리(VRAM)와 직접적으로 상호작용하며, 큰 메모리 대역폭을 가지고 있다.

  > 대역폭이 크다는 것은? 
  >
  > 한 번에 공급할 수 있는 데이터의 양이 많다는 의미



## Product line

Nvidia는 용도에 따라 아래 3개의 제품군으로 나뉜다.

| Product line   | Usage                                      |
| -------------- | ------------------------------------------ |
| Geforce        | 게임 플레잉을 위해 설계                    |
| Quadro         | 영상, 음악, 게임개발 등의 작업을 위해 설계 |
| Datacenter GPU | 딥러닝 연산을 위해 설계                    |



- Architecture 에 따른 GPU 모델 표

| Architecture     | Geforce              | Quadro                  | Datacenter GPU |
| ---------------- | -------------------- | ----------------------- | -------------- |
| **Pascal**       | GTX 1060, 1070, 1080 | -                       | P4             |
|                  | -                    | -                       | P40            |
|                  | -                    | -                       | P100           |
| **Volta**        | -                    | -                       | V100           |
|                  | -                    | -                       | TITAN V        |
| **Turing**       | GTX 1660             | RTX 5000                | T4             |
|                  | RTX 2060, 2070, 2080 | RTX 6000                | -              |
|                  |                      | RTX 8000                | -              |
| **Ampere**       | RTX 3060             | RTX A5000               | A2             |
|                  | RTX 3070             | RTX A5500               | A10            |
|                  | RTX 3080             | RTX A6000               | A16            |
|                  | RTX 3090             | -                       | A30            |
|                  | -                    | -                       | A40            |
|                  | -                    | -                       | A100           |
| **Ada Lovelace** | RTX 4060             | RTX 5000 Ada Generation | L4             |
|                  | RTX 4070             | RTX 6000 Ada Generation | L40            |
|                  | RTX 4080             | -                       | L40S           |
|                  | RTX 4090             | -                       | -              |
| **Hopper**       | -                    | -                       | H100           |
|                  | -                    | -                       | H200           |
| **Black well**   | -                    | -                       | B200           |

> Quadro는 5000급 이상 제품만 표에 포함



## Core type

### CUDA core

병렬적으로 연산을 수행하는 하드웨어 core 장치(그래픽 렌더링, 과학적 계산, 데이터 분석 등 범용적으로 사용된다.)

CPU와는 다르게 Instruction(명령어 전달)이나 decoding(명령어 해석)과 같은 동작은 할 수 없으나, 수치 연산에 특화된 명령어를 실행한다.

그 과정은 아래와 같다.

1. GPU의 control unit에 의해 명령어 scheduling
2. cuda core로 명령어 전달, 병렬 연산 수행
3. 완료된 연산 결과를 memory에 저장

![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/CUDA_core.png?raw=true)



### RT core

RT core는 Ray Tracing 관련 연산을 수행하는 하드웨어 core 장치.

3차원 그래픽 영상에 적용하거나, 개임 개발 시 사용된다. 

**Ray Tracing**

> AI연산과의 관련성은 없다. Ray Tracing은 영상의 CG제작, 게임의 그래픽 제작 과정에서 사용되는 것을 목적으로 만들어진 기능이다.
>
> - GTX와 RTX의 차이는 무엇인가?
>
>   Ray tracing 기술이 도입된 GPU에는 RTX 라는 이름을 붙인다.

공간 속에서 빛은 직선으로 이동한다.

그러다가 물체에 부딪치면 튕겨져서(반사돼서) 틀어진 방향으로 계속 나아가게 되거나, 혹은 물체에 흡수되어 사라지기도 한다.

빛이 이리저리 날아다니다가 우리 눈의 망막에 부딪치는 순간, 우리는 색과 물체를 인식하게 된다.

Ray Tracing은 이런 빛의 움직임을 흉내내는 기술이다. 

현실 세계에서는 광원에서 빛이 출발하여 오브젝트에 반사된 후 우리 눈에 들어오게 되는데, 디지털적으로는 정 반대의 단계를 통해 빛의 움직임을 추적한다.

이를 위해선 출발하는 빛의 벡터, 반사된 빛의 벡터를 계산하여 추적하는 연산을 수행해야 한다.

![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/Ray_tracing.png?raw=true)

이를 통해 물, 거울 과 같이 빛을 반사하도록 결정된 오브젝트는 반사된 빛이 만나게 되는 물체를 표면에 rendering을 수행하고

일반적인 오브젝트는 반사된 빛이 광원을 만나지 못하게 되면 노출도를 조정하여 그림자를 표현하게 된다.

- How to Use?

  개발자가 빛을 반사하는 오브젝트로 class표현만 한다면, GPU의 RTX 옵션 사용 시 자동으로 연산이 적용되며 화면에 출력된다.

- 단점

  Ray Tracing은 엄청나게 많은 연산을 필요로 하기 때문에, 영상의 품질은 좋아지지만 live환경에서 프레임 전달 속도는 상당히 느려진다.



### Tensor core

병렬적으로 연산을 수행하는 하드웨어 core 장치로, 수치 연산에 특화된 명령어를 수행한다.

**CUDA Core와의 차이점은?**

AI 및 머신 러닝 연산에 특화된 하드웨어로, 특히 딥 러닝의 매트릭스 계산과 같은 높은 수준의 병렬 처리를 위해 설계되었다.

더욱 딥한 차원의 행렬에 대한 연산에 집중되어 고도화 되어 있어 **여러 단위의 정밀도 계산**, **정밀도 조절**, **더욱 빠른 연산** 등의 기술을 제공한다.

> 기존의 CUDA core는 `FP32`, `FP16` 단위의 정밀도 계산만이 가능했다.

인공지능 연산에 대한 성능 평가 지표는 tensor core의 연산 수행 속도를 기준으로 한다.

**정밀도란?**

인공지능의 연산은 `목표로 하는 값`과 `현재 예측된 값` 사이의 차이(오차)를 줄여가며 최종적으로 가장 작은 오차를 달성하는 방식이다.

이 과정에서 우리는 오차값의 범위를 최소한으로 줄이면 줄일수록 원하는 값을 찾는것에 더욱 유리해진다.

예를 들자면,

- 소수점 1번째 자리까지만 표현하는 경우

  정답: 1  		예측된 값:  0.9	->	 오차: 0.1

- 소수점 3번째 자리까지만 표현하는 경우

  정답: 1  		예측된 값:  0.999	->	 오차: 0.001

- 소수점 8번째 자리까지만 표현하는 경우

  정답: 1  		예측된 값:  1 - 0.1^8 	->	 오차: 0.1^8

와 같다.

때문에 고 정밀도(더욱 깊은 소수점에 대한)계산은 인공지능 학습 및 추론에서 원하는 퍼포먼스를 확보하기에 더욱 유리하다.



**tensor core에서 주로 사용하는 정밀도 단위는 아래와 같다.**

- **`FP16`**(Half Precision): 16비트 부동소수점 포맷.  최소값: 2^(−14),  최대값: (2-2^(-10)) × 2^(15)
- **`FP32`**(Single Precision): 32비트 부동소수점 포맷.  최소값: 1×2^(−126), 최대값: (2−2^(−23))×2^(127)
- **`FP64`**(Double Precision): 64비트 부동소수점 포맷. 최소값: 2^(−1022),  최대값: (2-2^(-52)) × 2^(1023)

![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/FP32-FP16.jpeg?raw=true)



**부동소수점**

컴퓨터가 실수를 표현하는 한 방식으로, 실수를 정규화(normalization)된 이진수로 표현한다.

- 표현 방법: 실수 V = x × 2^y  => (1.가수) × 2^(지수)  

- 예시

  13.75 를 부동소수점으로 표현

  1. 실수를 이진수로 변환

     13 = 8 + 4+ 1 => 1101,       0.75 = 0.5 + 0.25 => 0.11

     13.75 => 1101.11   (지수 값이 0이기 때문에 비정규화 상태)

  2. 이진수를 정규화

     1101.11 => 1.10111 × 2^3    (정수값이 1이고, 지수가 0이 아니기 때문에 정규화 상태)

     여기서 10111 이 가수 이고,   3은 지수 이다.  

  3. 부동 소수점 변환 (32bit 표현)

     1.10111 × 2^3  는 다시 0과 1 만으로 표현되어야 하는데, 이는 부동소수점 표준 표현 방식으로 아래와 같이 표현될 수 있다.

     - FP32를 기준으로 설명

       FP32는 1비트의 부호 비트(Sign bit), 8비트의 지수부(Exponent), 23비트의 가수부(Mantissa)로 구성된다.

       ![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/FP32-FP16.jpeg?raw=true)

       - 부호비트: 0  (양수)

       - 지수부: 10000010

         왜 00000010 이 아니라 10000010 인가?

         FP32의 단위는 지수가 -126 ~ 127 사이의 값을 가지는 범위를 표현한다.

         이 때 지수의 값을 양수로만 표현하기 위해 127의 값(bias)을 더해주는데, 이는 지수를 처리하는 회로가 간단해지고 효율적으로 작동할 수 있기 때문이다.

       - 가수부: 10111000000000000000000

       즉, 0 10000010 10111000000000000000000 이 된다.

- 왜 정규화를 사용하는가?

  같은 비트(용량)을 사용했을 때 비 정규화보다 더 넓은 범위의 값을 표현할 수 있다.

  FP32를 기준으로 설명.

  FP32는 1비트의 부호 비트(Sign bit), 8비트의 지수부(Exponent), 23비트의 가수부(Mantissa)로 구성된다.

  여기서 최대값과 최소값을 표현해 보자면 

  - 부호비트: 0 or 1
  - 지수부의 최소값: 00000001, 최대값 11111110    (1~254)
  - 가수부의 최소값: 00000000000000000000000, 최대값 11111111111111111111111  ( 0 ~ (1−2^(−23) )

  이는 곧 

  - **정규화된 최소값**: `0 00000001 00000000000000000000000` (FP32에서 1×2^(−126))
  - **정규화된 최대값**: `0 11111110 11111111111111111111111` (FP32에서 (1−2^(−23))×2^(127))

  으로 표현된다.

  반면, 비 정규화된 값은 지수가 0이기 때문에 아래와 같이 표현된다.

  - 부호비트: 0 or 1
  - 지수부: 00000000  (모든 비트가 0, 비정규화된 상태)
  - 가수부의 최소값: 00000000000000000000001, 최대값 11111111111111111111111  ( 2^(-23) ~ (1−2^(−23) )

  이는 곧

  - **비 정규화된 최소값**: `0 00000000 00000000000000000000001` 2^(-23 -127) = 2^(-150)
  - **비 정규화된 최대값**: `0 00000000 11111111111111111111111` (1−2^(−23)) × 2^(-127)

  표현 범위가 제한적인 것을 확인할 수 있다.



다시, tensor core에서 주로 사용하는 정밀도 단위는 아래와 같다.

- **`FP16`**(Half Precision): 16비트 부동소수점 포맷.
- **`FP32`**(Single Precision): 32비트 부동소수점 포맷.  
- **`FP64`**(Double Precision): 64비트 부동소수점 포맷. 

![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/FP32-FP16.jpeg?raw=true)

Nvidia는 각 제품의 white paper에서 위 정밀도 단위로 성능을 표현하며, 웹 페이지에 tensor performance 라고 명시된 값은 가장 작은 단위의 정밀도에 의한 속도를 나타낸 것이다.

```
L40s의 tensor performance
```



- L40s의 datasheet에서 성능 표

  ![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/L40S_1.png?raw=true)

- L40s의 tensor performance 

  ![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/L40S_2.png?raw=true)

**정밀도 조절이 왜 필요한가?**

정밀도가 높아질수록 연산하는 과정에서 시간이 더욱 소요되기 때문에 정확도와 속도는 **반비례 관계**를 가지게 된다.

두 마리의 토끼를 잡을 순 없기 때문에, 사용자는 목적에 따라 정밀도를 조절하여 네트워크를 학습하거나 추론에 사용해야 한다.

pomission과 같은 경우는 연산 과정에서 정밀도가 높더라도 퍼포먼스가 크게 증가하지 않지만, face fusion과 같은 경우는 정밀도가 높을수록 더욱 섬세한 결과를 도출할 수 있다.

어떻게 활용되는가?

- 기존의 cuda core는 FP32 고정 또는 FP16고정의 multiply-add 연산만 가능했다.

  하지만 Tensor core의 등장 이후로 FP범위를 조절해가며 연산을 제어할 수 있게 되었으며, 이를 활용해 **Mixed Precision** (혼합 정밀도)가 등장하게 되었다.

#### Mixed Precision

`FP16`으로 입력을 받고, 연산이 완료되면 `FP32`로 최종 계산이 이루어지는 기술이다.

![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/mixed%20presision.png?raw=true)

위 그림은 mixed precision을 사용한 training 동작이다.

이는 아래의 순서대로 동작한다.

1. FP32 weight(Master Weights) 를 복사 후, FP16으로 캐스팅 한다.

   FP32에서 FP16으로의 캐스팅은 보통 간단한 데이터 타입 변환으로 처리한다.

   FP16로 변환된 값은 FP32 값에 비해 소수점 이하의 값이 소실될 수 있다.

2. FP16 weight를 사용하여 forward pass를 진행한다.  이 때 input 또한 FP16이다.

3. forward pass 로 계산된 FP16 prediction 값을 FP32로 캐스팅 하고 FP32 loss를 계산한다.

4. FP32 loss에 `scaling factor S`를 곱하여 그라디언트 계산 중 발생할 수 있는 숫자 범위의 문제를 방지한다.

   - underflow: 값이 매우 작을 때 FP16범위의 연산에서 이 값을 정확히 표현할 수 없어 0으로 처리되는 경우

5. FP32 loss를 사용하여 backward pass를 진행하며, FP32 gradient를 계산한다.

6. FP32 gradient에 `scaling factor S`를 나누어준다.

7. 조정된 FP32 grandient를 사용하여 최적화를 진행해 FP32 weight를 update한다.

이 동작을 통해 forward 과정에서 연산 숫자의 범위를 줄여 연산 속도를 높히면서 backward과정에서는 그라디언트 범위를 되돌려 정확도는 최대한 유지하게 된다.



#### Tensor performance

아래는 V100의 white papaer 중 tensor core의 FMA에 대한 내용이다.

```
In Volta GV100, each Tensor Core performs 64 floating point FMA operations per clock, and eight Tensor Cores in an SM perform a total of 512 FMA operations (or 1024 individual floating point operations) per clock.
```

각 tensor core는 1 clock 당 64회의 floating point(부동 소수점) FMA 연산을 수행하며, 1개의 SM에는 8개의 tensor core가 포함되어 있음을 알 수 있다.

- **FMA** (fused multiply-add)

  Tensor core의 연산을 의미하며, 하나의 연산에서 곱셈과 덧셈을 결합하는 기술을 말한다.

  이 FMA에 수행되는 속도를 기반으로 GPU의 성능을 계산한다.

- **SM**(Streaming Multiprocessor)

  다수의 core를 포함하는 하드웨어 단위이다.

  하나의 GPU architecture는 다수의 SM을 포함하여 구성되어 있다.

  ![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/SM.png?raw=true)

때문에 1 clock 당 SM에서는 64 * 8 = 512 회의 FMA 연산이 수행됨을 알 수 있지만, 위 문장에서는 `1 clock 당 512회의(또는 독립적인 1024회)` FMA의 연산이 이루어진다고 쓰여있다. FMA 횟수가 왜 2배나 뻥튀기가 될까? 이는 NVIDIA의 계산 단위에 의해 결정된다.

![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/FMA.png?raw=true)

FMA는 하나의 연산에서 곱셈과 덧셈을 결합하는 것을 의믜한다. NVIDIA는 곱셈과 덧셈을 독립적인 계산으로 간주하고, 횟수를 2회로 결정하여 계산하는 방식을 사용한다.

그럼 이제 우리는 GPU architecture에서 1 clock 당 몇 번의 FMA 연산이 수행되는지 알 수 있다.

**V100 기준 예시**

- tensor core에 의한 1 clock 당 FMA 횟수: **`64`**

- SM에 의한 1 clock 당 FMA 횟수: **`64 × 2 × 8 = 1,024`**

- GPU architecture 에 80개의 SM 이 있다면

  GPU architecture 에 의한 1 clock 당 FMA 횟수:  **`1024 × 80 = 81,920`**

그렇다면 1초당 몇 번의 clock이 수행될까? 이는 각 제품의 clock 을 확인하면 된다.

V100 SXM2의 **GPU Boost Clock**(최대 clock) 은 **1,530** MHz 이다.

이를 대입하여 계산하면, 1초에 수행되는 FMA는 **81,920 × 1,530,000,000  = 125,337,600,000,000 ==** **125,337,600 `MFLOPS` ==** **125.338 `TFLOPS`** 이 된다

- **TFLOPS**

  **FLOPS**(Floating Point Operations Per Second) 는 1초에 수행되는 FMA의 횟수를 나타내는 단위이며

  **Tera FLOPS**는 10의 12승(1조) 단위의 부동 소수점 연상 횟수를 의미한다.

  아래는 Tesla V100 datasheet 첨부

  ![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/V100_datasheet.png?raw=true)



## NVlink

NVlink 를 알기 위해선, PCIe를 알아야 한다.

#### PCIe

PCIe(Peripheral Component Interconnect Express)란, 다양한 유형의 하드웨어 (예: 그래픽 카드, 네트워크 카드, SSD)를 마더보드에 연결하는 표준 Device이다.

CPU는 system memory(RAM)를 사용하고 GPU는 GPU memory(VRAM)을 사용하기 때문에

과거의 GPU는 PCIe를 사용해서 CPU와 GPU의 연산 output 데이터를 필요할 때마다 memory를 옮겨가며 사용해야 했었다.

![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/PCIe.png?raw=true)

PCIe를 통해 Chat GPT가 동작하는 것으로 예시를 들어보겠다.

1. text가 입력되면, CPU는 해당 text를 읽어 토큰화(CPU에 특화된 작업을 수행) 하고 RAM에 저장한다.

2. CPU의 명령어에 의해 data가 RAM으로부터 PICe의 연결 통로(Bus)를 타고 VRAM으로 데이터를 옮겨간다.

   `data.cuda()`

3. GPU가 VRAM으로부터 데이터를 받고 추론을 수행하며, 그 output을 VRAM에 저장한다.

4. GPU의 명령어에 의해 data가 VRAM으로부터  PCIe의 연결 통로(Bus)를 타고 RAM으로 옮겨간다.  

   `data.cpu()`

5. CPU가 RAM에 있는 data를 읽어 수행하며 사용자에게 결과를 출력한다.



이러한 동작이 이루어지면, data가 memory를 옮겨가면서 시간이 소요되고 PCIe의 작은 대역폭 때문에 많은 data를 옮기는데 제한이 된다.

GPU도 각각의 memory 가지고 있기 때문에 GPU끼리 데이터를 공유하고자 한다면 위와 같은 절차를 따랐어야 했다.

![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/NVlink_1.png?raw=true)

#### NVlink

PCIe의 한계를 돌파하기 위해 Nvidia에서 독자적으로 만든 통신 Device이다.

NVlink의 특징은 아래와 같다.

- GPU와 GPU사이에 직접적으로 data를 공유할 수 있도록 물리적인 경로를 만들었다.

  

  ![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/NVlink_2.png?raw=true)

- 더욱 빠르게 데이터를 전달할 수 있도록 신호처리적인 기술 **PAM4**(Pulse-Amplitude Modulation)를 도입했다.

  기존의 NRZ(NonReturn to Zero) 방식은 아날로그 신호를 디지털 신호로 바꿀 때 0과 1로만 표현하여 통신을 수행했다.

  PAM4 는 4개의 층계에 패턴규칙까지 추가하여 적은 통신으로도 많은 정보를 통신할 수 있도록 했다. 

  ![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/RAM4_1.png?raw=true)

  아래 그림을 보면, NRZ는 5번의 비트 전환을 수행하지만, PAM4는 4번의 적은 비트 전환을 수행한다. 

  

  ![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/PAM4_2.png?raw=true)

  NVlink를 처음 공개하였을 때 

  1개의 속도가 PCIe의 최신 세대인 3세대 보다 1.25배 더 빠른 40GB/second 속도를 자랑하며, P100 기준으로 NVlink를 4개를 구성하여 사용한다고 발표했다. 

- 대역폭을 크게 높혔다.

  NVlink를 처음 공개하였을 때 PCIe의 최신 세대인 3세대 보다 5배 더 큰 160 GB/second 대역폭을 발표했다.

  ```
  CPU와 GPU끼리도 연결이 가능하다.
  ```

  

- CPU와 GPU끼리도 연결이 가능하다.

  ![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/NVlink_3.png?raw=true)



- PCIe 로 구성된 제품은 PCIe 라는 명칭을 붙이고, NVlink로 구성된 제품은 SXM2(NVIDIA's NVLink GPU Module) 이라는 명칭을 붙인다.

- NVLink의 세대별 성능표

![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/NVLink_list.png?raw=true)





## Architecture

- legacy architectures

  2017년 이전에 출시된 제품군으로, 현재에는 많이 쓰이지 않는 GPU Architecture

  - G80

  - Fermi

  - Kepler

  - Maxwell

  - **Pascal**

    CUDA core의 half-precision(`FP16`)계산 지원을 최초로 도입한 Architecture

    >  이전까지는 `32FP`계산만이 가능했다.

    최초의 NVlink 를 도입한 architecture



### Volta

현재 출시되는 Data Center 전용 GPU 기술력의 시작단계로 평가된다.

- **Tensor core를 최초로 도입한 architecture**

  정밀도 조정으로 mixed precision이 가능해졌다.

- 2세대 NVlink 도입

| Model name | release date |
| ---------- | ------------ |
| V100       | 2017.06.21   |
| TITAN V    | 2017.12.07   |

- V100의 보급형으로 평가되는 TITAN V 은 V100과 같은 architecture를 사용하지만, 성능(대역폭, VRAM용량)을 조금 줄이고 가격은 낮춘 제품이다.



### Turing

- RT Cores를 도입해 Ray Tracing기술을 활용할 수 있게 되었다.
- Turning SM을 도입했다.
  - 소수점 데이터와 정수 데이터를 전달하는 경로를 새롭게 구성하여 연산 데이터 제공 성능 향상
  - 공유 메모리, 텍스처 캐싱, 메모리 로드 캐싱을 하나의 단위로 통합하도록 SM 메모리 경로를 재설계하여 자원 관리의 효율성 증대.
    - 텍스처 캐싱: 3D 오브젝트의 표면적에 적용되는 이미지나 패턴에 대한 data를 캐시에 저장하는 기술
    - 메모리 로드 캐싱: GPU가 VRAM에서 데이터를 로드할 때 캐시에 저장하는 기술 
- 2세대 Tensor Core 인 **Turing Tensor Core** 사용한다.



**Turing Tensor Core**

- 빠른 추론을 위해 INT8, INT4 정밀도 모드를 지원한다.

- Deep Learning Super-Sampling (**DLSS**) 을 지원한다.

  DLSS이란?

  이미 학습된 모델을 사용하여 **tensor core**상에서 추론 연산을 통해 Super-Sampling을 수행하는 기술.

  - Super-Sampling이란? 

    화면에 이미지를 출력하기 전에 프로그램적으로 높은 해상도의 이미지를 구성한 후, 보간법을 사용하면서 본래의 화면 크기만큼 다운샘플링을 하는 기법.

    ![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/Super-Sampling.png?raw=true)

    이를 통해 더욱 부드럽고 자연스러운 이미지가 생성될 수 있지만, 시간과 비용 또한 증가한다.

  **Super-Sampling과 DLSS은 무엇이 다른가?**

  학습 data를 1920*1080 크기의 이미지로 하고 label data를 3840\*2160으로 하여 Super-Sampling의 결과 자체를 학습한 모델이다.

  때문에 큰 사이즈로 렌더링 후 다운샘플링 하는 과정을 모두 추론으로 진행하기 때문에, 비용과 시간은 단축시키고 성능은 더욱 높일 수 있게 된다.

  ![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/DLSS.jpg?raw=true)

  - DLSS는 3D 그래픽을 사용하는 개임 개발 및 이용 시 사용된다

    DLSS를 사용하기 위해선 

    - 개발자가 개발 과정 중에서 DLSS를 지원하는 cfg값을 설정하여 개발을 진행해야 한다.
    - 사용자가 DLSS를 지원하는 게임에서 DLSS mode를 켜 놓아야 한다.

    

| Model name | release date |
| ---------- | ------------ |
| T4         | 2018.09.13   |

기술적으로는 발전했지만 Volta의 V100, TITAN V에 비해 많이 적은 resource를 사용하기 때문에 스펙적으로는 더욱 낮은 성능을 보여준다.



### Ampere

- 2세대 RT Core 도입

- 2세대 DLSS 도입

- 3세대 NVLink 도입

- Tensor core에 데이터를 공급하는 thread 증설

- 행렬 곱셈의 차원을 V100보다 최대 4배 허용

- GPU control unit의 명령어 전달 효율성 V100보다 8배 증가

- 비동기 복사 명령어 추가로 데이터 공유 과정 대폭 축소

  - 데이터를 기다리는 시간이 줄어들어, 계산 코어가 더 자주 활성화된다.
  - 메모리 복사와 처리가 동시에 이루어지기 때문에, GPU의 리소스를 보다 효과적으로 사용할 수 있다.

- MIG(Multi instance GPU) 지원(DGX A100, DGX A30)

  GPU 1개에 여러 instance를 두고, 각각의 instance에 대해 독립적인 memory를 할당하는 기술.

- **Third-Generation Tensor Core** 사용



**Third-Generation Tensor Core**

- Tensor core 작업 성능 200% 개선

- FP32에 대한 연산을 가속화 하는 경로 제공

- Tensor Float 32 (TF32)정밀도를 사용한 연산 제공

  TF32는 FP32와 같은 범위를 유지하면서도, mantissa(소수점) 부분을 10비트로 제한하여 계산 효율을 높인다.

  ![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/FP32-FP16.jpeg?raw=true)

- FP64연산 속도 2.5배 증가

- INT8연산 속도 20배 증가

- Sparse Tensor Cores 기능 제공(Sparsity 기술을 활용한 학습 과속화 제공)

  Sparsity 이란? 

  **전체 네트워크에서 얼마나 많은 weight가 (작은 수가 아닌)정확하게 0인지를 나타내는 척도(알고리즘)를 의미한다.**

  가장 일반적인 알고리즘 Pruning

  - Pruning

    네트워크의 성능이 크게 저하되지 않는 선에서 model의 weight들 중 중요도가 낮은 weight의 연결을 제거하여 model의 parameter를 줄이는 기법

    weight의 연결은 어떻게 제거하는가? 바로 임계값 이하의 weight를 0으로 치환(sparse: 희소하게 :: 대부분의 값이 0이 되도록)하는 것이다.

  NVIDIA의 텐서 코어는 이러한 희소 행렬을 인식하고 처리하여, 필요 없는 연산을 제거함으로써 더 빠른 처리 속도와 향상된 에너지 효율을 제공한다.

  - How to Use?

    1. Sparsity metrics의 연산을 효율적으로 수행할 수 있도록 도와주는 라이브러리

       CUDA C/C++으로 cuSPARSE라이브러리를 include하여 Sparsity 알고리즘 code를 작성해야 한다. 

    2. model 구조를 Sparsity를 사용하기 위한 구조로 설계를 해야 한다.

       ![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/Sparsity.png?raw=true)

       위 그림은 Pruning기법을 사용하여 4개의 tensor중에서 2개의 weight를 삭제하는(50%비율을 삭제)것을 예시로 든다.

       이를 위해 model을 설계할 때 Sparsity를 적용하고자 하는 layer를 지정하고, 해당 layer는 size를 4의 배수로 결정해야 하며, weight를 0으로 치환할 비율을 50%로 결정해야 한다. 

| Model name | release date |
| ---------- | ------------ |
| A100       | 2020.06.22   |
| A40        | 2020.10.05   |
| A30        | 2021.04.12   |
| A10        | 2021.04.12   |
| A16        | 2021.07.17   |
| A2         | 2021.11.10   |

- `A100`: 광범위 대역폭, 대규모 계산을 위한 드랜지스터 구성.  MIG 기능 제공

  - `DGX station A100`: A100 8개를 포함한 인공지능 전문가를 위한 개인용 슈퍼컴퓨터 

    A100 * 8 * 624 = 5 PFLOPS (5,000 TFLOPS)

    DGX란? 병렬적으로 GPU를 연결한 슈펴컴퓨터

- `A40`: 

  - RT core 사용. 강력한 그래픽 및 렌더링 성능을 지원하기 때문에 그래픽 분야에 사용하기 적절

  - VGPU 기술 제공

    VGPU이란? VDI(Virtual Desktop Infrastructure) 환경에 GPU성능을 제공해주는 기술

    - VDI이란? 가상으로 PC하나를 구축하여 공유하는 기술

      Docker에 비유하자면, docker는 container를 시작할 시 1개 PC의 resource를 공유하여 가상 OS환경을 구성하는데

      VDI를 시작하면 다른 데이터 센터의 CPU, GPU, RAM 등의 하드웨어를 그대로 빌려서 사용하게 된다.

      사실상 cloud 환경보다 단점이 많아 사용되지 않음.

- `A30`: AI 추론 및 범용 컴퓨팅 가속화에 적절. `A100` 의 보급형 모델이다. (RT core 사용 X)

- `A10`: RT core 사용. A40보다 낮은 성능의 그래픽 분야에 적절. cloud 데이터 센터에 최적화.

- `A16`: VGPU 기술 제공. `A40`의 보급형

- `A2`: VGPU 기술 제공

  - 저전력 소형 디자인, 낮은 가격으로 사용시 적절



### Ada Lovelace

- 전력 대비 높은 Clock을 유지할 수 있도록 트랜지스터와 코어를 구성

  - 3090 Ti와 동일한 전력 내에서 더욱 높은 clock을 실행할 수 있음

- 더 빠른 레이 트레이싱을 위한 3세대 RT Core **`Ada RT`**사용

  - Opacity Micromap Engine: 광선 추적 속도 2배 향상
  - Displaced Micro-Mesh: 광선 추적에 필요한 연산을 즉석에서 생성하여 물제의 렌더링 즉시 생성
  - 빛 반사 셰이터 효율성 향상

- 3세대 DLSS 도입

  - DLSS 2 보다 프레임 속도를 2배 증가 (추론 속도 향상)

  - tracing을 활용한 그래픽 랜더링 속도 4배 향상

  - Frame generation 기능 도입

    image의 흐름을 파악하여 다음 image가 송출되기 전에 그 이전단계의 Frame을 생성해내는 기술

    ![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/Frame_generation.png?raw=true)

- 3D 그래픽 작업에 최적화된 구조 제공

- Optical Flow Acceleration 등 AI기반 프레임 생성 기술을 사용하여 게임 및 그래픽 전문 콘텐츠 제작에 유용하도록 설계.

  - Optical Flow

    각 프레임 간의 픽셀 변화를 계산하여 물체가 어떻게, 얼마나 움직였는지를 파악하는 기술

    ![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/Optical_Flow.jpg?raw=true)

- **Ada Fourth-Gen Tensor Cores** 사용

  ### **Ada Fourth-Gen Tensor Cores**

  ```
  Tensor Cores are specialized high performance compute cores that are tailored for the matrix multiply and accumulate math operations that are used in AI and HPC applications. Tensor Cores provide groundbreaking performance for the matrix computations that are critical for deep learning neural network training and inference functions that occur at the edge.
  ```

  tensor core의 성능이 획기적으로 좋아졌다고는 하지만, 명확히 그 수치를 제시하진 않음

  또한 그 외의 어떠한 차이점이 있는지 설명이 없음

| Model name | release date |
| ---------- | ------------ |
| L40        | 2022.10.13   |
| L40S       | 2022.10.13   |
| L4         | 2023.03.21   |

- `L40`: 3D, 그래픽 분야 작업에 특화되어 있으며. cloud 워크스테이션에 최적화.
- `L40S`:  `L40`와 같은 스펙과 기술을 제공하지만  Generative AI, 대규모 언어 모델 추론 및 훈련에 특화됨.
- `L4`: L40의 범용적인 목적으로, 보다 낮은 성능의 분야에 적절. (보급형 `L40`)



### Hopper

```
H100 Fourth-Gen Tensor Cores
```



그래픽, 게임작업 보다는 AI연구에 모든 기술력을 집중한 GPU airchitecture

용도가 정해져있기 때문에 model 종류가 적음

- 4세대 NVLink 도입

- DPX 명령어

  동적 프로그래밍 알고리즘을 크게 가속화하는 명령어 기능 추가 

  - 유전체학 처리를 위한 Smith-Waterman, 함대의 최적 경로를 찾는 Floyd-Warshall 알고리즘 등

- MIG 기능 개선

  A100에 비해 약 3배 더 많은 컴퓨팅 용량과 거의 2배 더 많은 메모리 대역폭을 각 GPU instance에 제공

- Thread Block Cluster 기능 제공

  CUDA programming을 통해 환경을 구성할 GPU의 계층에 Thread Block 이라는 개념을 추가한 것.

  이를 통해 개발자는 SM 그룹을 동시에 스케줄링 하거나 효율적으로 활용할 수 있도록 여러 기능을 추가할 수 있다.

  설명 docs: `https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#cooperative-groups`

- **H100 Fourth-Gen Tensor Cores**(Hopper Tensor Core) 사용

- **NVIDIA Grace Hopper Superchips**

**H100 Fourth-Gen Tensor Cores**

- clock 당 SM의 수행 속도를 더욱 빠르게 개선, A100에 비해 6배 더 빨라진 속도 제공
- FP8 단위 정밀도 모드 지원 (mixed precision 가능 )
- A100에 비해 FP16에서 2배의 MMA 속도를 보여준다.

```
Grace Hopper Superchips
```



| Model name | release date |
| ---------- | ------------ |
| H100       | 2023.03.21   |
| H200       | -            |

- H200: H100 보다 1.3배 더 빠른 속도, 1.4배의 대역폭 등 모든 스펙이 H100의 upgrade version

  datasheet 공개가 아직 안되어있음

  2024년 하반기에 출시될 예정

**Grace Hopper Superchips**

![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/Grace_hopper.jpg?raw=true)

Nvidia에서 개발한 Arm 기반 CPU(Grace)와 Hopper GPU를 결합하여 만든 하나의 board 

- 91개의 CPU 구성

- 120GB 용량, 819GB/S 의 대역폭을 가진 memory인 SK 하이닉스 사의 HBM3 (High Bandwidth Memory) 

  ![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/HBM3.jpg?raw=true)

- 576GB의 GPU memory 제공

- H100 단일 GPU와 비교해서 LLM 대형 모델의 목표값까지의 학습 속도 약 2.3배 달성 

- CPU와 GPU사이의 data이동 시 병목현상 제거, 상호 연결 소비 전력 5배 이상 감소



**DGX Grace hopper 200**

Grace Hopper Superchips 32개로 구성된 슈퍼 컴퓨터

- FP8 단위 기준 32 PFLOPS (32,000 TFLOPS) ≈ A100의 102배 빠른 속도

**Grace hopper Data Center**

Nvidia 생태계의 Data Center를 구성하기 위한 데이터 센터를 발표.

병렬적으로 DGX를 연결한 데이터센터를 구성하기 시작한 세대.

AI학습 시 하나의 슈퍼 컴퓨터처럼 사용 가능.

- DGX Grace hopper 200 8개로 데이터센터를 구성

- Grace Hopper Superchips 256개를 NVLink로 전부 연결

  ![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/Grace%20hopper%20Data%20Center%20NVlink.png?raw=true)

  독립적인 board를 전부 연결하여 하나의 board처럼 사용이 가능하도록 구현한 최초의 슈퍼 컴퓨터

- FP8 단위 기준 1 EXAFLOPS 의 속도 (1,000,000TFLOPS) ≈ DGX A100보다 200배 빠른 속도

- AWS, google cloud와 같은 could 환경 제공 서비스 업체에게 그대로 양도하는것이 목적

![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/Grace%20hopper%20Data%20Center.png?raw=true)



단점: Superchips 사이의 데이터 이동 시 병목현상이 나타남



### Black well

그래픽, 게임작업 보다는 AI연구에 모든 기술력을 집중한 GPU airchitecture

- 2024년 3월 19일에 발표된 새로운 architecture. 정확한 스펙은 공개되지 않았음

- 5세대 NVLink 도입

  - 1.8TB/s 의 대역폭 제공

  - 최대 576개의 GPU를 하나로 연결이 가능

  - Superchips 사이의 데이터 이동 시 병목현상 최소화

    

  ![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/NVlink_4.png?raw=true)

- **nvlink switch 도입**

  - 4개의 NV link를 내장하여 1.8 TB/sec 의 속도를 제공
  - 7.2 TB/sec의 대역폭 제공
  - nvlink 와 연동하여 GPU를 서로 연결하는 용도
  - 독립적인 GPU를 사상 최고 속도로 데이터를 주고받을 수 있는 성능을 자랑 

- **Fifth-generation of Tensor Cores** 도입



**Fifth-generation of Tensor Cores**

- FP4 정밀도 연산 지원

| Model name | release date |
| ---------- | ------------ |
| B200       | -            |

- B200: Black well GPU 2개를 연결하여 구성된 chipset

  ![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/B200.jpg?raw=true)



**Grace Blackwell 200 Superchips**

- B200 GPU *2 + Grace CPU 를 연결한 Chiplet으로, 반도체 패키징 기술 중 MCM(Multi chip module)을 사용하여 

  하나의 공통 기판(main board) 위에서 여러 GPU가 하나의 GPU처럼 사용될 수 있도록 구성한 Superchips.

  NVLink만으로 연결한 것 보다 호환성이 더욱 높다.

-  HBM3 의 다음 세대인 HBM3e 사용. (용량 192GB   대역폭 1,280GB/s)

![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/GB200-Grace-Blackwell-Superchip.jpg?raw=true)



**GB200 NVL72**

Grace Blackwell 200 Superchips 36개로 구성된 슈퍼 컴퓨터

- FP8 단위 기준 720 PFLOPS  (DGX Grace hopper 200 보다 22배 빠른 속도)
- 수냉식 지원
- GB200 NVL72 다수를 구성하여 Grace hopper Data Center보다 더욱 높은 성능의 data center를 제공할 예정

GB200 NVL72 그림 삽입





**data center용 GPU의 tensor Performance 비교**

![](https://github.com/HibernationNo1/TIL/blob/master/semina/images/tensor%20Performance.png?raw=true)