# Pandas

Pandas는 numpy를 기반으로, 보다 고차원적인 데이터 처리를 돕는 라이브러리이다. 

동일한 데이터를 가진 Series를 기본으로 하며, 이를 여러개 묶어 사용하는 DataFrame을 사용하여 표 형태로 된 자료를 다룬다. (pandas는 dataframe을 주로 다루기 위한 라이브러리)

- Series

  pandas에서 제공하는 데이터타입으로, index가 있는 1차원 배열이라고 생각하면 좋다. 문자, 논리형, 숫자 모든 데이터타입이 들어갈 수 있다. dataframe의 columns가 series이다.

```python
import pandas as pd
```




---



### 생성

#### pd.DataFrame

```python
data_frame = pd.DataFrame(data,index = ,columns = )
```



ex)

```python
import pandas as pd

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



####  read

##### pd.read_csv

csv파일 읽는 방법

```python
df = pd.read_csv('path\file_name.csv')
```

> object에 파일을 할당한다.
>
> colap에서는 파일 이름만 입력해도 됨

- `delimiter`

  data set을 구분하는 str을 결정한다.(`sep =` 과 같다.)

  ```python
  df = pd.read_csv('path\file_name.txt', delimiter = '\t')
  ```

  > .txt file을 load하는 경우
  >
  > .txt file은 tap으로 각 data가 표시되어 있을 수 있으니 
  >
  > tap으로 구분된 data를 load

- `header`

  data에 column이 따로 없을 때 `header = None` 을 입력하면 colmuns가 0부터 정수형으로 자동 주어진 상태로 load한다.

  ```python
  df = pd.read_csv('path\file_name.csv', header = None)
  ```

- `names`

  data set의 columns를 결정한다.

  ```python
  columns = ['매출액', '영업이익', '순이익'] 
  df = pd.read_csv('path\file_name.csv', header = None, names = columns)
  ```



##### pd.read_sql_query

sql파일에서 데이터를 가져오는 방법 

> sqlite3.connect 를 통해 dataset을 가져온 후

```python
conn = sqlite3.connect('database.sqlite')

df_country = pd.read_sql_query('SELECT * from Country', conn)
df_league = pd.read_sql_query('SELECT * from League', conn)
df_match = pd.read_sql_query('SELECT * from Match', conn)
```



##### pd.read_html

웹 페이지도 가져올 수 있다.

```python
state_code = pd.read_html('https://www.infoplease.com/us/postal-information/state-abbreviations-and-state-postal-codes')[0]
```



---



### acess

#### df.head()

data_frame의 상위 n개를 반환한다.

```python
df.head(num)
```

> default = 5
>
> num이 음수면 뒤의 |num|개 까지 보여준다.



#### df.tail()

data_frame의 하위 n개를 반환한다.

```python
df.tail(num)
```







#### columns

기본적으로 pandas의 data frame은 indexing이 가능

```python
foo2 = df[['매출액','영업이익']]
```

> column 이 '매출액', '영업이익'인 data를 확인할 수 있다.



##### df.columns

object에 할당된 data frame에서 columns를 반환한다.

```python
df.columns
```



```python
df.columns = ['매출액', '영업이익', '순이익'] 
```

> data_frame의 columns 결정



- columns 대신 특정 colum의 name 자체를 가져다 쓰면 해당 column에 접근할 수 있다.

  ```python
  df_col1 = df.매출액
  df_col2 = df.name
  df_col3 = df[df.age > 25] # age 라는 column에서 25 이상의 value를 가진것만 return



##### df.query()

```python
df_col3 = df[df.age > 25]
```

와 같은 원리다.

```python
df.query('age>25')
```

> the argument should be given string type

```python
foo = df.query('매출액>300' and '영업이익 == 17')
```

> can use conditional  



#### tuple

기본적으로 pandas의 data frame은 indexing이 가능

```python
df[:3]
```

> tuple의 index 0부터 2까지 담겨져 있는 data를 볼 수 있다. 



##### df.loc[ ]

tuple에 접근하는 방법

1. index마다 name이 있을 때

```python
df.loc['index_name']  
df.loc['index_name':4]  
```

> tuple 중 해당 index의 모든 columns data를 return
>
> can use indexing  

2. index에 name이 없을 때

