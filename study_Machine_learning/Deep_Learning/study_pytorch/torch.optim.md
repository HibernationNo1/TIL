# torch.optim

weight inference에 필요한 optimizer algorithm을 포함한 module

```python
import torch
import torch.optim
```



### optim.SGD

```
optimizer = optim.SGD(model.parameters(), lr = learning_rate, momentum=0.9)
```

- `model.parameters()`
- `lr`
- `momentum`



### optim.Adam

```python
optimizer = optim.Adam(model.parameters(), lr = learning_rate)
```

- `model.parameters()` 를 통해 parameters를 받아와 optimize를 진행
- `lr`



#### zero_grad()

```python
optimizer = optim.Adam(model.parameters(), lr = learning_rate)

for ...
	optimizer.zero_grad()
```

for문 안에서, 1 step을 시작하기 전, 이전 반복 시행에서 저장된 optimizer의 gradient를 초기화 한다.



#### step()

```python
optimizer.step()
```

loss function에 의해 계산된 gradient를 통해 model의 weight를 updata한다.



#### param_groups

training과정에서의 parameter를 저장하고 있는 dict

```python
optimizer.param_groups
```

```python
# key정보
param_groups = {'ir', 'momentum', 'dampening', 'weight_decay', 'nesterov', 'params'}
```



#### e.g.

```python
from torch import optim as optim
import sys


_C.TRAIN.OPTIMIZER = CN()
_C.TRAIN.OPTIMIZER.NAME = 'adamw'
# Optimizer Epsilon
_C.TRAIN.OPTIMIZER.EPS = 1e-8
# Optimizer Betas
_C.TRAIN.OPTIMIZER.BETAS = (0.9, 0.999)
# SGD momentum
_C.TRAIN.OPTIMIZER.MOMENTUM = 0.9


def build_optimizer(config, model):
    """
    Build optimizer, set weight decay of normalization to 0 by default.
    """
    
    skip = {}
    skip_keywords = {}
    if hasattr(model, 'no_weight_decay'):
        skip = model.no_weight_decay()    
        # @torch.jit.ignore
        # def no_weight_decay(self):
        # return {'absolute_pos_embed'}    
        
    if hasattr(model, 'no_weight_decay_keywords'):
        skip_keywords = model.no_weight_decay_keywords()
        # @torch.jit.ignore
        # def no_weight_decay_keywords(self):
        # return {'relative_position_bias_table'}
    
    # parameters[0].keys() : 'params' == list      parameters[1].keys() : 'params' == list, 'weight_decay' == float
    parameters = set_weight_decay(model, skip, skip_keywords)

    opt_lower = config.TRAIN.OPTIMIZER.NAME.lower()  # lowercase
    
    optimizer = None
    if opt_lower == 'sgd':
        optimizer = optim.SGD(parameters, momentum=config.TRAIN.OPTIMIZER.MOMENTUM, nesterov=True,
                              lr=config.TRAIN.BASE_LR, weight_decay=config.TRAIN.WEIGHT_DECAY)
    elif opt_lower == 'adamw':
        optimizer = optim.AdamW(parameters, eps=config.TRAIN.OPTIMIZER.EPS, betas=config.TRAIN.OPTIMIZER.BETAS,
                                lr=config.TRAIN.BASE_LR, weight_decay=config.TRAIN.WEIGHT_DECAY)

    return optimizer


def set_weight_decay(model, skip_list=(), skip_keywords=()):
    has_decay = []
    no_decay = []

    for name, param in model.named_parameters():
        if not param.requires_grad:
            continue  # frozen weights
        if len(param.shape) == 1 or name.endswith(".bias") or (name in skip_list) or \
                check_keywords_in_name(name, skip_keywords):
            no_decay.append(param)
            # bias이거나 skip대상이면 weight decay적용 안함
            # print(f"{name}      has no weight decay")
        else:
            has_decay.append(param)
            
    return [{'params': has_decay},
            {'params': no_decay, 'weight_decay': 0.}]


def check_keywords_in_name(name, keywords=()):
    isin = False
    for keyword in keywords:
        if keyword in name:
            isin = True
    return isin


if __name__ == '__main__':

	optimizer = build_optimizer(config, model)
```







### lr_scheduler

learning rate를 관리하는 class

```python
from forch.optim import lr_scheduler
```



#### StepLR

Epoch에 따라 Learning Rate를 변경하는 역할을 한다.

```python
scheduler = lr_scheduler.StepLR(oprimizer, step_size, gamma)
```

- `oprimizer` : oprimizer instance
- `step_size` : int, 몇 Epoch마다 gamma를 lr에 곱할지를 결정
- `gamma` : float, 몇의 값을 lr에 곱할지를 결정



##### step()

StepLR 내부의 step에 1을 더하는 과정을 수행. `step_size`마다 gamma가 곱해진다.

```python
scheduler.step()
```



#### LambdaLR

미리 정의한 함수를 사용해 Learning Rate를 변경하는 역할을 한다.

```python
scheduler =lr_scheduler.LambdaLR(oprimizer, lr_lambda)
```

- `oprimizer` : oprimizer instance
- `lr_lambda` : scheduling할 함수
