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



