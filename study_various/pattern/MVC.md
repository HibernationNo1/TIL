### MVC

웹 인터페이스를 통해 AI 모델을 서빙하는 경우에는 유용한 패턴

### DI (Dependency Injection, 의존성 주입)

객체가 직접 의존성을 생성하는 대신 외부에서 제공받도록 하는 방법으로, 소프트웨어 구성 요소 간의 결합도를 낮추고 코드의 유연성, 재사용성 및 테스트 용이성을 높이기 위해 사용되는 설계 기법이다.

**의존성을 외부에서 제공받는다는 것**: 객체가 자신이 필요한 다른 객체를 스스로 생성하지 않고, 외부에서 주입(제공)받는 것을 의미한다.

#### 의존성 주입 방법

의존성 주입 방법은 크게 3가지 방법이 있다.

1. 생성자 주입(Constructor Injection)

   ```python
   class Service:
       def do_something(self):
           print("Service is doing something")
   
   class Controller:
       def __init__(self, service: Service):
           self.service = service
   
       def handle_request(self):
           self.service.do_something()
   
   # 의존성 주입
   service = Service()
   controller = Controller(service)
   controller.handle_request()
   ```

2. 메서드 주입(Method Injection)

   ```python
   class Service:
       def do_something(self):
           print("Service is doing something")
   
   class Controller:
       def handle_request(self, service: Service):
           service.do_something()
   
   # 의존성 주입
   service = Service()
   controller = Controller()
   controller.handle_request(service)
   ```

3. 속성 주입(Property Injection)

   ```python
   class Service:
       def do_something(self):
           print("Service is doing something")
   
   class Controller:
       def __init__(self):
           self.service = None
   
       def handle_request(self):
           self.service.do_something()
   
   # 의존성 주입
   service = Service()
   controller = Controller()
   controller.service = service
   controller.handle_request()
   ```

   

#### Interface

객체지향 프로그래밍에서 클래스가 구현해야 하는 method의 집합을 정의한 것이다. 

사용하고자 하는 class는 interface class를 상속받은 후, 수정이 필요한 method를 적절하게 수정하여 사용한다. 

**Interface를 사용한 DI 예시**

- Interface 정의

  ```python
  from abc import ABC, abstractmethod
  
  class IService(ABC):
      @abstractmethod
      def some_function(self):
          pass
  ```

- 구현 class

  ```python
  class RealService(IService):
      def some_function(self):
          print("RealService: some_function executed")
  
  class MockService(IService):
      def some_function(self):
          print("MockService: some_function executed")
  ```

- client class

  ```python
  class Controller:
      def __init__(self, service: IService):
          self.service = service
  
      def handle_request(self):
          self.service.some_function()
  ```

- main

  ```python
  def main():
      service = RealService()  # 또는 MockService()로 교체할 수 있습니다.
      controller = Controller(service)
      controller.handle_request()
  
  if __name__ == "__main__":
      main()
  
  ```

  



- 굳이 interface class를 만들어 상속받는 이유

  - **결합도 감소**

    Interface를 사용하면 class 간의 결합도를 낮출 수 있다. 

    client class는 인터페이스에 의존하고, 구체적인 구현 class는 interface를 구현한다. 이를 통해 client class는 구현 세부 사항을 몰라도 interface를 통해 기능을 사용할 수 있다.

  - **유연성 증가**:

    Interface를 사용하면 다양한 구현체를 쉽게 교체할 수 있다.

    예를 들어, `Service` interface를 구현하는 여러 구현 class가 있을 때, client class는 interface를 통해 다양한 구현체를 주입받아 사용할 수 있다.

  - **테스트 용이성**:

    interface를 사용하면 테스트할 때 모의 객체(Mock Object)를 쉽게 주입할 수 있다.

    이를 통해 실제 구현체가 아닌 테스트용 구현체를 사용하여 테스트를 수행할 수 있습니다.

  



DTO**(Data Transfer Object)**

```
로직을 가지지 않는 순수한 데이터 객체이며 getter/setter 메소드만 가진 클래스를 의미
```



**DAO(Data Access Object)**

```
DataBase의 data에 접근하기 위한 객체로 직접 DataBase에 접근하여 데이터를 삽입, 조회, 변경, 삭제(CRUD) 등을 조작할 수 있는 기능
```



 

