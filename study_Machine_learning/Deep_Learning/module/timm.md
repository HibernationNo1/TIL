# timm

```
$ pip install timm
```

[documentation](https://timm.fast.ai/)



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



##### mixup_fn

```python
# samples.shape == [batch_size, channel, height, width]
# targets.shape == [batch_size]

if mixup_fn is not None:
    after_samples, after_targets = mixup_fn(samples, targets)   # len(semples) 이 2의 배수여야 함 ( % 2 !=0)

# after_samples.shape == [batch_size, channel, height, width]
# after_targets.shape == [batch_size, num_class]
```





**Using**

data를 GPU에 올려 학습준비를 마친 후 mixup function적용

```python
for idx, (samples, targets) in enumerate(data_loader):        
    samples = samples.cuda(non_blocking=True)
    targets = targets.cuda(non_blocking=True)


    if mixup_fn is not None:
        samples, targets = mixup_fn(samples, targets)
```

- `samples` : torch.Size(batch_size, chennal, height, width])  random한 tensor값
- `targets` : torch.Size([batch_size, max_instance_num])      label값 



### models.layers

##### to_2tuple

인자로 받는 값을 2 element의 tuple로 return 

```python
from timm.models.layers import to_2tuple

img_size = 224
img_size = to_2tuple(img_size)
print(img_size) # (224, 224)
```



##### trunc_normal_

tensor에 Truncated **normal initailization**을 적용한다.

```python
from timm.models.layers import trunc_normal_
trunc_normal_(x, mean = 0, std = 1)
```

- x : tensor
- mean : mean (default = 0)
- std : srandard deviation



##### DropPath

Dropout과의 차이점 : Dropout은 random한 index에 대해서 element 단위로 out을 적용하지만, DropPath는 batch 단위로 out을 적용한다.

```python
from timm.models.layers import DropPath
trunc_normal_(x, mean = 0, std = 1)

self.drop_path = DropPath(drop_path) if drop_path > 0. else nn.Identity()
```

- `drop_path` : (float) batch중에서 dropout을 적용할 비율





### scheduler

