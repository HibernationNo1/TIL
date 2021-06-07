# tf.train

Reference : https://www.tensorflow.org/api_docs/python/tf/train



Support for training models.



### Checkpoint

Reference : https://www.tensorflow.org/api_docs/python/tf/train/Checkpoint

Manages saving/restoring trackable values to disk.

model, oprimizer등, 저장할 values를 instance에 저장해서 관리

```python
ckpt = tf.train.Checkpoint(step=tf.Variable(0), model=YOLOv1_model)
```

- `step` : 몇 step 번째에 대한 checkpoint인지를 의미 

  > `step=tf.Variable(0)` : 최초 시작을 의미

- `model` : 저장할 model

- `oprimizer` : optimizer도 저장 가능



##### tf.Variable() 

Reference : https://www.tensorflow.org/guide/variable

일반 list 또는 value를 tensor type의 변수로 만들어줌 ()

```python
print(tf.Variable(0))
```

```
<tf.Variable 'Variable:0' shape=() dtype=int32, numpy=0>
```



#### restore

path위의 file을 불러와서 tf.train.Checkpoint의 instance에 다시 저장한다.

```python
ckpt.restore(path)
```

이후 instance의 step 역시 path위의 file에 저장된 step으로 updata된다.



##### assign_add()

`tf.train.Checkpoint` 의 instance에 저장된 step을 증가시키는 함수

```python
ckpt.step.assign_add(1)
```

> step 1 증가



#### step

이제까지 진행 된 step을 반환

```python
print(f'global_step : {int(ckpt.step)}, checkpoint is restored!')
```





### CheckpointManager

Reference : https://www.tensorflow.org/api_docs/python/tf/train/CheckpointManager

주기적으로 저장하기 위해 

```python
ckpt_manager = tf.train.CheckpointManager(checkpoint, directory, max_to_keep)
```

- `checkpoint` : 저장할 value를 tf.train.Checkpoint 의 instance로 가져온다.

- `directory` : path to save

- `max_to_keep` : 저장할 checkpoint의 개수

  > `max_to_keep = None` :모든 checkpoint 에 대해서 저장



**예시**

```python
flags.DEFINE_string('checkpoint_path', default='saved_model', help='path to a directory to save model checkpoints during training')

if not os.path.exists(FLAGS.checkpoint_path):
    os.mkdir(FLAGS.checkpoint_path)

ckpt = tf.train.Checkpoint(step=tf.Variable(0), model=YOLOv1_model)
ckpt_manager = tf.train.CheckpointManager(checkpoint = ckpt, directory = FLAGS.checkpoint_path, max_to_keep = True)
```



#### save

`tf.train.CheckpointManager` 의 instance에 저장된 parameter를 설정된 directory에 저장

```python
ckpt_manager.save(checkpoint_numbe)
```

- `checkpoint_numbe` : 저장되는 시점의 step을 의미



**예시**

```python
ckpt_manager.save(checkpoint_number=ckpt.step)
```





### latest_checkpoint

Reference : https://www.tensorflow.org/api_docs/python/tf/train/latest_checkpoint

마지막에 저장된 checkpoint file의 name을 찾아낸다.

```python
latest_ckpt = tf.train.latest_checkpoint(checkpoint_dir)
```

- `checkpoint_dir` : 마지막 checkpoint에서 저장된 file이 있는 path

- `latest_ckpt` : 마지막 checkpoint에서 저장된 file name의 path



**예시**

```python
if latest_ckpt:
    ckpt.restore(latest_ckpt)
```

