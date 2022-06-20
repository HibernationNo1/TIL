# mmdet



## utils

#### collect_env()

running environments의 information을 collect하여 반환한다.

```python
from mmdet.utils import collect_env

env_info_dict = collect_env()
env_info = '\n'.join([(f'{k}: {v}') for k, v in env_info_dict.items()])

print(env_info)
```

```
        git config --global --add safe.directory D:/Noh_TaeUk/swintransform/Swin-Transformer-Object-Detection
sys.platform: win32
Python: 3.7.13 (default, Mar 28 2022, 08:03:21) [MSC v.1916 64 bit (AMD64)]
CUDA available: True
GPU 0: GeForce GTX 1660 SUPER
CUDA_HOME: C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v10.2
NVCC: Cuda compilation tools, release 10.2, V10.2.8
MSVC: Microsoft (R) C/C++ 최적화 컴파일러 버전 19.29.30145(x64)
GCC: n/a
PyTorch: 1.10.0
PyTorch compiling details: PyTorch built with:
  - C++ Version: 199711
  - MSVC 192829337
  - Intel(R) Math Kernel Library Version 2020.0.2 Product Build 20200624 for Intel(R) 64 architecture applications
  - Intel(R) MKL-DNN v2.2.3 (Git Hash 7336ca9f055cf1bfa13efb658fe15dc9b41f0740)
  - OpenMP 2019
  - LAPACK is enabled (usually provided by MKL)
  - CPU capability usage: AVX2
  - CUDA Runtime 10.2
  - NVCC architecture flags: -gencode;arch=compute_37,code=sm_37;-gencode;arch=compute_50,code=sm_50;-gencode;arch=compute_60,code=sm_60;-gencode;arch=compute_61,code=sm_61;-gencode;arch=compute_70,code=sm_70;-gencode;arch=compute_75,code=sm_75;-gencode;arch=compute_37,code=compute_37
  - CuDNN 7.6.5
  - Magma 2.5.4
  - Build settings: BLAS_INFO=mkl, BUILD_TYPE=Release, CUDA_VERSION=10.2, CUDNN_VERSION=7.6.5, CXX_COMPILER=C:/cb/pytorch_1000000000000/work/tmp_bin/sccache-cl.exe, CXX_FLAGS=/DWIN32 /D_WINDOWS /GR /EHsc /w /bigobj -DUSE_PTHREADPOOL -openmp:experimental -IC:/cb/pytorch_1000000000000/work/mkl/include -DNDEBUG -DUSE_KINETO -DLIBKINETO_NOCUPTI -DUSE_FBGEMM -DUSE_XNNPACK -DSYMBOLICATE_MOBILE_DEBUG_HANDLE -DEDGE_PROFILER_USE_KINETO, LAPACK_INFO=mkl, PERF_WITH_AVX=1, PERF_WITH_AVX2=1, PERF_WITH_AVX512=1, TORCH_VERSION=1.10.0, USE_CUDA=ON, USE_CUDNN=ON, USE_EXCEPTION_PTR=1, USE_GFLAGS=OFF, USE_GLOG=OFF, USE_MKL=ON, USE_MKLDNN=ON, USE_MPI=OFF, USE_NCCL=OFF, USE_NNPACK=OFF, USE_OPENMP=ON,

TorchVision: 0.11.1
OpenCV: 4.5.5
MMCV: 1.5.0
MMCV Compiler: MSVC 192930137
MMCV CUDA Compiler: 10.2
MMDetection: 2.24.1+
```

위 정보를`get_root_logger()`를 통해 logger를 생성하여 log file에 담는다.





#### get_root_logger()

logger생성 함수

```python
from mmdet.utils import get_root_logger

timestamp = time.strftime('%Y%m%d_%H%M%S', time.localtime())
log_file = osp.join('work_dir', f'{timestamp}.log')
# 현재 년월일-시간.log라는 이름의 log file 생성

logger = get_root_logger(log_file=log_file, log_level=log_level)
```

- `log_file` : log를 저장할 file path (str, optional)
- `log_level` : logger의 level을 명시. (int, oprional, default : 'INFO')

- `logger` : 생성된 logger. 이 logger을 통해 `.info`를 호출해서 해당 log file에 log information을 저장할 수 있다.



##### info()

인자로 받은 값을 log file에 저장한다.

```python
from mmdet.utils import collect_env, get_root_logger

timestamp = time.strftime('%Y%m%d_%H%M%S', time.localtime())
log_file = osp.join(cfg.work_dir, f'{timestamp}.log')
logger = get_root_logger(log_file=log_file, log_level=cfg.log_level)

env_info_dict = collect_env()
env_info = '\n'.join([(f'{k}: {v}') for k, v in env_info_dict.items()])
dash_line = '-' * 60 + '\n'
logger.info('Environment info:\n' + dash_line + env_info + '\n' +
            dash_line)
```



#### get_device()

Returns an available device, cpu, cuda or mlu.

```python
from mmdet.utils import get_device

device = get_device()
```

> `torch.cuda.is_available() = True` 이면 return `cuda`
>
> `torch.is_mlu_available() = True` 이면 return `mlu`
>
> 둘 다 `ture` 이면 `cuda, mlu` 을 return, 둘 다 `False` 이면 return `cpu`





## apis

#### init_random_seed()

Initialize random seed

```python
from mmdet.apis import init_random_seed

return_seed = init_random_seed(seed, device)
```

