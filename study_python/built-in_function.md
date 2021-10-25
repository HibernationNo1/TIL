# built-in_function

### iter()

iterable한 instance를 Iterator class로 만들 수 있다.

```python
a = [1, 2, 3]

print(type(a))  # list 출력
a = iter(a)		# iterable한 a를 Iterator로 만듬
print(type(a))  # list_iterator 출력
```

- `__iter__()` 을 통해 동일한 동작을 할 수 있다.

  ```
  a.__iter__()
  ```

  



### next()

 iterate한 container 를 인자로 받아 호출될 때마다 하나의 elements씩 리턴

```python
iter = [1, 2, 3]
print(next(iter)) # 1
print(next(iter)) # 2
print(next(iter)) # 3
```

`iter` : iterate한 container

- `__next__()` 는  `iter()`에 의해 만들어진 list_iterator에 대해 `next()`와 같은 동작을 할 수 있다.

  ```python
  a = [1, 2, 3]
  a = iter(a)
  print(a.__next__())	# 1
  print(a.__next__()) # 2
  print(a.__next__()) # 3
  ```

  

  

  





### startswith()

string의 호출 함수로

string에 argument로 받은 인자가  포함되어 있으면 True, 아니면 False를 반환

```python
str_ = "model_0001"
arg1 = "model"
arg2 = "ssss"
print(str_.startswith(arg1)) # True
print(str_.startswith(arg2)) # False
```



### filter()

boolean을 return하는 function과 iterate한 container를 받아 

하나의 element씩 function에 할당한다.

결과가 True이면 element을 반환한다.

```python
target = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
result = filter(lambda x : x%2==0, target)
print(list(result))  # [2, 4, 6, 8, 10]
```

