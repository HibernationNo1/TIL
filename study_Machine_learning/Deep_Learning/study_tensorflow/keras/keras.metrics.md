# keras.metrics

method used to chack model's performance

```python
import tensorflow as tf
```



### Mean

주어진 값의 (가중) mean을 계산

instance의 argument에 loss값을 주면 mean을 구해서 cost를 computes 한 후 자신에게 누적한다.

```python
from tensorflow.keras.metrics import Mean
cost = Mean()
cost(loss)
# loss == computed loss values 
```

$$
(x_{n}\theta_n ,\ x_{n-1}\theta_{n-1} ,\ ... ,\ x_{1}\theta_{1} ,\ \theta_{0})
$$

 값 theta에 대해서 가중치 weight를 곱한 모든 value에 대해서 mean을 계산한다.

ex) 

>  value = [1, 3, 5, 7]   	mean == 4
>
>  but, if weight = [1, 1, 0, 0]	than	mean == 2



#### .result()

Mean의 instance에 누적된 cost값을 return하는 function

```python
tmp = cost(loss).result()
```



- 이전에는 `.result().numpy()` 해서 result를 호출했지만, 이제는 이러지 않아도 됨.

  그냥 `.result()`를 사용할 것



### CategoricalAccuracy

method computes accuracy

instance의 argument에 labels, predictions를 주면 accuracy을 computes 한 후 자신에게 누적한다.



### SparseCategoricalAccuracy

CategoricalAccuracy와 동작은 같다.

단, argument는 one-hot encoding 된 data이어야 한다.

```python
from tensorflow.keras.metrics import SparseCategoricalAccuracy
acc = SparseCategoricalAccuracy()
acc(labels, predictions)
```





#### .result()

SparseCategoricalAccuracy()의 instance에 누적된 accuracy  값을 return하는  method

```python
acc(labels, predictions).result()
```