```python
df.loc[2]
df.loc[:2]
```

> can use indexing  

3.  위와 같은 정보를 뽑아내지만, dataframe의 형태 그대로 index만 뽑아 보여준다. (더 보기 좋음)

```python
df.loc[df['index_name']]
df.loc[df[2]]
```



ex)

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

> can use indexing  



##### df.index

data frame에서 tuple을 반환한다.

```python
df.index
```

> tuple의 개수를 return



- `df.index.name`

  default로 tuple은 명시된 이름이 없지만, `df.index.name` 를 통해 이름을 지어줄 수 있다.

  ```python
  df.index.name = 'foo'
  ```

- `df.index[1]`

  tuple 중 index1에 위치한 index를 return



##### df.set_index()

```python
df = df.set_index()
```

특정 열을 tuple로 설정할때 사용된다.

```python
df.set_index('name')
```

> 그 전에는 그냥 1, 2, 3...과 같은 순서가  tuple였다면, 이제부터는 'name'이 tuple로 되는 것이다.

```python
set_index(['foo','bar'])
```

 tuple이 다수가 될 수 있다. 이를 multi index라고 한다.



##### df.reset_index()

```python
df = df.reset_index()
```



tuple을 다시 처음부터 재배열 해주는 함수다.

```
df == 
	매출액  영업이익  순이익
1월  100    25   10
2월  200    20   11
3월  300    15   12
4월  350    16   13
5월  320    17   12
```

여기서 `df = df.reset_index()`를 한 후 출력해보면

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



#### df.filter()

```python
df.filter( items = )
```

- `items =['column_name']`  : data frame에서 원하는 column에 접근 가능

  ```python
  df.filter( items = ['매출액','영업이익'])
  ```

  > `df[['매출액','영업이익']]`  과 같은 동작을 수행한다.

  `items = index_name` : data frame에서 원하는 index에 접근 가능

  ```python
  df.filter( items = '1월' )
  ```

- `like = ' '` 특정 string이 포함된 data을 뽑을 수 있다.

  ```python
  df.filter(like = 'a', axis =1)
  ```

  > `axis =0` : index에서 뽑
  >
  > `axis =1` : column에서 뽑

- `regex =' $'` 특정 string으로 끝나는 data를 뽑을 수 있다.

  ```python
  df.filter(regex ='b$', axis =1)
  ```

  > columns중에서 'b' 단어로 끝나는 name만 return



#### df.iloc[ ]

df.loc[ ]는 오직 tuple관점에서만 사용 가능했지만, df.iloc은 tuple, column관점에서 사용 가능

```python
df.iloc[ 'index_name', 'column_name' ]
```

> 특정 index 안에서 원하는 column만 뽑아서 return

```python
foo1 = df.loc[ '2월':'1월', '영업이익':]
foo2 = df.iloc[ :3, 2: ]
```





### delete data

#### df.drop()

using when drop non use data (only)

```python
df.drop(['name1', 'name1'], axis = , inplace=True)
```

- `axis = 0` : index_name에 해당되는 data만 drop

  `axis = 1` : column_name에 해당되는 data만 drop

- `inplace=True`가 되어야 drop된 데이터를 뺀 나머지가 다시 df에 할당된다.

  default = False

  ```python
  df = df.drop(['name', 'name'], axis =1)
  ```

  > 위 코드와 같음

> tip) 컬럼명1 =  x, 	컬럼명2 = -x의 값을 가지고 있으면 두 컬럼 중 하나는  drop해줘야 한다.
>
> **Multicollinearity**(다중공선성): 일반적으로 회귀 분석에서 발생하며, 분석에서 사용된 모델 데이터의 일부 컬럼이 다른 컬럼과 상관 정도가 높아, 데이터 분석 시 위험한 영향을 미치는 현상  



```python
col_cats = list['column_name1', 'column_name1' ...]
x_num = df.drop(col_cats, axis=1)
```

> categorycal data만 drop하고 싶을 때 처럼, 특정 column만 drop하고 싶을 때는 위 처럼 list를 사용하자. 



### save file

#### df.to_csv

```python
df.to_csv('file_name')
```



**property**

- `index = ` : default = True, False면 tuple를 없앰

- `names = `: default = True

- `na_rep = '-'`  : None Value는 '-'로 채워서 저장

