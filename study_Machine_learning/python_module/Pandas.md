# Pandas

Pandas는 numpy를 기반으로, 보다 고차원적인 데이터 처리를 돕는 라이브러리이다. 

동일한 데이터를 가진 Series를 기본으로 하며, 이를 여러개 묶어 사용하는 DataFrame을 사용하여 표 형태로 된 자료를 다룬다. (pandas는 dataframe을 주로 다루기 위한 라이브러리)

- Series

  pandas에서 제공하는 데이터타입으로, index가 있는 1차원 배열이라고 생각하면 좋다. 문자, 논리형, 숫자 모든 데이터타입이 들어갈 수 있다. dataframe의 한 컬럼, 한 컬럼이 series이다.

```python
import pandas as pd
```



## 메소드

- read_csv

  파일 읽는 방법

  ```python
  변수명 = dp.read_csv('파일 위치\파일 이름')
  ```

  > 변수에 파일을 할당한다.
  >
  > colap에서는 파일 이름만 입력해도 됨

- columns

  변수에 할당된 파일에 속한 컬럼을 반환한다.

  ```python
  print(df.columns)
  ```

  > `df`라는 변수에 csv파일을 할당했다고 가정



#### 1. DataFrame의 각 컬럼 분석하기

`df`라는 변수에 csv파일을 할당했다고 가정

```python
df = pd.read_csv('~~~')
```

- 데이터가 광범위할때, 출력을 하고 중간이 `...`으로 생략되어 출력된다. 이러한 데이터도 다 보기 위해서 설정값을 미리 호출해야 한다.

  1.  모든 열을 다 보고자 할 때.

     `pd.set_option('display.max_columns', None)`

  2. 모든 행을 다 보고자 할 때.

     `pd.set_option('display.max_rows', None)`
  
- 데이터 셋의 각 칼럼을 보고자 할땐 `df.cloumns`를 통해 알 수 있다.

  ```python
  print(df.cloumns)
  ```

  

##### 1. head()

dataframe의 상위 n개를 반환한다.

```python
df.head()
print(df.head())

n = 10
foo = df.head(n)
print(foo)
```

> 디폴트 head()는 5개를 보여줌
>
> n이 음수면 뒤의 -n개 까지 보여준다.

##### 2. info()

데이터의 information을 반환한다.

```python
print(df.info())
```

##### 3. describe()

수치형 데이터들의 통계를 반환한다.

```python
print(df.describe())
```



##### 4. value_counts()

특정 칼럼의 정보를 알 수 있다.(범주형, 수치형 상관 없음)

`df['컬럼명'].value_counts()`

```python
print(df['gender'].value_counts())
```



##### 5. corr()

각 칼럼의 correlation을 수치화 할 수 있다.

```python
print(df.corr())
```







### 2. 데이터 전처리

#### 1. concat()

dataframe을 물리적으로 이어 붙여주는 함수로, 매개변수 axis에 따라서 해당 축의 동일한 자료형(또는 key)끼리 묶어주는 동작을 한다.

```python
X = pd.concat([x_scaled, x_cat], axis = 1)
```



#### 2. drop()

Multicollinearity을 예방하기 위해 서로 값이 완전히 반대인 컬럼들을 drop해줘야 한다.

```python
df.drop(['컬럼명1', '컬럼명2'], axis=1, inplace=True)
```

> ex) 컬럼명1 =  x, 	컬럼명2 = -x의 값을 가지고 있으면 두 컬럼 중 하나는  drop해줘야 한다.

- **Multicollinearity**(다중공선성): 일반적으로 회귀 분석에서 발생하며, 분석에서 사용된 모델 데이터의 일부 컬럼이 다른 컬럼과 상관 정도가 높아, 데이터 분석 시 위험한 영향을 미치는 현상  



#### 3. one - hot encoding

get_dummies 함수를 활용하면 데이터를 one - hot벡터로 바꿔줄 수 있다.

범주형 데이터만 one - hot encoding 해줘야 한다.

`변수명 = pd.get_dummies( df, columns=['컬럼명1', '컬럼명2' ...  '컬럼명n'], drop_first=True)`

- drop_first=True로 하는 이유: Multicollinearity를 피하기 위해


변수명이 x라고 가정할 때, x에는 DataFrame의 모든 데이터가 할당되며, 이 중 get_dummies에 명시된 데이터에만 one - hot encoding이 적용되어 할당된다.

- 만약 할당하고 싶지 않은 컬럼이 있다면 df.drop을 사용해서 명시해준다.

  `x = pd.get_dummies( df.drop(['드롭컬럼명1, 드롭컬럼명2'], axis = 1), columns=['컬럼명1', '컬럼명2' ...  '컬럼명n'], drop_first=True)`

  - axis = 1을 해 줘야만 컬럼에서 drop을 한다. (axis = 0 을 하면 row에서 찾다가 drop을 안해버림)

  ```python
x = pd.get_dummies(df.drop(['ParentschoolSatisfaction', 'Class', 'Class_value'], axis=1),
                   columns=['gender', 'NationalITy', 'PlaceofBirth',
                            'StageID', 'GradeID','SectionID', 'Topic',
                            'Semester', 'Relation', 'ParentAnsweringSurvey',
                            'StudentAbsenceDays'],
                   drop_first=True)
  ```

  

