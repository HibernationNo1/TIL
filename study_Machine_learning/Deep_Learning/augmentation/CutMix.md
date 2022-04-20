# CutMix

**`CutMix: Regularization Strategy to Train Strong Classifiers with Localizable Features`**

peper : https://arxiv.org/abs/1905.04899



CutMix는 모델이 객체의 차이를 식별할 수 있는 부분에 집중하지 않고, 덜 구별되는 부분 및 이미지의 전체적인 구역을 보고 학습도록 하여 일반화와 localization 성능을 높이는 방법이다. 

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbbJGPV%2Fbtq4Ufmxat3%2FRn3Zp89aSWwtU07xIOE8Q0%2Fimg.png)



```python
# generate mixed sample
lam = np.random.beta(args.beta, args.beta)
rand_index = torch.randperm(input.size()[0]).cuda()
target_a = target
target_b = target[rand_index]
bbx1, bby1, bbx2, bby2 = rand_bbox(input.size(), lam)
input[:, :, bbx1:bbx2, bby1:bby2] = input[rand_index, :, bbx1:bbx2, bby1:bby2]
# adjust lambda to exactly match pixel ratio
lam = 1 - ((bbx2 - bbx1) * (bby2 - bby1) / (input.size()[-1] * input.size()[-2]))
# compute output
output = model(input)
loss = criterion(output, target_a) * lam + criterion(output, target_b) * (1. - lam)
```

- `lam` : 균일 distribution에서 sampling한 값
- `target` : traning dataset
- `bbx1, bby1, bbx2, bby2` : input image에서 `lam`비율에 따라 random하게 crop된 bbox
- `model()` 에 입력되는`input`은  `bbx1, bby1, bbx2, bby2` 의 영역에 대해 다른 image의 crop된 부분으로 대체된다.



CutMix로 생성한 이미지로 학습한 신경망은 이미지의 특정 부분만을 보고 판단하는 것이 아니라, 전체적인 영역을 보고 판단하도록 유도하며, 따라서 train set과 test set의 분포가 다른 경우를 의미하는 OOD(out of distribution)와 이미지가 가려진 sample, adversarial sample에서의 robustness도 좋은 성능을 나타낸다.



#### code

cutmix는 timm module을 호출해서 사용할 수 있다.

```python
import timm
from timm.data import Mixup

mixup_fn = Mixup( 
    cutmix_alpha=, 
    cutmix_minmax=, 
    prob=, 
    mode=,
    label_smoothing=, 
    num_classes=)
```

- `cutmix_alpha` : cutmix alpha value, cutmix is active if > 0. (default: 0)

- `cutmix_minmax` : cutmix min/max image ratio, cutmix is active and uses this vs alpha if not None.

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
    'mixup_alpha': 0.,
    'cutmix_alpha': 1.0,
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



