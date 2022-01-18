# Swin Transformer

{:toc}

원문 : https://arxiv.org/pdf/2103.14030.pdf



#### Abstract

저자는 language와 image영역 사이의 큰 변환값을 차이를 해결하기 위해 Shifed windows방법을 제안합니다. Shifed windows는 cross-window연결과 동시에 self-attention계산을 겹치지 않는 local windows로 진행함으로써 높은 효율을 보여줍니다. 이러한 계층적 architectrure은 image 크기에 대해 linear한 연산량을 가지며 다양한 scale에 대해서 model의 높은 유연성을 가지고 있습다.  Swin Transformer은 semantic segmentation과 object detection과 같은 dense predction task와, image classification을 포함한 광대한 영역에서 image task에 대한 호환 기능을 제공합니다.

[code](https://github.com/microsoft/Swin-Transformer)



###  Introduction

기존의 Transformer기반의 model은 고정된 scale의 token을 활용했습니다. 이는 vision에 알맞지 않습니다.  또한 vision영역과 language의 차이는, 글자의 단어에 비해 pixel의 해상도가 훤씬 높다는 것입니다.  vision영역의 semantic segmentation는 pixel level의 dense prediction을 필요로 하며 이는 2차원의 연산량를 가진 self-attention을 활용한 높은 해상도에서의 Transformer는 다루기 힘듭니다. 이를 해결하기 위해 저자는 Swin Transformer라 불리는 범용의 Transformer backbone을 제안합니다. Swin Transformer는 계층적 feature map으로 구성되어 있으며 image size에 linear한 연산량을 가지고 있습니다. 



![](https://production-media.paperswithcode.com/social-images/unHHISomtzDKWczC.png)

위 그림에서 볼 수 있듯, Swin Transformer은 작은 patch로 이루어진 layer부터 이웃한 patch를 병합하여 더 큰 patch를 가진 바로 위의 layer과 같이 점점 큰 patch로 이루어진 feature map으로 이루어진 계층적 표현으로 이루어져 있습니다.  이러한 계층적 feature map으로 Swin Transformer은 FPN또는 U-Net과 같은 dense prediction의 기술을 보다 편리하게 활용할 수 있습니다. linear한 연산량은 image를 겹치지 않은 상태로 여러 partition으로 나눔으로써 self-attention을 locally하게 수행할 수 있게 해 줍니다. (이 때 각각의 window안의 수많은 patch는 고정이기 때문에 연산량은 image size에 따라 linear하게 됩니다.) 이러한 merits는  Swin Transformer를 vision영역에서 범용적으로 사용 가능한 backbone으로 사용할 수 있게 해 줍니다.



![](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTdTsZLP7jlYRDimGCwOc_yWVr8K4T9coECpwmjaCOuM8pwIK-GTxf3ZRnW40nwF8aO9jY&usqp=CAU)

 Swin Transformer의 핵심 요소는 연속되는 self-attention layer사이에서 진행되는 window partition shift입니다. 이는 window를 이전 앞선 layer에 연결시키며, 이는 상당한 모델링 성능 향상을 제공합니다. 이러한 전략은 실제 처리시간을 줄이는데도 효과적입니다. shifted window사 window안의 여러 patch는 같은 key set을 가지고 있고, 이 patch의 요청은 hardware에서 memory접근에 더욱 용이하게 합니다. 이전의 sliding window 방식은 각각의 patch가 각기 다른 key set을 가지고 있었음에도 low latency였는데, shifted window는 이보다도 빠릅니다. 







### Method

#### 1. Overall Architecture

![](https://media.arxiv-vanity.com/render-output/4986850/x1.png)

> 위 그림은 간단한 version의 Swin Transformer architecture임 (version. T )

먼저 ViT와 같은 mobule을 사용하여 input RGB를 겹치지 않는 다수의 patch로 나눈다.  (이하 각각의 patch는 token이라 칭함) 각각의 token은 각 pixel의 RGB 값을 이어 붙인 것이다. 
$$
shape = H \times W \times 3
$$

1. **Patch partition**

   저자는 4×4 크기의 patch를 사용했으며, 이를 통해 각각의 patch는 4×4×3의 shape을 가지게 됩니다. 이를 flatten하면 patch는 총 48개의 channel을 가지게 된다.

    따라서 전체 tensor의 shape은 아래와 같다.
   $$
   shape = \frac{H}{4} \times \frac{W}{4} \times 48
   $$

2. **Stage 1**

   1. linear embedding

      48개의 channel을 임의의 C개의 channel로 변환한다.
      $$
      shape = \frac{H}{4} \times \frac{W}{4} \times C
      $$

   2. Swin Transformer block 

      > self-attention을 수정해서 만들어진 block으로, 구성은 위 그림의 (b)와 같다.
      >
      > 1. LN(Layer Norm)
      > 2. W-MSA(Window MSA)
      > 3. SW-MSA(Shifted Window MSA)
      > 4. MLP(multi-layer perceptron)
      >
      > 자세한 내용은 아래에 

      Swin Transformer block 은 token의 숫자를 유지한 채 적용한다.
      $$
      shape = \frac{H}{4} \times \frac{W}{4} \times C
      $$

3. **Stage 2, 3, 4**

   > Stage 2, Stage 4 에는 Swin Transformer block 을 2개를 사용하고
   >
   > Stage 3 에는 Swin Transformer block 을 6개 사용한다.

   1. Patch marging

      계층적 표현을 수행하기 위해, Patch marging layer에 의해 token의 숫자는 줄어들게 된다.

      Stage 2에서 Patch marging layer은 이웃하는 2×2의 patch를 연결한다.

      >  이 때 각 patch는 C개의 channel을 가지고 있는데(1×1×C), patch에 이웃하는 2×2를 연결하는 경우 patch의 shape은 2×2×C이기 때문에 이를 flatten하면 총 4C의 channel을 가지게 된다.

      $$
      shape = \frac{H}{8} \times \frac{W}{8} \times 4C
      $$

      이후 output의 channel을 2C로 변환한다.
      $$
      shape = \frac{H}{8} \times \frac{W}{8} \times 2C
      $$

   2. Swin Transformer block 

      Patch marging의 output의 shape을 유치한 채로 적용한다.

      

   이러한 동작을 Stage 3, Stage 4에서 반복한다.

   Stage 3 
   $$
   shape = \frac{H}{16} \times \frac{W}{16} \times 4C
   $$
   Stage 4
   $$
   shape = \frac{H}{32} \times \frac{W}{32} \times 8C
   $$
   

   모든 stage는 일반적인 convolutional networks의 feature map 해상도와 같이 계층적 표현으로 수행된다.

    



##### Swin Transformer block

![](https://media.arxiv-vanity.com/render-output/4986850/x1.png)

Swin Transformer는 표준 shifted window를 기반으로 한 Transformer block module안의  multi-head self attention(MSA)을 대체하여 설계 되었으며, 그 이외는 기존block과 그대로 구현되어 있다.  또한 위 그림의 (b)를 보면 알 수 있듯, Swin Transformer은 GELU nonlinearity로 구성된 2-layer MLP사이에  shifted window기반의 MSA module로 구성되어 있다. 

LayerNorm(LN) layer은 각각의 MAS module과 MLP이전에 적용되었으며, residual connection은 각각의 module이후에 적용된다.



#### 2. Shifted Window based Self-Attention

image classification을 위한 표준 Transformer architecture과 그 적용방법은 모두 global self attention으로 수행되며, 이는 각각의 token과 그 외의 모든 token사이의 관계에 대해서 계산을 진행한다. global적인 계산은 다수의 token에 대한 2차 계산성을 표현하기 때문에,  dense prediction나 고해상도 이미지와 같은 수많은 token을 다루는 많은 vision문제에 적합하지 않다.



##### Self-attention in non-overlapped windows

효율적인 modeling을 위해, 저자는 local windows에서 self attention을 계산하는 방법을 제안한다. 이 방법은 windows를 겹치지 않는 방식을 유지하며 각 image의 부분을 고르게 재정렬한다.

h × w의 이미지에서 각각의 window가 M × M의 patch로 구성되어 있다면, window 기반의 global MSA module 계산량은 아래와 같다.
$$
\Omega(MSA) = 4hwC^{2} + 2(hw)^{2}C \ \ \ \ \ (1)\\
\Omega(W-MSA) = 4hwc^{2} + 2M^{2}hwC 	\ \ \ \ \ (2)
$$
 (1)의 경우 hw에 대해 2차 patch이고, (2)의 경우 M값이 고정되어 있을 때 선형이다. (default M값은 7). Global self-attention계산은 일반적으로 큰 hw에 대해 감당이 불가능한 반면, window기반의 self-attention은 확장이 가능하다.



##### Shifted window partitioning in successive blocks

window기반의 self-attention module은 windows간의 연결이 약해 modeling 능력이 부족하기 때문에, 겹치지 않는 windows에서의 효율적인 계산을 유지하며 cross-window 연결을 도입하기 위해 저자는 shifted window 분할 접근방법을 제안한다.  이는 두 개의 분할된 구성을 번갈아 사용하는 연속된 Swin Transformer block으로 구성되어 있다. 

![](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTdTsZLP7jlYRDimGCwOc_yWVr8K4T9coECpwmjaCOuM8pwIK-GTxf3ZRnW40nwF8aO9jY&usqp=CAU)

첫 번째 module은 top-left pixel로부터 시작하는 regularly  window 분할 전략을 사용하는데, 이는 8 × 8 크기의 feature map은 4 × 4의 크기의 window를 2 × 2 모양으로 분할한다(이 때의 M = 4). 다음 module은 regularly하게 분할된 windows를 (M/2, M/2)만큼 이동하여 이전 layer의 windows구성에 적용한다. (대각선 이동) 이러한 shifted window 분할 접근법으로 인한 연속적인 Swin Transformer의 계산은 아래와 같이 표현된다.
$$
\hat{z}^{l} =  W-MSA(LN(z^{l-1})) + z^{l-1}, \ \ \ \ \ \ \ \ \ (1)\\
z^{l} = MLP(LN(\hat{z}^{l})) + \hat{z^{l}}, \ \ \ \ \ \ \ \ \ (2)\\
\hat{z}^{l+1} = SW-MSA(LN(z^{l})) + z^{l}, \ \ \ \ \ \ \ \ \ (3)\\
z^{l+1} = MLP(LN(\hat{z}^{l+1})) + \hat{z}^{l+1} \ \ \ \ \ \ \ \ \ (4)
$$
(1)번은 block 'l' 에 대한 (S)W-MSA module 의 output feature을,

(2)번은 block 'l' 에 대한 MLP module의 output feature을 나타낸다.

> W-MSA은 일반적인 window 분할 구성을 사용한 multi-head self-attention이며
>
> SW-MSA는 shifted window 분할 구성을 사용한 multi-head self-attention이다.

shift window 분할 접근방법은 이전 layer안의 근접한(그리고 겹치지 않은) window간의 연결을 가능하게 했으며, 이는 image classification, object detection, and semantic segmentation 과 같은 분야에 더욱 효율적이다.



##### Efficient batch computation for shifted configuration

shifted window 분할의 문제점은 더 많은 window가 그 결과값으로 생성된다는 것이다. 이는 [f/M] × [w/M]의 크기에서 ([f/M] + 1) ×([w/M] + 1)의 크기로 window가 늘어나는 것인데, 이 때 몇몇의 window는 M × M보다 더 작은 사이즈의 window가 된다. 가장 근본적인 문제 해결방법은 M × M보다 더 작은 사이즈의 window에 pad를 적용해 M × M으로 만들고, attention계산을 진행할 때 pad가 적용된 영역은 mask영역에서 제외한다. 만일 window의 개수가 적은 경우 (2 × 2 처럼), pad에 의한 증가량은 상당하다. 

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbfY1G2%2Fbtq6RMW4EiY%2FmWabryoM0v8F2lr47Nw5B1%2Fimg.png)

저자는 위 문제점을 해결하기 위해 더욱 효율적으로 계산하는 방법인 좌상단 방향으로 이동하는 cyclic-shifting을 제안한다. 위 그림을 보면 알 수 있듯, window의 좌상단 이동 이후 자리잡은 여러개의 sub-windows는 feature map의 영역을 벗어난다. 이렇게 벗어난 영역에 mask를 씌워서 self-attention 계산이 이루어지지 않도록 한다.

cyclic-shift은 다수의 windows를 일반적인 window 분할 방법처럼 유지하기 때문에 효율적이다.  



##### Relative position bias



respect : 존경, ~에 대해

sophisticate : 정교하다.

query : 요청

displace : 옮기다, 바꾸다