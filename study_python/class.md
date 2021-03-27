# class

### 기본 형태

```python
class foo:
    def __init__(self):
        print("Hello World")
        
tmp = foo()
```

> `foo`: 클래스 이름
>
> `__init__`: 이니셜라이저. class 객체가 생성되면 자동으로 호출된다. (c++의 생성자와 비슷하지만 같은건 아니다.)
>
> - `__`이 앞 뒤로 붙어있는 메서드를 매직매서드라고 한다.
> - `self`: class안에서 self매개변수는 class 이름을 의미한다.



클래스에서 정의된 함수를 메서드라고 한다.

클래스에서 정의된 변수 중 이니셜라이저 함수에서 정의된 변수를 '인스턴스 변수', 이니셜라이저 밖에서 정의된 변수를 '클래스 변수'라고 한다.

```python
class foo:
    z = 0	# 클래스 변수
    def __init__(self, x, y):
      	self.x = x 	# 인스턴스 변수
        self.y = y
        self.add =None
        
    def adder(self):
        self.add =self.x+self.y
        
    def multi(self):
        return self.x * self.y
        
tmp = foo(10, 20)
print(tmp.x, tmp.x, tmp.add)   	# 10 20 None
tmp.adder()
print(tmp.x, tmp.x, tmp.add)	# 10 20 30
print(tmp.multi() ) 				# 200
```

> instance variable에 사용된 self는 c++에서 `->` 포인터와 같은 역할을 한다.



##### variable

instance variable과 class variable의 차이

```python
class node:
    node_cnt = 0
    
    def __init__(self, x, y):
        self.x, self.y = x, y
        node.node_cnt += 1
        
node1 = node(10, 20)
print(node1.x, node1.y, node1.node_cnt)  	# 10 20 1
node2 = node(100, 200)
print(node2.x, node2.y, node2.node_cnt)		# 100 200 2
```

> `node_cnt`는 클래스 전체가 사용 가능한 공통된 값
>
> `self.x`, `self.y`는 각 객체마다 고유하게 가지고 되는 값
>
> `node1` 객체가 생성될 때 이니셜라이저에서 class variable에 접근해 +1을 수행. 이 값은 클래스 자체가 가지게 된다.



##### private

python의 class는 private, public 개념이 없다. 그렇기 때문에 코드 공유자에게 private으로 말하고 싶은 메서드 또는 변수의 이름 앞에 `_` 하나를 붙여서 이름을 짓는다. 

```python
class calculator:
    def __init__(self, x, y, operator):
        self._x = x
        self._y = y
        self._operator = operator
        
        self.result = None
        
        if self._operator == '+':
            self._adder()
        else self._operator == '*':
            self._multiplier()
    
    def _adder(self):
        self.result = self._x + self._y
    def _multiplier(self):
        self.result = self._x * self._y
    
    def get_result(self):
        return self.result
    
tmp1 = calculator(10, 20, '*')
result = tmp1.get_result()
print(result)	# 200
tmp2 = calculator(100, 200, '+')
result = tmp2.get_result()
print(result)	# 300
```



##### dir

`dir(class 객체)`: class의 매직메서드, 메서드, instance variable들을 반환한다.

해당 class의 구성을 알 수 있다.

```python
class tmp_class:
    def __init__(self):
        self.x = 0
        self.y = 0
    def method1():
        pass
    def method2():
        pass
    
tmp  = tmp_class()
print(dir(tmp))
```

```
['__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__le__', '__lt__', '__module__', 
'__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', 'method1', 'method2', 'x', 'y']
```

