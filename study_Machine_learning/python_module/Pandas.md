# Pandas

Pandas는 numpy를 기반으로, 보다 고차원적인 데이터 처리를 돕는 라이브러리이다. 

동일한 데이터를 가진 Series를 기본으로 하며, 이를 여러개 묶어 사용하는 DataFrame을 사용하여 표 형태로 된 자료를 다룬다. (pandas는 dataframe을 주로 다루기 위한 라이브러리)

- Series

  pandas에서 제공하는 데이터타입으로, index가 있는 1차원 배열이라고 생각하면 좋다. 문자, 논리형, 숫자 모든 데이터타입이 들어갈 수 있다. dataframe의 한 컬럼, 한 컬럼이 series이다.

```python
import pandas as pd
```



## 메소드

##### 1. DataFrame 생성

```python
import pandas as pd
import numpy as np

data = [[100, 25, 10],
        [200, 20, 11],
        [300, 15, 12],
        [350, 16, 13],
        [320, 17, 12]]
df = pd.DataFrame(data, 
                  index = ['1월', '2월', '3월', '4월', '5월'],
                  columns = ['매출액', '영업이익', '순이익'] )
print(df)
```

```
    매출액  영업이익  순이익
1월  100    25   10
2월  200    20   11
3월  300    15   12
4월  350    16   13
5월  320    17   12
```



##### 2. read

- dp.read_csv

  csv파일 읽는 방법

  ```python
  변수명 = dp.read_csv('파일 위치\파일 이름')
  ```

  > 변수에 파일을 할당한다.
  >
  > colap에서는 파일 이름만 입력해도 됨

- pd.read_sql_query

  sql파일에서 데이터를 가져오는 방법 

  ```python
  conn = sqlite3.connect('database.sqlite')
  
  df_country = pd.read_sql_query('SELECT * from Country', conn)
  df_league = pd.read_sql_query('SELECT * from League', conn)
  df_match = pd.read_sql_query('SELECT * from Match', conn)
  ```

- pd.read_html

  웹 페이지도 가져올 수 있다.

  ```python
  state_code = pd.read_html('https://www.infoplease.com/us/postal-information/state-abbreviations-and-state-postal-codes')[0]
  ```



---

### 1. 적용 함수

##### 1. set_option()

데이터가 광범위할때, 출력을 하고 중간이 `...`으로 생략되어 출력된다. 이러한 데이터도 다 보기 위해서 설정값을 미리 호출해야 한다.

1. 모든 열을 다 보고자 할 때.

   `pd.set_option('display.max_columns', None)`

2. 모든 행을 다 보고자 할 때.

   `pd.set_option('display.max_rows', None)`

   >None 대신 정수를 넣으면 그 정수만큼 보여줌



##### 2. 연산: apply() 

행 또는 열 또는 전체의 셀(=원소)에 원하는 연산을 지원한다.

- 데이터의 형식을 바꾸는 경우

  ```python
  df.apply(int)
  ```

  df안의 data 값들을 int로 바꾼다.

  반환 전 df는 dateframe이지만, 반환된 df는 series임.

- numpy의 연산을 적용하는 경우

  sqrt과 같이 단일 연산인 경우 전체에 적용

  min, max, average와 같이 집계되는 경우 사라질 축을 지정

  ```python
  df.apply(np.sqrt)
  df.apply(np.average, axis = 1)
  ```

- lambda 사용

  - 미리 정의할 함수를 사용할 경우

    `df.apply(lambda x: 함수명(매개변수1,매개변수2),axis)`

    ```python
    def col(x, y, z):
        return (x+y)/z
    df_new = df.apply(lambda x: col(x['foo'], x['bar'], x['baz']), axis = 1)
    ```

    > (x+y)/z이 적용되는 함수를 정의하고, lambda 를 통해 전달되는 각 컬럼의 값들에 대해 연산을 진행한다.

  - if문으로 사용할 경우

    `df.apply(lambda x: 함수명(매개변수) in 조건)`

    ```python
    data = df.loc[df['foo'].apply(lambda s: str(s) in ['one', 'two'])]
    ```

    > foo컬럼 안에 'one' 또는 'two'라는 데이터가 있으면 str형으로 변환. 없으면 pass
    >
    > loc[df['컬럼']] 을 통해 해당 컬럼의 모든 index에 apply적용



---

### 2. DataFrame의 각 컬럼 분석

`df`라는 변수에 데이터를 할당했다고 가정

```python
df = pd.read_csv('~~~')
```

##### 0. columns

변수에 할당된 파일에 속한 컬럼을 반환한다.

```python
print(df.columns)
```