> - `seed` : int값의 특정 seed값이 parameter값으로 input되면 해당 seed값을 그대로 return
>
>   `seed = None` 이면
>
>   - single gpu사용시 `seed = np.random.randint(2**31)` 의 seed값 return
>   - multi gpu사용시 > 직접 해서 확인해보기



#### set_random_seed()

각종 random의 seed를 고정하는 역할

```python
from mmdet.apis import set_random_seed

set_random_seed(seed, deterministic=deterministic
```

- `seed` :  고정할 seed값

```python
def set_random_seed(seed, deterministic=False):
    """Set random seed.

    Args:
        seed (int): Seed to be used.
        deterministic (bool): Whether to set the deterministic option for
            CUDNN backend, i.e., set `torch.backends.cudnn.deterministic`
            to True and `torch.backends.cudnn.benchmark` to False.
            Default: False.
    """
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    torch.cuda.manual_seed_all(seed)
    if deterministic:
        torch.backends.cudnn.deterministic = True
        torch.backends.cudnn.benchmark = False
```



**set random seeds**

```python
from mmdet.apis import init_random_seed, set_random_seed
from mmdet.utils import get_device

device = get_device()
seed = np.random.randint(2**31)
diff_seed = False # multi gpu인 경우 True
deterministic = False


seed = init_random_seed(seed, device = device)
seed = seed + dist.get_rank() if diff_seed else seed

set_random_seed(seed, deterministic=deterministic)
```



### train_detector





## models

### build_detector

mmcv의 Registry를 통해 model, loss등의 module을 build한다

```python
from mmdet.models import build_detector

model = build_detector(
    cfg.model,
    train_cfg=cfg.get('train_cfg'),
    test_cfg=cfg.get('test_cfg'))    
```

- `cfg.model` : model에 대한 config

- `train_cfg` : teain mode에 대한 config

- `test_cfg` : test mode에 대한 config

- `model` 

  ` type(model)` : `<class 'mmdet.models.detectors.mask_rcnn.MaskRCNN'> `형식의 정의된 model class

  

#### init_weights()

호출시 model의 parameters가 `build_detector` 의 입인 config의 구성으로 initialize된다.





## datasets

### build_dataset()

dataset을 build할때 사용되는 method

```python
datasets = [build_dataset(cfg.data.train)]
```

> `cfg.data.train`  : training을 위한 config
>
> ```
> # cfg.data.train
> {'type': 
>  'CocoDataset',
>  'ann_file': 'data/coco/annotations/instances_train2017.json',
>  'img_prefix': 'data/coco/train2017/',
>  'pipeline': 
>  	[
>      {'type':
>         'LoadImageFromFile'
>         },
>      {'type': 
>         'LoadAnnotations',
>         'with_bbox': True,
>         'with_mask': True
>         },
>      {'type':
>         'Resize',
>         'img_scale': (1333, 800),
>         'keep_ratio': True
>         },
>      {'type':
>         'RandomFlip',
>         'flip_ratio': 0.5
>         },
>      {'type':
>         'Normalize',
>         'mean': [123.675, 116.28, 103.53],
>         'std': [58.395, 57.12, 57.375],
>         'to_rgb': True
>         }, 
>      {'type':
>         'Pad',
>         'size_divisor': 32
>         }, 
>      {'type': 
>         'DefaultFormatBundle'
>         },
>      {'type':
>         'Collect',
>         'keys': ['img', 'gt_bboxes', 'gt_labels', 'gt_masks']
>         }
>   	]
> }
> ```



custom dataset이면 `mmcv.utils.registry`의 `build_from_cfg`를 반환한다. 

```python
from mmcv.utils import Registry, build_from_cfg

cfg = cfg.data.train
DATASETS = Registry('dataset')

dataset = build_from_cfg(cfg, DATASETS, default_args = None)

```



### build_dataloader()

Build PyTorch DataLoader

```python
# type(dataset) : list, 	len(dataset) = 1
#  
# dataset[0] : CustomDataset Train dataset with number of images 1894, and instance counts:
# +------------+-------+------------+-------+----------+-------+----------+-------+-----------+-------+
# | category   | count | category   | count | category | count | category | count | category  | count |
# +------------+-------+------------+-------+----------+-------+----------+-------+-----------+-------+
# | 0 [flower] | 4892  | 1 [midrid] | 5640  | 2 [leaf] | 5583  | 3 [stem] | 10682 | 4 [fruit] | 1580  |
# |            |       |            |       |          |       |          |       |           |       |
# | 5 [cap]    | 1569  |            |       |          |       |          |       |           |       |
# +------------+-------+------------+-------+----------+-------+----------+-------+-----------+-------+

# train_loader_cfg : 
# {'samples_per_gpu': 1, 'workers_per_gpu': 1, 'num_gpus': 1, 'dist': False, 'seed': 670038930, 'runner_type': 'EpochBasedRunner', 'persistent_workers': False}
data_loaders = [build_dataloader(ds, **train_loader_cfg) for ds in dataset]

# type(data_loaders) : [<torch.utils.data.dataloader.DataLoader object at 0x00000281CF927430>], <class 'list'>

for i, data_batch in enumerate(self.data_loader):
    # type(data_batch) : dict()
    # data_batch.keys() : ['img_metas', 'img', 'gt_bboxes', 'gt_labels', 'gt_masks']
```

