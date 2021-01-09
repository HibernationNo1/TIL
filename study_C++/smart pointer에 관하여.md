# Pointer

포인터는 단지 메모리 주소에 불과해서 타입을 엄격히 따지지 않는다.

`*`연산자로 포인터를 역참조하면 메모리에서 한 단계 더 들어가 볼 수 있다.

`&`연산자를 사용하면 특정 지점의 주소를 얻을 수 있다.

힙에 할당된 배열은 첫 번째 원소를 가리키는 포인터로 참조한다.

스택에 할당된 배열은 배열 문법`[]` 으로 참조한다.



스택 배열에 포인터로 접근

```c++
itn arr[10] = {};
int* ptr = arr;     // 포인터로 arr배열에 접근
ptr[4] = 5
```

배열을 함수에 넘길 때 유용하다.



```c++
void exmple(int* arr, size) //arr배열을 받아온다.
{
    for(int i = 0; i<size; i++)
        arr[i] *=2           	//각 배열에 *2
}
```

이 함수를 호출할 때 arr가 

스택 배열이면: exmple 함수에 배열 변수를 전달하고 컴파일러가 이를 배열에 대한 포인터로 변환.

힙 배열이면:  이미 포인터가 담겨 있어서 함수에 값으로 전달됨.



포인터 연산

C++은 포인터 연산을 수행할 때 포인터에 선언된 타입을 이용한다.





스마트 포인터

스마트 포인터를 사용하면 동적으로 할당한 메모리를 관리하기 쉽다.

메모리 누수를 방지하기 아주 좋다. 

스마트 포인터는 메모리뿐만 아니라 동적으로 할당한 모든 리소스를 가리킨다.

스마트 포인터가 스코프를 벗어나거나 리셋되면 거기에 할당된 리소스가 자동으로 해제된다. 

> 리소스에 대한 고유 소유권들 받는 스마트 포인터일 때



스마트 포인터는 함수 안에서 동적으로 할당된 리소스를 관리하는 데 사용할 수도 있고, 클래스의 데이터 멤버로 사용할 수도 있다.



템플릿을 이용하면 모든 포인터 타입에 대해 안전한 스마트 포인터를 클래스를 작성할 수 있다.

연산자 오버로딩을 이용하여 스마트 포인터 객체를 일반 포인터처럼 활용할 수 있다.



동적으로 할당된 리소스는 항상 unique_ptr와 인스턴스에 저장하는 것이 바람직하다.





unique_ptr

unique_ptr는 `make_unique()`로 생성한다.

unique_ptr 메모리 할당 및 해제는 new와 delete 키워드를 사용한다.

```c++
void tmp()
{
Foo* myFoo  = new Foo();
myFoo -> go();
delete myFoo;
}
```

여기서 go 메서드에 익셉션이 발생하면 delete가 실행되지 않음



unique_ptr 스마트 포인터를 사용하여 자동 delete가 될 수 있도록 코딩

```c++
void tmp()
{
Foo myFoo = make_unique<Foo>(1, 2); 
// Foo의 객체를 생성 (make_nuique 키워드 적용) 
// 1과2는 생성자의 매개변수에 전달할 인수
    mtFoo -> go(); 
}
```

> - 스마트 포인터는 일반 포인터처럼 `*`나 `->`로 역참조한다.
>
> ```c++
> unique_ptr<Foo> myFoo(new Foo());
> // make_unique를 지원하지 않는 컴파일러에선 unique_ptr을 사용한다.
> ```
>
> - 가독성은 make_unique가 더 좋다.



unique_ptr 사용 방법

unique_ptr에서는 get()과 reset(), release()메서드를 제공한다.

get()메서드

get()메서드를 이용하면 내부 포인터에 직접 접근할 수 있다.

함수는 보통 일반 포인터만 전달할 수 있지만, get()을 사용해서 스마트 포인터를 전달할수 있다.

```c++
void tmp(Foo* mybar) { /* 스마트 포인터를 사용하느 코드 */ }       
// tmp라는 함수에 Foo클래스의 mybar라는 객체를 생성해서 인자로 전달

// 위 함수를 get()메서드를 사용해서 함수에 스마트 포인터를 전달해서 함수 호출
Foo myFoo = make_unique<Foo>();
tmp(myFoo.get());
```

reset()을 사용하면 unique_prt의 내부 포인터를 해제하거나 다른포인터로 변경할 수 있다.

```c++
myFoo.reset();				// 리소스 해제 후 nullptr로 초기화
myFoo.reset(new Foo());  // 리소스 해제 후 새로운 Foo 인스턴스로 설정
```

release()를 이용하면 unique_ptr와 내부 포인터의 관계를 끊을 수 있다.

release()는 리소스에 대한 내부 포인터를 리턴한 뒤 스마트 포인터를 unllptr로 설정한다.  그러면 스마트 포인터는 그 리소스에 대한 소유권을 잃고, 그 리소스를 다 쓴 뒤 반드시 직접 해제해야 한다.

```c++
Foo mybar = myFoo.release();  // 리소스 소유권 해체
// mybar라는 객체 
 
delete mybar;
mybar = nullptr;
```

unique_ptr는 복사할 수 없다.



shared_ptr 

shared_ptr는 `make_shared()`로 생성한다.

shared_ptr도 메모리 할당 및 해제는 new와 delete 키워드를 사용한다.

공유하는 shared_ptr 개수는 use_count()로 알아낼 수 있다.





shared_ptr는 레퍼런스 카운팅을 지원한다.

shared_ptr 에서도 get()과 reset()메서드를 제공한다. (release는 없음)

> 단, shared_ptr의 reset()는 레퍼런스 카운팅 메커니즘에 따라 마지막 shared_ptr가 제거되거나 리셋될 때 리소스가 해제된다.

shared_ptr는 복사할 수 있다.

```c++
Foo myFoo = make_shared<Foo>();  //shared_ptr 생성

shared_ptr<Foo> myBar(myFoo);  // myFoo를 복사한 myBar라는 shared_ptr의 복제 생성자
```

위는 shared_ptr 두 개(객체 myFoo, 객체 myBar)가 한 Foo 객체를 동시에 가리키는 것. 

myFoo객체가 생성될 때 생성자 호출, 레퍼런스 카운팅 메커니즘으로 인해 myBar객체가 소멸할 때 소멸자 호출       

객체는 두개지만 생성자 소멸자 1번 씩만 호출된다.



shared_ptr는 앨리어싱을 지원한다.

그래서 한 포인터(소유한 포인터)를 다른 shared_ptr와 공유하면서 다른 객체(저장된 포인터)를 가리킬 수 있다.  shared_ptr가 객체를 가리키는 동시에 그 객체의 멤버도 가리킬 수 있다.

```c++
class Foo
{
    public:
    Foo(int value) : mData(value) {}
    int mData;
} 
auto foo =make_share<Foo>(42);
auto aliasing = share_ptr(foo, &foo->mData);
```

나중에 이어서 적기





p. 297

