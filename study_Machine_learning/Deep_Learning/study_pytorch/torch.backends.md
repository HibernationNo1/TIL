#  torch.backends





### cudnn

```python
import torch
import torch.backends.cudnn as cudnn
```



#### cudnn.version()

cuDNN의 version을 return

```python
version = cudnn.version()
```



#### cudnn.is_available()

cuDNN 사용 가능 여부를 확인 (가능시 True, 아닐시 False)

```python
available_cudnn = cudnn.is_available()
```



#### cudnn.enabled

cuDNN 사용 여부를 제어 하는 `bool` 

```python
cudnn.enabled = True
```



#### cudnn.benchmark

True 인 경우 cuDNN이 다중 회선 알고리즘을 벤치마킹하고 가장 빠른 알고리즘을 선택하도록 하는 `bool`

```python
cudnn.benchmark = True
```

