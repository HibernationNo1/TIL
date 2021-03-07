# `__init__`, call

## 1. `__init__`

`__init__`은 초기화(initialize)메서드라고 한다.

> 앞 뒤로 `__`(밑줄 두 개)가 붙은 메서드는 파이썬이 자동으로 호출해주는 메서드임

클래스에 `( )`(괄호)를 붙여서 인스턴스를 만들 때 호출되는 특별한 메서드다. (인스턴스를 초기화 한다.) 

> **C++에서 class의 생성자라고 생각하면 됨**



- self

  self는 인스턴스 자기 자신을 의미한다. 

**형태**

```python
class 클래스이름:
    def __init__(self):
        self.속성 = 값
```



**코드 예시**

```python
class Person:
    def __init__(self):
        self.hello = '안녕하세요.'
 
    def greeting(self):
        print(self.hello)
 
james = Person()    # Person클래스 객체 생성. 
# self를 인자로 가진 생성자에 의해서 self에 Person()이 들어간다. 
james.greeting()    # 안녕하세요. 출력
```

> `james = Person() `: 생성자 호출되어 Person.hello = '안녕하세요.' 가 되는 것임.



## 2. `__call__`

함수를 호출하는 것처럼 클래스의 객체도 호출할 수 있게 만들수 있는데 이때 필요한 매직메소드가 `__call__`이다.

__init__:  인스턴스 초기화 할 때 호출됨

__call__: 은 인스턴스가 호출됐을 때 실행됨