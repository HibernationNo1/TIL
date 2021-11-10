# torch.distributed

분산 통신 package

```python
import torch
import torch.distributed as dist
```







#### is_available()

```python
dist.is_available()
```

배포 된 패키지를 확인하고, 해당 패키지를 사용할 수 있으면 `True`를 반환



#### is_initialized()

```python
dist.is_initialized()
```

기본 process 그룹이 초기화되었으면 `True`를 반환





#### get_world_size()

```
dist.get_world_size()
```

현재 process 그룹의 process 수를 return