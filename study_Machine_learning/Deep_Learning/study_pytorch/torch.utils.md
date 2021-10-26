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
from torch.utils.data import DataLoader

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





#### Dataset

Dataset을 상속받아 subclassing으로 custom dataset class를 만든다.

```python
from torch.utils.data import Dataset

class CustomImageDataset(Dataset):
    def __init__()
    
    def __getitem__()
    
    def __len__()
```

`def __init__()`

`def __getitem__()`

`def __len__()`

위 세 개의 함수는 반드시 정의되어있어야 한다.



### 
