# namespace

네임스페이스는 모든 식별자(변수, 함수, 클래스 등)의 이름이 고유하도록 보장하는 코드 영역을 정의하는 것이다.

사용자 정의 네임스페이스 내부에 선언된 모든 것은 전역 네임스페이스가 아닌 해당 네임스페이스에 속하게 된다.

- **예시**

```c++
#include <iostream>
using namespace std;

namespace A  // namespace A  구역을 정의
{ 
	class Foo  // A구역에서 Foo이름의 클래스 생성
	{
	private:
		int a = 10;

	public:
		void print()
		{
			cout << "namespcae A 구역 a값 : " << a << endl;
		}
	};
}

namespace B  // namespace B  구역을 정의
{
	class Foo	// B구역에서 Foo이름의 클래스 생성
	{
	private:
		int a = 20;

	public:
		void print()
		{
			cout << "namespcae B 구역 a값 : " << a << endl;
		}
	};
}

int main()
{
	A::Foo myfoo;  // namespace A 공간의 Foo클래스 인스턴스 생성
	B::Foo mybar; // namespace B 공간의 Foo클래스 인스턴스 생성
	// 인스턴스는 main함수에서 생성되는 것이라 다른 namespace구역의 클래스 객체와 같은 이름으로 선언할 수 없다.

	myfoo.print();  // namespcae A 구역 a값 : 10  출력
	cout << endl;
	mybar.print();	// namespcae B 구역 a값 : 20  출력
}
```

> 여기서 using을 사용하면 namespace를 전역에 정의가 가능하다.
>
> namespace가 전역에 정의된 순간, 해당 namepace의 객체는 따로 명시하지 않아도 된다.
>
> ex) `using namespace std;`  코딩 후 `std::`를 명시하지 않아도 됨
>
> ```c++
> // --------- 위와 같은 namespace 생략--------- //
> using namespace B;  //using으로 namespace B 선언
> // B namepace의 객체는 따로 명시하지 않아도 된다.
> 
> int main()
> {
> 	A::Foo myfoo;  // namespace A 공간의 Foo클래스 인스턴스 생성
>     // A는 전역에 생성되지 않았기 때문에 명시해야 한다.
> 	Foo mybar; // namespace B 공간의 Foo클래스 인스턴스 생성
> 	
> 
> 	myfoo.print();  // namespcae A 구역 a값 : 10  출력
> 	cout << endl;
> 	mybar.print();	// namespcae B 구역 a값 : 20  출력
> }
> ```
>
> 위 코드와 같이 namespace A, B가 같은 이름의 멤버를 가지고 있을 때 using namespace 로 A와 B를 둘 다 선언하면 컴파일 에러
>
> using namespace는 **using지시자**를 사용한 것으로 다른 네임스페이스에서 선언된 이름에 대한 지역 동의어를 만들어 주는 것.



## using

using 은 선언자, 지시자로 나뉜다.

**using선언자**: 오버로딩과 이름 식별의 역할을 하는 다른 선언과 똑같은 일을 한다.

> Using 선언은 지역변수와의 명칭이 충돌할 경우 에러로 처리한다.



**using지시자**: 는 위와 같이 지정한 네임스페이스의 모든 명칭을 이 선언이 있는 영역으로 가져와 소속 지정없이 명칭을 바로 사용할수있다. Ex) `using namespace `

> Using 지시자는 네임스페이스의 명칭에 대한 가시성이 제한될 뿐 에러나 경고를 내지 않는다.









