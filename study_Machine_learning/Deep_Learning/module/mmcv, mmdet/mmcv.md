# mmcv

## mmcv

### Config

#### fromfile

python code file형식의 config file로부터 정보를 취합하여 config instance를 생성한다.

```python
from mmcv import Config
cfg = Config.fromfile(args.config)		# args.config : config.py
```

- `config.py` 예시

  ```python
  # 각 세부 config file의 path
  _base_ = [  
      './_base_/models/mask_rcnn_swin_fpn.py',
      './_base_/datasets/coco_instance.py',
      './_base_/schedules/schedule_1x.py', 
      './_base_/default_runtime.py'
  ]
  
  # 기본 config
  model = dict(
      backbone=dict(
          embed_dim=96,
          depths=[2, 2, 18, 2],
          num_heads=[3, 6, 12, 24],
          window_size=7,
          ape=False,
          drop_path_rate=0.2,
          patch_norm=True,
          use_checkpoint=False
      ),
      neck=dict(in_channels=[96, 192, 384, 768]))
  
  img_norm_cfg = dict(
      mean=[123.675, 116.28, 103.53], std=[58.395, 57.12, 57.375], to_rgb=True)
  
  # augmentation strategy originates from DETR / Sparse RCNN
  train_pipeline = [
      dict(type='LoadImageFromFile'),
      dict(type='LoadAnnotations', with_bbox=True, with_mask=True),
      dict(type='RandomFlip', flip_ratio=0.5),
      dict(type='AutoAugment',
           policies=[
               [
                   dict(type='Resize',
                        img_scale=[(480, 1333), (512, 1333), (544, 1333), (576, 1333),
                                   (608, 1333), (640, 1333), (672, 1333), (704, 1333),
                                   (736, 1333), (768, 1333), (800, 1333)],
                        multiscale_mode='value',
                        keep_ratio=True)
               ],
               [
                   dict(type='Resize',
                        img_scale=[(400, 1333), (500, 1333), (600, 1333)],
                        multiscale_mode='value',
                        keep_ratio=True),
                   dict(type='RandomCrop',
                        crop_type='absolute_range',
                        crop_size=(384, 600),
                        allow_negative_crop=True),
                   dict(type='Resize',
                        img_scale=[(480, 1333), (512, 1333), (544, 1333),
                                   (576, 1333), (608, 1333), (640, 1333),
                                   (672, 1333), (704, 1333), (736, 1333),
                                   (768, 1333), (800, 1333)],
                        multiscale_mode='value',
                        override=True,
                        keep_ratio=True)
               ]
           ]),
      dict(type='Normalize', **img_norm_cfg),
      dict(type='Pad', size_divisor=32),
      dict(type='DefaultFormatBundle'),
      dict(type='Collect', keys=['img', 'gt_bboxes', 'gt_labels', 'gt_masks']),
  ]
  data = dict(train=dict(pipeline=train_pipeline))
  
  optimizer = dict(_delete_=True, type='AdamW', lr=0.0001, betas=(0.9, 0.999), weight_decay=0.05,
                   paramwise_cfg=dict(custom_keys={'absolute_pos_embed': dict(decay_mult=0.),
                                                   'relative_position_bias_table': dict(decay_mult=0.),
                                                   'norm': dict(decay_mult=0.)}))
  lr_config = dict(step=[27, 33])
  runner = dict(type='EpochBasedRunnerAmp', max_epochs=36)
  
  # do not use mmdet version fp16
  fp16 = None
  optimizer_config = dict(
      type="DistOptimizerHook",
      update_interval=1,
      grad_clip=None,
      coalesce=True,
      bucket_size_mb=-1,
      use_fp16=True,
  )
  ```

  - `coco_instance.py` 예시

    ```
    dataset_type = 'CocoDataset'
    data_root = 'data/coco/'
    img_norm_cfg = dict(
        mean=[123.675, 116.28, 103.53], std=[58.395, 57.12, 57.375], to_rgb=True)
    train_pipeline = [
        dict(type='LoadImageFromFile'),
        dict(type='LoadAnnotations', with_bbox=True, with_mask=True),
        dict(type='Resize', img_scale=(1333, 800), keep_ratio=True),
        dict(type='RandomFlip', flip_ratio=0.5),
        dict(type='Normalize', **img_norm_cfg),
        dict(type='Pad', size_divisor=32),
        dict(type='DefaultFormatBundle'),
        dict(type='Collect', keys=['img', 'gt_bboxes', 'gt_labels', 'gt_masks']),
    ]
    test_pipeline = [
        dict(type='LoadImageFromFile'),
        dict(
            type='MultiScaleFlipAug',
            img_scale=(1333, 800),
            flip=False,
            transforms=[
                dict(type='Resize', keep_ratio=True),
                dict(type='RandomFlip'),
                dict(type='Normalize', **img_norm_cfg),
                dict(type='Pad', size_divisor=32),
                dict(type='ImageToTensor', keys=['img']),
                dict(type='Collect', keys=['img']),
            ])
    ]
    data = dict(
        samples_per_gpu=2,
        workers_per_gpu=2,
        train=dict(
            type=dataset_type,
            ann_file=data_root + 'annotations/instances_train2017.json',
            img_prefix=data_root + 'train2017/',
            pipeline=train_pipeline),
        val=dict(
            type=dataset_type,
            ann_file=data_root + 'annotations/instances_val2017.json',
            img_prefix=data_root + 'val2017/',
            pipeline=test_pipeline),
        test=dict(
            type=dataset_type,
            ann_file=data_root + 'annotations/instances_val2017.json',
            img_prefix=data_root + 'val2017/',
            pipeline=test_pipeline))
    evaluation = dict(metric=['bbox', 'segm'])
    
    ```



