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

for n, param in model.named_parameters():
    print(f"Parameter Name: {n}, shape {papram.shape}")
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



### ModuleList

여러 layer를 list형태로 담을 때 사용. (일반 python list의 속성들을 그대로 가지고 있다.)

```python
import torch
import torch.nn as nn

class TMP(nn.Module):
    def __init__(self, fc_input_size, fc_hidden_sizes, num_classes):
        super(TMP, self).__init__()
        
        fcs = [nn.Sequential(
                nn.Linear(fc_input_size, fc_hidden_size),
                nn.ReLU(),
        		nn.Linear(fc_hidden_size, num_classes)
        for fc_hidden_size in fc_hidden_sizes)]
        
        self.layers1 = nn.ModuleList(fcs)
        self.layers2 = fcs
```

> `self.layers2` : 일반 python list
>
> `self.layers1` : nn.ModuleList 객체
>
> 차이점 : nn.ModuleList 객체인 `self.layers1` 만 model parameter에 등록이 되기 때문에 추후 `model.parameters()` 로 model의 parameter를 전달할 때 list내부의 element를 사용할 수 있다.
>
> (반드시 `nn.ModuleList()` 를 사용해야 함)
>
> ```python
> # 확인방법
> model = TMP(fc_input_size = 4, fc_hidden_sizes(8, 8), num_calsses = 3)
> 
> for n, param in model.named_parameters():
>     print(f"Parameter Name: {n}, shape {papram.shape}")
> ```
>
> 



### Conv2d

```python
conv = nn.Conv2d(in_channels, out_channels, kernel_size, stride, padding = 0)
```

`in_channels` : input tensor의 channel

`out_channels` : output tensor의 channel

`kernel_size` : 

`stride`

`padding` : default는  0



### Dropout2d

```python
droup = nn.Dropout2d(p)
```

`p` : drop out할 node의 ratio

> #### F.dropout
>
> ````
> x = F.dropout(x, p, training = self.training)
> ```
>
> - `x` : input data
>
> - `p` : drop out할 node의 rate
>
> - `training = self.training` : training mode일 때와 evaluation mode일 때 각각 다르게 적용되기 위해 존재.
>
>   >  self.training이라는 variable은 model.train() 또는 model.eval() 함수를 호출하여 모드를 바꿀때마다, self.training이 True 또는 False로 바뀐다.



- **Dropout**

  ```python
  drop_rate = 0.0
  self.pos_drop = nn.Dropout(p=drop_rate)
  ```

  



### Linear

fully connected layer을 구현

```python
fc = nn.Linear(in_features, out_features, bias = True)
```

- `in_features`  : flatten형태의 input tensor

- `out_features` : flatten형태의 output tensor

- `bias` : `False`일 경우 bias추가 안함



### LayerNorm

input의 batch size에 대해 normelize를 적용한다.

```python
# Image Example  
Batch, C, H, W = 20, 5, 10, 10
input = torch.randn(Batch, C, H, W)		# input.size() : [20, 5, 10, 10]
layer_norm = nn.LayerNorm([C, H, W])	# [C, H, W]에만 normalize적용하는 layer instnace
output = layer_norm(input)
```

![](https://pytorch.org/docs/stable/_images/layer_norm.jpg)



### Maxpool2d

Maxpooling을 수행하는 layer(단순 연산이므로 학습할 weight가 없음)

```python
layer = nn.Maxpooling(kernel_size, stride)
```

- `kernel_size`

- `stride`

> #### F.max_pool2d
>
> Max pooling을 적용
>
> ```python
> F.max_pool2d(input, kernel_size, stride = 1)
> ```
>
> - `input`
> - `kernel_size` :
> - `stride`



### ReLU

activation function적용

```python
layer = nn.ReLU()
x = layer(x)
```

>#### F.relu
>
>```python
>x = F.relu(x)
>```



### Softmax

softmax function을 적용

> 단순 연산이므로 학습할 weight가 없음

```python
layer = nn.Softmax(dim = )
```

- `dim` : convert할 dimension을 결정 

> #### F.log_softmax
>
> ```python
> output = F.log_softmax(input, dim = 1)
> ```
>
> - `dim` : convert할 dimension을 결정 
>





### ReflectionPad2d

padding을 적용한다. 단, zero padding과는 다르게, input tensor에 대해 각 element를 대각선 방향으로 반전배치하여 padding을 한다. 

주로 GAN에서 사용된다.

```python
nn.ReflectionPad2d(padding)
```

- `padding` 

  - int인 단일 값일 때

    해당 숫자 만큼의 겹으로 pad 

  - 4개의 element인 tuple일 때

    (left, right, top, bottom) 순으로 pad의 겹을 결정한다.



### InstanceNorm2d

data 개별로 normalization을 진행한다.

batch_norm과 다른 점 : batch_norm은 data의 batch단위로 mean와 std를 구하여 학습의 안정성을 높이지만, instance Norm은 image에 특화된 정규화 과정으로, image를 개별로 정규화 한다.

input으로 4-dimension을 받는다 (batch, w,, h, c)

```python
nn.InstanceNorm2d(image)
```





### Sequetial

여러 함수를 argument로 받고, 순서대로 호출한다.

주로 class안에서 여러 layer를 한 번에 적어넣을때 사용한다.

```python
class ResidualBlock(nn.Module):
    def __init__(self, in_features):
        supter(ResidualBlock, self).__init__()
        self.block = nn.Sequential(
        nn.ReflectionPad2d(1),
        nn.Conv2d(in_features, infeatures, 3),
            ...
        )
     def forward(slef, x):
        return self.block(x)
```



### Loss

#### CrossEntropyLoss

```python
criterion = nn.CrossEntropyLoss()
for ...
	output = model(data)
    loss = criterion(output, target)
# 또는 
```

- `output` : model의 inference값
- `target` : label



### MSELoss

mean square error 

```python
criterion = nn.MSELoss()
```



### L1Loss, L2Loss

```python
criterion = nn.L1Loss()
criterion = nn.L2Loss()
```







##### loss.backward()

```python
criterion = nn.CrossEntropyLoss()

for ...
	output = model(data)
	loss = criterion(output, target)
    loss.backward()
```

loss function을 통해 gradient를 계산한다.



##### loss.item()

```
for ...
	output = model(data)
	loss = criterion(output, target)
    loss.item()
```



계산된 loss값을 반환





### Parameter()

parameter값 만을 return (layer가 아님)

```python
tmp = nn.Parameter(torch.randn([3, 3, 3]))
```

