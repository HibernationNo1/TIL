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
Loss = L_{RPN} + L_{MRCNN}
$$



#### L_{RPN}

$$
Loss_{RPN} = L_{Bbox} + L_{Classification}
$$

$$
L_{Bbox} :Regression\\ L_{Classification} : Categorical\ Cross \ Entropy
$$

##### L_{Bbox}

`smooth_l1_loss`



##### L_{Classification}

`tf.keras.losses.sparse_categorical_crossentropy`





#### L_{MRCNN}

$$
L_{MRCNN} = L_{Bbox} + L_{Classification} + L_{Mask}
$$

$$
L_{Bbox} :Regression\\ L_{Classification} : Categorical\ Cross \ Entropy \\ L_{Mask} : Binary\ Cross\ Entropy
$$



##### L_{Bbox}

`smooth_l1_loss`



##### L_{Classification}

`tf.nn.sparse_softmax_cross_entropy_with_logits`

##### L_{Mask}

`tf.keras.binary_crossentropy`











###### L_Bbox

$$
L_{Bbox} = \lambda\frac{1}{N_{reg}}\sum_ip^*_iL_{reg}(t_i, t^*_i)
$$



- `N_{reg}` : anchor의 총 개수(feature map의 w × h × num_anchor)

- `lambda` : Balancing parameter

  > Ncls와 Nreg 차이로 발생하는 불균형을 방지하기 위해 사용된다. cls에 대한 mini-batch의 크기가 256(=Ncls)이고, 이미지 내부에서 사용된 모든 anchor의 location이 약 2,400(=Nreg)라 하면 lamda 값은 10 정도로 설정한다. (1~100 사이에서는 학습결과에 큰 변화가 없다)

- `t_i` : Bbox에 대한 prediction  

- `t^*_i` : Bbox에 대한 label

- `L_{reg}` : smooth L1

  `L_{reg}`에서는 predicted value, label 각각의 coordinate에 대해 다음과 같은 연산을 취한다.

  - predicted value : `t_x`, `t_y`, `t_w`, `t_h`
    $$
    t_x = \frac{x - x_a}{w_a}, \ \ \ \ \ \ \ \ t_y = \frac{y - y_a}{h_a}\\
    t_w = log(\frac{w}{w_a}), \ \ \ \ \ \ \ \ \ t_h = log(\frac{h}{h_a})
    $$

    - `x` : predicted x center coordinate (or `y`)
    - `x_a` : x center coordinate of anchor box (or `y_a`)
    - `w_a` : width of  anchor box (or `h_a`)

  - label : `t^*_x`, `t^*_y`, `t^*_w`, `t^*_h`
    $$
    t^*_x = \frac{x^* - x_a}{w_a}, \ \ \ \ \ \ \ \ t^*_y = \frac{y^* - y_a}{h_a}\\
    t^*_w = log(\frac{w^*}{w_a}), \ \ \ \ \ \ \ \ \ t^*_h = log(\frac{h^*}{h_a})
    $$

  이후 
  $$
  L_{reg}(t, t^*) = \sum_{i \in\{x, y, w, h\}} smooth_{L_1}(t_i - t^*_i)
  $$
  계산을 수행하게 되고, `smooth_L_1` 은 아래의 계산을 수행한다.
  $$
  smooth_{L_1}(x) = \left\{\begin{matrix} 0.5x^2 \ \ \ \ \ \ if\ \  |x| < 1\\ 
  |x| - 0.5 \ \ \ \ \ otherwise \end{matrix}\right.
  $$

  > 예시 :: mini-batch 내의 anchor의 index == 1일 때
  > $$
  > L_{reg}(t_1, t^*_1) \\
  > = smooth_{L_1}(t_x - t^*_x) + smooth_{L_1}(t_y - t^*_y) + smooth_{L_1}(t_w - t^*_w) + smooth_{L_1}(t_h - t^*_h)
  > $$
  >
  > $$
  > = smooth_{L_1}(\frac{x - x_a}{w_a} - \frac{x^* - x_a}{w_a}) + smooth_{L_1}(\frac{y - y_a}{h_a} - \frac{y^* - y_a}{h_a})
  > \\+ smooth_{L_1}(log(\frac{w}{w_a}) - log(\frac{w^*}{w_a}))+ smooth_{L_1}(t_h = log(\frac{h}{h_a}) - log(\frac{h^*}{h_a}))
  > $$





###### L_Classification

$$
L_{Classification} = \frac{1}{N_{cls}}\sum_i L_{cls}(p_i, p^*_i)
$$



- `i` : mini-batch 내의 anchor의 index
- `N_{cls}` : mini-batch의 크기
- `p_i` : anchor `i`에 object가 존재할 probability에 대한 prediction
- `p^*_i` :  anchor `i`에 object가 존재할 경우에 대한 label. (존재할 경우 1, 아닐 경우 0)
- `L_{cls}` : log loss (binary cross entropy)





###### L_mask

mask loss는 pixel 단위로 object에 대한 masking을 binary로 수행하므로 BCE를 사용한다.

이는 곧 주어진 groundtruth에 해당하는 Bbox의 class에 대한 loss만 계산하고 다른 class들에 대해서는 학습을 하지 않는다는 것이다.

예를 들어, class가 class1, class2, class3 이 있고 classification에서 나온 결과 class 2에 대한 mask만 학습하고자 한다면

class 2를 제외한 class의 mask는 제거하고, class 2의 mask형태에 대해서만 pixel학습을 한다.

그렇게 때문에 class가 무엇인지 학습 할 필요가 없기 때문에 BCE를 사용하는 것이다.

