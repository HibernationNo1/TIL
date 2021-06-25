# TensorBoard

학습 과정을 이미지화 해서 확인할 수 있도록 도와주는 기능

**장점**

1. 실시간으로 학습 과정을 그래프로 확인할 수 있다.

   학습이 시작되고 우리가 원하는 step마다 summary를 실행하는 순간부터 tensorboard에서 학습이 어떻게 되고 있는지 확인 할 수 있다.

2. 기존에 학습했던 것과 동시에 비교 분석이 가능하다.

   같은 step수 안에서 기존과 학습이 더 잘 되고 있는지 또는 performance가 나빠지고 있는지 확인 할 수 있다.

3. 분할 문제를 풀고 있다면 동시에 label과 inference 결과를 실시간으로 image화 해서 확인할 수 있다.

   convolution의 filter나 각 layer에서 나온 결과값들을 실시간으로 확인도 가능하다. 이를 통해 blackbox라고 불리는 신경망을 시각적으로 이해하는데 조금이라도 더 도움이 될 것이다.





## how to use?

### install

```
$ pip install tensorboard
```

> 물론 tensorflow도 설치가 되어있어야 한다.



### execute

```
$ tensorboard --log=log_directory
```

> log_directory안에는 tensorboard에 기록한 data가 존재해야 한다.

오류 없이 tensorboard를 실행하면  http://localhost:6006/ 과 같이 브라우져로 6006번 포트에 들어갈 수 있다.



### method

#### checkpoint namager

##### Checkpoint()

check point의 instance를 만드는 method

```python
ckpt = tf.train.Checkpoint(step = , model = )
```

- `ckpt` : Checkpoint를 표현하는 information을 담은 instance

- `step` : start checkpoint

  > `step = tf.Variable(0)`

- `model` : 학습에 사용할 model의 instance



###### restore()

path상의 Checkpoint를  tf.train.Checkpoint의 instance에 저장

```
ckpt.restore(path)
```

- `path` : checkpoint가 저장된 file의 path



###### step

현 시점의 ckeckpoint의 step을 return

```python
ckpt.step
```



###### assign_add()

몇 번의 step을 쌓을건지 결정

```python
ckpt.step.assign_add(number)
```

- `number` : 쌓을 step의 숫자

  > ckpt.step.assign_add(1)
  >
  > step 1번 증가



##### CheckpointManager()

check point를 관리하는 instance를 만든다.

```python
ckpt_manager = tf.train.CheckpointManager(ckpt, directory = ,
                                            max_to_keep=None)
```

- `ckpt_manager` : CheckpointManager의 instance

- `ckpt` : `tf.train.Checkpoint`로 만든 instance

- `directory` : 각 Checkpoint마다 model을 저장할 directory의 path

  > `directory = checkpoint_path`
  >
  > `checkpoint_path`는 path를 저장한 variable

###### save()

특정 시점의 checkpoint에 CheckpointManager의 parameter를 save

```python
ckpt_manager.save(checkpoint_number=ckpt.step)
```

- `checkpoint_number` : 저장할 시점의 step



##### latest_checkpoint()

마지막 checkpoint에서 저장된 file의 path를 return

```python
latest_ckpt = tf.train.latest_checkpoint(checkpoint_path)
```

- `latest_ckpt` : 마지막 checkpoint에서 저장된 file의 path

  저장된 file이 없으면 `None`

- `checkpoint_path` : checkpoint가 path를 저장한 variable





#### writer

##### writer()

tnesorboard의 log를 write하기 위한 writer instance

```python
instance = tf.summary.create_file_writer(path)
```

- `instance` : writer instance 

- `path` : log를 기록할 file을 저장하기 위한 directory의 path

  > path에 directory가 없다면 생성한다.
  >
  > ```
  > instance = tf.summary.create_file_writer(tensorboard_log_path +  '/train')
  > ```
  >
  > tensorboard_log_path 라는 경로 위에 train이라는 directory 생성

  

##### scalar()

parameter를 log에 기록하는 method

```python
with train_summary_writer.as_default():
    tf.summary.scalar('log_name', data, step = ckeckpoint)
```

- `with train_summary_writer.as_default()` : tensorboard 기록을 위해 호출
- `'log_name'` : tensorboard에 기록할 data의 이름
- `data` : tensorboard에 기록할 parameter
- `step` : 몇 step에 기록하는지 표현
- `ckeckpoint` : ckeck point manager의 instance





## **exam**

###### set checkpoint manager

```python
checkpoint_path = 'saved_model'
checkpoint_path = os.path.join(os.getcwd(), checkpoint_path)

model_instance = YOLOv1(input_height, input_width, cell_size, boxes_per_cell, num_classes)

ckpt = tf.train.Checkpoint(step =tf.Variable(0) , model = model_instance)
ckpt_manager = tf.train.CheckpointManager(ckpt, directory=checkpoint_path, max_to_keep=None)
latest_ckpt = tf.train.latest_checkpoint(checkpoint_path)

# 마지막 checkpoint의 값들을 ckpt에 저장. 저장된 file이 없으면 if문 pass
if latest_ckpt:
		ckpt.restore(latest_ckpt)
		print('global_step : {}, checkpoint is restored!'.format(int(ckpt.step)))
```



###### save checkpoint

```python
save_checkpoint_steps = 50

if ckpt.step % save_checkpoint_steps == 0:
		ckpt_manager.save(checkpoint_number=ckpt.step)  # CheckpointManager의 parameter 저장
		print('global_step : {}, checkpoint is saved!'.format(int(ckpt.step)))
```



###### write parameter

```python
tensorboard_log_path = 'tensorboard_log'
tensorboard_log_path = os.path.join(os.getcwd(), tensorboard_log_path)

train_summary_writer = tf.summary.create_file_writer(tensorboard_log_path +  '/train')   
validation_summary_writer = tf.summary.create_file_writer(tensorboard_log_path +  '/validation')  

	# dir_name	|-- saved_model
	#			|-- tensorboard_log	|-- train
	#								|-- validation

with train_summary_writer.as_default():
	tf.summary.scalar('learning_rate ', optimizer.lr(ckpt.step).numpy(), step=int(ckpt.step))
	tf.summary.scalar('total_loss', total_loss, step=int(ckpt.step))
	tf.summary.scalar('coord_loss', coord_loss, step=int(ckpt.step))
	tf.summary.scalar('object_loss ', object_loss, step=int(ckpt.step))
	tf.summary.scalar('noobject_loss ', noobject_loss, step=int(ckpt.step))
	tf.summary.scalar('class_loss ', class_loss, step=int(ckpt.step))
    
with validation_summary_writer.as_default():
	tf.summary.scalar('total_validation_total_loss', total_validation_total_loss, step=int(ckpt.step))
	tf.summary.scalar('total_validation_coord_loss', total_validation_coord_loss, step=int(ckpt.step))
	tf.summary.scalar('total_validation_object_loss ', total_validation_object_loss, step=int(ckpt.step))
	tf.summary.scalar('total_validation_noobject_loss ', total_validation_noobject_loss, step=int(ckpt.step))
	tf.summary.scalar('total_validation_class_loss ', total_validation_class_loss, step=int(ckpt.step))
```

