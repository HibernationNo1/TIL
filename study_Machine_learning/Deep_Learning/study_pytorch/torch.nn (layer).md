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



### 2d

#### Conv2d

```python
conv = nn.Conv2d(in_channels, out_channels, kernel_size, stride, padding = 0)
```

`in_channels` : input tensor의 channel

`out_channels` : output tensor의 channel

`kernel_size` : 

`stride`

`padding` : default는  0



#### Dropout2d

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

  

  

#### Maxpool2d

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







#### ReflectionPad2d

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



#### InstanceNorm2d

data 개별로 normalization을 진행한다.

batch_norm과 다른 점 : batch_norm은 data의 batch단위로 mean와 std를 구하여 학습의 안정성을 높이지만, instance Norm은 image에 특화된 정규화 과정으로, image를 개별로 정규화 한다.

input으로 4-dimension을 받는다 (batch, w,, h, c)

```python
nn.InstanceNorm2d(image)
```







### 1d

#### AdaptiveAvgPool1d

1D에 대해서 AvgPooling을 계산하는데, output의 shape은 target output size에 반드시 맞춘다.

```python
m = nn.AdaptiveAvgPool1d(8)
input = torch.randn(1, 1, 4)
output = m(input)	# output.shape : (1, 10, 8)
```

> input의 1차원에 대해서만, 앞에서부터 두 값에 대한 평균을 만들거나 또는 값 그대로를 복사해서 shape을 채워넣는다.
>
> 예시
>
> ```python
> m = nn.AdaptiveAvgPool1d(5)
> input = torch.randn(1, 1, 4)
> # tensor([[[ 2.8294, -0.2607, -0.0103, -1.0190]]],
> 
> output = m(input)	# (1, 1, 5)
> # tensor([[[ 2.8294,  1.2843, -0.1355, -0.5146, -1.0190]
> ```
>
> `2.8294` 의 값은 그대로
>
> `1.2843 = (2.8294 + (-0.2607)) /2` (앞의 값과의 평균)
>
> `-0.1355 = (-0.2607 -0.0103) / 2` 	(앞의 값과의 평균)
>
> `-1.0190` 다시 있는 값 그대로 가져옴
>
> 이런 식으로, 앞의 값과의 평균을 내거나, 값을 그대로 가져오는 방법으로 shape을 채운다.





```
tensor([[[ 2.8294, -0.2607, -0.0103, -1.0190],
         [ 0.6776, -0.8817,  0.8641,  0.2123],
         [ 0.8508, -0.0626,  1.3388, -0.1071],
         [-0.0585, -3.4800, -1.3583,  0.3412],
         [-0.5279,  0.5565, -1.9341, -0.3278],
         [ 1.7319, -1.0630,  0.1277, -0.1421],
         [ 0.9807,  0.2094, -0.8594, -0.8776],
         [-0.8487, -0.9491, -0.2112, -0.6472],
         [ 0.3436, -0.8994, -1.5023,  0.0585],
         [-0.7358, -1.7485,  1.2704,  2.6015]]])

tensor([[[ 2.8294,  1.2843, -0.1355, -0.5146, -1.0190],
         [ 0.6776, -0.1021, -0.0088,  0.5382,  0.2123],
         [ 0.8508,  0.3941,  0.6381,  0.6159, -0.1071],
         [-0.0585, -1.7693, -2.4192, -0.5086,  0.3412],
         [-0.5279,  0.0143, -0.6888, -1.1309, -0.3278],
         [ 1.7319,  0.3344, -0.4677, -0.0072, -0.1421],
         [ 0.9807,  0.5951, -0.3250, -0.8685, -0.8776],
         [-0.8487, -0.8989, -0.5801, -0.4292, -0.6472],
         [ 0.3436, -0.2779, -1.2008, -0.7219,  0.0585],
         [-0.7358, -1.2421, -0.2391,  1.9359,  2.6015]]])
         
tensor([[[-2.3097, -0.3076, -0.8748, -0.6077],
         [-2.2063,  0.5650,  1.6227,  0.4511],
         [-1.0441, -0.2179, -1.3662, -0.7428],
         [-0.8159,  0.0362, -0.5216, -0.8314],
         [-1.0316,  0.5792,  0.6597,  0.5364],
         [ 0.2205,  0.0069,  0.6084,  0.0920],
         [ 0.2710, -0.8101, -1.0774, -0.2829],
         [ 0.0602,  0.9704, -0.3990,  0.1972],
         [ 2.4760,  1.0581, -0.9880, -1.5616],
         [ 0.5815, -1.1660,  0.4263,  0.6190]]])
         
         
utput : tensor([[[-2.3097, -1.3086, -0.3076, -0.8748, -0.7413, -0.6077],
         [-2.2063, -0.8207,  0.5650,  1.6227,  1.0369,  0.4511],
         [-1.0441, -0.6310, -0.2179, -1.3662, -1.0545, -0.7428],
         [-0.8159, -0.3899,  0.0362, -0.5216, -0.6765, -0.8314],
         [-1.0316, -0.2262,  0.5792,  0.6597,  0.5981,  0.5364],
         [ 0.2205,  0.1137,  0.0069,  0.6084,  0.3502,  0.0920],
         [ 0.2710, -0.2696, -0.8101, -1.0774, -0.6801, -0.2829],
         [ 0.0602,  0.5153,  0.9704, -0.3990, -0.1009,  0.1972],
         [ 2.4760,  1.7670,  1.0581, -0.9880, -1.2748, -1.5616],
         [ 0.5815, -0.2922, -1.1660,  0.4263,  0.5227,  0.6190]]])
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
	
    loss.backward()
    
```

- `output` : model의 inference값
- `target` : label



#### MSELoss

mean square error 

```python
criterion = nn.MSELoss()
```



#### L1Loss, L2Loss

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