이후 config값을 바꾸려면 그냥 값을 할당하면 된다.

```python
cfg.work_dir = args.work_dir	# 예시
```





##### merge_from_dict()

config instance에 merge한다. 

단, 인자로 들어오는 값은 위의 python file형식처럼 dict type이여야 한다.

```python
cfg.merge_from_dict(args.cfg_options)
```



##### dump()

인자로 받은 path에 file 생성

```python
cfg.dump(osp.join('work_dir', osp.basename('config.py')))
```

> `work_dir` 안에 `config.py` 저장



##### pretty_text

config를 읽기 좋게 반환

```python
print(f"{cfg.pretty_text}")
```





##### pop()

특정 값만 return

```python
samples_per_gpu = cfg.data.pop('samples_per_gpu')
```

> cinfig의 data table안에 있는 `samples_per_gpu`라는 key의 값을 return



### ConfigDict

config를 담을 Dict객체

```python
from mmcv import ConfigDict
tmp_dict = ConfigDict()
```





### mkdir_or_exist

인자로 받은 path가 존재하면 pass, 아니면 make directory

```python
mmcv.mkdir_or_exist(osp.abspath('work_dir'))		
```







## utils

### collect_env()

현재 running environments를 dict type으로 반환

```python
from mmcv.utils import collect_env as collect_base_env

env_info = collect_base_env()
for i in list(env_info.keys()):
    print(f"{i} : {env_info[f'{i}']}")
```

```
sys.platform : win32
Python : 3.7.13 (default, Mar 28 2022, 08:03:21) [MSC v.1916 64 bit (AMD64)]
CUDA available : True
GPU 0 : GeForce GTX 1660 SUPER
CUDA_HOME : C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v10.2
NVCC : Cuda compilation tools, release 10.2, V10.2.8
MSVC : Microsoft (R) C/C++ 최적화 컴파일러 버전 19.29.30145(x64)
GCC : n/a
PyTorch : 1.10.0
PyTorch compiling details : PyTorch built with:
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

TorchVision : 0.11.1
OpenCV : 4.5.5
MMCV : 1.5.0
MMCV Compiler : MSVC 192930137
MMCV CUDA Compiler : 10.2
```



### get_git_hash()

git_hash를 return 

```python
from mmcv.utils import get_git_hash
print(get_git_hash())		# 240d7a31c745578aa8c4df54c3074ce78b690c34

MMDetection = mmdet.__version__ + '+' + get_git_hash()[:7]
print(MMDetection)		# 2.24.1+240d7a3
```



### Registry

mmcv에서 OpenMMLab의 대부분의 project의 dataset, model 및 세부 layer moduel을 관리할때 사용하는 것으로, 

string문자열을 통해 class를 찾고 instance화 한다.

```python
from mmcv.cnn import MODELS as MMCV_MODELS
from mmcv.utils import Registry

MODELS = Registry('models', parent=MMCV_MODELS)
```

