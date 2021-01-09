# class에 관하여

## 1. 정의 및  특징

- class는 서로 연관 있는 데이터를 묶을 수 있는 문법적 장치, 객체 지향 프로그램을 작성할 수 있다.

- class는 객체 지향 프로그래밍의 특징 중 하나인 추상화(abstraction)를 사용자 정의 타입으로 구현한 것이다.

- 클래스(class)란 구조체의 상위 호환으로 이해하자.

  > **struct와 다른 점:  접근법의 차이** struct의 디폴트 접근 제한자는 public이다. 
  >
  > - `sturct` : 접근제어 지시자를 따로 선언하지 않는다면 모든 변수화 함수는 public으로 선언
  >
  > - `class` :  접근제어 지시자를 따로 선언하지 않는다면 모든 변수화 함수는 private로 선언

- 클래스 정의 파일은 '클래스이름.h'파일에 저장한다.

- 클래스의 멤버 변수를 프로퍼티(property), 멤버 함수를 메소드(method)라고도 한다.

- 클래스를 사용하기 위해서는 우선 해당 클래스 타입의 객체를 선언해야 하며, 선언된 해당 클래스 타입의 객체를 인스턴스(instance)라고 한다. 인스턴스는 메모리에 대입된 객체를 의미함.

- 클래스는 개념을 정의하고 객체는 클래스의 실체를 정의한다. 따라서 객체마다 데이터멤버 변수의 값을 따로 갖는다. 멤버 함수의 구현 코드는 모든 객체가 공유한다.

  > 클래스의 각 멤버는 그 클래스에 대한 '인스턴스'인 '객체'단위로 적용된다.







## 2. class 구성

#### 1. class 코드 예제

 ```c++
class Foo 					// class 클래스이름
{
	private:				// 접근제어지시자:
	
    	int mValue1;		// Foo 클래스의 데이터 멤버
    	int mValue2;
    	int sum;
    
    public: 				// 접근제어지시자:
    
    	Foo()				// 생성자(디폴트)
        {					// 생성자는 프로토타입(반환타입)이 없다(void도 작성 안함)
           mValue = 0; 
        }
    	
    	Foo(int a, int b)	// 생성자 (매개 변수를 사용함)
        {
            mValue1 = a;
            mValue2 = b;
            sum = 0;
        }    
								// 메서드
    	void SumValue() 		// 클래스 멤버 함수	
    	{
         sum = mValue1 + mValue2;  // 값을 변경하는 동작이 있음
    	}	
    
    	void SumValue(int a, int b)  // 인자를 받는 멤버함수
    	{
         sum = a + b; 
    	}	
        
    	void PrintValue() const; 
        {
            cout<<"sum의 값: "sum<<endl;  // 값을 변경하는 동작이 없음
        }
     
    
};	// C++에서 클래스는 '문장'이므로 반드시 세미콜론(;)으로 끝나야 한다.
 ```

