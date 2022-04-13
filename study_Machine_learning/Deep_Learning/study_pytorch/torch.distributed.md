# torch.distributed

분산 통신 package

```python
import torch
import torch.distributed as dist
```



### syncronize



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



#### get_rank()

```python
dist.get_rank()
```





#### barrier()

```pt
dist.barrier()
```

모든 프로세스가 이 함수에 진입할 때까지 모든 프로세스를 멈춘다.





```python
def syncronize():
    if not dist.is_available():
        return
    if not dist.is_initialized():
        return
    world_size = dist.get_world_size()
    if world_size==1:
        return
    dist.barrier()
    

if cfg.distributed: # 2개 이상의 gpu가 있을 때 True
        torch.cuda.set_device(gpu_idx)
        
        # 기본 분산 processe를 초기화 한다. 
        # 단일 PC에서 단일 GPU사용시 world_size=-1, rank=-1
        dist.init_process_group(backend='nccl', init_method='env://', world_size=-1, rank=-1)
        
        syncronize()
```

> torch를 통해 연구 및 학습을 시작하기 전, process를 사용할 수 있는지 확인
>
> 주로 2개 이상의 GPU가 PC에 있을 때,  사용자가 선택 한 GPU를 사용할 수 있는지 확인하는데 사용한다.