> `df`라는 변수에 csv파일을 할당했다고 가정

- 특정 컬럼에 대한 정보를 볼 수 있다.

  ```python
  print(df_player_att['player_api_id'])
  ```

- 몇 번째에 어떤 컬럼이 위치하고 있는지도 알 수 있다.

  ```python
  print(df.columns[3])
  # 3 번째 컬럼명 출력
  
  print(df.columns[3:])
  # 3 번째 컬럼명부터 마지막 컬럼명까지 출력
  ```

- for문 활용

  ```python
  for col in df.columns:
      print(col)
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

특정 칼럼의 어떤 값이 몇개가 있는지 내림차순으로 반환한다.(범주형, 수치형 상관 없음)

`df['컬럼명'].value_counts()` 또는 `df.value_counts()`

```python
print(df['gender'].value_counts())
```



##### 5. corr()

각 칼럼의 correlation을 수치화 할 수 있다.

```python
print(df.corr())
```



##### 6. unique()

컬럼이 가지고 있는  유일한 값을 찾는 함수다.

`df['컬럼명'].unique()`

```python
pd['foo'].unique()
```

foo라는 컬럼 안에 존재하는 모든 경우의 수를 볼 수 있다고 생각하면 된다.



##### 7. loc[]

행(인덱스)에 접근하는 함수

`df.loc['index']` 또는 `df.loc[df['컬럼']]`

`df.loc['index']`: 해당 인덱스의 모든 columns data를 반환한다.

`df.loc[df['컬럼']]`: 해당 컬럼의 모든 indax를 반환한다.

```
    매출액  영업이익  순이익
1월  100    25   10
2월  200    20   11
3월  300    15   12
4월  350    16   13
5월  320    17   12
```

```python
print(df.loc['2월'])
print(df.loc[['2월']])
```

```
매출액     200
영업이익     20
순이익      11
Name: 2월, dtype: int64

    매출액  영업이익  순이익
2월  200    20   11
```



```python
print(df.loc[df['순이익'] == 12])
```

> 순이익이 12인 data가 포함된 dataframe을 출력

```
    매출액  영업이익  순이익
3월  300    15   12
5월  320    17   12
```

```python
print(df.loc[df['순이익'] == 12]['매출액'])
```

> 순이익이 12인 data가 포함된 dataframe에서 매출액만 집계해서 출력

```
3월    300
5월    320
Name: 매출액, dtype: int64
```



---

### 3. 결측 분석

##### 1. isin()

DataFrame에서 list의 값들을 포함하고 있는 모든 행(colonm)들을 골라낼 때 주로 쓰인다. 

```python
df = DataFrame({'A': [1, 2, 3], 'B': ['a', 'b', 'f']})
df.isin([1, 3, 12, 'a'])
```

출력

```
      A      B