> - Foo class에서 선언된 함수는 'Foo class에서 지원하는 메서드' 라고 한다.
> - 메서드는 비정적 멤버, 데이터 멤버는 정적 멤버다.
>
> - 메서드는 프로토타입(void같은)과 메서드 이름, 메서드를 구현하는 정의 코드가 반드시 있어야 한다.
>
> - 데이터 멤버는 가능하면 private에서 선언한다.
>
> - 데이터 멤버는 생성자 안에서 초기화한다.
>
> -  클래스를 선언하게 되면 그 클래스는 메모리에 객체로써 자리를 잡게 된다. 그러나, 이 객체는 해당 메모리에 자리만 잡고 있을 뿐이지, 초기화는 되지 않으므로, 생성자를 통해서 초기화를 해줄 필요가 있다.
>
>   > 객체가 선언되면 class 안의 생성자 함수가 호출돼서 실행된다. 
>
> - 클래스 정의는 주로 헤더 파일에 정의하고, 메서드 정의는 소스 파일에 작성한 뒤 소스 파일에서 #include 문으로 헤더 파일을 불러오는 방식으로 사용한다.
>
> > 위의 코드를 다시 정리하면
>
> ```c++
> // Foo.h 헤어파일
> class Foo 					
> {
> 	private:				// 접근제어지시자:
> 
>     	int mValue1;		// Foo 클래스의 데이터 멤버
>     	int mValue2;
>     	int sum;
> 
>     public: 				// 접근제어지시자:
> 
>     	Foo();				// 생성자(디폴트) 디폴트생성자라고 불림
> 
>     	Foo(int a, int b);	// 생성자 (매개 변수를 사용함) 
> 								// 메서드
>     	void SumValue(); 		// 클래스 멤버 함수	
> 
>     	void SumValue(int a, int b);  // 인자를 받는 멤버함수
> 
>     	void PrintValue() const; 
> 
> };
> ```
>
> ```c++
> // 메서드 파일을 모아둔 소스파일
> 
> #include "Foo.h"    //클래스 헤더파일을 포함히야 한다.
> 
> 		Foo::Foo()	// 소스파일에서는 클래스명::함수명 형태로 함수 작성
>         {			// :: 는 스코프 지정 연산자
>            mValue1 = 1;
>            mValue2 = 2;
>            sum = 5; 
>         }
> 
>     	Foo::Foo(int a, int b)	
>         {
>             mValue1 = a;
>             mValue2 = b;
>             sum = 0;
>         }    
> 
>     	void Foo::SumValue() // 아래 메서드와 이름은 같지만 매개변수는 없음(오버로딩)
>     	{
>          sum = mValue1 + mValue2; 
>     	}	
> 
>     	void Foo::SumValue(int a, int b)  
>     	{
>          sum = a + b; 
>     	}	
> 
>     	void Foo::PrintValue() const
>         {
>             cout<<"sum의 값: "<<sum<<endl;  
>         }
> 
> void FOO::PrintAll() const
> {
>     cout << "sum의 값: "<<sum <<endl;
>     cout << "Value1의 값: "<< Value1 endl;
>     cout << "Value2의 값: "<< Value2 <<endl; 
> }
> ```
>
> - 클래스 정의 코드 다음에 메서드 정의 코드가 나와야 한다.



#### 2. 접근 제어 지시자, 적용 가이드

- `public` : 어디서든 접근 가능

  > 모든 클라이언트가 사용할 동작(메서드). 
  >
  > private 또는 protected 데이터 멤버에 대한 접근 메서드(게터와 세터)

- `protected` : 상속관계에 놓여있을 때, 유도 클래스에서의 접근 허용

  > 외부 클라이언트가 사용하면 안 되는 헬퍼 메서드

- `private` : 클래스 내에 정의된 함수에서만 접근 허용

  > 데이터 멤버,  public, protected에도 적용할 필요성을 못느끼는 모든 것

> class에서 접근제어 지시자를 따로 선언하지 않는다면 모든 변수화 함수는 private로 선언됨



#### 3. 메서드

- 메서드는 같은 클래스에 정의된 다른 메서드도 호출할 수 있다.

```c++
#include "Foo.h"
void Foo::setValue(int inValue)   
{
    mValue1 = inValue;
    return PrintValue();   
} //예로 들기 위한 코드임
```

