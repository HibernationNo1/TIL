# Region Proposal Network

#### Region proposals

object가 존재할법한 위치 제안하는 방법이다.

(object가 존재할법한 위치를 찾아 나열하는 과정)



**Region Proposal의 종류**

1. Silding Window

   image에서 다양한 형태의 window를 silding하며 object가 존재하는지 확인한다.

   이러한 방법은 너무 많은 영역에 대하여 확인해야 한다는 단점이 있다.

2. Selective Search

   CPU기반에서 동작하며, 주변 픽셀 간의 유사도를 기준으로 Segmentation을 만들고, 이를 기준으로 물체가 있을법한 박스를 추론한다.

   ![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FSRNtz%2FbtqAPeQCKIU%2F1JsEHoX4e2bSAgzrgQQCD1%2Fimg.png)

   Object가 존재할법한 위치 약 2000개를 찾게 된다.

   > R-CNN, Fast R-CNN에서 사용됨
   >
   > 지금은 CNN에 의해 진행되기 때문에 사용되어지지 않는 알고리즘

3. Region Proposal Network(RPN)

   Silding Window의 방식을 GPU에서 수행한다.



## Region Proposal Network(RPN)

Input image를 CNN에 통과시켜 얻은 feature map을 input으로 받아 object가 존재할법한 위치를 제안하도록 도와주는 Network이다.

RPN의 output 값은 object가 존재할 것이라는 확률이 높고, non-maximum suppression과정을 통해 남은 Bbox이다. 이것이 바로 관심영역(ROI)이다. 

​																 ┌ Classification Layer

image ─ CNN ─  Intermediate Layer ┤

​																 └ Regression Layer

​							  └						**RPN**								┘     

### Process_simple