0   True   True
1  False  False
2   True  False
```

포함하고 있으면 True, 아니면 False를 반환한다.

##### 2. isna()

DataFrame에서 수치형 값이 비어있는지 확인하는 함수다.

```python
df.isna()
```

비어 있으면 True, 아니면 False를 반환한다.

여기에 .sum()을 사용하면 빈 데이터가 몇개있는지 알수 있다.

```python
df.isna().sum()
```

- 여러 dataframe에 대해서 비교하며 사용하는 법

  ```python
  for c, num in zip(df_match.columns, df_match.isna().sum()):
  	print(c, num)
  ```

  zip함수를 사용해 c에는 df_match.columns을, num에는 df_match.isna().sum()을 할당해서 

  df_match의 각 컬럼당 몇 개의 df_match가 비어있는 데이터인지를 볼 수 있다.

- 해당 dataframe에 빈 데이터가 있는지 확인하는 법

  아래 dropna()를 사용한다.



---

### 4. 데이터 전처리

##### 1. concat()

dataframe을 물리적으로 이어 붙여주는 함수로, 매개변수 axis에 따라서 해당 축의 동일한 자료형(또는 key)끼리 묶어주는 동작을 한다.

```python
x = pd.concat(['x_scaled', 'x_cat'], axis = 1)
```



##### 2. drop()

사용 안하는 데이터를 버릴때 사용한다. 

또는 Multicollinearity을 예방하기 위해 서로 값이 완전히 반대인 컬럼들을 drop해줘야 한다.

```python
df.drop(['컬럼명1', '컬럼명2'], axis=1, inplace=True)
```

> ex) 컬럼명1 =  x, 	컬럼명2 = -x의 값을 가지고 있으면 두 컬럼 중 하나는  drop해줘야 한다.
>
> inplace=True가 되어야 drop된 데이터를 뺀 나머지가 다시 df에 할당된다.

- **Multicollinearity**(다중공선성): 일반적으로 회귀 분석에서 발생하며, 분석에서 사용된 모델 데이터의 일부 컬럼이 다른 컬럼과 상관 정도가 높아, 데이터 분석 시 위험한 영향을 미치는 현상  

```python
x_num = df.drop(['정답으로 쓸 데이터 컬럼'] + col_cats, axis=1)
```

> 예시)범주형 데이터와 수치형 데이터가 있는 DataFrame에서 수치형 데이터만 분리하고자 할 때 (col_cats는 범주형 데이터list)
>
> 위와 같은 식으로 df에서 정답 데이터와 범주형 데이터를 drop해서 할당해도 된다. 



##### 3. dropna()

NaN을 가진 데이터를 제거한 df를 반환한다.

```python
df.dropna()
```

df자체에 NaN을 가진 데이터를 제거된 df가 저장되는 것이 아니라, 그냥 단순이 반환하는 것임.

```python
df.dropna(inplace = True)
```

> dropna()가 적용된 df가 다시 자기 자신에게 할당됨



##### 4. one - hot encoding

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

- list컨테이너 활용

  > 'Class'라는 단어가 포함되어있는 컬럼이 범주형 컬럼이라고 가정했을 때

  ```python
  col_cats = list(filter(lambda s: s.find('Class') >= 0, df.columns))
  df_cats = pd.get_dummies(df[col_cats], drop_first=True)
  ```

  > filter함수를 사용. lambda에 df.columns가 할당되어 각 컬럼에 'Class'라는 단어가 포함되었는지 찾는다. find가 1이 반환돠는 컬럼들만 list화
  >
  > 

---

### 5. 그룹화

#### 1. groupby()

데이터를 그룹별로 나누어 연산을 통해 정보를 얻는 방법을 사용할 수 있다.

그룹별로 min(), max(), sum(), mean() 등의 연산을 할 수 있다.

1. 컬럼 1개에 대한 그룹별 집계

   `df이름.groupby(['컬럼명A']).연산`

   ```python
   print(df_player_att.groupby(['gk_positioning']).mean())
   ```

   > 컬럼명A가 가지고 있는 각 값중 중복되는 값을 그룹화 후 해당 값을 가진 모든 row에 대해서 각 컬럼당 평균 연산을 진행하여 반환한다. 
   >
   > 평균연산이 가능한 컬럼들에 대해서만 연산이 이루어진다.

   - as_index=False 을 매개변수로 추가하면 각 그룹을 index로 표시해준다.

     ```python
     df_player_att.groupby(['gk_positioning'], as_index=False).mean()
     ```



2. 컬럼 2개에 대한 그룹별 집계

   `df이름.groupby(['컬럼명A', '컬럼명B']).연산`

   ```python
   df_player_att.groupby(['gk_kicking', 'gk_positioning'], as_index=False).mean()
   ```

   > 컬럼명A에 대한 각 값중 중복되는 값을 그룹화 후 또 그 안에서 컬럼명B에 대한 각 값을 그룹화 하여 해당 값을 가진 모든 row에 대해서 각 컬럼당 평균 연산을 진행하여 반환한다. 

   

3. 컬럼A에 대한 컬럼 B의 집계(컬럼A 포함)

   `df이름.groupby(['컬럼A'])['컬럼B'].연산`

   ```python
   df_player_att.groupby(['gk_positioning'], as_index=False)['gk_kicking'].mean()
   ```

   > 컬럼A에 대한 각 값중 중복되는 값을 그룹화 후 해당 값을 가진 모든 row에 대해서 컬럼B의 평균 연산을 진행하여 반환한다. 
   >
   > print로 보면 각 index에는 그룹화 된 컬럼A의 값도 포함되어 있지만 없다고 봐야한다.

   

4. 컬럼A에 대한 컬럼 B의 집계(컬럼 B만 반환)

   `df이름.groupby(['컬럼A'], as_index=False).연산['컬럼B']`

   ```python
   df_player_att.groupby(['gk_positioning'], as_index=False).mean()['gk_kicking']
   ```

   > 위의 3번과 동일한 동작을 하지만 print를 해도 dataframe에 컬럼A의 값이 포함되어있지 않다. (컬럼B의 값만 줌)
   >
   > 사실 위 3번과 같은 동작이다. 단지 print를 할 때 값이 다르게 보인다는 것일 뿐.
   >
   > 여기서 as_index=False이 없이 `df이름.groupby(['컬럼A']).연산['컬럼B']`을 해도 무방하다.

   ```
   # as_index=False 포함할때 출력
   0        60.142857
   1        69.380952
   2        69.285714
   3        71.133333
   4        70.200000
              ...
   11055    51.909091
   11056    59.000000
   11057    58.000000
   11058    56.444444
   11059    58.000000
   Name: overall_rating, Length: 11060, dtype: float64
   
   # as_index=False 미포함할때 출력
   		player_api_id
   2625      60.142857
   2752      69.380952
   2768      69.285714
   2770      71.133333
   2790      70.200000
               ...
   744907    51.909091
   746419    59.000000
   748432    58.000000
   750435    56.444444
   750584    58.000000
   Name: overall_rating, Length: 11060, dtype: float64
   # 여기서 왼쪽 2625부터 750584까지의 값은 없다고 봐도 된다.
   ```



#### 2. aggregate()

함수를 호출할때 사용하는 함수이다(?)

각 그룹별로 min, max, mean과 같은 라이브러리에 정의된 함수 외에 다른 연산을 하고 싶으면 해당 연산을 하는 함수를 따로 정의해준 후 aggregate()을 통해 내부로 호출해줘야 한다.

`df이름.groubpy('컬럼A').aggregate({'컬럼B : 함수'})`

```python
def most(x):
  return x.value_counts().index[0]