- *this pointer**

  >- 일반 메서드를 호출하면 항상 메서드가 속한 객체의 포인터인 this가 숨겨진 매개변수 형태로 전달된다. 
  >- this포인터로 해당 객체의 데이터 멤버나 메서드에 접근할 수 있으며, 다른 메서드나 함수에 매개변수로 전달할 수도 있다.
  >- 때로는 이름을 명확히 구분하는 용도로도 사용된다.
  >
  >> ```c++
  >> void Foo::setValue(double Value)
  >> {
  >> this->Value = Value;     // this.Value는 데이터멤버, Value는 매개변수
  >> }	
  >> //------------------또는------------------
  >> // Foo class의 생성자
  >> Foo(int sum, int Value1, int Value2)		
  >> {
  >> this->sum = sum;
  >> this->Value1 = Value1;
  >> this->Value2 = Value2;
  >> }
  >> ```
  >
  >- 어떤 객체의 메서드 안에서 다른 메서드나 함수를 호출하는 과정에서 그 객체의 포인터를 전달할 때도 this 포인터를 사용한다.
  >
  >> ```c++
  >> //printVlaue 메서드에서 SumValue()를 호출했다고 가정
  >> void Foo::printVlaue(const Foo& tmp)  const  //인수로 객체의 포인터를 받아옴
  >> {
  >>      cout<<tmp.SumValue()<<endl;  //SumValue()함수 호출
  >> } 
  >> ```
  >>
  >> printVlaue() 함수를 setVlaue() 메서드 안에서 호출하려면 반드시 *this를 인수로 전달해야 한다. 그래야 printVlaue() 안에서 호출할 SumValue() 메서드는 자신을 호출한  printVlaue() 가 setValue()에 속한 것임을 알 수 있다.
  >>
  >> ```c++
  >> //setValue()에서 printVlaue()를 호출했다고 가정
  >> void Foo::setValue(double Value)
  >> {
  >>     this.Value = Value;    
  >>     printVlaue(*this);   //*this인수
  >> }	
  >> ```



#### 3. 객체

> - 객체가 생성되면, 그 객체는 자신만의 class타입의 데이터 멤버에 접근할 수 있다. 
> - 메서드는 클래스에 정의된 데이터 멤버 중 객체에 속한 멤버에 대해 접근한다.



- **객체 선언**

1. 스택에 생성한 객체

> - 형태
>
> ```c++
> Foo myFoo;  	// 클래스이름 객체참조변수이름;
> ```
>
> > class 타입의 변수를 '객체' 라고 함
>
> ```c++
> int main(void)
> {
>     Foo* myFoo;    			// 자신만의 mValue를 가지고 있음
>     // 디폴트 생성자 호출
>     
>     Foo* myBar(4, 5);		// 얘도 자신만의 mValue를 가지고 있음
>     //인수 4, 5를 매개변수로 하는 생성자 호출
>     
>     
>     // 객체를 통한 멤버 함수의 호출
>     myFoo.PrintAll();			//객체이름.멤버함수이름();          
>     myBar.PrintAll();						
> 	// 멤버 함수는 멤버 참조 연산자(.)를 사용하여 호출할 수 있다.
> }
> 
> /*----------------- 출력 결과 -----------------
> sum의 값: 1        
> Value1의 값: 2
> Value2의 값: 5
>     
> sum의 값: 4        
> Value1의 값: 5
> Value2의 값: 0
> ```
>

2. 힙에 생성한 객체

