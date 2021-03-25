# sklearn

Scikit_learn라이브러리는 머신 러닝 라이브러리중 하나로, classification, Regression, Clustering, Decision tree 등의 머신러닝 알고리즘을 제공하고 Scaler,  split과 같은 데이터 전처리 및 분류 알고리즘도 제공한다.



## 1. 전처리

전처리란? 

데이터를 제거 또는 수정하여 최대한 소스 데이터의 정확성을 높히는 것을 말한다.

뿐만 아니라 중요성이 현저히 낮은 데이터를 과도하게 많이 포함한 경우 이들을 적절히 축소 조절하여 관리와 사용에 용이한 형태로 변경시켜 주기도 한다.

### 1. Scaler

데이터 전처리 모듈. (수치형 데이터에만 적용한다.)

**사용하는 경우**

1. 데이터 분석간 변수들의 단위 차이로 인해 숫자의 스케일이 크게 달라지는 경우
2. 신경망 학습간 데이터셋의 값이 들쑥날쑥하거나 매우 큰 경우 cost값이 발산해서 정상적인 학습이 이루어지지 않는 경우

`from sklearn.preprocessing import 스케일러`

**sklearn에서 제공하는 기본 스케일러 종류 4가지**

1. StandardScaler
2. MinMaxScaler
3. RobushScaler
4. Normalizer



#### 1. StandardScaler

데이터를 평균 0, 분산 1로 조정해주는 Scaler

```python
from sklearn.preprocessing import StandardScaler
```



- 수치형 데이터를 전처리하고 입력 데이터 통합

  `x_num`에 수치형 데이터 컬럼들이 할당되어있다고 가정할 때

  ```python
  scaler = StandardScaler()	#스케일러 생성
  scaler.fit(x_num)			
  x_scaled = scaler.transform(x_num)
  
  # 메소드체이닝을 사용하면 아래처럼 연달아 호출할 수 있다.
  x_scaled = scaler.fit(x_num).transform(x_num)
  # 스케일러의 transform를 사용하면 x_scaled는 numpy형으로 바뀌게 된다.
  # 그렇기 때문에 데이터를 다시 DataFrame으로 바꿔준다. (pandas사용)
  x_scaled = pd.DataFrame(data=x_scaled, index = x_num.index, columns = x_num.columns)
  # index와 columns는 x_num의 것을 그대로 가져와준다.
  ```
  

**fit()** : 데이터 변환을 학습, 학습용 데이터에만 적용
**transform()** : 실제 데이터의 스케일을 조정, 학습용 데이터와 테스트 데이터에 적용



#### 2. MinMaxScaler



### 2. Principal Component Analysis, PCA

주성분 분석

데이터의 **분산(variance)**을 최대한 보존하면서 서로 직교하는 새 기저(축)를 찾아, 고차원 공간의 표본들을 선형 연관성이 없는 저차원 공간으로 변환하는 기법.