# x함수에서 각 값의 포함 횟수를 내림차순으로 정렬 한 것의 첫 번째: 가장 큰 값

def sqr(x):
    idff = abs(x.min()-x.max())
    return idff

team_map = df_team_att.groupby('team_api_id').aggregate(
    {
       'PlaySpeed': 'mean',   # 라이브러리 내부 함수
       'PlaySpeedClass': most,	# 직접 정의한 함수
       'PlayPassing': sqr
    }
)
```

> df_team_att이라는 DataFrame안의 team_api_id컬럼의 각 값을 그룹화 하고, 그룹화 된 값을 가진 컬럼 중 얻고하 하는 데이터를 가진 컬럼만 함수를 적용해서  team_map이라는 변수에  할당한다.
>
> 카테고리형 컬럼에서 가장 많이 등장하는 값을 찾으려면 위의 `most(x)`와 같은 함수를 선언 후 aggregate통해 호출해야 한다.
>
> aggregate통해 호출되는 함수가 라이브러리에 내부에 정의된 함수면 `컬럼: '함수'` 로 호출하고, 직접 정의한 함수면 `컬럼: 함수` 로 호출한다

- aggregate()내부에서 함수 정의

  lambda 함수를 활용

  ```python
  df['tmp'] = df[['foo', 'bar']].aggregate(lambda x: 0 if x[0] > x[1] else 1 if x[0] == x[1] else 2, axis=1)
  ```

  > `0 if x[0] > x[1] else 1 if x[0] == x[1] else 2` 3항 연산자
  >
  > lambda 안에 ['foo', 'bar'] 가 할당된다.
  >
  > foo > bar 이면 0, 또는 foo == bar 이면 1, 그 이외에는 2 를 의미한다.
  >
  > aggregate에서 lambda를 통해 컬럼을 비교하거나 연산을 진행하려면 axis에 값을 할당해서 방향을 잡아줘야 한다.(디폴트 0)





---

### 6. mapping

##### 1. map()

DataFrame 1에 컬럼A가 있고 DataFrame 2에 컬럼B가 있다고 가정했을 때, map(컬럼B)을 통해 컬럼A의 각각의 row에 컬럼B의 각각의 row값을 할당할 수 있다.

`DataFrame1['컬럼A'].map(DataFrame2['컬럼B'])`

- groupby 활용

  ```python
  df_match['home_player_1'].map(df_player_att.groupby(['player_api_id']).mean()['overall_rating'])
  ```

  > 컬럼 `player_api_id`의 각 값을 그룹화 하고 그에 대한 컬럼`overall_rating`값의 평균을 구한 다음 컬럼`home_player_1`에 할당

- dropna().apply() 활용

  ```python
  df_match['home_player_1'].dropna().apply(int).map(df_player_att.groupby(['player_api_id']).mean()['overall_rating'])
  ```

  > 컬럼`home_player_1`안의 빈 데이터를 삭제하고, 남은 데이터를 전부int형으로 바꿔 준 다음 mapping

- isna().sum() 활용

  ```python
  print(df_match['home_player_1'].dropna().apply(int).map(df_player_att.groupby(['player_api_id']).mean()['overall_rating']).isna().sum())
  ```

  > mapping 후 두 컬럼의 크기차이로 인해 빈 데이터가 발생하지 않았는지 확인하는 방법. 0이 출력되면 깔끔하게 컬럼이 가득 찬 것이다.

---

### 7. DataFrame구조

##### 1. index

각 row의 이름을 저장하는 객체이다.

```python
print(df.index)
```

> df의 row 개수를 알 수 있다.

```python
print(df.index.name)
```

> None이 출력된다. row를 나타내는 열 자체에는 이름이 없기 때문이다.

```python
df.index.name = 'foo'
print(df.index.name)
```

이런 식으로 인덱스에 이름을 할당해줄 수 있다.(이름이 할당되기 전에는 None임)



###### 1. set_index()

df를 먼저 불러온 후에, 특정 열을 인텍스로 설정할때 사용된다.

```python
set_index('이름')
```

> 그 전에는 그냥 1, 2, 3...과 같은 순서가 index였다면, 이제부터는 이름이 index가 되는 것이다.

```python
set_index(['foo','bar'])
```

인덱스가 다수가 될 수 있다. 이를 멀티인덱스라고 한다.



###### 2. reset_index()

인덱스를 다시 처음부터 재배열 해주는 함수다.

```
df == 
	매출액  영업이익  순이익