![](https://miro.medium.com/max/750/1*JDQw0RwmnIKeRABw3ZDI7Q.png)

1. k개의 anchor box를 이용하며, 각각의 box로 image상에서 Intermediate Layer를 통해 sliding window를 수행해 Intermediate feature를 추출한다.

   > anchor box는 1:1 또는 1:2 비율 등 여러가지 형태에 대해 사전에 정의되어 있지만, Regression과정을 통해 object의 모양에 따라 다양한 size의 Bbox로 prediction하게 된다.

2. 1. Intermediate feature에 대해 Regression을 수행하여 object의 coordinate에 대한 추론값을 계산한다.

      > k * 4(x, y, w, h) 개의 값을 prediction

   2. Intermediate feature에 대해 Classification을 수행하여 object의 존재 여부에 대한 probability score를 계산한다.

      > k * 2(있을 확률, 없을 확률) 개의 score를 prediction
      >
      > 이 때 어떤 class인지 분류하는 것이 아닌, 두 개의 class(object가 있는 경우, object가 없는 경우)에 대한 classification을 수행하는 이유는 RPN을 가볍게 만들기 위해서 이다.



##### Anchor box

anchor box는 원본 image의 각 grid cell의 중심을 기준으로 생성하고, 각각의 비율에 대해 각각의 scale을 적용하여 정의한다.

- **parameters for define Anchor**

  scale : feature map에서의 anchor의 size

  ratio : feature map에서의 anchor의 `width:height` ratio

  stride : image를 기준으로 어느 정도 간격으로 Anchor를 생성할 것인지 나타내는 값

  > 주로 image와 feature map의 크기의 비율(sub sampling ratio)값을 사용

  - feature map에서의 Anchor_base_size를 결정하는 요인 == scale, ratio
  - feature map의 size는 image의 w, h를 stride로 나눈 값이기 때문에, 이 것이 반영된 원본 image에서 Anchor의 크기는 Anchor_base_size + stride 이다.

  > 예시 ::
  >
  > Fast R-CNN에서는 3개의 스케일[128, 256, 512]과 3개의 비율[1:1, 1:2, 2:1]을 사용하여 k=9개의 앵커를 사용하였다.
  >
  > ![](https://media.vlpt.us/images/suminwooo/post/49fa1d5a-d59c-4272-b43d-4af416134bf3/image.png)
  >
  > 원본 image의 크기가 600×800이고, sub-sampling ratio = 1/16일 때
  >
  > CNN에 의한 feature map은 38×50이다. (38, 50가 곧 stride)
  >
  > 그렇기에 Fast R-CNN에서는 각 cell마다 9개의 anchor box를 만들었다. (총 개수 17100 = 38×50×9 ) 

  

- **Generate Anchors**

  a개의 scale과 b개의 ratio를 가진 Anchor box를 만든다고 할 때,  

  이미지의 크기에 sub-sampling ratio를 곱한만큼의 grid cell을 그린 후 각각의 cell 기준으로 a×b개의 Anchor를 만든다.

  Anchor하나의 값의 구성은 left top, right bottom의 x, y좌표를 표현하며 이는 각각 (x1, y1) (x2, y2)로 표현되기 때문에 (x1, y1, x2, y2)형식의 구조를 갖는다.



##### Delta

기본 Anchor의 크기와 위치를 조정하기 위한 값으로, model을 통해 학습되는 parameter이다.

즉, object에 대한 (y, x, h, w)이다.

Anchor하나에 Delta가 하나씩 대응되며, Delta하나의 값의 구성은 (deltaCenterY, deltaCenterX, deltaHeight, deltaWidth)형식의 구조를 갖는다.



##### Probability

각 Anchor 내부에 객체가 존재할 확률이다.



### Process_detail

1. **Generate Anchors**

   anchor box를 생성한다.

2. **input data to RPN** 

   > 예시 :: VGG 기반의 CNN의 output으로 14×14×512의 input data를 받는다.

3. **sliding window with Intermediate Layer**

   image상에서 Intermediate Layer로 sliding window를 진행하며, 각 kernel에 대해서 Intermediate feature를 계산한다.

   > 예시 :: 
   >
   > layer의 channel(kernel의 개수) = input channel의 개수
   >
   > kernel_size = 3×3, stride = 1, padding = 1 일 때
   >
   > 14×14×512의 input data에서 Intermediate Layer를 통과한 output의 shape == 14×14×512

4. - **Classification Layer**

     Intermediate feature에 대해 object가 있을probability, 없을(background) probability를 계산한다.

     이때 각 계산은 각 anchor box에 대응되며 반영해야 하기 때문에 channel의 개수는 anchor box의 개수 × 2 이다.

     back propagation과정에서 Probability가 학습되게 된다.

     > 예시 ::
     >
     > layer의 channel(kernel의 개수) = anchor box의 개수 × 2
     >
     > kernel_size = 1×1, stride = 1, padding = 0 일 때
     >
     > 14×14×512의 input data에서 Classification Layer를 통과한 output의 shape == 14×14×9×2

   - **Regression Layer**

     Intermediate feature에 대해 object 위치에 대한 Delta(y, x, w, h)를 계산한다.

     이때 각 계산은 각 anchor box에 대응되며 반영해야 하기 때문에 channel의 개수는 anchor box의 개수 × 4 이다.

     back propagation과정에서 Delta가 학습되게 된다.

     > 예시 ::
     >
     > layer의 channel(kernel의 개수) = anchor box의 개수 × 4
     >
     > kernel_size = 1×1, stride = 1, padding = 0 일 때
     >
     > 14×14×512의 input data에서 Classification Layer를 통과한 output의 shape == 14×14×9×4

   

### Loss Function

$$
L(\{p_i\}, \{t_i\}) = 
\frac{1}{N_{cls}}\sum_i L_{cls}(p_i, p^*_i) + 
\lambda\frac{1}{N_{reg}}\sum_ip^*_iL_{reg}(t_i, t^*_i)
$$

- `i` : mini-batch 내의 anchor의 index

- `N_{cls}` : mini-batch의 크기

- `p_i` : anchor `i`에 object가 존재할 probability에 대한 prediction

- `p^*_i` :  anchor `i`에 object가 존재할 경우에 대한 label. (존재할 경우 1, 아닐 경우 0)

- `L_{cls}` : log loss (binary cross entropy)



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



### Training
