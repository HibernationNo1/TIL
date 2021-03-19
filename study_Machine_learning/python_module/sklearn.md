# sklearn

Scikit_learn라이브러리는 머신 러닝 라이브러리중 하나로, classification, Regression, Clustering, Decision tree 등의 머신러닝 알고리즘을 제공하고 Scaler,  split과 같은 데이터 전처리 및 분류 알고리즘도 제공한다.





## 1. Scaler

데이터 전처리 모듈. (수치형 데이터에만 적용한다.)

- 전처리란? 

  데이터를 제거 또는 수정하여 최대한 소스 데이터의 정확성을 높히는 것을 말한다.

  뿐만 아니라 중요성이 현저히 낮은 데이터를 과도하게 많이 포함한 경우 이들을 적절히 축소 조절하여 관리와 사용에 용이한 형태로 변경시켜 주기도 한다.

**사용하는 경우**

1. 데이터 분석간 변수들의 단위 차이로 인해 숫자의 스케일이 크게 달라지는 경우
2. 신경망 학습간 데이터셋의 값이 들쑥날쑥하거나 매우 큰 경우 cost값이 발산해서 정상적인 학습이 이루어지지 않는 경우

`from sklearn.preprocessing import 스케일러`

**sklearn에서 제공하는 기본 스케일러 종류 4가지**

1. StandardScaler
2. MinMaxScaler
3. RobushScaler
4. Normalizer



### 1. StandardScaler

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



### 2. MinMaxScaler



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
plt.bar(X.columns, model_lr.coef_[0, :]) # [0, :] == [첫 번째 index = 'H', 전체 feature]
plt.xticks(rotation=90)  #이름이 겹쳐보이니까 90도 돌린다.
plt.show()
```