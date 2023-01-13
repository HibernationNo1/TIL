{:toc}



# PypI

pip install로 나만의 package를 load할 수 있다.



**order**

**directory map**

```
package(dir)	┬	custom_package(dir)		┬	__init__.py
				└	setup.py				...
```

> - `custom_package(dir)` : pypi에 upload할 package
> - `setup.py` : custom package를 upload할 때 사용할 python file
> - `__init__.py` : custom package upload를 위해 package 의 각 요소(class)를 포함시키는 python file



1. install `wheel`, `twine`

   ```
   $ pip install wheel && pip install twine
   ```

2. set setup.py

3. build package `$ python setup.py bdist_wheel`

4. upload package 



## setup.py

```python
import os
from setuptools import setup, find_packages

version_file = os.path.join(os.getcwd(), 'pipeline_taeuk4958', 'version.py')             # version이 명시된 file

def get_version():
    with open(version_file, 'r') as f:
        exec(compile(f.read(), version_file, 'exec'))
    return locals()['__version__']


if __name__ == '__main__':
    setup(
        name='pipeline_taeuk4958',      # package 명
        version=get_version(),
        description='package to load file from docker local in docker container during container running',
        author='taeuk4958 ',
        author_email='taeuk4958@gmail.com',
        url='https://github.com/HibernationNo1/project_4_kubeflow_pipeline.git',
        packages=find_packages(),
        include_package_data=True,
        license='Apache License 2.0',
        install_requires=['numpy'])
```



### exam_package(dir)

#### version.py

```python
__version__ = '1.0.1'       
short_version = __version__


def parse_version_info(version_str):
    version_info = []
    for x in version_str.split('.'):
        if x.isdigit():
            version_info.append(int(x))
        elif x.find('rc') != -1:
            patch_version = x.split('rc')
            version_info.append(int(patch_version[0]))
            version_info.append(f'rc{patch_version[1]}')
    return tuple(version_info)


version_info = parse_version_info(__version__)

```



#### __init__.py

```python
from .version import __version__, short_version
__all__ = ['__version__', 'short_version']
```



이 외에도 각 dir마다 `__init__.py`가 있어야 하며 해당 dir에 속한 모든 dir과 files에 대한 import와 `__all__`의 할당이 있어야 한다.

**exam**

- ```python
  from .config import Config, merge_config
  from .utils import (change_to_tuple, emptyfile_to_config, dump_sub_key, pretty_text_sub_key,
                      get_tuple_key)
  
  __all__ = [
      "Config", "merge_config",
      "change_to_tuple", "emptyfile_to_config", "dump_sub_key", "pretty_text_sub_key","get_tuple_key"
  ]
  ```

- ```python
  from .checkpoint import load_checkpoint, save_checkpoint
  from .eval import *
  from .inference import *
  from .optimizer import *
  from .registry import Registry, build_from_cfg
  from .runner import Runner
  from .scatter import scatter_inputs
  from .utils import *
  from .visualization import mask_to_polygon
  
  
  from .data.api.coco import COCO
  from .data.datacontainer import DataContainer
  from .data.dataloader import build_dataloader
  from .data.dataset import build_dataset, CustomDataset
  from .data.sampler import GroupSampler
  from .data.transforms.collect import Collect
  from .data.transforms.compose import Compose
  from .data.transforms.defaultformatbundle import DefaultFormatBundle
  from .data.transforms.loadannotations import LoadAnnotations
  from .data.transforms.loadimagefronfile import LoadImageFromFile
  from .data.transforms.multiscaleflipaug import MultiScaleFlipAug
  from .data.transforms.normalize import Normalize
  from .data.transforms.pad import Pad
  from .data.transforms.randomflip import RandomFlip
  from .data.transforms.resize import Resize
  from .data.transforms.utils import imrescale, rescale_size, imresize, imflip
  
  from .hooks.checkpoint import CheckpointHook
  from .hooks.custom import Validation_Hook, Check_Hook
  from .hooks.hook import Hook
  from .hooks.itertime import IterTimerHook
  from .hooks.logger import LoggerHook
  from .hooks.optimizer import OptimizerHook
  from .hooks.steplrupdater import StepLrUpdaterHook
  
  from .modules.dataparallel import build_dp, DataParallel
  from .modules.register_module import *
  from .modules.base.module import BaseModule, ModuleList
  from .modules.base.initialization.constant import constant_init
  from .modules.base.initialization.initialize import initialize
  from .modules.base.initialization.kaiming import kaiming_init
  from .modules.base.initialization.normal import NormalInit, trunc_normal_init
  from .modules.base.initialization.utils import BaseInit, update_init_info, _no_grad_trunc_normal_
  from .modules.base.initialization.xavier import XavierInit
  from .modules.detector.maskrcnn import MaskRCNN
  
  
  
  __all__ = [
      "load_checkpoint", "save_checkpoint",
      "Evaluate", "compute_iou", "get_divided_polygon", "divide_polygon", "get_box_from_pol",
      'parse_inferece_result', "inference_detector",
      "DefaultOptimizerConstructor", "build_optimizer",
      "Registry", "build_from_cfg", 
      "Runner", "build_runner",
      "scatter_inputs",
      'to_2tuple', 'to_tensor', 'load_ext', "compute_sec_to_h_d", 'get_host_info', "auto_scale_lr",
      "mask_to_polygon",
      
      "COCO",
      "Collect", 'Compose', "DefaultFormatBundle", "LoadAnnotations", "LoadImageFromFile", "MultiScaleFlipAug", "Normalize", "Pad", "RandomFlip", "Resize",
      "imrescale", "rescale_size", "imresize", "imflip",
      'DataContainer', "build_dataset", "CustomDataset", "GroupSampler", "build_dataloader",
  
      'CheckpointHook', "Validation_Hook", "Check_Hook", "Hook", "IterTimerHook", "LoggerHook", "OptimizerHook", "StepLrUpdaterHook",
      
      "build_dp", "DataParallel",
      "BaseModule", "ModuleList",
      "initialize", 
      "NormalInit", "XavierInit", "kaiming_init", "constant_init",
      "BaseInit", "update_init_info", "_no_grad_trunc_normal_", "trunc_normal_init",
      "MaskRCNN"
  ]
  
  
  
  
  ```





## build package

`setup.py` 이 있는 위치에서

```
$ python setup.py bdist_wheel
```

```
...
removing build\bdist.win-amd64\wheel
```

> 위 출력이 뜨면 성공



**directory map**

```
package(dir)	┬	custom_package(dir)		┬	__init__.py
				├	setup.py				...
				├	build(dir)				
				├ 	dist(dir)				─ custom_package-1.0.1-py3-none-any.whl
				└	custom_package.egg-info(dir)
```

> `build`, `dist`, `custom_package.egg-info `세 dir이 생성된 것을 확인
>
> `dist` 안에는 `custom_package-1.0.1-py3-none-any.whl` 가 생김





## upload package 

1. PypI 가입
   - `Username`과 `Password`는 기록
   - 가입 후 Account Email은  `UNVERIFIED` 상태이다. email인증을 해서 ` VERIFIED` 상태로 만들자



2. upload

   ```
   $ twine upload dist/custom_package-1.0.1-py3-none-any.whl
   ```

   ```
   Enter your username: 
   Enter your password: 
   ```

   > `username`, `password` 를 입력

   ```
   View at:
   https://pypi.org/project/custom_package/1.0.1/
   ```

   > upload완료

   

3. check

   ```
   $ pip install custom_package
   ```

   