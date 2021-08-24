#  Mask R-CNN

주로 Faster R-CNN을 기반으로 image segmentation을 학습하는 network

Faster R-CNN으로부터 달라진 점

- 3번째 병렬 분기를 추가해 확장함으로써 각 영역의 요소에 대한 이진 mask를 출력한다.

  Fast R-CNN의 calssification, localization(Bbox regression) branch에 새롭게 mask branch가 추가됐다.

- RPN전에 Feature Ptramod Network(FPN)가 추가됐다.
- image segmentation의 masking을 위해 ROI pooling대신 ROI align을 사용한다.

![](https://media.vlpt.us/images/suminwooo/post/1ae76a13-5eb5-40cc-935f-9c1517b92089/loss.png)

​																						   ┌ Classification

​										   ┌  RPN  ┐				   ┌  FC  ┤

image ─ ResNet ─ FPN  ┤  		  ├  ROI Align ┤ 		└ Regression

​										   └    ─    ┘					└  Mask Branch



Mask R-CNN의 backbone network는 ResNet-101을 사용한다.

> ResNet-101의 input size는 800~1024일 때 성능이 좋다고 알려져있다.





### Process

1. **image resize**

   Mask R-CNN의 backbone network는 ResNet-101을 사용하는데, ResNet-101의 input 은 1024×1024이기 때문에 resize한다.

   1. ResNet-101의 input size는 800~1024일 때 성능이 좋다고 알려져 있기 때문에  

      image를 800~1024으로 resize한다.

      > bilinear interpolation (쌍선형보간법) 사용

   2. image를 1024보다 작게 resize했을 경우, 1024×1024으로 맞추기 위해 나머지 pixel은 zero padding으로 값을 채워준다.

   3. FPN의 input으로 전달한다.

2. **make feature map by Bottom-up pathway**

   FPN의 backbone network인 ResNet-101의 각 stage에서 feature map (C2, C3, ..., C5)를 생성한다.

3. **make feature map by Top-down pathway**

   1. feature map (C2, C3, ..., C5)을 통해 Top-down pathway으로 feature map (M2, M3, ..., M5)를 생성한다.
   2. feature map M5에 maxpooling layer를 통해 feature map P6를 생성한다.
   3. feature map (M2, M3, ..., M5)에 3×3 conv 연산을 통해 feature map(P2, P3, P4, P5)을 계산한다.
   4. RPN의 input으로 feature map (P2, P3, P4, P5, P6)을 전달한다.

4. **Region Proposals by RPN**

   1. input인 P2, P3, P4, P5, P6에 대해 각각의 ratio의 anchor를 생성 후 대응시킨다.
   
      > feature map의 cell size × 3개의 rario = anchor의 총 개수
   
   2. anchor에 대해서 Non-maximum-suppression을 수행한다.
   
5. **RoI align**

   1. ROI영역에 대해 bilinear interpolation을 활용하여 max pooling을 계산하고 7×7의 pooled feature을 출력한다. 

6. **mask branch**

   





### Loss Function

$$
Loss = L_{Bbox} + L_{Classification} + L_{Mask}
$$

$$
L_{Bbox} :Regression\\ L_{Classification} : Softmax\ Cross \ Entropy \\
L_{Mask} : Binary\ Cross\ Entropy
$$



#### L_mask

mask loss는 pixel 단위로 object에 대한 masking을 binary로 수행하므로 BCE를 사용한다.

이는 곧 주어진 groundtruth에 해당하는 Bbox의 class에 대한 loss만 계산하고 다른 class들에 대해서는 학습을 하지 않는다는 것이다.

