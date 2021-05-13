# pandas

#### df.apply()

specific value에 access해서 그 value를 변경

```python
df.apply(method)
```

ex)

```python
df.apply(int)
```



```python
def pass_or_fail(row):
    if row > 150:
        return "Pass"
    else:
        return "Fail"
    
df.매출액.apply(pass_or_fail)
```



```
	   y-m-d
0	2000-06-27
1	2007-10-27
```

```python
def extract_year(row):
    return row.split('-')[0]

df[year] = df[y-m-d].apply(extract_year)
```

```
	   y-m-d		year
0	2000-06-27		2000
1	2007-10-27		2007
```







#### aggregate()