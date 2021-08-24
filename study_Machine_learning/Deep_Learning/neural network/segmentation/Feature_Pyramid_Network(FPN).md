# Feature Pyramid Network(FPN)

FPN은 backbone network의 각각의 layer를 통해 얻어진 feature map을 사용해서 object detection을 수행한다.



- Region Proposal Network와 Feature Pyramid Network의 차이점

  RPN은 backbone network의 output인 feature map을 받아 다양한 size의 anchor를 대응시켜 object detection을 수행하도록 한다.

  > backbone network의 last layer의 output만 사용한다.

  FPN은 backbone network의 내부 layer 각각의 output인 feature map에 anchor를 대응시켜 object detection을 수행하도록 한다.

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FDFL4S%2FbtqEeX5IAp0%2FCbvO9zsvHU9Z6fNcrFkf8K%2Fimg.jpg)

##### Resnet

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fb2vbLx%2FbtraGFFzB47%2F7DklJHSXGkNfx0IEZb8lOk%2Fimg.png)



### Process

#### Bottom-up pathway

backbone network의 각각의 layer로부터 feature map (C1, C2, C3, C4, C5)를 계산한다.

> input image size : 1024×1024
>
> conv1(str = 2)의 output size   // conv1은 큰 memory를 차지하기 때문에 ptramid에 포함시키지 않는다.

- stage-2의 output shape(C2) = 64×64×256
- stage-3의 output shape(C3) = 32×32×512
- stage-4의 output shape(C4) = 16×16×1024
- stage-5의 output shape(C5) = 8×8×2048



#### Top-down pathway

Bottom-up과정에서 계산한 feature map (C2, C3, C4, C5)을 통해 feature map (M2, M3, M4, M5)을 계산한다.

- M5계산 방법

  feature map C5에 1×1 conv1 layer을 통해 채널 수를 256개로 맞춰준다.

  > 채널 수를 256개로 맞추는 이유
  >
  > M5, 4, 3은 결국 M2의 계산에 활용되는데 M2의 channel이 256이기 때문에 통일시켜준다. 

  output shape(M5) = 8×8×256

- M4계산 방법

  1. 계산된 M5의 size을 2배로 upsampling한다.

  2. feature map C4에 1×1 conv1 layer을 통해 채널 수를 256개로 맞춰준다.
  3. 1번과 2번 과정으로 계산된 각 feature map을 element-wise addition 연산을 수행한다.

  M3, M2의 계산 과정도 동일하다.

  output shape(M4) = 16×16×256

  output shape(M3) = 32×32×256

  output shape(M2) = 64×64×256

  

M4는 M5의 정보를, M2는 M3, 4, 5의 정보를 담고 있기 때문에 한 개의 feature map에 대해서 여러 scale의 anchor를 생성할 필요가 없게 된다.



#### output feature map

feature map (M2, M3, M4, M5)로부터 feature map (P2, P3, P4, P5)을 계산한다.

- 계산 

  M5에 3×3 conv연산을 수행하고 channel은 128로 통일한다.

  > F2~F5는 upsampling과 이전 feature map의 addition과정을 통해 feature data가 학습에 맞지 않게 망가졌을 수 있기 때문이다.
  
  output shape(P2) = 64×64×128
  
  output shape(P3) = 32×32×128
  
  output shape(P4) = 16×16×128
  
  output shape(P5) = 8×8×128





