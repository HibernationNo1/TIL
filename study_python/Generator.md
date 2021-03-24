# Generator

list에 적용되는 반복자라고 생각하면 된다. 단, 한번에 모든 값을 포함한 배열을 만들어서 리턴하는 대신에 한 번 호출될 때마다 하나의 값만을 리턴한다.

함수를 정의할때 return 대신 yield를 사용하는 경우와, list를 하나의 반복자 매개변수로 사용하는 경우가 있다.

#### 1. 함수를 정의할 때

yield를 사용, next로 호출

예

```python
def square_numbers(nums):
    result = []
    for i in nums:
        result.append(i * i)
    return result

my_nums = square_numbers([1, 2, 3, 4, 5])

print my_nums
```

위의 출력은 각 list원소가 제곱이 되어 한 번에 출력이 되는 모습을 볼 수 있다. [1, 4, 8, 16, 25]

하지만 아래 출력은 next함수의 호출에 따라 순차적으로 출력이 됨을 볼 수 있다.

```python
def square_numbers(nums):
    for i in nums:
        yield i * i  # return  대신 yield사용

my_nums = square_numbers([1, 2, 3, 4, 5])  #1

print(next(my_nums))
print(next(my_nums))
print(next(my_nums))
```

> 출력 1: 다음줄에 4 다음줄에 9



#### 2. list comprehension

```python
my_nums = [x*x for x in [1, 2, 3, 4, 5]]
print(my_nums)
```

위의 코드에서 출력은 [1, 4, 8, 16, 25]으로 나온다. 여기서 []를 ()로만 바꿔주면 제네레이터가 적용된다.

```python
my_nums = (x*x for x in [1, 2, 3, 4, 5])   # 제네레이터 적용

print(next(my_nums))
print(next(my_nums))
```

> 출력 1: 다음줄에 4

```python
for num in my_nums:
    print(num)        	# for문을 사용해서 호출이 가능하다.
    
print list(my_nums)  	# 제너레이터를 리스트로 변형도 가능하다.
```



제네레이터 안의 2중 for문

```python
for col in (s + str(idx) for s in ['foo_', 'bar_'] for idx in range(1, 4)):
	print(col)
```

> foo_1
>
> foo_2
>
> foo_3
>
> bar_1
>
> bar_2
>
> bar_3