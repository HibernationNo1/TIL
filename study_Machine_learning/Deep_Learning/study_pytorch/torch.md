# torch

{:toc}





### install

pip를 통해 torch를 따로 install 후 

cudatoolkit의 version에 맞는 pytorch를 설치해야 한다. 그렇지 않으면 

`torch.cuda.is_available()` 이 Flase을 반환한다.

> cudatoolkit, cudnn, ndivia driver 설치 후 pytorch와 cudatoolkit을 명령어를 통해 install해야 한다.
>
> 알맞는 명령어는 [여기](https://pytorch.org/) 에서 찾기.
>
> - requirements.txt 예시
>
>   ```
>   opencv-python
>   Pillow
>   pytz
>   PyYAML
>   timm
>   yacs
>   termcolor
>   
>   torch==1.10.1
>   torchvision==0.11.2
>   torchaudio==0.10.1
>   
>   ### cudatoolkit, torch
>   # conda install pytorch==1.10.1 torchvision==0.11.2 torchaudio==0.10.1 cudatoolkit=10.2 -c pytorch
>   
>   ### apex
>   # $ git clone https://github.com/NVIDIA/apex
>   # $ cd apex
>   # $ python setup.py install --cuda_ext --cpp_ext 
>

- conda

  ```
  $ conda install pytorch==1.8.0 torchvision==0.9.0 torchaudio==0.8.0 cudatoolkit=11.2 -c pytorch -c conda-forge
  ```

  > 제거는 `pip uninstall pytorch`
  >
  > cudatoolkit version은 `nvcc -V` 명령어 사용
  >
  > `conda-forge` 는 cudatoolkit이 11.3 이상 version일때만

  - ex

    ```
    $ conda install pytorch==1.10.1 torchvision==0.11.2 torchaudio==0.10.1 cudatoolkit=11.5 -c pytorch conda-forge
    ```

    > pytorch version명시 안하면 cudatoolkit의 version에 알맞게 알아서 설치
    >
    > cudatookit 11.5를 사용할 때 위 명령어 사용
    >
    > - pytorch와 torchvision이 이미 install되어 있다면 아래 명령어만 실행
    >
    >   ```
    >   $ conda install pytorch torchvision torchaudio cudatoolkit=11.5 -c pytorch
    >   ```
    >
    >   `torch.cuda.is_available()` True반환 확인
  
  
  
- conda 가 아닐 때

  ```
  pip install torch==1.7.1+cu110 torchvision==0.8.2+cu110 -f https://download.pytorch.org/whl/torch_stable.html
  ```





### cuda

##### is_available

CUDA를 통해  GPU를 사용할 수 있는지 여부를 알 수 있다.

```
is_cuda = torch.cuda.is_available()
```

> CUDA를 통해  GPU를 사용할 수 있으면 `True`반환, 아니면 `False`반환



##### device_count

모든 gpu를 사용할 때(gpu 개수 확인)

```python
num_gpus = torch.cuda.device_count()
init_process_group(backend='nccl', init_method='env://')
```

- `backend` 

  > - Use the NCCL backend for distributed **GPU** training
  > - Use the Gloo backend for distributed **CPU** training.





##### set_device

여러개의 GPU를 사용할 때, 몇 번째 GPU를 사용할지 결정

```python
torch.cuda.set_device(gpu_idx)
```

> `gpu_idx` : gpu의 index (0~)



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







### tensor



#### permute()

tensor의 size위치를 바꾼다.

```python
x = torch.randn(2, 3, 5)
x.size()							# 	torch.Size([2, 3, 5])
torch.permute(x, (2, 0, 1)).size()	# 	torch.Size([5, 2, 3])
```

> size[2] 가 size[0] 으로,
>
> size[0]이 size[1]로,
>
> size[1]이 size[2]로







#### contiguous()

연속적인 메모리 tensor를 return한다.

```python
a = torch.randn(2, 3, 4)	# a.size() [2, 3, 4]
a.stride()	# (12, 4, 1) 
# 0차원에서 1차원으로 넘어가려면 12개의 원소를 지나야 하고
# 1차원에서 2차원으로 넘어가려면 4개의 원소를 지나야 한다.

a = a.transpose(0, 1)		# a.size() [3, 2, 4]
b = torch.randn(3, 2, 4)	# a와 같은 size의 tensor를 만든다

# a.stride() = (4, 12, 1)
# b.stride() = (8, 4, 1)	
## a, b tensor의 shape은 같지만 stride가 다르다.
```

> a.stride()가 변화한 이유 : 텐서 a의 형태가 변화될때 실제로 해당 원소에 접근할때는(메모리에서는 원소들의) 위치가 변화되지 않았고 접근 인덱스만 변화되었기 때문
>
> (만약 텐서의 형태가 바뀔때마다 메모리에 있는 그래도 배치하려면 재 할당을 해주어야 하는데 이러한 연산이 잦으면 오히려 성능을 떨어뜨리는 원인이 될수있다.)
>
> 이 때 a는 비 연속적인 tensor가 되는데, `contiguous()` 메서드는 다음과 같이 이러한 a와 같은 비연속적인 텐서를 연속적으로 만들어주는 역할을 한다.
>
> ```python
> a = a.contiguous()
> a.stride()		# (8, 4, 1)
> ```
>



#### view()

numpy 에서의 reshape과 같은 동작을 한다.





#### masked_fill()

특정 조건이 맞는 element에 원하는 값을 할당한다.

```python
a = torch.randn(1000, 100, 100)
a.masked_fill(a != 0, float(-100.0)).masked_fill(a == 0, float(0.0))
```

> 0이 아닌 경우 -100을, 0인 경우 0.0의 값을 할당





#### shape

tensor의 shape을 return



#### requires_grad

tensor의 모든 연산을 추적하는지에 대한 여부(bool)

```python
model = Model()

for name, param in model.named_parameters():
    print(f"Parameter Name: {name},     shape: {param.shape}         param.requires_grad : {param.requires_grad}")
```

> 만일 `param.requires_grad` 가 `False`이면 frozen weights 인 것.



#### numel()

tensor의 elements개수를 return

```python
for param in model.parameters():
    print(f" layer의 parameter 개수 : {param.numel()}")
```

```python
n_parameters = sum(p.numel() for p in model.parameters() if p.requires_grad)
print(f"총 parameter개수 : {n_parameters}")
```

