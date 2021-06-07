# tfds

Reference : https://www.tensorflow.org/datasets/overview

```python
import tensorflow_datasets as tfds
```



### tfds.list_builders()

사용 가능한 dataset list를 보여준다.

```python
tfds.list_builders()
```



### tfds.load()

Reference : https://www.tensorflow.org/datasets/api_docs/python/tfds/load

dataset을 가져온다.

```python
(train_ds, test_ds), ds_info = tfds.load(name = 'mnist',
                                         shuffle_files = True,
                                         as_supervised = True,
                                         with_info = True, 
                                         split = ['train', 'test']
                                         )
```

- `name` : 가져올 dataset 이름
- `shuffle_files` : bool, 정렬된 dataset을 섞을지 여부
- `as_supervised` : bool, dataset을 tuple type으로 받을지 여부
- `with_info` : bool, dataset에 대한 information을 받을지 여부

- `split` : dataset을 어떤 방식으로 분할해서 받을지 결정

  > Reference : https://www.tensorflow.org/datasets/splits

- `(train_ds, test_ds)` :  `split`에 의해 결정되어 return된 dataset

-  `ds_info` :  `with_info = True` 일 때만 return

- `batch_size` : 각 dataset의 batch size를 결정

  > `batch_size = -1` 로 지정하면 전체 data가 하나의 batch size



#### split

##### tfds.Split.TEST

전체 dataset에서 test데이터만 extraction할 때 사용

**tfds.Split.TRAIN**, **tfds.Split.VALIDATION**도 마찬가지

```python
voc2007_test_split_data = tfds.load("voc/2007", split=tfds.Split.TEST, batch_size=1)
```

> voc/2007 라는 dataset에서 test dataset만 extraction



#### ds_info

##### ds_info.splits[]

dataset information에서 specific data에 접근한다.

```python
train_ds = ds_info.splits['train']
```

> 'train' data에 접근



##### ds_info.num_examples

dataset 의 개수를 return

```python
num_train_ds = ds_info.splits['train'].num_examples
```

> 'train' dataset의 data 개수 return



#### ds

Reference : https://www.tensorflow.org/api_docs/python/tf/data/Dataset

##### ds.take()

dataset에서 specific number 만큼의 data를 return

```python
train_ds_tmp = train_ds.take(1000)
```

> train_ds에서 1000개의 data를 return



##### ds.skip()

dataset에서 specific number 만큼을 제외한 data를 return

```python
train_ds_tmp = train_ds.skip(1000)
```

> train_ds에서 (전체 개수 - 1000개)의 data를 return



##### ds.shuffle()

dataset을 specific number만큼씩 섞는다

```python
train_ds = train_ds.shuffle(1000)
```

> train_ds의 dataset을 1000개 단위로 random한 순서로 섞어준다.



##### ds.batch()

dataset을 specific number만큼씩 잘라서 묶어 return한다.

```python
train_batch_size = 1000
train_ds_batch = train_ds.batch(train_batch_size)
```

> train_ds의 dataset을 1000개씩 묶어 여러개의 dataset을 만들고, 여러개의 dataset을 train_ds_batch에 return (한 개의 batch만 return되는게 아님)



##### ds.padded_batch()

input dataset의 크기가 가변적일때 사용하는 **ds.batch()** 라고 이해하면 된다.

```python
train_batch_size = 1000

def predicate(x):
    if x > 3 :
        return True  
  	return False

train_data = train_data.filter(predicate)
train_ds_batch = train_ds.padded_batch(train_batch_size)
```

> train_data의 각 data값에 따라서 그 dataset의 개수가 달라진다. 그렇기 때문에 이럴 때는 ds.batch()보다 padded_batch()를 사용해야 한다.



##### ds.map()

dataset에 여러 column이 있을때, mapping을 할 수 있다.

```python
def normalization(images, labels):
        images = tf.cast(images, tf.float32)/255.

        oh_labels = tf.one_hot(labels, 10)
        return [images, oh_labels]
    
train_ds = train_ds.map(normalization)
```

> train_ds dataset에 images, labels이란 object가 담겨져 있어 map(normalization) 가능



##### ds.concatenate

dataset끼리 말 그대로 concatenate할때 사용

```python
train_ds = voc2007_test_split_data.concatenate(voc2012_train_split_data).concatenate(voc2012_validation_split_data)
```

> `voc2007_test_split_data`에 `voc2012_train_split_data`과 `voc2012_validation_split_data` dataset을 concatenate해서 train_ds에 반환



##### ds.filter()

argument로 받은 x가 specific 조건에 만족할 때만 x값을 return (element wise)

```python
def predicate(x):
    if x > 3 :
        return True  
  	return False

train_data = train_data.filter(predicate)
```

> x가 3보다 크면 return되는 True값에 따라 x값만 train_data에 할당



- lambda 사용

  ```python
  dataset = dataset.filter(lambda x: x < 3)
  ```

  



