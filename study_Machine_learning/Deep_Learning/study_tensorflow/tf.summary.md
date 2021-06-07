# tf.summary

Reference : https://www.tensorflow.org/api_docs/python/tf/summary

Operations for writing summary data, for use in analysis and visualization.



### create_file_writer

Reference : https://www.tensorflow.org/api_docs/python/tf/summary/create_file_writer

지정된 directory path에 대한 summary file writer를 instance에 할당

```python
train_summary_writer = tf.summary.create_file_writer(path)
```

`path` : file name이 아닌, directory name에 대한 path여야 한다.



#### as_default

`tf.summary.create_file_writer` 로 생성된 summary file writer를 open

`tf.summary.scalar`를 위해 사용됨



##### scalar

`tf.summary.create_file_writer` 로 생성된 summary file writer를 통해 값을 write

```python
tf.summary.scalar(name, data, step=None, description=None)
```

- `name` : write하고자 하는 data의 name

- `data` : write하고자 하는 data

- `step` : write하는 시점의 step
- `description` : 해당 data에 대한 description (string)



**예시**

```python
ckpt = tf.train.Checkpoint(step=tf.Variable(0), model=YOLOv1_model)

if latest_ckpt:
    ckpt.restore(latest_ckpt)
    print('global_step : {}, checkpoint is restored!'.format(int(ckpt.step)))
    
with train_summary_writer.as_default():
    tf.summary.scalar('learning_rate ', optimizer.lr(ckpt.step).numpy(), step=int(ckpt.step))
    tf.summary.scalar('total_loss', total_loss, step=int(ckpt.step))
    tf.summary.scalar('coord_loss', coord_loss, step=int(ckpt.step))
    tf.summary.scalar('object_loss ', object_loss, step=int(ckpt.step))
    tf.summary.scalar('noobject_loss ', noobject_loss, step=int(ckpt.step))
    tf.summary.scalar('class_loss ', class_loss, step=int(ckpt.step))
```



##### image

Reference : https://www.tensorflow.org/api_docs/python/tf/summary/image

image의 summary를 write하기 위한 method

```python
tf.summary.image(name, data, step=None, description=None)
```

- `name` : write하고자 하는 data의 name

- `data` : write하고자 하는 data

- `step` : write하는 시점의 step
- `description` : 해당 data에 대한 description (string)

