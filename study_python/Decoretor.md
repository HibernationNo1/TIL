# Decoretor

파이썬은 데코레이터(decorator)라는 기능을 제공한다. 

데코레이터는 함수를 수정하지 않은 상태에서 추가 기능을 구현할 때 사용한다.

#### 구조

함수로 만드는 데코레이터는 일반적으로 아래와같은 구조를 가지고 있다.

```python
def out_func(func):  # 기능을 추가할 함수를 인자로
    
    def inner_func():
        #func()가 실행되기 전 iner_func 함수 정의 
        func()
        #func()가 실행된 후 iner_func 함수 정의 
    return inner_func #inner_func을 리턴해야함

@out_func  # @데코레이터
def foo():
    #foo 함수 정의
    
@out_func  # @데코레이터
def bar():
    #bar 함수 정의    
```

> `out_fucn`는 기능을 추가할 함수를 인자로 받으며 데코레이터(@)에 사용되기 위한 용도로만 쓰인다.
>
> `inner_func` 는 실질적으로 데코레이터 되는 함수로, @데코레이터에 의해 호출되면 이미 정의된 코드만 반복적으로 실행된다.
>
> `@out_func` 는 `inner_func`를 호출하며 그 아래 등장하는 함수는 `func()` 대신에 적용되는 함수다.
>
> 이런 방식으로 하나의 함수에 여러 기능을 추가하여 반복적으로 사용이 가능하다.