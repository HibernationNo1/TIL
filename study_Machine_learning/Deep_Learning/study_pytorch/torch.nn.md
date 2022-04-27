# torch.nn

deep learning에 기본 구성 요소를 포함한 module

```python
import torch
import torch.nn as nn
```



># torch.nn.functional
>
>deep learning에 자주 사용되는 function이 포함된 module
>
>```python
>import torch
>import torch.nn.functional as F
>```
>
>
>
>**torch.nn.functional vs torch.nn**
>
>두 방식 다 같은 결과를 제공해주며, 편한 것으로 선택해서 개발하면 됨
>
>torch.nn.functional은 function이고, torch.nn은 class이다.



### Module

model을 구현할 때 inherited해서 sub-classing하는데 사용된다. 

> tensorflow.keras.models.Model과 비슷한 역할

```python
class Model(nn.Module) : 
    # nn.Module을 상속받는 class를 정의
    def __init__(self):
        super(CNN, self).__init__()
        # nn.Module class의 attribute를 inherit하고 initialize 
    ...
```



##### self.register_buffer()

`nn.Module`을 상속받은 model에서 선언할 수 있는 파라미터

일반적으로 model의 매개 변수로 간주되지 않는 버퍼를 등록하는데 사용된다.

네트워크를 구성함에 있어서 네트워크를 end2end로 학습시키고 싶은데 중간에 업데이트를 하지않는 일반 layer를 넣고 싶을 때 사용할 수 있다.

- register_buffer 로 layer를 등록할 시 
  - optimizer가 업데이트하지 않는다.
  -  값은 존재한다(하나의 layer로써 작용한다고 보면 된다.)
  -  state_dict()로 확인이 가능하다.
  -  GPU연산이 가능하다.

```python
class MyModel(nn.Module):
    def __init__(self):
        super(MyModel, self).__init__()
        self.my_tensor = torch.randn(1)
        self.register_buffer('my_buffer', torch.randn(1))
```







#### to()

model을 CUDA에 최적화된 model로 convert한다.

```python
torch.cuda.is_available()
device = torch.device('cuda' if is_cuda else 'cpu')

Model.to(device)
```



##### output

```python
is_cuda = torch.cuda.is_available()
device = torch.device('cuda' if is_cuda else 'cpu')

model = model.to(divice)

print(model) # summury
output = model(data)		# data는 학습을 위한 dataset
```





#### parameters()

model의 parameters를 iterator로 return한다.

주로 `torch.optim`의 첫 번째 parameter로 assign한다.

```python
for param in model.parameters():
            param.requires_grad = False
```



##### requires_grad

parameters에 대해서 freeze할지 말지에 대한 여부를 담고 있다. (boolean)

```python
param.requires_grad = False  # freeze
param.requires_grad = True 	# 학습시 paramaters updata
```



#### named_parameters()

model에 등록된 parameter를 iterator로 return

```python
model = Model()

for name, param in model.named_parameters():
    print(f"Parameter Name: {name}, shape {papram.shape}")
```





#### train()

```python
model.train()
```

model instance를 train mode로 실행할 것을 명시한다.



#### eval()

```python
model.eval()
```

model instance를 evaluation mode로 실행할 것을 명시한다.

evaluation mode에서는 Dropout과 Batch-Normalization도 evaluation mode로 전환된다.



#### state_dict()

model의 각 계층을 매개변수 tensor로 mapping되는 python dict 객체

즉, 학습 가능한 parameter가 담겨있는 dict.  (parameter만 담겨있다.)

```python
parameter = model.state_dict()
```

> model안에는 optimizer, epoch, score등의 모든 state가 있지만, model.state_dict()는 딱 parameters만 return한다.
>
> ```python
> import copy
> parameter = copy.deepcopy(model.state_dict())
> ```
>
> 보통 copy.deepcopy를 사용해서 복사한다.



#### load_state_dict()

model의 parameters를 받아온다.

```python
model.load_state_dict(parameter)
```

> parameter 는 `model.state_dict()`로 얻어진 parameters dicts



#### children()

model의 자식 module을 iterable한 instance로 return

instance는 model의 layer정보를 담고 있다.

이를 이용해서 layer를 freeze할 수 있다.

```python
ct = 0
for child in resnet.children():
    ct +=1
    if ct < 6:
        for param in child.parameters():
            param.requires_grad = False
```

> resnet의 layer중 input에 가까운 layer부터 1~5까지 Freeze (fine - tuning)





#### cuda()

cuda toolkit을 적용

```python
model = build_model(config) # nn.Module을 상속받아 만든 model
model.cuda()	
```





#### str(model)

model의 각 parameters를 출력한다.

```python
logger = create_logger(output_dir=OUTPUT, dist_rank=dist_rank, name=f"{NAME}")

logger.info(str(model))
```





### Parameter()

parameter값 만을 return (layer가 아님)

```python
tmp = nn.Parameter(torch.randn([3, 3, 3]))
```



