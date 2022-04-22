# timm

pytorch로 구현된 model들의 저장소

```python
import timm
```





model list확인 

```python
model_names = timm.list_models(pretrained=True)
print(f"model_names : {model_names}")
```



#### create_model

특정 model을 생성한다.

```python
import timm

model = timm.create_model('vit_base_patch16_224', pretrained=True)
```

> 예시로 `'vit_base_patch16_224'`를  create



### data



#### resolve_data_config

model에 대한 default config를 return한다.

```python
from timm.data import resolve_data_config
config = resolve_data_config({}, model=model)
```



#### create_transform

```python
from timm.data import create_transform
```



#### Mixup

mixup과 cutmix를 사용할 수 있게 해주는 class

> setup mixup / cutmix

```python
from timm.data import Mixup

MIXUP = 0.3
CUTMIX = 0.3
CUTMIX_MINMAX = None
MIXUP_PROB = 1.0
MIXUP_SWITCH_PROB = 0.5
MIXUP_MODE = "batch"

LABEL_SMOOTHING = 0.1

num_classes = 1000


mixup_fn = None
mixup_active = mixup_alpha > 0 or cutmix_alpha > 0. or cutmix_minmax is not None
  
if mixup_active:
    mixup_fn = Mixup(
    		mixup_alpha=AUG.MIXUP, 
         	cutmix_alpha=CUTMIX, 
        	cutmix_minmax=CUTMIX_MINMAX,
        	prob=MIXUP_PROB, 
        	switch_prob=MIXUP_SWITCH_PROB, 
        	mode=MIXUP_MODE,
            label_smoothing=LABEL_SMOOTHING, 
        	num_classes=num_classes)
        
```

- `mixup_alpha` :  mixup alpha value, mixup is active if > 0., (default: 1)

- `cutmix_alpha` : cutmix alpha value, cutmix is active if > 0. (default: 0)

- `cutmix_minmax` : cutmix min/max image ratio, cutmix is active and uses this vs alpha if not None.

  > 보통 None

- `prob`: he probability of applying mixup or cutmix per batch or element (default: 1)

  >`mode = batch`이면 per batch, `mode = elem` 이면 per element

- `switch_prob`: mixup, cutmix 둘 다 활성일 때 mixup대신 cutmix로 전환할 확률 (default: 0.5)

- `mode` : how to apply mixup params (default: *batch*)

  >dataset을 batch 로 나누지 않았다면
  >
  >`mode = elem`

- `label_smoothing` :  the amount of label smoothing to apply to the mixed target tensor (default: 0.1)

- `num_classes` : the number of classes for the target variable

  > 보통 1000 할당



### models

#### layers

##### to_2tuple

인자로 받는 값을 2 element의 tuple로 return 

```python
from timm.models.layers import to_2tuple

img_size = 224
img_size = to_2tuple(img_size)
print(img_size) # (224, 224)
```