> ```c++
> Foo* myFoo = new Foo();
> Foo* myBar = new Foo();
> 
>  myFoo->PrintAll();				
>  myFoo->SumValue(2, 5); // 매개변수가 있는 SumValue() 메서드 호출
> 
>  myBar->PrintAll();				
>  myBar->SumValue();		// 매개변수가 없는 SumValue() 메서드 호출
> 
> // 힙에 생성한 객체로 멤버 함수를 호출할 땐 -> 를 사용하여 호출할 수 있다.
> 
> delete myFoo;   
> myFoo = nullptr;
> delete myBar;   
> myBar = nullptr;
> ```
>
> - 힙에 할당한 객체 메모리도 반드시 delete로 해제해야 한다.
>
> - 메모리 관련 문제가 발생하지 않게 하려면 반드시 **스마트 포인터**를 사용한다.
>
>   ```c++
>   Foo tmp1 = make_unique<Foo>();
>   tmp->num3(3, 7);
>   ```
>
>   > 스마트 포인터를 사용하면 메모리를 자동으로 해제하기 때문에 직접 해제하는 문장을 작성할 필요가 없다.
>   >
>   > 참고 내용: [스마트 포인터](https://github.com/HibernationNo1/TIL/blob/master/study_C%2B%2B/smart%20pointer%EC%97%90%20%EA%B4%80%ED%95%98%EC%97%AC.md)

3. 다른 클래스의 데이터 멤버로 정의된 객체

> ```c++
> class Foo 					
> {
> 	private:			
>     	int mValue1;		
>     	int mValue2;
>     	int sum;
>     public: 			
>     	Foo();			
> };
> 
> class Bar
> {
>     public: 
>         Bar();
>     private:
>     	Foo mValue1;      //Foo class의 데이터 멤버를 Bar class의 객체 데이터 멤버로 정의  
> };  
> ```
>
> > 여기서 `mValue1`를 객체 멤버라고 한다.
> >
> > 만약 `Foo()`생성자가 없으면 컴파일러는 Bar class에서 정의된 `mValue`을 초기화 할 방법이 아예 없다.
> >
> > c++은 객체 멤버를 디폴트 생성자로 초기화한다. 디폴트 생성자가 없으면 이 객체를 초기화할 수 없다.



- **객체의 라이프 사이클**

> - 객체의 라이프 사이클은 생성, 소멸, 대입 세 가지가 있다.
> - 스택에 생성되는 객체는 선언하는 시점에 class의 멤버 변수도 생성된다.
> - 스마트 포인터나 `new`를 사용해서 힙에 생성한 객체는 직접 공간을 할당해야 class의 멤버 변수도 생성된다.



#### 4. 생성자

> - 생성자는 스스로 자기 자신의 객체를 초기화 하는 방법을 정의하는 것으로써, 생성자의 이름은 항상 클래스명과 동일해야 한다. 
>  - 오버로딩을 통해서 인자값을 받을 수 있으나, 리턴값을 가질 수 없다.
>  - 객체는 생성자를 통해 생성되고 그 객체의 값을 초기화할 수 있다. 
>  - 생성자를 하나도 지정하지 않으면 인수를 받지 않는 디폴트 생성자를 컴파일러가 대신 만들어준다.



##### 1.**디폴트 생성자**

> 디폴트 생성자는 아무런 인수도 받지 않는 생성자다. 영인수 생성자라고도 부른다. 디폴트 생성자를 이용하면 직접 값을 지정하지 않고도 데이터 멤버를 초기화할 수 있다.
>
> **디폴드 생성자가 필요한 경우 : `객체 배열`**
>
> - 객체 배열을 생성하는 과정
>
> 1. 원하는 객체들을 배열에 모두 담을 정도로 충분한 공간을 연속된 메모리에 할당한다. 
> 2. 그러고 나서 각 객체마다 디폴트 생성자를 호출한다. 이 때 인수는 없다. 
>
> > **스택 배열이라면?**
> >
> > 스택 배열이라면 객체를 선언할 때 **이니셜라이저**를 제공하는 방식을 사용하거나, 디폴드 생성자를 정의하자. 
> >
> > **이니셜라이저**
> >
> > ```c++
> > Foo myFoo[2] = {Foo(0), Foo(3), F(23)}; 
> > ```
> >
> > 단, vector 컨테이너에 저장하려면 반드시 디폴드 생성자를 정의한다.
> >
> > 
>
> **걍 디폴트 생성자는 정의하자.**



##### 2. **스택과 힙 객체 생성자**

> 1. 스택 객체 생성자
>
>    >스택 메모리를 사용하는 생성자는 객체가 선언될 때 바로 호출한다. 
>
>    ```c++
>    Foo myFoo;  	// 인수가 있을 때: Foo myFoo(3); 
>    ```
>
>   2. 힙 객체 생성자
>
>      >힙 메모리를 사용하는 생성자는 객체가 선언된 다음 호출된다.
>
>      ```c++
>      Foo myFoo = make_unique<Foo>();  
>      ```
>
>      > 힙 객체 생성자를 이해하기 위해 꼭 봐야 할 참고내용
>      >
>      > [스마트 포인터](https://github.com/HibernationNo1/TIL/blob/master/study_C%2B%2B/smart%20pointer%EC%97%90%20%EA%B4%80%ED%95%98%EC%97%AC.md)



##### 3. **여러 생성자 제공**

> 클래스에 생성자를 여러 개 만들 수 있다. 이름은 모두 클래스 이름으로 정하고, 인수의 개수나 타입만 서로 다르게 정의한다.

```c++
class Foo
{
  public:
    Foo(double a);  // double타입의 인수를 받는 생성자 
    Foo(int b);		// int타입의 인수를 받는 생성자 
    Foo(string c)
};

int main(void)
{
    Foo myFoo(1.72); 		// double타입의 인수를 받는 생성자 사용
    Foo myBar(2);			// int타입의 인수를 받는 생성자 사용
    auto myBaz = make_unique<Foo>("5.5")	// string타입의 인수를 받는 생성자 사용
}
```



##### 4. **생성자 이니셜라이저**

> - 일반 생성자 작동 과정: 
>
> >  데이터 멤버 변수를 생성 후, 객체가 구성됐다면 생성자를 호출한 후 생성자 안에서 객체에 따로 값을 대입해야 함.
>
> - 이니셜라이저 작동 과정
>
> > 데이터 멤버를 생성하는 과정에서 초깃값을 설정할 수 있음. 훨씬 효율적 

```c++
class Foo
{
    // 매개변수가 있는 생성자 이니셜라이저
    Foo(int a, b) : mvalue1(a),mvalue2(b)  
    // 생성자(타입 매개변수) : 멤버변수(매개변수)
    {
        // 멤버변수 mvalue1의 초깃값 = a, 멤버변수 mvalue2 초깃값 = b
    }
    
    // 매개변수가 없는 생성자 이니셜라이저
    Foo() : mNum1(1),mNum2(2) { }
    // 멤버변수 mNum1의 초깃값 = 1, 멤버변수 mNum2의 초깃값 = 2
}
```

> - 데이터 멤버에 대해 디폴트 생성자가 정의돼 있다면 **생성자 이니셜라이저**에서 이 객체를 명시적으로 초기화하지 않아도 된다.
>
> -  **생성자 이니셜라이저**나 클래스 내부 생성자 구문으로 초기화해야 하는 데이터 타입과 그 이유
>
>   > 1. const 데이터 멤버:
>   >
>   >    >  const변수가 생성된 후에는 정상적인 방법으로 값을 대입할 수 없다. 반드시 생성 시점에 값을 지정해야 한다.
>   >
>   > 2. 레퍼런스 데이터 멤버: 
>   >
>   >    > 가리키는 대상 없이는 레퍼런스가 존재할 수 없다.
>   >
>   > 3. 디폴트 생성자가 정의되지 않은 객체 데이터 멤버:
>   >
>   >    > A 클래스 데이터 멤버를 B클래스에서 객체 데이터 멤버로 정의할 때, 디폴트 생성자가 없으면 이 객체를 초기화 할 수 없다.
>
> - **생성자 이니셜라이저**를 할 때 주의할 점
>
>   > **생성자 이니셜라이저**를 통해 나열된 데이터 멤버는 클래스 정의에 작성된 순서대로 초기화된다.



##### 5. **복제 생성자**

> 다른 객체와 똑같은 객체를 생성할 때 사용한다.
>
> 복제 생성자를 직접 작성하지 않으면 컴파일러가 대신 만들어주며 이 생성자는 데이터 멤버가 기본 타입이라면 똑같이 복사하고, 객체 타입이라면 그 객체의 복제 생성자를 호출한다. 
>
> 보통 컴파일러가 만들어주는 것만 해도 충분하다.

 ```c++
 class Foo
 {
  public:
     Foo(const Foo& src) : m1(scr.m1), m2(scr.m2),m3(scr.m3)   // 복제 생성자
     {
         
     }
 };  //데이터 멤버가 m1, m2, m3라고 가정할때의 복제 생성자
 ```
>
> - 복제 생성자는 원본 객체에 대한 const 레퍼런스를 인수로 받는다.
>- 생성자 안에서 원본 객체에 있는 데이터 멤버를 모두 복사한다. 새로 만들 객체의 데이터 멤버를 모두 기존 객체의 데이터 멤버로 초기화한다. 
> - C++에서 함수에 인수를 객체로 전달할 때 컴파일러는 그 객체의 복제 생성자를 호출하는 방식으로 초기화한다. (명시적으로 호출할때 아니면 다 이럴 때 사용됨)



- 복제 생성자 명시적으로 호출하기

> 주로 다른 객체를 똑같이 복사하는 방식으로 객체를 만들 때 사용한다.
>
> ```c++
> Foo myFoo(3);      // 첫 번째 객체 생성
> Foo myBar(myFoo);	// myFoo 객체를 복제하는 복제 생성자가 호출됨
> ```



##### 6. 레퍼선스로 객체 전달하기

> 함수나 메서드에 객체를 레퍼런스로 전달하면 복제 연산으로 인한 오버헤드를 줄일 수 있다. 객체에 있는 주소만 복사하기 때문이다.
>
> 객체의 값을 사용하는 함수나 메서드는 원본 객체를 변경할 수 있다.
>
> 값을 사용하지 않고 성능의 이유로 레퍼런스 전달 방식을 사용한다면 const를 붙여야 한다. (성능이 좋아진다.)

```c++
Foo(const Foo& stc);  //위의 코드에서 생성자 매개변수를 보면
// const 클래스명& 객체명  을 매개변수로 가지고 있다.  
```

















- 전체 코드

  ```c++
  #include <iostram>
  using namespace std;
  
  class Hibernation      		// class 클래스이름
  {
  	private:				// 접근제어지시자1:
  	
      int sum;				// 멤버변수
      int x;					
      int y;	
    
      
      void num1()				// 멤버함수
      {						// private 이므로 main함수에서 접근 불가능
          sum = x + y;
      }
      
      public: 				// 접근제어지시자2:
      
         Hibernation() 		// 기본 생성자 
      {
          sum = 0;			// 변수 값 초기화
          x = 1;
          y = 0;      
      }
      
      Hibernation(int s, int x1, int y1)			// 매개 변수를 사용하는 생성자
      {
          sum = s;
          x = x1;
          y = y1;
      }
      
      void num2() 			// 멤버함수
      {						// public 이므로 main함수에서 접근 가능
         sum = x + y;		
       cout << "두 수의 합: " << sum <<endl; 
      }
      
      void num3(int a, int b) 	// 인자를 받는 멤버함수
      {		
         sum = a + b;		
         cout << "두 수의 합: " << sum <<endl; 
      }
      
      void new(int x, int y); 	
      {		
         this-> x = x;          // class의 맴버변수 x = 인자의 그릇인 변수 x
         this-> y = y;	
      }
      
      
  };				// ; 필수
  
  int main(void)
  {
      Hibernaion tmp1, tmp2; 		// tmp1, tmp2라는 객체 선언										// == 입력 인수가 없는 기본 생성자 호출
      
      tmp1.num2();				// class 안의 num2라는 맴버 함수 호출
      tmp2.num3(2, 5);
      tmp1.num2();				
      tmp2.num3(5, 5);
     
      cout << endl;
      tmp1.new(2, 2);
      tmp1.num2();	
     
      cout << endl;
      Hibernaion tmp1(1, 2, 3)	// == 입력 인수가 있는 생성자 호출
      tmp1.num2();
          
      return 0;
  }
  /*
  ---출력---  
  두 수의 합: 1
  두 수의 합: 7
  두 수의 합: 1
  두 수의 합: 10
  
  두 수의 합: 4
  
  두 수의 합: 5
  
  */
  ```
  
  



### 3.  클래스 상속  

- **정의**

  >클래스 상속(Class Inheritance)이란 기초 클래스의 모든 특성을 물려받아 새롭게 작성된 클래스를 가리킨다.

- 특징

  > 1. 파생 클래스는 반드시 자신만의 생성자를 작성해야 한다.
  >
  > 2. 파생 클래스에는 기초 클래스의 접근할 수 있는 모든 멤버 변수들이 저장된다.
  >
  > 3. 파생 클래스는 기초 클래스의 접근할 수 있는 모든 멤버 함수를 사용할 수 있다.
  >
  > 4. 파생 클래스에는 필요한 만큼 멤버를 추가할 수 있다.
  > 5. 코드의 양도 줄어들고, 프로그램의 유연성이 높아지는 등 여러가지 이점을 누릴 수 있다.

- 선언

  ```c++
  class Winter : public Hibernaion
  //class 파생클래스이름 : 접근제어지시자 기초클래스이름
  {
   	private:
   	   
    	public:   							
  	Winter() : Hibernation()     // 생성자 상속
     // 클래스 이름 : 상속받은 부모클래스 이름
  }
  ```

  - private 상속: `class Winter : private Hibernaion`

    >private 상속을 하게되면 private보다 접근 범위가 넓은(public, protected) 멤버들은 모조리 private로 바꾸어서 넘어온다. 
    >
    >즉, class전체가 private.

  - protected 상속:  `class Winter : protected Hibernaion`

    >private, protected 멤버는 그대로 있고, Parent 클래스의 public 멤버는 protected로 바뀌어 상속되는 것.

  - public 상속: `class Winter : public Hibernaion`

    >부모 class의 접근 범위를 그대로 상속

- 생성자 상속 전체 코드로 이해하기

  ```c++
  #include <iostream>
  using namespace std;
  
  class A
  {
      private:
      int x;
      public:
      A() { x = 0; }  		// 기본생성자. 
      A(int x)				// int형 x를 매개변수로 받은 생성자
      {
          this->x = x;
          cout<< x <<endl;
   	}    
  };
  
  class B : public A 	//  A라는 class를 상속받은 B class
  {
      int y;             			// private: 는 생략 가능
      public:
    	B();				// 기본생성자. 아무것도 상속받지않음
      B(int y) : A(y+5)   //A의 class에서 매개변수를 가진 생성자를 상속 
      // 개체선언처럼 동작을 이해하면 됨
      {
          this->y = y;
          cout << y <<endl;
      }    
  };
  
  class C : public B
  {
      int m;
      public:
      C();
      C(int x,int y,int z) : B(x) // 받은 3 개의 인자 중 x를 상속받은 B 생성자에게 전달     
      {
          m = x*y*z;    // 받은 3개의 인자는 m을 초기화하는데 사용
          cout<< m <<endl;
      }    
  };
  
  int main(void)
  {
     C temp(1, 2, 3);
  }
  
  /* -- 출력
  6           C class의 C(int 1, int 2, int 3) 생성자 실시, 1값은 B에게
  1			B class의 B(int 1) 생성자 실시, 1+5값은 A생성자에게
  6			A class의 A(int 6) 생성자 실시
  */
  ```

  









**추가 참고할 내용**

- 객체 지향 프로그래밍

  > 객체 지향 프로그래밍에서는 모든 데이터를 객체(object)로 취급하며, 객체가 바로 프로그래밍의 중심이 됩니다.
  >
  > 객체(object)란 간단히 이야기하자면 실생활에서 우리가 인식할 수 있는 사물로 이해할 수 있습니다.
  >
  > 이러한 객체의 상태(state)와 행동(behavior)을 구체화하는 형태의 프로그래밍이 바로 객체 지향 프로그래밍입니다.
  >
  > 즉, 프로그램을 기능 단위로 조각 내서 프로그래밍하는 것.
  >
  > 또한, 이와 같은 객체를 만들어 내기 위한 틀과 같은 개념이 바로 클래스(class)입니다.

- 객체 지향 프로그래밍이 가지는 특징

  > 1. 추상화(abstraction)
  >
  > 2. 캡슐화(encapsulation)
  >
  > 3. 정보 은닉(data hiding)
  >
  > 4. 상속성(inheritance)
  >
  > 5. 다형성(polymorphism)

