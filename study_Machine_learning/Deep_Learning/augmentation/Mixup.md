# Mixup

**`mixup: Beyond Empirical Risk Minimization`**

> paper : https://arxiv.org/abs/1710.09412



#### Risk Minimization

- **Emprical Risk Minimization(ERM) principle** 

  training dataset에 대한 mean error를 최소화 함으로써 신경망을 최적화 한다.

  empirical distribution(경험적 분포 즉, dataset만의 분포)을 통해서 risk(error)를 최소화한다.

  훈련 데이터는 이 세상에 있는 모든 특징들을 포함하고 있지 않기 때문에 학습한 모델은 데이터셋에 편향된다. 또한 훈련 데이터셋의 규모가 커질수록 ERM의 수렴성이 보장된다

  하지만 ERM 기반의 학습에는 훈련 데이터는 "기억(memorize)"하여 강한 규제(regularization) 방법을 쓰더라도 훈련 데이터에 과적합되는 현상이 발생한다는 단점이 있다. 따라서, ERM을 기반으로 학습한 신경망은 OOD(Out Of Distribution) 데이터에 취약할 수 밖에 없다.



- **Vicinal Risk Minimization(VRM) principle**

  training dataset만 학습하는 것이 아니라 training dataset의 vicinal distribution(근방 분포)도 함께 활용한다. vicinal distribution는 data augmentation으로 만들어진 가상의 dataset을 샘플링하여 신경망 학습의 도움을 주는 전략이다.



### Mixup

mixup은 하나의 data augmentation기법으로, Out Of Distribution data에 취약한 인공지능 성능을 향상시키기 위한 VRM학습의 한 종류라고 볼 수 있다.

> 과적합이 덜 발생한다는 의미도 있기 때문에 regularization의 역할도 한다고 볼 수 있다.



- mixup에서 설명하는 data augmentation는 어떤 방식을 취하는가?

  class가 다른 두 개의 training data를 섞어 가상의 data를 만든 후, 해당 가상 dataset으로 학습을 하는 방식

  

  ![](https://blog.airlab.re.kr/assets/images/posts/2019-11-23-mixup/img_08.png)

  - `loader1` : training data의 class_1 값

  - `loader2` : training data의 class_2 값

  - `lam` : [0, 1] 사이에서 뽑아내는 random한 값으로, 가상의 data를 train data에 투영(섞는)하는 비율이다.

    > `alpha = 1` 로 고정

  

  training data에 cat, dog라는 두 개의 calss가 있을 때

  ![](https://blog.airlab.re.kr/assets/images/posts/2019-11-23-mixup/img_01.png)

  



### code

mixup은 timm module을 호출해서 사용할 수 있다.

```python
import timm
from timm.data import Mixup

mixup_fn = Mixup( 
    mixup_alpha=, 
    prob=, 
    mode=,
    label_smoothing=, 
    num_classes=)
```

- `mixup_alpha` : mixup alpha value, mixup is active if > 0., (default: 1)

- `prob` : he probability of applying mixup or cutmix per batch or element (default: 1)

  > `mode = batch`이면 per batch, `mode = elem` 이면 per element

- `mode` : how to apply mixup params (default: *batch*)

  > dataset을 batch 로 나누지 않았다면
  >
  > `mode = elem`

- `label_smoothing` : the amount of label smoothing to apply to the mixed target tensor (default: 0.1)

- `num_classes` : the number of classes for the target variable

  > 보통 1000넣음



e.g.

```python
import timm
from timm.data import Mixup

mixup_args = {
    'mixup_alpha': 1.,
    'cutmix_alpha': 0.,
    'cutmix_minmax': None,
    'prob': 1.0,
    'switch_prob': 0.,
    'mode': 'batch',
    'label_smoothing': 0,
    'num_classes': 1000}


mixup_fn = None
mixup_active = config.AUG.MIXUP > 0

if mixup_active:
    mixup_fn = Mixup(**mixup_args)
```

