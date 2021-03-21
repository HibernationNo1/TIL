# classification

### 1. Logistic Regression

#### 1. 모델 정의

범주형 변수를 예측하는 모델로, 두 가지의 결과가 나오는 분류 문제에서 각각의 결과가 나오는  확률을 구할 수 있다. 입력 데이터가 주어졌을 때 해당 데이터의 결과가 특정 분류로 나뉘기 때문에 일종의 **classification** 기법으로 본다.

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



#### 2. 모델 학습 결과 평가

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



---

### 2. XGboost Classification

#### 1. 모델 정의

XGboost Classification는 약한 분류기를 세트로 묶어서 정확도를 예측하는 기법이다. 10원, 50원, 100원, 500원이 섞인 주머니를 여러 크기의 체를 가지고 조합해서 그것을 분류하는 과정으로 생각하면 된다.

kaggle에서는 거의 XGboost를 사용하고 있다.

```python
from xgboost import XGBClassifier
```



- 입력 데이터와 출력 데이터를 매개변수로 모델에 학습시키기

  ```python
  model_xgb = XGBClassifier()
  model_xgb.fit(x_train, y_train)
  ```



#### 2. 모델 학습 결과 평가

```python
from sklearn.metrics import classification_report
pred = model_xgb.predict(x_test)
print(classification_report(y_test, pred))
```



#### 3. 학습 결과 분석

모델로부터 학습된 결과로부터 특징의 중요도를 확인한다.

XGBClassifier라이브러리의 feature_importances_함수를 사용한다.

```python
plt.bar(x.columns, model_xgb.feature_importances_)
plt.xticks(rotation=90)
plt.show()
```

> bar함수를 사용해 막대그래프를 사용, x축엔 x.columns, y축엔 model_xgb.feature_importances_를 사용
>
> xticks함수의 rotation을 사용해 x축의 이름을 90도 돌려서 볼 수 있다.