- `name` : string, user가 원하는 name으로 instance를 생성한다. 여러 model (backbone과 segmentation model이 합쳐진 경우)에 대한 instance를 선언할땐 `models`로 한다.

- `parent` : 하위 class를 name으로 한 Registry의 instance이다.

- **`mcvv.cnn MODELS`**

  ```python
  MODELS = Registry('model', build_func=build_model_from_cfg)
  ```

  - `name` : model == backbone model과 같은 단일 model class를 build하기 위한 Registry임을 명시

- `build_func`  : == `build_model_from_cfg`

  ```python
  from mmcv.utils import build_from_cfg
  from mmcv.utils import Registry
  
  def build_model_from_cfg(cfg, registry, default_args=None):
      """Build a PyTorch model from config dict(s). Different from
      ``build_from_cfg``, if cfg is a list, a ``nn.Sequential`` will be built.
  
      Args:
          cfg (dict, list[dict]): The config of modules, is is either a config
              dict or a list of config dicts. If cfg is a list, a
              the built modules will be wrapped with ``nn.Sequential``.
          registry (:obj:`Registry`): A registry the module belongs to.
          default_args (dict, optional): Default arguments to build the module.
              Defaults to None.
  
      Returns:
          nn.Module: A built nn module.
      """
      if isinstance(cfg, list):
          modules = [
              build_from_cfg(cfg_, registry, default_args) for cfg_ in cfg
          ]
          return Sequential(*modules)
      else:
          return build_from_cfg(cfg, registry, default_args)
  ```

  - cfg의 type이 list인 경우(model, loss등을 한 번에 담은 config인 경우) 각 class의 config에 대하여 `build_from_cfg`를 호출하여 return
  - cfg의 type이 dict인 경우 해당 config에 대한 `build_from_cfg`를 호출하여 return

##### build_from_cfg()

dict type의 config정보를 바탕으로 module을 build함

```python
def build_from_cfg(cfg, registry, default_args=None):
    """Build a module from config dict.

    Args:
        cfg (dict): Config dict. It should at least contain the key "type".
        registry (:obj:`Registry`): The registry to search the type from.
        default_args (dict, optional): Default initialization arguments.

    Returns:
        object: The constructed object.
    """
    # check config type
    if not isinstance(cfg, dict):
        raise TypeError(f'cfg must be a dict, but got {type(cfg)}')
    if 'type' not in cfg:
        if default_args is None or 'type' not in default_args:
            raise KeyError(
                '`cfg` or `default_args` must contain the key "type", '
                f'but got {cfg}\n{default_args}')
    if not isinstance(registry, Registry):
        raise TypeError('registry must be an mmcv.Registry object, '
                        f'but got {type(registry)}')
    if not (isinstance(default_args, dict) or default_args is None):
        raise TypeError('default_args must be a dict or None, '
                        f'but got {type(default_args)}')
    
    args = cfg.copy()
	
    if default_args is not None:
        for name, value in default_args.items():
            args.setdefault(name, value)
    
    obj_type = args.pop('type')	
    # obj_type 예시 : MaskRCNN, CrossEntropyLoss, Normal, CocoDataset ...
    # 온갖게 다 들어오며, 이런 방식으로 모든 module을 관리한다.
    if isinstance(obj_type, str):
        obj_cls = registry.get(obj_type)    	# 여기서 
        # print(f"obj_cls : {obj_cls}")   # 세부 code가 어디에 있는지 위치를 알 수 있음.
        if obj_cls is None:
            raise KeyError(
                f'{obj_type} is not in the {registry.name} registry')
    elif inspect.isclass(obj_type):
        obj_cls = obj_type
    else:
        raise TypeError(
            f'type must be a str or valid type, but got {type(obj_type)}')
     
    try:
        return obj_cls(**args)  # 기대하는 최종 return
    except Exception as e:
        # Normal TypeError does not print class name.
        raise type(e)(f'{obj_cls.__name__}: {e}')
```





#### build()

**build_func을 return**

```python
def build(self, *args, **kwargs):
   return self.build_func(*args, **kwargs, registry=self)
```

- `self.build_func()의 return값 예시` : `self._module_dict['MaskRCNN'](config) `
- `args` : config



input config의 정보를 토대로 특정 class를 build한다.

