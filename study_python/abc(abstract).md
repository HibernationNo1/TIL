# abc

### ABC

```python
from abc import ABC
```

ABC는 **추상 클래스(abstract base class)**를 정의할 때 사용하는 기본 class이다.

**abstract base class**

- 추상 클래스는 **직접 인스턴스화할 수 없으며** 서브클래스에 의해 상속받아 사용된다.
- ABC는 **공통 인터페이스를 정의하고, 서브클래스가 반드시 구현해야 하는 메서드(추상 메서드)를 선언하는 데 사용**된다.
  - **sub class에 특정 method 구현 강제**: 추상 메서드를 정의하면 sub class가 반드시 해당 메서드를 구현해야 하므로, 인터페이스 일관성을 유지할 수 있다.
  - **명확한 구조와 책임 할당**: ABC를 사용하여 interface를 명확히 정의하면, class 구조를 보다 명확하게 설계할 수 있어 유지보수성이 높아진다.
  - **코드 재사용성과 다형성 지원**: ABC를 통해 정의한 공통 interface는 다양한 서브클래스에서 동일하게 구현될 수 있어, 코드 재사용과 다형성을 쉽게 구현할 수 있다.
  - **IDE와 Linter 지원**: ABC를 사용하면 IDE와 Linter가 추상 메서드 구현을 검사하여 subclass가 필요한 method를 빠뜨리지 않도록 도와준다.



### abstractmethod

abstractmethod는 **추상 메서드**를 정의하기 위한 데코레이터로, **메서드의 시그니처만 선언하고 실제 구현은 생략**한다.

abstractmethod 데코레이터가 적용된 메서드는 서브클래스에서 반드시 구현해야 하며, 추상 메서드를 구현하지 않은 서브클래스는 인스턴스화할 수 없다.

```python
from abc import ABC, abstractmethod

# 추상 클래스 정의
class Shape(ABC):
    
    @abstractmethod
    def area(self):
        """도형의 면적을 계산하는 메서드"""
        pass

    @abstractmethod
    def perimeter(self):
        """도형의 둘레를 계산하는 메서드"""
        pass

# 서브클래스에서 추상 메서드를 구현
class Circle(Shape):
    def __init__(self, radius):
        self.radius = radius

    def area(self):
        return 3.1415 * self.radius ** 2

    def perimeter(self):
        return 2 * 3.1415 * self.radius

# 올바른 사용
circle = Circle(radius=5)
print("Area:", circle.area())
print("Perimeter:", circle.perimeter())

# 오류: 추상 메서드를 구현하지 않으면 인스턴스화할 수 없음
class Square(Shape):
    pass
# square = Square()  # TypeError 발생
```

