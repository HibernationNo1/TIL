# torch.nn (layer)



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
>  print(f"Parameter Name: {n}, shape {papram.shape}")
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
> ````



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



### nn.Identity()

input과 동일한 tensor를 return한다.

> 사용 예시

```python
import torch
import torch.nn as nn

from timm.models.layers import DropPath

drop_path = 0.3
self.drop_path = DropPath(drop_path) if drop_path > 0. else nn.Identity()
```

> drop_path = 0이면 drop_path를 적용하지 않는 그냥 layer