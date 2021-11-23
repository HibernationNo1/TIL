# torch

### install

```
$ conda install pytorch torchvision torchaudio cudatoolkit=11.1 -c pytorch -c conda-forge
```





### cuda

##### is_available

CUDA를 통해  GPU를 사용할 수 있는지 여부를 알 수 있다.

```
is_cuda = torch.cuda.is_available()
```

> CUDA를 통해  GPU를 사용할 수 있으면 `True`반환, 아니면 `False`반환



### torch

#### Tensor()

`tf.constant` 와 같다.

```python
torch.Tensor([1, 2])
```

> `torch.Tensor` 는 CPU memory를,
>
> `torch.cuda.Tensor` 는 GPU memory를 사용한다.

torch에서는 Tensor 선언시 사용할 수 있는 data type이 여러개가 있다. 

- 32-bit floating Point : `FloatTensor`  주로 계산을 위한 data에 사용된다.

- 64-bit floating Point : `DoubleTensor`

- 16-bit floating Point : `HalfTensor`

- 8-bit integer : `ByteTensor(unsigned)`, `CharTensor(signed)`  boolean을 사용시

- 16-bit integer : `ShortTensor`

- 32-bit integer : `IntTensor`

- 64-bit integer : `LongTensor`   int형 숫자를 사용할 때 사용된다.

>  `FloatTensor` 에서 `LongTensor`  로 바꿀 때
>
> ```python
> x = torch.FloatTensor([1.0, 2.0])  # FloatTensor
> x.type(torch.LongTensor)		# `LongTensor`  
> ```
>
> `type` 을 사용하자.



**requires_grad**

torch.Tensor의 parameter중 하나인 requires_grad는 autograd에 모든 opration을 tracking해야 한다고 알려준다.

>  tf.gradientTape이라고 생각하면 됨

```python
a = torch.Tensor([2., 3.], requires_grad = True)
```





#### randint()

범위 내 integer element tensor를 생성한다.

```python
torch.randint(low = 0, high, size)
```

- `low` : inclusive한 최소값
- `high` : exclusive한 최대값
- `size`



#### device()

CUDA사용 여부를 결정

```python
is_cuda = torch.cuda.is_available()
device = torch.device('cuda' if is_cuda else 'cpu')
```

is_cuda가 `True` 이면 device에 `'cuda'`가, 

is_cuda가 `False` 이면 device에 `'cpu'`가, assign된다.





#### flatten()

tensor의 shape을 reshape한다.

주로 high dimension을 1차원의 vector로 변환할때 사용한다.

> `tensor.reshape()`과 같다. 

```
torch.flatten(input, start_dim, end_dim)
```

- `input` : tensor

- `start_dim` : 줄이고자 하는 dimension을 결정. start_dim = 1이면 2차원으로 flatten

  > default = 0
  >
  > ```python
  > >>> t = torch.tensor([[[1, 2],
  > ...                    [3, 4]],
  > ...                   [[5, 6],
  > ...                    [7, 8]]])
  > >>> torch.flatten(t)
  > tensor([1, 2, 3, 4, 5, 6, 7, 8])
  > >>> torch.flatten(t, start_dim=1)
  > tensor([[1, 2, 3, 4],
  >         [5, 6, 7, 8]])
  > ```

-  `end_dim` : 

  > default = -1



#### no_grad()

model을 evaluation하는 단계에서 model의 parameter를 updata하지 않기 위해 사용하는 method

```python
with torch.np_grad():	# np_grad의 scope안에서 test 진행
    for ...
```



#### set_grad_enabled()

model을 training하는 단계에서 model의 parameter를 updata함을 결정하는 method

주로 training과정에서 validation을 진행할 때 사용

```python
for phase in ['train', 'val']:
    if phase == 'train':
        model.train()
    else:
        model.eval()
            
...

with torch.set_grad_enabled(phase == 'train'):	# set_grad_enabled scope안에서 test 진행
```

- parameter : boolean으로, 

  `True`인 경우 parameters updata

  `False`인 경우엔 updata안함



#### save()

```python
torch.save(model, path)
```

- `model` : 저장하고자 하는 model

  > parameter만 저장하고자 한다면 
  >
  > `model.parameters()` 를 사용

- `path` : model을 저장하고자 하는 path

  > 저장시 file형식까지 명시해야함



#### load()

저장된 model의 base line을 load한다.

```python
model = torch.load(path)
```

- `path` : model의 path







#### math

##### torch.max()

```python
torch.max(input, dim)
```

- `input` : input tensor
- `dim` : max를 적용할 diemension





##### torch.sum()

```python
torch.sum(input, dim)
```

- `input` : input tensor

- `dim` : max를 적용할 diemension

- `boolean` : `input`, `dim` 대신 boolean을 return하는 조건식이 대신 들어가면

  True일 경우 1을 반환

