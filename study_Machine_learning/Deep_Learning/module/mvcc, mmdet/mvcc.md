# mcvv

## mcvv

### Config

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





#### merge_from_dict()

config instance에 merge한다. 

단, 인자로 들어오는 값은 위의 python file형식처럼 dict type이여야 한다.

```python
cfg.merge_from_dict(args.cfg_options)
```



#### dump()

인자로 받은 path에 file 생성

```python
cfg.dump(osp.join('work_dir', osp.basename('config.py')))
```

> `work_dir` 안에 `config.py` 저장





### mkdir_or_exist

인자로 받은 path가 존재하면 pass, 아니면 make directory

```python
mmcv.mkdir_or_exist(osp.abspath('work_dir'))		
```





## utils



## runner