```python
from mmcv.utils import Registry

MODELS = Registry('models', parent=MMCV_MODELS)

BACKBONES = MODELS
NECKS = MODELS
ROI_EXTRACTORS = MODELS
SHARED_HEADS = MODELS
HEADS = MODELS
LOSSES = MODELS
DETECTORS = MODELS

def build_backbone(cfg):
    """Build backbone."""
    return BACKBONES.build(cfg)


def build_neck(cfg):
    """Build neck."""
    return NECKS.build(cfg)


def build_roi_extractor(cfg):
    """Build roi extractor."""
    return ROI_EXTRACTORS.build(cfg)


def build_shared_head(cfg):
    """Build shared head."""
    return SHARED_HEADS.build(cfg)


def build_head(cfg):
    """Build head."""
    return HEADS.build(cfg)


def build_loss(cfg):
    """Build loss."""
    return LOSSES.build(cfg)

def build_detector(cfg, train_cfg=None, test_cfg=None):
    """Build detector."""
    
    if train_cfg is not None or test_cfg is not None:
        warnings.warn(
            'train_cfg and test_cfg is deprecated, '
            'please specify them in model', UserWarning)
    assert cfg.get('train_cfg') is None or train_cfg is None, \
        'train_cfg specified in both outer field and model field '
    assert cfg.get('test_cfg') is None or test_cfg is None, \
        'test_cfg specified in both outer field and model field '
        
    return DETECTORS.build(
        cfg, default_args=dict(train_cfg=train_cfg, test_cfg=test_cfg))
```

>`build_backbone` 함수에서 `BACKBONES.build(cfg)`을 호출할 때 cfg는 dict 이며 
>
>`dict(type='Resnet')` 와 같이 type이라는 key를 통해 backbone model name을 명시한다. 이를 통해 Resnet backbone model class가 build되는 것이며, 같은 프로세스로 loss를 비롯한 다양한 class를 build할 수 있다.

- `cfg` : dict type의 config
- `default_args` : 





### get_logger()

인자로 받는 name의 logger를 생성

```python
logger = get_logger(name='mmdet', log_file=log_file, log_level=log_level)
```

- `name` : logger의 namespace
- `log_file` : init log information file이 있을 경우 할당 (default = None)
- `log_level` : log의 카테고리. 
  -  `log_level = 'INFO'`



## runner

### get_dist_info()

gpu ran(gpu number)와 word_size(number of gpu)를 return

```python
from mmcv.runner import get_dist_info

rank, world_size = get_dist_info()
```

> single gpu일 때 `rank = 0, world_size = 1`





### build_runner()

training, validation과 같은 process를 진행하기 위한 runner를 build

```python
from mmcv.runner import build_runner

runner = build_runner(
    cfg.runner,
    default_args=dict(
        model=model,
        optimizer=optimizer,
        work_dir=cfg.work_dir,
        logger=logger,
        meta=meta))
    
```

- `cfg.runner` : configuration for run

  e.g.

  ```python
  cfg.runner : {'type': 'EpochBasedRunner', 'max_epochs': 12}
  ```

- `default_args` : dict, 

  - `model` : build된 model instance

  - `optimizer` : build된 optimizer instance

  - `work_dir` : path of directory 

  - `logger` : instance of logger

    ```python
    from mmdet.utils import get_root_logger
    logger = get_root_logger(log_level=cfg.log_level)	# 예시임
    ```

  - `meta` : meta information (dict)



#### timestamp

현재 시간을 담은 runner class attribute

```python
runner.timestamp = timestamp
print(f"timestamp : {timestamp}")	# 20220519_164937
```



#### register_training_hooks()

다양한 동작이 구현된 여러 hook을 담은 method로, 입력 args(config정보)에 method들이 call된다.

```python
runner.register_training_hooks(
        lr_config = cfg.lr_config,
        optimizer_config = cfg.optimizer_config,
        checkpoint_config = cfg.checkpoint_config,
        log_config = cfg.log_config,
        momentum_config = cfg.get('momentum_config', None),
    	timer_config = 
        custom_hooks_config=cfg.get('custom_hooks', None))
```

- `lr_config` : learning rate 관련 configuration

  ```python
  {
   'policy': 'step',
   'warmup': 'linear',
   'warmup_iters': 1000,
   'warmup_ratio': 0.001,
   'step': [8, 11]
  }
  ```

  > dict형식이 아니라 custom hook function이여도 괜찮지만, mvcc를 사용하는 경우에는 dict형식으로 사용하자.

