# RoI pooling

RoI(Region of interest) pooling : 관심 영역에 대한 max pooling을 수행하는 방법이다.

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FoR8hS%2FbtqMRlbMqao%2FdDjfVA0HP6fclZlUIxR6M1%2Fimg.png)

위의 image는 CNN의 output인 feature map이며, map에서 h*w영역이 ROI영역이다.

이 ROI영역을 (H, W)의 고정된 작은 window size으로 나누고, 나눠진 각각의 section에서 max pooling을 적용하게 되어 H*W size의 feature map이 생성되는 것이다.

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2F33Spy%2FbtqMPi7sTXw%2FjZjWcK05KoPgb3IJ5WKbFk%2Fimg.png)

이런 pooling을 하는 이유는, 다 제각각의 크기인 RoI 영역을 동일한 크기로 맞춰 fullly connected layer로 넘기기 위함이다.

> 위의 이미지를 보면 RoI 영역 안의 max-pooling 영역이 모두 동일하지 않음을 알 수 있다. 그럼에도 불구하고 고정된 길이의 벡터로 만드는 것이 RoI pooling layer의 역할이다.



Faster R-CNN부터는 Region Proposal의 동작이 Region Proposal Network(RPN)에 의해 동작한다.

그리고 RPN의 output으로부터 얻은 ROI를 통해 ROI를 수행한다.

> 각각의 ROI는 (y, x, w, h)의 형태이다.



**동작**

1. 각각의 ROI를 (H, W)개수의 grid 형태 section으로 분할한다.

   > H, W는 사전에 설정해 놓는 output shape이다.
   >
   > 각 section의 size는 (h/H, w/W)이며, 이 때 shape이 정수로 정확히 나눠지지 않을 때는 임의로 section의 size를 조절한다.
   >
   > 예시 :: 
   >
   > input ROI == 5 × 4 , 	target activation map == 2 × 2  일 때
   >
   >  h/H, w/W = 2.5, 2 가 된다.
   >
   > 이런 경우 2개의 section은 2 × 2가 되어야 하고, 나머지 2개의 section은 3 × 2가 되어야 한다.

2. 각각의 section에서 max pooling을 수행한다.



**문제점**

Quantization Problem 

Feature map에서 ROI Feature map으로 계산을 진행할 떄 H, W가 정수값이여야 한다. 그렇기 때문에 Feature map에서의 ROI의 h, w를 H, W로 나눈 값인 h/H, w/W가 정수로 떨어지지 않으면 나머지 over size의 영역은 버리게 된다. 

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FcKBVPm%2Fbtq4s3LQtv0%2FBQDhE6GGqZ92EmsiakQkU0%2Fimg.png)

