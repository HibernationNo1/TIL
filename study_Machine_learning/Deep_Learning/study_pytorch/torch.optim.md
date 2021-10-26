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