1월  100    25   10
2월  200    20   11
3월  300    15   12
4월  350    16   13
5월  320    17   12
```

여기서 print(df.reset_index())를 보면

```
[Output]
	index 매출액  영업이익  순이익
0	1월   100    25   10
1	2월   200    20   11
2	3월   300    15   12
3	4월   350    16   13
4	5월   320    17   12
```

이름이 없던 인덱스에 index라는 이름이 생기고 첫 번째 컬럼으로 자동 할당된 것을 볼 수 있다.



##### 2.  pivot_table()

pivot할 데이터 프레임, 인덱스로 사용할 컬럼 , 컬럼으로 사용할 컬럼, 데이터로 사용할 컬럼 을 매개변수로 가지며 각 매개변수를 속성으로 가진 DataFrame을 만들어낸다.

```
	월    매출액  영업이익  순이익
0	1월   100    25   10
1	2월   200    20   11
2	3월   300    15   12
3	4월   350    16   13
4	5월   320    17   12
```

```python
df_new = pd.pivot_table(df, index = '월', columns = '영업이익', values = '매출액')
print(df_new)
```

```python
영업이익     15     16     17     20     25
월
1월      NaN    NaN    NaN    NaN  100.0
2월      NaN    NaN    NaN  200.0    NaN
3월    300.0    NaN    NaN    NaN    NaN
4월      NaN  350.0    NaN    NaN    NaN
5월      NaN    NaN  320.0    NaN    NaN
```

> df == pivot할 데이터 프레임
>
> index == 인덱스로 사용할 컬럼
>
> columns == 컬럼으로 사용할 컬럼
>
> values == 데이터로 사용할 컬럼
>
> 여기에 aggfunc에 'mean' 등과 같은 기본연산 함수를 할당하면 각 데이터에 연삭이 적용된다.



##### 3. rename()

컬럼의 이름을 재정의할 수 있다.

`rename({'old컬럼1': 'new컬럼1', 'old컬럼2': 'new컬럼2'}, axis=1)`

```python
df.rename({'월': '기간', '매출액': '매애출액'}, axis=1, inplace=True)
```

```
   기간  매애출액  영업이익  순이익
0  1월   100    25   10
1  2월   200    20   11
2  3월   300    15   12
3  4월   350    16   13
4  5월   320    17   12
```

> 위의 예시 df에 적용한 것

---

### x. 그외

##### 

- **copy()**

  말 그대로 복사하는 함수

  `df.copy()`

  df를 복사해서 반환

  ```python
  df = df_init[['foo', 'bar']].copy()
  ```

  > df에 'foo', 'bar' 컬럼을 가진 DataFrame 할당

- **for문 활용**

  ```python
  for numerlic in ['min_', 'max_']:
      for col in df.columns:
          print(numerlic + col)
  ```

  df의 columns: 'one', 'two', 'three' 라고 가정

  ```
  출력
  min_one
  min_two
  min_three
  max_one
  max_two
  max_three
  ```

  - index.name과 map까지 활용

  ```python
  df_new = df_old[['bar']].copy()
  # df_old의 bar컬럼만 카피
  
  for numerlic in ['min_', 'max_']:
    df.index.name = numerlic + 'foo_'
    for col in df.columns:
      df[numerlic + col] = df_old[df.index.name].map(df[col])
  ```

  > 2차 for문 안의 `df[numerlic + col] = df_old[df.index.name].map(df[col])`: df의 각 컬럼을 df_old의 index에 mapping해준 후 해당 index를 numerlic + col 이름을 가진 df의 컬럼으로 생성

- **shape()**

  `df.shape()`: df의 모양 반환