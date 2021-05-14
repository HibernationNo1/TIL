# Pandas 



### math

#### df.min()

```python
min_value = df.min()
```



#### df.max()

```python
max_value = df.max()
```



#### df.sum()

```python
sum_value = df.sum()
```



#### df.mean()

```python
mean_value = df.mean()
```



---



### Analysis

#### df.info()

데이터의 information을 반환한다.

```python
print(df.info())
```



#### df.describe()

수치형 데이터들의 통계를 반환한다.

```python
print(df.describe())
```



#### df.value_counts()

dataframe 안에 어떤 값이 몇개가 있는지 내림차순으로 반환한다.(범주형, 수치형 상관 없음)

```python
print(df.value_counts())
```

ex)

```python
df['column_name'].value_counts()
```



#### df.corr()

columns의 correlation을 수치화 할 수 있다.

```python
print(df.corr())
```



#### df.unique()

columns가 가지고 있는  유일한 value를 return

```python
df.unique()
```



ex)

```python
pd['foo'].unique()
```

foo라는 컬럼 안에 존재하는 모든 경우의 수를 볼 수 있다고 생각하면 된다.



#### df.shape()

df의 shape을 return

```python
print(df.shape())
```



#### df.copy()

```python
new_df = df.copy()
```





#### df.isna()

> data값이 NaN인 것을 찾아서 True로 return

```python
df.isna()
```





---



### group

#### df.groupby()

df안의 value들을 category별로 묶어서 dictionary로 return

```python
groupby(df)
```

`as_index = False ` : group으로 묶인 각 category 안의 value에 정수형으로 index를 붙여준다 



- 컬럼 1개에 대한 그룹별 집계

  ```python
  df.groupby(['column_A'])
  ```

  

- 컬럼 2개에 대한 그룹별 집계

  ```python
  df.groupby(['column_A', 'column_B'])
  ```

  



#### pd.concat()

dataframe을 물리적으로 이어 붙여주는 함수로, axis에 따라서 해당 축의 동일한 자료형끼리 묶어주는 동작을 한다.

```python
x = pd.concat(['df_A', 'df_B'], axis = 1)
```

