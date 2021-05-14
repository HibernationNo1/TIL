# drop, fill, transform

## drop

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



#### df.dropna()

NaN value data를 delete한 df를 return

```python
new_df = df.dropna()
```

```python
df.dropna(inplace = True)
```





#### df.duplicated()

중복된 data를 찾아서 True or False로 반환

```python
check_df = df.duplicated()
```

> 전체 index를 순차적으로 탐색해서 모든 columns의 data가 같은 index가 발견될 경우 True



```python
check_df = df.duplicated(['col'])
```

> 'col' 이라는 column에서 중복 탐색



#### df_drop_duplicates()

중복된 valuse를 찾아서 drop

```python
check_df = df_drop_duplicates()
```

> 중복된 data (df.duplicated를 통해 True가 return되는 data)는 drop

- `keep = ` 

  > `keep = 'first'` 첫 번째로 나온 중복 data를 제외한 모든 중복 data drop
  >
  > `keep = 'last'` 마지막으로 중복 data를 제외한 모든 중복 data drop

```python
check_df = df_drop_duplicates(['name'], keep = 'first')
```





## fill

#### df.fillna()

NaN value는 argument로 받은 value로 대체한다.

```python
new_df = df.fillna(0)
```

> NaN value는 0으로 변경



ex)

```python
df매출액.fillna(df.매출액.transform('median'), inplace = True)
```







## transform