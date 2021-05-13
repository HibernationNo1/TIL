# keras.callbacks

iteration 이 반복되다가 특정 particular condition이 맞으면 반복을 멈추고 여러 작업등을 수행할 수 있게 해준다.

보통 overfitting이 발생하거나 performance가 더 이상 좋아지지 않으면 collback 함수를 사용한다.



### ModelCheckpoint()

save file depedns on specific condition

```python
from tensorflow.keras.callbacks import ModelCheckpoint()
```





```python
instance = ModelCheckpoint(filepath = , monitor = , mode = )
```

- `filepath` : path for save file

  >format기능을 가질 수 있음
  >
  >ex)
  >
  >if filepath = 'weights.{epoch:02d}-{val_loss:.2f}.hdf5 ='
  >
  >epoch:02d와 val_loss:.2f 의 자리에 해당 information을 넣어 저장됨

- `monitor` : 모니터 할 지표 (validation data를 모니터함)

  - `monitor = val_loss`
  - `monitor = val_accuracy`

- `mode` : monitor로 설정한 지표에 대한 positive mode 결정

  - `mode = 'min'` : moniter지표가 감소해야 좋을 경우  
  - `mode = 'max'` : moniter지표가 증가해야 좋을 경우  
  - `mode = 'auto'` : moniter지표가 감소해야 좋을지 증가해야 좋을지를 moniter arg의 name을 보고 자동 유추

- `save_best_only` : 가장 좋은 performance를 가진 model만 save할지 (True ro False)

  > model의 크기가 커지면 매 epoch마다 저장할 때 공간을 많이 잡아먹음
  >
  > 결국 가장 마지막에 학습된 model이 저장되는 경우가 대부분

- `save_weights_only` : weights만 save할 지 여부 (True ro False)

  > False엔 tf ver.2 의 issue가 있다고 하여 True만 사용

- `verbose ` 1 을 설정해놓으면  학습의 진행 상황을 보여준다.

- `period ` save wights every given Integer epoch. (model size가 크면 이것도 크게 설정)

ex)

```python
import os
from tensorflow.keras.callbacks import ModelCheckpoint()

save_path = os.getcwd() + 'weights.{epoch:02d}-{val_loss:.2f}.hdf5'

model.compile(~~~)

mcp_cb = ModelCheckpoint(filepath = save_path, monitor = 'val_loss', 
                        save_best_only = True, save_weights_only = True,
                        mode = 'min', verbose = 1)

loss_acc = model.fit(x = train_iamges, y = train_oh_labels, batch_szie = 128, epoch = 10, validation_data = (val_images, val_oh_labels), callbacks = [mcp_cb])
```





### ReduceLROnPlateau()

특정 epochs 횟수통안 performance가 개선 되지 않으면 learning rate를 동적으로 감소시킴

```python
from tensorflow.keras.callbacks import ReduceLROnPlateau
```

```python
instance = ReduceLROnPlateau( monitor = , mode = )
```

- `monitor`

- `mode`

- `factor` : learning 속도를 줄일 인수  

  > new_lr = lr*factor

- `patience` : lr을 줄이기 전에 monitor할 epochs횟수

  > patience = 10 이면
  >
  > epoch가 10회 interation 할 동안 lr가 변함이 없을 때 factor를 곱함

- `verbose`



ex)

```python
from tensorflow.keras.callbacks import ReduceLROnPlateau

model.compile(~~~)

rlr_cb = ReduceLROnPlateau(monitor = 'val_loss', fector = 0.3, patienc = 10, mode = 'min', verbose = 1)

loss_acc = model.fit(x = train_iamges, y = train_oh_labels, batch_szie = 128, epoch = 30, validation_data = (val_images, val_oh_labels), callbacks = [rlr_cb])
```



### EarlyStopping()

specifical epochs 동안 performance가 개선되지 않을 시 learning을 조기에 stop 

```python
from tensorflow.keras.callbacks import EarlyStopping
```

```python
instance = EarlyStopping(monitor = , mode =)
```

- `monitor`

- `mode`

- `patience` : Early Stopping 적용 전에 monitor 할 epochs 횟수

  > patience = 10 이면
  >
  > epoch가 10회 interation 할 동안 loss 개선이 없으면 Early Stopping



ex)

```python
from tensorflow.keras.callbacks import EarlyStopping

model.compile(~~~)

elr_cb = EarlyStopping(monitor = 'val_loss', patienc = 20, mode = 'min', verbose = 1)

loss_acc = model.fit(x = train_iamges, y = train_oh_labels, batch_szie = 128, epoch = 50, validation_data = (val_images, val_oh_labels), callbacks = [elr_cb])
```



---

세 개 한 번에

```python
import os
from tensorflow.keras.callbacks import ModelCheckpoint()
from tensorflow.keras.callbacks import ReduceLROnPlateau
from tensorflow.keras.callbacks import EarlyStopping

save_path = os.getcwd() + 'weights.{epoch:02d}-{val_loss:.2f}.hdf5'

model.compile(~~~)

mcp_cb = ModelCheckpoint(filepath = save_path, monitor = 'val_loss', 
                        save_best_only = True, save_weights_only = True,
                        mode = 'min', verbose = 1)
rlr_cb = ReduceLROnPlateau(monitor = 'val_loss', fector = 0.3, 
                           patienc = 10, mode = 'min', verbose = 1)
elr_cb = EarlyStopping(monitor = 'val_loss', patienc = 20, 
                       mode = 'min', verbose = 1)

loss_acc = model.fit(x = train_iamges, y = train_oh_labels, batch_szie = 128, epoch = 50, validation_data = (val_images, val_oh_labels), callbacks = [mcp_cb , rlr_cb, elr_cb])
```

