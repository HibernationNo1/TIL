# sklearn

## sklearn.model_selection

data set을 train data와 test data를 split하는 module

교차 validation split 및 evaluation 기능도 있다.





### train_test_split

데이터 분할 함수

```python
from sklearn.model_selection import train_test_split
```

split between training data and test data

```python
from sklearn.model_selection import train_test_split

# 예시 데이터
X = [[1, 2], [3, 4], [5, 6], [7, 8]]
y = [0, 1, 0, 1]

# 학습 세트와 테스트 세트로 분할
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=42)
print("X_train:", X_train)
print("X_test:", X_test)
print("y_train:", y_train)
print("y_test:", y_test)
```

- `test_size = ` decision of ratio between training data and test data

  `test_size = 0.3` == test_data 30%, training data 70%



### StratifiedKFold

Stratified K-Fold 교차 검증을 수행할 때 사용하는 모듈로, 데이터셋을 여러 개의 폴드(fold)로 분할하여 교차 검증을 수행하되, 각 폴드가 원본 데이터셋의 클래스 비율을 유지하도록 분할하는 기능을 제공한다.

```python
from sklearn.model_selection import StratifiedKFold
import numpy as np

# 예제 데이터: 특성 X와 레이블 y
X = np.array([[1], [2], [3], [4], [5], [6], [7], [8], [9], [10]])
y = np.array([0,   0,   0,   1,   1,   1,   1,    1,    1,  1])  # 불균형 클래스 예시

# Stratified K-Fold 초기화 (여기서는 3개의 폴드로 분할)
skf = StratifiedKFold(n_splits=3)

# 각 폴드의 인덱스 생성 및 출력
for train_index, test_index in skf.split(X, y):
    print("TRAIN:", train_index, "TEST:", test_index)
    X_train, X_test = X[train_index], X[test_index]
    y_train, y_test = y[train_index], y[test_index]
```

- K-Fold란: 데이터셋을 K개의 균등한 부분(fold)으로 나누는 방법

  예를 들어, K=5이면 전체 데이터셋을 5개의 부분으로 나누어 각 폴드를 사용하여 여러 번 모델을 학습하고 평가하게 된다.

  K-Fold는 교차 검증과 결합하여 사용되며, 데이터셋을 효율적으로 활용하고 모델의 일반화 성능을 평가하는 데 중요한 역할

  - K-Fold 교차 검증

    K-Fold 교차 검증(K-Fold Cross Validation)은 K-Fold 방식을 통해 데이터를 K개로 나누어 모델을 학습하고 평가하는 기법이다.

    학습 데이터와 검증 데이터를 다르게 설정하여 여러 번 평가를 수행하는 방식으로, 전체 데이터셋을 최대한 활용하면서 모델의 성능을 평가할 수 있다.

- `n_splits` (default = 5): 폴드의 개수를 지정한다.

- `shuffle` (default = False):  True로 설정하면 데이터를 분할하기 전에 무작위로 섞는다.

- random_state : 데이터를 셔플할 때 사용하는 시드 값으로, shuffle=True인 경우에만 작동한다.

출력

```
TRAIN: [1 2 4 5 6 7 9] TEST: [0 3 8]
TRAIN: [0 2 3 5 6 8 9] TEST: [1 4 7]
TRAIN: [0 1 3 4 7 8 9] TEST: [2 5 6]
```







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

