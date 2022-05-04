# torch.distributed

분산 통신 package

```python
import torch
import torch.distributed as dist
```



##### synchronize

**torch.cuda.is_available()** 가 True임을 확인 후 설정할것

```python
assert torch.cuda.is_available(), "is_available is False!"
```

> `torch.cuda.is_available()` 가 False이면 아래 함수 다 안됨.





distributed를 사용하기 위해선 실행 명령어를 달리 사용해야 한다.

```
$ python -m torch.distributed.launch --nproc_per_node=1 main.py 
```

> `--nproc_per_node` : 각 node에서 사용 가능한 GPU의 수
>
> single GPU를 사용한다면 1 할당

위 명령어는 곧 사라질 예정 앞으로는 `torchrun`을 사용한다. (pytorch 1.10이상 version에서 사용)

```
$ torchrun main.py
```

> https://pytorch.org/docs/stable/elastic/run.html



`python -m torch.distributed.launch` 또는 `torchrun` 를 사용하게 되면 환경변수에 `RANK(GPU에 명명되는 이름)`와 `WORLD_SIZE(GPU개수)` 가 할당된다.

이를 이용해 `torch.distributed.init_process_group`의 parameter `rank`, `world_size` 를 결정할 수 있다.

**초기 synchronize**

```python
if __name__ == '__main__':
# set gpu    
    if 'RANK' in os.environ and 'WORLD_SIZE' in os.environ:
        rank = int(os.environ["RANK"])
        world_size = int(os.environ['WORLD_SIZE'])
        print(f"RANK and WORLD_SIZE in environ: {rank}/{world_size}")
    else:
        rank = -1
        world_size = -1
    torch.cuda.set_device(rank)
    
    if os.name == 'nt':
        torch.distributed.init_process_group(backend="gloo", init_method='env://', world_size=world_size, rank=rank)
    elif os.name == 'posix':
        torch.distributed.init_process_group(backend="nccl", init_method='env://', world_size=world_size, rank=rank)
    torch.distributed.barrier()
```

> TODO : 한 대의 PC에 여러대의 GPU를 설치했을 시의 코드 추가하기



---



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



#### init_process_group()

분산 환경의 prcess gruop을 초기화한다. 

```python
if os.name == 'nt':
    torch.distributed.init_process_group(backend="gloo", init_method='env://', world_size=world_size, rank=rank)
elif os.name == 'posix':
    torch.distributed.init_process_group(backend="nccl", init_method='env://', world_size=world_size, rank=rank)
```

> windows 에서는 `backend="gloo"`
>
> linux에서는 `backend="nccl"`
>
> - 특정 cuda toolkit에서만 정상 작동
>
>   ```
>   $ conda install pytorch==1.10.1 torchvision==0.11.2 cudatoolkit=10.2 -c pytorch
>   ```
>
>   > 그 외 version에서는 `RuntimeError: No rendezvous handler for env://` 라는 error가 뜸



#### get_world_size()

```
dist.get_world_size()
```

현재 process 그룹의 process 수를 return (GPU개수 return)

>`init_process_group()` 이 error없이 invoke된 수 정상 동작



#### get_rank()

```python
dist.get_rank()
```

GPU에 명명되는 이름(숫자, 0부터 ~)를 return

> `init_process_group()` 이 error없이 invoke된 수 정상 동작





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
        dist.init_process_group(backend='gloo', init_method='env://', world_size=-1, rank=-1)
        
        syncronize()
```

> torch를 통해 연구 및 학습을 시작하기 전, process를 사용할 수 있는지 확인
>
> 주로 2개 이상의 GPU가 PC에 있을 때,  사용자가 선택 한 GPU를 사용할 수 있는지 확인하는데 사용한다.

