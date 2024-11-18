## pydantic

### **BaseModel**

Pydantic 라이브러리에서 제공하는 **기본 모델 클래스**로, 데이터 유효성 검사를 위한 강력한 기능을 제공한다.

- BaseModel은 각 필드에 지정된 타입을 검사한다. 모델 인스턴스가 생성될 때 입력된 값이 지정된 타입과 일치하지 않으면 오류를 발생한다.

- 만약 입력 값이 지정된 타입으로 변환 가능하다면, Pydantic은 해당 타입으로 자동 변환을 시도한다.

   예를 들어, int로 지정된 필드에 문자열 "123"이 입력되면 int 타입으로 자동 변환한다.

- 각 필드에 기본값이나 제약 조건을 Field()를 사용하여 설정할 수 있다.

-  model_validator 데코레이터나 @field_validator 데코레이터를 사용하여, 개별 필드 또는 모델 전체에 대해 추가적인 검증 로직을 정의할 수 있다.

### model_validator

Pydantic 모델에서 데이터 유효성을 검사하고 조건을 추가하는 데 사용하는 데코레이터로, 개별 필드뿐만 아니라 **모델 인스턴스 전체**에 대한 검증을 추가할 수 있다.

model_validator는 Pydantic 모델의 메서드 위에 데코레이터로 사용되며, 검증의 시점이나 방식 등을 제어할 수 있는 여러 파라미터를 제공한다.

model_validator 데코레이터는 BaseModel 를 상속받은 calss 내부의 method에만 적용이 가능하다.

**예시 코드**

BaseModel 를 상속받은 class내부에서, 필드를 검증하는 함수를 정의한 후 decorator로 사용된다.

```python
from pydantic import BaseModel, model_validator

class User(BaseModel):
    username: str
    age: int

    # 모든 필드가 검증된 후, 추가 검증 수행
    @model_validator(mode="after")
    def check_age(cls, values): # 필드 검증 함수
        print("검증 전 values:", values)  # 검증 전의 values 출력
        if values['age'] < 18:
            raise ValueError("User must be at least 18 years old")
        print("검증 후 values:", values)  # 검증 후의 values 출력
        return values
      
# 검증 실패 예시 (ValueError 발생)
try:
    user = User(username="alice", age=15)
except ValueError as e:
    print("Error:", e)

# 검증 성공 예시
user = User(username="alice", age=20)
print("Return된 values로 생성된 User 인스턴스:", user)
print("User 인스턴스의 딕셔너리 표현:", user.dict())
```

- model_validator decorator가 적용된 method는 class instance를 생성할 때 자동으로 호출된다.

- values는 자연스럽게 dict형태로 구성된다.

```
검증 전 values: {'username': 'alice', 'age': 15}
Error: User must be at least 18 years old

검증 전 values: {'username': 'alice', 'age': 20}
검증 후 values: {'username': 'alice', 'age': 20}
Return된 values로 생성된 User 인스턴스: username='alice' age=20
User 인스턴스의 딕셔너리 표현: {'username': 'alice', 'age': 20}
```



**Parameters**

- mode: 검증의 시점을 지정한다.

  - `mode="after"`: **모델의 필드 검증이 끝난 후** 실행된다.

    모델 인스턴스 전체가 검증된 이후에 추가적인 상호 의존적 필드 검증을 할 때 유용하다.

  - `mode="before"`: **모델의 필드 검증 전에** 수행된다.

    데이터가 모델에 할당되기 전이라 초기 데이터 값을 정리하거나, 전처리 과정이 필요한 경우에 유용하다.

- each_item: 리스트, 튜플, 딕셔너리와 같은 **반복 가능한 컬렉션 항목을 개별적으로 검증**할지 여부를 결정한다.

  - `each_item=True`로 설정하면 각 항목에 대해 개별적으로 검증이 적용된다.

- pre: 필드의 기본 값이 할당되기 전에 검증을 수행할지 여부를 결정한다.

  - `pre=True`를 지정하면, 필드의 기본값이 설정되기 전에 초기화된 값을 기준으로 검증한다.



### Field

Pydantic의 Field()는 각 필드의 **제약 조건, 기본값 및 설명**을 추가할 수 있게 해준다.

```python
from pydantic import BaseModel, Field

class User(BaseModel):
    username: str = Field(..., min_length=3, max_length=20, description="Username must be between 3 and 20 characters")
    age: int = Field(..., gt=17, description="Age must be greater than 17")
    country: str = Field("Unknown", description="User's country, defaults to 'Unknown'")

# Example usage
User(username="alice", age=18)
```

- `username`: 필수 필드로 설정(...)되며, 길이는 3자 이상, 20자 이하로 제한
- `age`: 필수 필드이며, 18세 이상이어야 한다.
- `country`: 기본값이 "Unknown"으로 설정

