# yacs, config

system 설정 parameter를 관리하는 라이브러리. 

YAML형식을 file로 parameter를 저장한다. 



사용 방법 : 

1. config.taml과 같은 yaml file을 만든다.

   ```yaml
   GPUS: (0,1,2,3)
   OUTPUT_DIR: output
   CUDNN:
     ENABLED: true
   
   MODEL:
     TYPE: swin
     NAME: test
     PRETRAINED: model_name.pth
     SWIN: # model에 필요한 parameter
   ```

2. config.py를 만들고 yacs.config의 CfgNode를 호출하여 defualt config를 정의한다.

   ```python
   from yacs.config import CfgNode as CN
   import yaml
   
   _C = CN()		# 일반적으로 _C라는 이름으로 instance를 생성한다.
   
   # Base config files	(따로 또 다른 base config file이 없다면 [''] 으로 할당)
   _C.BASE = ['']	
   
   # -----------------------------------------------------------------------------
   # Data settings
   # -----------------------------------------------------------------------------
   _C.DATA = CN()
   _C.DATA.BATCH_SIZE = 128
   _C.DATA.DATA_PATH = 'train_dataset'
   	# 등등
   
   # -----------------------------------------------------------------------------
   # Model settings
   # -----------------------------------------------------------------------------
   _C.MODEL = CN()
   _C.MODEL.TYPE = 'ITC'		# model 이 custum이라면, 프로젝트 이름을 넣는다.
   _C.MODEL.NAME = 'test_model'
   
   # custum model backbone model parameters
   _C.MODEL.BACKBONE = CN()
   _C.MODEL.SWIN.PATCH_SIZE = 4
   
   # custum model MLP parameters
   _C.MODEL.SWIN_MLP = CN()
   _C.MODEL.SWIN_MLP.PATCH_SIZE = 4
   
   # custum model MASK HEAD model parameters
   _C.MODEL.MASK_HEAD = CN()
   	# 등등
       
   # -----------------------------------------------------------------------------
   # Training settings
   # -----------------------------------------------------------------------------
   _C.TRAIN = CN()
   	# 등등..
   ```

   

3. 위에서 정의한 _C의 instance를 생성하고, yaml file을 통해 updata를 진행한다.

   1. 
      define `_update_config_from_file`

      yaml file을 load한다.

      ```python
      def _update_config_from_file(config, cfg_file):		
          # config = _C.clone()
          # cfg_file : path of config file
          
          config.defrost()	# 사전에 정의한 _C를 변경 가능한 상태로 만든다.
          with open(cfg_file, 'r') as f:	# load yaml file
              yaml_cfg = yaml.load(f, Loader=yaml.FullLoader)
      	
          # _C.BASE = ['']가 아닐 경우, (base config file이 따로 있을 경우) base config file을 다시 load 
          for cfg in yaml_cfg.setdefault('BASE', ['']):	
              if cfg:
                  
                  _update_config_from_file(
                      config, os.path.join(os.path.dirname(cfg_file), cfg)
                  )
          print('=> merge config from {}'.format(cfg_file))
          # default config 중 cfg_file에 의해 바뀔 값이 있다면 바꾼다.
          config.merge_from_file(cfg_file)	
          config.freeze()	# updata후 freeze
      ```

      

   2. define `update_config`

      ```python
      def update_config(config, args):
          _update_config_from_file(config, args.cfg)		# args.cfg : path of config file 
      
          config.defrost()
          
          if args.opts:
          # args.opts : 명령어를 통해 python file을 실행할 때 option으로 넣어어 바꿀 값이 있을 경우
              config.merge_from_list(args.opts)
      
          # merge from specific arguments
          if args.batch_size:
              config.DATA.BATCH_SIZE = args.batch_size
          if args.data_path:
              config.DATA.DATA_PATH = args.data_path
          if args.zip:
              config.DATA.ZIP_MODE = True
          if args.cache_mode:
              config.DATA.CACHE_MODE = args.cache_mode
          if args.pretrained:
              config.MODEL.PRETRAINED = args.pretrained
          if args.resume:
              config.MODEL.RESUME = args.resume
          if args.accumulation_steps:
              config.TRAIN.ACCUMULATION_STEPS = args.accumulation_steps
          if args.use_checkpoint:
              config.TRAIN.USE_CHECKPOINT = True
          if args.amp_opt_level:
              config.AMP_OPT_LEVEL = args.amp_opt_level
          if args.output:
              config.OUTPUT = args.output
          if args.tag:
              config.TAG = args.tag
          if args.eval:
              config.EVAL_MODE = True
          if args.throughput:
              config.THROUGHPUT_MODE = True
      
          # set local rank for distributed training
          config.LOCAL_RANK = args.local_rank
      
          # output folder
          config.OUTPUT = os.path.join(config.OUTPUT, config.MODEL.NAME, config.TAG)
      
          config.freeze()
      ```

      

   3. define `get_config` 

      ```python
      def get_config(args):
          """Get a yacs CfgNode object with default values."""
          # Return a clone so that the defaults will not be altered
          # This is for the "local variable" use pattern
          config = _C.clone()
          update_config(config, args)
      
          return config
      ```




#### _C.clone()

defualt config의 intance를 생성한다.

```python
config = _C.clone()
```



##### config.defrost()

config를 변형 가능한 상태로 전환한다.
```python
config.defrost()
```



##### config.freeze()

formatted configs 를 변형 불가능한 상태로 전환한다.

```python
config.freeze()
```



```python
config.defrost()
config.TRAIN.BASE_LR = linear_scaled_lr
config.TRAIN.WARMUP_LR = linear_scaled_warmup_lr
config.TRAIN.MIN_LR = linear_scaled_min_lr
config.freeze()
```

> config.defrost() 호출 후 config값을 변경한 뒤 config.freeze()를 호출한다.



##### config.dump()

formatted configs를 반환한다. 

```python
print(configs.dump())
```

