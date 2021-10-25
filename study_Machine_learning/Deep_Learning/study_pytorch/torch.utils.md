# torch.utils

```py
import torch
import torch.utils
```



### utils.data

```python
import torch.utils.data
```



#### DataLoader

batch size를 통해 mini batch를 구성하는 함수

```python
import torch

train_loader = torch.utils.data.DataLoader(dataset = train_data, batch_size = batch_size, shuffle = True)
```

- dataset : mini batch로 구성할 input dataset

- batch_size :

- shuffle : dataset의 순서를 random으로 섞어서 배치를 구성할지 여부를 결정

  > `True` or `False`

> ```
> # mnist기준
> train_loader[0].shape() = [batch_size, 1, 28, 28]
> ```

- `torch.utils.data.DataLoader` 의 return값은 [`data`, `target`]이고,

  `data`는 mini batch로 구성된 input data

  `target`은 mini batch로 구성된 label이다.







##### 