[scheduler github](https://github.com/rwightman/pytorch-image-models/tree/master/timm/scheduler)

#### cosine_lr

##### CosineLRScheduler

 [SGDR: Stochastic Gardient Descent with Warm Restarts](https://arxiv.org/abs/1608.03983) 에서 제안된 learning rate scheduling 방법으로, cosine형태로 learning rate를 cosine값처럼 조정하면서 정확도를 상승시키는 방법

![](https://timm.fast.ai/images/SGDR.png)

learning rate은 계속해서 수렴해서 마른걸레를 짜다가, 다시한번 크게 가져가서 또다른 optima를 찾는 노력을 할수 있다.



**code**

```python
from timm.scheduler.cosine_lr import CosineLRScheduler

lr_scheduler = CosineLRScheduler(
            optimizer = optimizer,
            t_initial=total_step,
            t_mul=1.,
            lr_min=config.TRAIN.MIN_LR,
            warmup_lr_init=config.TRAIN.WARMUP_LR,
            warmup_t=warmup_steps,
            cycle_limit=1,
            t_in_epochs=False,
        )
```

- `optimizer` : 앞서 정의한 optimizer

-  `t_initial` : initial number of epochs

- `t_mul` : learning rate를 annealing(restart) 하는 값. 보통 1 할당  (Default 1)

  > 그냥 안씀

- `lr_min` :  minimum learning rate to use during the scheduling (Defaults `1e-5`)

- `warmup_lr_init` : The initial learning rate during warmup

- `warmup_t` : 초기에 warmup을 적용할 epochs의 수

- `cycle_limit` : SGDR를 다시 시작하는 숫자

- `t_in_epochs` : `False`일 때 임의의 epoch `t` 에 대해 return된 learning rate를 None으로 만든다.

  > 보통 False로 set



#### step_lr

##### StepLRScheduler

learning rate를 일정한 값으로 줄여가면서 변화시키는 방법

![](https://timm.fast.ai/images/StepLR.png)



**code**

```python
from timm.scheduler.cosine_lr import CosineLRScheduler

lr_scheduler = StepLRScheduler(
            optimizer,
            decay_t=decay_steps,
            decay_rate=config.TRAIN.LR_SCHEDULER.DECAY_RATE,
            warmup_lr_init=config.TRAIN.WARMUP_LR,
            warmup_t=warmup_steps,
            t_in_epochs=False,
        )

```

- `optimizer` : 앞서 정의한 optimizer

- `decay_t` : epoch마다 learning rate를 감소할지 결정

- `decay_rate` : decay시 기존의 learning rate에 곱할 값

- `warmup_lr_init` : The initial learning rate during warmup

- `warmup_t` : 초기에 warmup을 적용할 epochs의 수

- `t_in_epochs` : `False`일 때 임의의 epoch `t` 에 대해 return된 learning rate를 None으로 만든다.

  > 보통 False로 set　	



#### scheduler

##### Scheduler

custom scheduler를 구현할때 상속　

```python
import torch
from timm.scheduler.scheduler import Scheduler

class LinearLRScheduler(Scheduler):
    def __init__(self,
                 optimizer: torch.optim.Optimizer,  # type만 명시
                 t_initial: int,                    # type만 명시  initial number of epochs
                 lr_min_rate: float,                # type만 명시   허용하는 최소값 learning rate
                 warmup_t=0,                        # 초기에 warmup을 적용할 epochs의 수
                 warmup_lr_init=0.,                 # initial learning rate during warmup
                 t_in_epochs=True,                  # get_epoch_values, get_update_values 실행 조건
                 noise_range_t=None,
                 noise_pct=0.67,
                 noise_std=1.0,
                 noise_seed=42,
                 initialize=True,
                 ) -> None:
        super().__init__(
            optimizer, param_group_field="lr",
            noise_range_t=noise_range_t, noise_pct=noise_pct, noise_std=noise_std, noise_seed=noise_seed,
            initialize=initialize)

        self.t_initial = t_initial  
        self.lr_min_rate = lr_min_rate
        self.warmup_t = warmup_t
        self.warmup_lr_init = warmup_lr_init
        self.t_in_epochs = t_in_epochs
        if self.warmup_t:       # 초기에 warmup을 적용할 epochs의 값이 0이 아니면 warmup_steps 계산
            self.warmup_steps = [(v - warmup_lr_init) / self.warmup_t for v in self.base_values]
            super().update_groups(self.warmup_lr_init)
        else:
            self.warmup_steps = [1 for _ in self.base_values]

    # learning rate계산
    def _get_lr(self, t):
        if t < self.warmup_t:   # warmup epoch일땐 warmup learning rate 계산
            lrs = [self.warmup_lr_init + t * s for s in self.warmup_steps]
        else:
            t = t - self.warmup_t
            total_t = self.t_initial - self.warmup_t
            lrs = [v - ((v - v * self.lr_min_rate) * (t / total_t)) for v in self.base_values]
        return lrs

    def get_epoch_values(self, epoch: int):
        if self.t_in_epochs:
            return self._get_lr(epoch)
        else:
            return None

    def get_update_values(self, num_updates: int):
        if not self.t_in_epochs:
            return self._get_lr(num_updates)
        else:
            return None
```





### loss

#### LabelSmoothingCrossEntropy

label smoothing을 적용한 Negative Log Likelihood(NLL) Loss 와 같다. 

```python
from timm.loss import LabelSmoothingCrossEntropy

LABEL_SMOOTHING = 0.1	

if LABEL_SMOOTHING > 0.:
    criterion = LabelSmoothingCrossEntropy(smoothing=LABEL_SMOOTHING)

outputs = model(input)	# 약식 표현
    
loss = criterion(outputs, labels)
```

- `LABEL_SMOOTHING` : model이 terget을 incorrect하게 예상했을때 punish값에 곱해지는 값

  0.1정도면 smoothing punish가 이루어짐



#### SoftTargetCrossEntropy

log softmax 기반의 CrossEntropy loss function. mixup을 사용하여 label smoothing을 적용하고  mixing을 조절한다.

```python
from timm.loss import SoftTargetCrossEntropy
from timm.data import Mixup

mixup = True
if mixup:
	mixup_fn = Mixup()	# 약식 표현

if mixup:
	criterion = SoftTargetCrossEntropy()

outputs = model(input)	# 약식 표현
    
loss = criterion(outputs, labels)
```





### utils

#### AverageMeter

Computes and stores the average and current value.



```python
from timm.utils import AverageMeter
```

구조는 아래와 같음

```python
class AverageMeter(object):
    """Computes and stores the average and current value"""
    def __init__(self):
        self.reset()

    def reset(self):
        self.val = 0
        self.avg = 0
        self.sum = 0
        self.count = 0

    def update(self, val, n=1):
        self.val = val
        self.sum += val * n
        self.count += n
        self.avg = self.sum / self.count
```

- store loss

  ```python
  loss_meter = AverageMeter()
  # ...
  loss_meter.update(loss.item(), targets.size(0))
  ```

- store accuracy

  ```python
  acc_meter = AverageMeter()
  # ...
  acc_meter.update()
  ```

- store normalization

  ```python
  norm_meter = AverageMeter()
  # ...
  norm_meter.update(grad_norm)
  ```

- store batch_time

  ```python
  batch_time = AverageMeter()
  # ...
  batch_time.update(time.time() - end)
  ```

- store data_time

  ```python
  data_time = AverageMeter()
  # ...
  data_time.update(time.time() - end)
  ```

  





#### accracy

```python
from timm.utils import accuracy
```

