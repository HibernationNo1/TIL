# sklearn

## sklearn.model_selection

data set을 train data와 test data를 split하는 module

교차 validation split 및 evaluation 기능도 있다.





### train_test_split

```python
from sklearn.model_selection import train_test_split
```

split between training data and test data

```python
x_train, x_test, y_train, y_test = train_test_split(feature_data, label_data, test_size = )
```

- `test_size = ` decision of ratio between training data and test data

  `test_size = 0.3` == test_data 30%, training data 70%



## sklearn.preprocessing

data preprocessing module



### StandardScaler

for standardization

make mean == 0, std == 0
$$
x_i' = \frac{x_i - mean(x)}{stdec(x)}
$$

```python
from sklearn.preprocessing import StandardScaler
scaler = StandardScaler()
```



#### fit_transform()

```python
data_scaled = scaler.fit_transform(data_set)
```

return as ndarray



### MinMaxScaler

for Normalization

reduce the range of value from 0 to 1
$$
x_i' = \frac{x_i - min(x)}{max(x) - min(x)}
$$

```python
from sklearn.preprocessing import MinMaxScaler
scaler = MinMaxScaler()
data_scaled = scaler.fit_transform(data_set)
```