![](http://i.imgur.com/Uv2dlsH.gif)

> 여기에서 핑크색 표시가 돼 있는 사선축이 원 데이터의 분산을 최대한 보존하는(=데이터가 가장 많이 흩뿌려져 있는) 새 기저임. PCA의 목적은 바로 이런 축을 찾는 데 있다.

이를 통해 데이터를 축소해서 (C, N) 크기의 데이터를 (M, N)크기로 축소했다고 가정했을 때 그 동작은 더 중요한 데이터가 빠른 순번에 위치하게 만드는 것이고, 늦은 순번의 데이터는 제외하는 방식으로 축소를 하는 것이다.



**전처리 과정**

```python
from sklearn.decomposition import PCA
```

```python
pca = PCA()
pca.fit(x_train)
plt.plot(range(1, len(pca.explained_variance_) + 1), pca.explained_variance_)
plt.grid()
```

> `pca.explained_variance_`: 모든 컬럼에 대한 분산. 0이 되면 원본의 variance가 전부 표현이 된다는 의미, 높을수록 원본의 variance가 표현이 안된다는 의미
>
> `len(pca.explained_variance_)`: 컬럼의 갯수(차원으로 이해해도 된다.)

![](data:image/png;base64,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)

예제로 사용된 데이터에서, 10정도의 차원만 되어도 원본 분산의 대부분이 표현이 됨을 볼 수 있다.

 ```python
pca = PCA(n_components=10)
pca.fit(x_train)
 ```

> `n_components`: 구성요소(차원)의 갯수를 결정한다.
>
> 다시fit을 진행한다.



---

## 2. split

데이터를  학습 데이터와 테스트 데이터로 분류할때 사용

### 1. train_test_split

```python
from sklearn.model_selection import train_test_split
```

디폴트로 shuffle은 Ture로 적용됨(앞의 데이터와 뒤의 데이터를 순서대로 나눠서 분류해야 할 땐 shuffle을 False로 할당해줘야함)



- x, y의 train데이터와 test데이터 분류

  ```python
  x_train, x_test, y_train, y_test = train_test_split(x, y, test_size = 0.3, random_state = 1)
  ```

  > `test_size = 0.3` : 30%는 test data로, 70%는 training data로 사용됨
  >
  > `random_state` : test data와 training data를 나누는 seed (값이 크게 중요하지 않음)
  >
  > x와 y는 이미 코드에서 입력값과 출력값으로 정의가 되어있어야 한다.



---

## 3. Classification

### 1. Logistic Regression

범주형 변수를 예측하는 모델로, 두 가지의 결과가 나오는 분류 문제에서 각각의 결과가 나오는  확률을 구할 수 있다. 입력 데이터가 주어졌을 때 해당 데이터의 결과가 특정 분류로 나뉘기 때문에 일종의 classification 기법으로 본다.

```python
from sklearn.linear_model import LogisticRegression
```



- 입력 데이터와 출력 데이터를 매개변수로 모델에 학습시키기

```python
model_lr = LogisticRegression()
model_lr.fit(x_train, y_train)
# 이렇게만 해도 학습이 된 모델 완성됨
```

> `fit`: 매개변수를 활용해 학습하는 함수
>
> final function value: 모델이 얻은 최종 Logistc 함수값
>
> - iteration이 부족해 학습이 잘 되지 않았다는 문구가 뜨면 매개변수로 max_iter에 값을 할당해서 반복 횟수를 지정할 수 있다.
>
> - verbose를 1로 할당하면 학습하는 과정을 볼 수 있다. (2로 할당하면 더 많이 보여줌)
>
> ```python
> model_lr = LogisticRegression(max_iter = 1000, verbose = 1)
> model_lr.fit(x_train, y_train)
> ```





## 4. Regression





## 5. Report

학습 결과를 평가하는 알고리즘

### 1. Classification 평가

```python
from sklearn.metrics import classification_report
```



- predict함수를 사용

  ```python
  pred = model_lr.predict(x_test)
  print(classification_report(y_test, pred))
  ```

  > predict 함수의 매개변수로 입력 test data를 사용하면 예측값을 반환
  >
  > classification_report를 통해 정답 test data와 예측된 test data를 비교 

  precision, recall, f1-score 에 대한 분류 평가지표를 전부 계산해서 보여주고, 종합해서 나오는 accuracy도 확인할 수 있다.

  (support는 데이터의 개수를 의미함)



## 6. Analysis

### 1. Curve

모델의 학습 결과를 심화 분석할때 사용하는 알고리즘으로, 평가 분류의 곡선을 확인할 수 있다.

`plot_precision_recall_curve`

- Precision-Recall Curve 확인

  Precision과 Recall의 관계를 확인함으로서 Recall을 유지하면서 Precision을 얼만큼 끌어 올릴 수 있는지를 확인할 수 있다. (Recall에 비해 Precision가 높을수록 좋다.)

  `plot_precision_recall_curve`  모듈 사용

  ```python
  from sklearn.metrics import plot_precision_recall_curve
  
  fig = plt.figure()
  ax = fig.gca() # ax 그래프 상 위에 두 커브를 겹쳐서 그리기
  plot_precision_recall_curve(model_lr, x_test, y_test, ax=ax)
  # model_lr 라는 모델의 Precision-Recall 커브
  plot_precision_recall_curve(model_xgb, x_test, y_test, ax=ax)
  # model_xgb 라는 모델 Precision-Recall 커브
  plt.show()
  ```




- ROC Curve

  Fales Positive Rate와 Ture Positive Rate를 비교하는 그래프

  Fales Positive Rate를 낮게 유지하면서 Ture Positive Rate가 1에 얼마나 빨리 도달하는지를 확인할 수 있다. (Fales Positive Rate에 비해 Ture Positive Rate가 빨리 1에 도달할수록 좋다.)

  `plot_roc_curve` 모듈 사용

  ```python
  from sklearn.metrics import plot_roc_curve
  
  fig = plt.figure()
  ax = fig.gca()
  plot_roc_curve(model_lr, x_test, y_test, ax=ax)
  # model_lr 라는 모델의 ROC 커브
  plot_roc_curve(model_xgb, x_test, y_test, ax=ax)
  # model_xgbr 라는 모델의 ROC 커브
  plt.show()
  ```



### 2. Coefficient

모델의 학습 결과를 심화 분석할때 사용하는 알고리즘으로, 각 모델의 계수를 파악하여 상관성을 파악할 수 있다.

`coef_`

- classes_ 속성

  학습 모델에 사용된 정답 값의 정보를 보여준다.

  `모델명.classes_`

  ```python
  print(model_lr.classes_)
  ```

  > model_lr이라는 학습 모델에 사용된 정답 데이터가 범주형 데이터고, 각 범주가 'H' 'L' 'M'일때 
  >
  > ['H' 'L' 'M'] 을 출력한다.

- shape 속성

  속성이 가리키고 있는 데이터의 모양을 보여준다.

  `모델명.coef_.shape`

  ```python
  print(model_lr.coef_.shape)
  ```

  > (3, 58) 라고 출력이 됐다면, 3은 정답 데이터의 범주의 개수, 58은 학습에 사용된 feature의 개수

  데이터의 모양을 알아야 그래프를 그릴 수 있다.

'H' 가 도출되도록 하는데 각feature에 대한 계수(영향 정도) 그래프를 그릴 때

> classes_ 속성과 shape 속성을 통해 'H'는 model_lr.coef_의 첫 번째 index에 위치하고 있음을 알 수 있다.

```python
fig = plt.figure(figsize=(15, 8))  # 그래프가 너무 커서 그래프 창을 키워야 한다.
plt.bar(x.columns, model_lr.coef_[0, :]) # [0, :] == [첫 번째 index = 'H', 전체 feature]
plt.xticks(rotation=90)  #이름이 겹쳐보이니까 90도 돌린다.
plt.show()
```

 

그래프를 정렬하기 위해선 새 변수에 데이터를 할당하고, 정렬을 진행해야 한다.

```python
model_coef = pd.DataFrame(data=model_lr.coef_[0], index=x.columns, columns=['Model Coefficient'])
# 모든 컬럼을 Model Coefficient라는 컬럼의 범주로 간주하여 변수에 할당
model_coef.sort_values(by='Model Coefficient', ascending=False, inplace=True)
# 정렬 진행 ascending의 디폴드는 True로, 오름차순이다. inplace를 True로 하면 정렬된 자체 DataFrame을 model_coef에 다시 저장한다.
plt.bar(model_coef.index, model_coef['Model Coefficient'])
plt.xticks(rotation=90)
plt.grid()
plt.show()
```

