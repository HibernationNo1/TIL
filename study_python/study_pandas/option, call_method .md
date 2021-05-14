# pandas

## set_option()

### display

데이터가 광범위할때, 출력을 하고 중간이 `...`으로 생략되어 출력된다. 이러한 데이터도 다 보기 위해서 설정값을 미리 호출해야 한다.

#### max_columns

모든 열을 다 보고자 할 때.

```python
pd.set_option('display.max_columns', None)
```

> None 대신 정수를 넣으면 그 정수만큼 보여줌



#### max_rows

모든 행을 다 보고자 할 때.

```python
pd.set_option('display.max_rows', None)
```

> None 대신 정수를 넣으면 그 정수만큼 보여줌



## df.apply()

call other method and apply to dataframe

```python
df.apply(method)
```

> axis 지정 가능



##### 내장 method 호출

- dtype cast

  ```python
  df.apply(int)
  ```

- call numpy.method

  sqrt과 같이 단일 연산인 경우 전체에 적용

  min, max, average와 같이 집계되는 경우 사라질 축을 지정

  ```python
  df.apply(np.sqrt)
  df.apply(np.average, axis = 1)
  ```

##### call def mothed

- argument가 1개인 경우

```python
df.apply(def_method)
```

> ex)
>
> ```python
> def pass_or_fail(row):
>     if row > 150:
>         return "Pass"
>     else:
>         return "Fail"
>     
> df_new = df.매출액.apply(pass_or_fail)
> ```
>
> 
>
> ```
> 	   y-m-d
> 0	2000-06-27
> 1	2007-10-27
> ```
>
> ```python
> def extract_year(row):
>     return row.split('-')[0]
> 
> df[year] = df[y-m-d].apply(extract_year)
> ```
>
> ```
> 	   y-m-d		year
> 0	2000-06-27		2000
> 1	2007-10-27		2007
> ```
>

- argument가 2개 이상인 경우 : **lambda** 사용

  ```python
  df.apply(lambda x: def_method(arg1, arg2))
  ```

  > ex)
  >
  > ```python
  > def col(x, y, z):
  >     return (x+y)/z
  > df_new = df.apply(lambda x: col(x['foo'], x['bar'], x['baz']), axis = 1)
  > ```
  >
  > (x+y)/z이 적용되는 method를 정의하고, lambda 를 통해 전달되는 각 columns value에 대해 compute

  - lambda를 조건문으로 사용할 경우

    ```python
    df.apply(lambda x: 조건문)
    ```

    > ex)
    >
    > ```python
    > data = df.loc[df['foo'].apply(lambda s: str(s) in ['one', 'two'])]
    > ```
    >
    > foo컬럼 안에 'one' 또는 'two'라는 데이터가 있으면 str형으로 변환. 없으면 pass
    >
    > loc[df['컬럼']] 을 통해 해당 컬럼의 모든 index에 apply적용









## df.aggregate()

call mutiple other method by dict  and apply to dataframe

```python
df.aggregate()
```



##### 내장 method 호출

```python
new_df = df.aggregate({'int'})
```



##### call def mothed

```python
new_df = df.aggregate({def_method})
```



ex)

```python
def most(x):
  return x.value_counts().index[0]
# x함수에서 각 값의 포함 횟수를 내림차순으로 정렬 한 것의 첫 번째: 가장 큰 값

def sqr(x):
    idff = abs(x.min()-x.max())
    return idff

new_df = df.aggregate(
    {
       'foo': 'mean',   # 라이브러리 내부 함수
       'bar': most,	# 직접 정의한 함수
       'baz': sqr
    }
)
```

> DataFrame안의 columns 중 특정 columns만 함수를 적용해서  new_df에 할당

