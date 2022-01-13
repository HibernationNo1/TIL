# Vision Transformer (ViT)

### ABSTRACT

Transformer는 language processing task에서 많이 사용되어왔지만, computer vision 분야에서는 제한적이였다. vision에서 attention은 convolutional networks와 결합되거나, 전체 구조를 유지하며 특정 요소를 convolutional networks와 대체하여 사용되는데 사용했기 때문이다.

논문에서는 이러한 CNN에 대한 의존이 필요하지 않고, transformer가 직접적으로 연속적인 image patchs에 적용되어 classification task에 대해 동작할 수 있다고 말하고 있다.

학습된 많은 양의 data에서 사전학습되고, 여러 mid or small size images가 전이학습될 시, Vision Transformer (ViT) 는 state-of-the-art(SOTA) convolutional networks의 결과와 비교해서 계산량은 매우 적지만 훌륭한 결과를 보여준다.



### INTRODUCTION

특정 Transformers에서 Self-attention을 기반으로 한 architecture는 NLP에 사용되는 model이 되었다. 이러한 접근법은 거대한  text corpus의 pre-train과 특정 작은 dataset의 fine-tune의 방면에서 지배적이였다. Transformer의 계산 효율성과 확장성덕에 1000억개의 parameter가 넘는 전례없이 큰 model의 학습이 가능하게 되었다. 이러한 성능덕에 model과 dataset의 크기가 커짐에도 아직까지 성능포화 현상이 나타나지 않고 있다.

하지만 computer vision에서 convolutional architectures가 지배적이다. NLP의 성공에 힘입어, 다수의 CNN군 architecture에서 convolution이 self-attention으로 대체하기 위한 시도가있었는데, 이론적으로는 효과적이였지만 실제로는 특수한 attention 패턴 때문에 하드웨어 상에서 크게 효율적이지 못했기 때문에, classic ResNet과 같은 큰 image의 recognition을 위한 모델이 아직 SOTA이다.

NLP에 적용된 Transformer scaling이 성공적이였던것에 영감을 받아, 논문에서는 표준 Transformer에 약간의 수정을 거져 image에 직접적으로 적용하는 것을 실험했다. 이미지를 patch로 나누고 순서대로 linear한 embedding형태로 Transformer에 입력하여 (patch는 NLP의 Transformer에서처럼 token으로 간주한다.) 지도학습 방식으로 image classification model을 학습시켰다.

imageNet의 mid-size dataset을 큰 regularization없이 학습을 시켰을 때, 비슷한 size의 ResNet에 대해 조금 낮은 퍼센트의, 적당한 결과를 얻을 수 있었다. 이는 예상보다 실망스러운 결과처럼 보일 수 있는데, 그 이유는 Transformers에는 translation equivariance와 locality같은, CNN고유의 inductive biases가 적기 때문에 충분하지 않은 양의 데이터로 학습을 진행할 때 일반화가 잘 되지 않기 때문이다.

하지만 model이 1400백만~3억개의 image와 같은, 큰 dataset으로 학습을 받으면 결과가 달라진다. 논문에서는, 큰 규모의 학습에서는 inductive bias를 능가하는 것을 발견했다고 한다. 

저자의 Vision Transformer(ViT)는 적은 datapoints가 있는 작업에서 충분한 규모의 dataset으로 pre-trained되고 전이학습이 진행되었을 때 훌륭한 결과를 보여줬다고 말한다. ImageNet-21k dataset이나, JFT-300M dataset으로 pre-trained 되었을 때, ViT는 다수의 image 인식 표준 테스트에서 최신 기술을 능가하는 성능을 발휘했다. 특히, 가장 성능이 좋은 model은 ImageNet에서 88.55%의 정확도를, CIFAR-100에서는 94.55%의 정확도 등 VTAB군의 19개의 작업에서 높은 정확도를 보여준다.



### METHOD

model 구축시 ViT는 original Transformer에 최대한 가깝게 구성했다. NLP Transformer architecture를 확장하고 효율적으로 구현하여 간단하게 구축했기 때문에 별도의 설치 없이 즉시 사용이 가능하다는 이점이 있다.

####  VISION TRANSFORMER (VIT)

![](https://blog.kakaocdn.net/dn/7yg4q/btq8A9nxSKk/7Mcrjwtm2qxkkaEDgLcvk1/img.png)

 위 그림에서 보이듯, 표준 standard Transformer는 1차원의 token embedding을 sequence로 input한다. 2차원 image를 다루기 위해서, 저자는 image를 `H×W×C` 에서 flatten된 2차원 patches sequence `N×P^2×C`으로 reshape한다.

> $$
> from\ \ \ X\in \mathbb{R}^{H \times W \times C}
> $$
>
> $$
> to\ \ \ \ X\in \mathbb{R}^{N \times(p^{2} \cdot C )}
> $$
>
> - H, W : 해상도
> - C : channel
> - P : patch의 해상도 
> - N = H×W/P^2  , patch의 개수

 Transformer는 일정한 D size의 latent vector를 모든 layer에 걸쳐 사용하는데, 이를 통해 patchs를 flatten시키고 학습 가능한 linear projection을 통해 D차원에 mapping한다. 저자는 이 projection 출력을 patch embeddings라고 한다.

저자는 학습가능한 embedding을  embedding된 여러 patch의 sequence 앞에 붙여 추가한다.이는 image representation 'y' 로, Transformer encoder의 출력 상태이다.  pre-training과 fine-tuning동안 classification head는 Transformer encoder에 연결된다. classification head는  fine-tuning간에는 한 개의 linear layer인,  pre-training간에는 한 개의 hidden layer인 MLP로 구현된다. (위 그림 참고)

Position embedding은 위치정보를 유지하기 위해 patch embedding에 추가한다. 저자는 다른 2D  position embedding을 사용했지만 충분한 성능을 얻지 못했기 때문에, 학습가능한 표준 1D position embedding을 사용했다.

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FAIHts%2Fbtq5OTI5z80%2FKBKuLPZwKkw6lxxxvmO7O1%2Fimg.png)

> 위의 figure 1에서 확인할 수 있듯이 Encoder는 L개로 되어있으므로 위의 식에서 ll은 1부터 L까지로 되며 iteratively 계산되어 최종적으로 representation yy가 나온다.



#### FINE-TUNING AND HIGHER RESOLUTION

전형적으로, 저자는 ViT를 거대한 dataset에서 사전학습시키고 custom dataset에서  fine-tune을 진행한다. 이를 위해서 저자는 사전 학습된 prediction head를 제거하고 0으로 초기화 된 D × K shape의 feedforward layer를 연결한다. (K는 custom dataset에서의 class의 개수를 의미한다.) 이러한 방식은 종종 높은 해상도의 image의 dataset를 통한 사전 학습보다 좋은 결과를 보여준다. 높은 해상도의 image를 input으로 줄 때 patch의 size를 같게 유지하기 때문에 결과적으로 더 큰 효율적인 sequence 길이를 갖게 된다. ViT는 임의의 sequence길이를 조절할 수 있지만 (메모리 제약을 피하기 위해), 이런 경우 사전 학습된 position embedding은 더 이상 의미가 없게 될지도 모른다. 그렇기 때문에 저자는 원본 image의 위치에 따라 사전 학습된 position embedding에 대해 2D 보간법을 수행한다. 이러한 해상도 조절과 patch 추출은 image의 2D구조에 대한 inductive bias을 Vision Transformer에 직접적으로 적용하는 유일한 방법이다.



