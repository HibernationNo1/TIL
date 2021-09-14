# tensorflow.python.keras.saving

```python
import tensorflow.python.keras.saving
```





### hdf5_format

```python
import h5py
from tensorflow.python.keras.saving import hdf5_format
```

`hdf5`형식의 file을 다룰때 사용





#### load_weights_from_hdf5_group_by_name()

각각의 layer에 name을 할당한 경우

```python
with h5py.File(filepath, mode='r') as f
	keras_model = model  # keras_model : 특정 model의 instance
    layers = keras_model.layers
    
	hdf5_format.load_weights_from_hdf5_group_by_name(f, layer)
```

`f` : file

`layer` : trained weight를 받을 layer



#### load_weights_from_hdf5_group

각각의 layer에 name을 할당하지 않은 경우

```python
with h5py.File(filepath, mode='r') as f
	keras_model = model  # keras_model : 특정 model의 instance
    layers = keras_model.layers
    
	hdf5_format.load_weights_from_hdf5_group(f, layer)
```