- `optimizer_config` : optimizer 관련 configuration 

  e.g. `optimizer_config : {'grad_clip': None}`

- `checkpoint_config` : 

  e.g.

  ```
  {'interval': 1, 
   'meta': 
   	{'mmdet_version': '2.24.1240d7a3',
   	'CLASSES': ('person', 'bicycle', 'car', 'motorcycle', 'airplane', 'bus', 'train', 'truck', 'boat', 'traffic light', 'fire hydrant', 'stop sign', 'parking meter', 'bench', 'bird', 'cat', 'dog', 'horse', 'sheep', 'cow', 'elephant', 'bear', 'zebra', 'giraffe', 'backpack', 'umbrella', 'handbag', 'tie', 'suitcase', 'frisbee', 'skis', 'snowboard', 'sports ball', 'kite', 'baseball bat', 'baseball glove', 'skateboard', 'surfboard', 'tennis racket', 'bottle', 'wine glass', 'cup', 'fork', 'knife', 'spoon', 'bowl', 'banana', 'apple', 'sandwich', 'orange', 'broccoli', 
  'carrot', 'hot dog', 'pizza', 'donut', 'cake', 'chair', 'couch', 'potted plant', 'bed', 'dining table', 'toilet', 'tv', 'laptop', 'mouse', 'remote', 'keyboard', 'cell phone', 'microwave', 'oven', 'toaster', 'sink', 'refrigerator', 'book', 'clock', 'vase', 'scissors', 'teddy bear', 'hair drier', 'toothbrush')
  	}
  }
  ```

  

- `log_config` : ` log_config : {'interval': 50, 'hooks': [{'type': 'TextLoggerHook'}]}`

  key값 `type` 을 통해 사전에 정의된 log를 위한 특정 Hook을 registry에서 호출

- `momentum_config` : 연구하기 이전까진 `None`할당. 

- `timer_config` : `{'type': 'IterTimerHook'}`

  key값 `type` 을 통해 사전에 정의된 timer를 위한 특정 Hook을 registry에서 호출

  None값을 할당해도 defualt가 `dict(type='IterTimerHook')` 이다.

- `custom_hooks_config` : `[{'type': 'NumClassCheckHook'}]`

  key값 `type` 을 통해 사전에 정의된 특정 Hook을 registry에서 호출

```python
def register_training_hooks(self,
                            lr_config,
                            optimizer_config=None,
                            checkpoint_config=None,
                            log_config=None,
                            momentum_config=None,
                            timer_config=dict(type='IterTimerHook'),
                            custom_hooks_config=None):
    """Register default and custom hooks for training.

        Default and custom hooks include:

        +----------------------+-------------------------+
        | Hooks                | Priority                |
        +======================+=========================+
        | LrUpdaterHook        | VERY_HIGH (10)          |
        +----------------------+-------------------------+
        | MomentumUpdaterHook  | HIGH (30)               |
        +----------------------+-------------------------+
        | OptimizerStepperHook | ABOVE_NORMAL (40)       |
        +----------------------+-------------------------+
        | CheckpointSaverHook  | NORMAL (50)             |
        +----------------------+-------------------------+
        | IterTimerHook        | LOW (70)                |
        +----------------------+-------------------------+
        | LoggerHook(s)        | VERY_LOW (90)           |
        +----------------------+-------------------------+
        | CustomHook(s)        | defaults to NORMAL (50) |
        +----------------------+-------------------------+

        If custom hooks have same priority with default hooks, custom hooks
        will be triggered after default hooks.
        """
    # 대부분 registry에서 class호출
    self.register_lr_hook(lr_config)
    self.register_momentum_hook(momentum_config)
    self.register_optimizer_hook(optimizer_config)
    self.register_checkpoint_hook(checkpoint_config)
    self.register_timer_hook(timer_config)
    self.register_logger_hooks(log_config)
    self.register_custom_hooks(custom_hooks_config)
```





#### run()

```python
runner.run(data_loaders = data_loaders,
           workflow = cfg.workflow)
```

- `data_loaders` : list[:obj:`DataLoader`] 

  `DataLoader` : object of  `torch.utils.data.dataloader.DataLoader`

- `workflow` : (phase, epochs) 를 element로 가진 list

  E.g.

  `[('train', 2), ('val', 1)]` : 2 epoch는 training을 하고 1epoch는 validation을 진행하며 이를 반복한다.



## cnn

### MODELS