# class에 관하여

### 1. 정의 및  특징

- 클래스(class)란 구조체의 상위 호환으로 이해하자.

  > **struct와 다른 점:  접근법의 차이**
  >
  > - `sturct` : 접근제어 지시자를 따로 선언하지 않는다면 모든 변수화 함수는 public으로 선언
  >
  > - `class` :  접근제어 지시자를 따로 선언하지 않는다면 모든 변수화 함수는 private로 선언

- class는 서로 연관 있는 데이터를 묶을 수 있는 문법적 장치, 객체 지향 프로그램을 작성할 수 있다.
- 객체 지향 프로그래밍의 특징 중 하나인 추상화(abstraction)를 사용자 정의 타입으로 구현한 것.

- 클래스의 멤버 변수를 프로퍼티(property), 멤버 함수를 메소드(method)라고도 한다.

- 클래스를 사용하기 위해서는 우선 해당 클래스 타입의 객체를 선언해야 하며, 선언된 해당 클래스 타입의 객체를 인스턴스(instance)라고 한다. 인스턴스는 메모리에 대입된 객체를 의미함.

- instance는 독립된 메모리 공간에 저장된 자신만의 멤버 변수를 가지지만, 멤버 함수는 모든 인스턴스가 공유한다.



### 2. 선언

- **형태**

 ```c++
class Hibernation      		// class 클래스이름
{
	private:				// 접근제어지시자1:
	
    int sum;				// 멤버변수
    int x;					
    int y;	
    
    
    void num1() 			// 멤버함수
    {						// private 이므로 main함수에서 접근 불가능
        sum = x + y;
    }
    
    public: 				// 접근제어지시자2:
    
       Hibernation() 			// 기본 생성자 
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
    
       void new(int x, int y) 	
    {		
       this-> x = x;          // class의 맴버변수 x = 인자의 그릇인 변수 x
       this-> y = y;	
    }
    
    
};				// ; 필수
 ```

- 접근 제어 지시자

  >- `public` : 어디서든 접근 가능
  >- `private` : 클래스 내에 정의된 함수에서만 접근 허용
  >
  >- `protected` : 상속관계에 놓여있을 때, 유도 클래스에서의 접근 허용
  >
  >접근제어 지시자를 따로 선언하지 않는다면 모든 변수화 함수는 private로 선언됨

- 생성자

  >- 클래스를 선언하게 되면 그 클래스는 메모리에 객체로써 자리를 잡게 된다. 그러나, 이 객체는 해당 메모리에 자리만 잡고 있을 뿐이지, 초기화는 되지 않으므로, 생성자를 통해서 초기화를 해줄 필요가 있다.
  >
  >- 생성자는 스스로 자기 자신의 객체를 초기화 하는 방법을 정의하는 것으로써, 생성자의 이름은 항상 클래스명과 동일해야 한다. 또한 오버로딩을 통해서 인자값을 받을 수 있으나, 리턴값을 가질 수 없는것이 특징이다. 
  >
  >- 객체가 선언되자 마자 class 안의 생성자 함수가 실행된다고 이해. 
  >
  >- 종류
  >
  >  - 기본 생성자
  >
  >    >매개 변수를 갖지 않거나 모두 기본값이 설정된 매개 변수를 가지고 있는 생성자를 **기본 생성자(Default constructor)**라고 한다
  >
  >    ```c++
  >    Hibernation() 			// 기본 생성자 
  >    {
  >            sum = 0;			// 직접 변수 값 초기화
  >            x = 1;
  >            y = 0;      
  >    }                   
  >    ```
  >
  >  - 매개 변수가 있는 생성자
  >
  >    >멤버 변수의 값을 특정한 값으로 초기화하고 싶은 경
  >
  >    ```c++
  >    Hibernation(int s, int x1, int y1)		
  >    {
  >            sum = s;		// 받은 매개변수로 맴버함수 초기화
  >            x = x1;
  >            y = y1;
  >    }
  >    ```
  >
  >    > 아래의 경우처럼 this활용 가능
  >
  >    ```
  >    Hibernation(int sum, int x, int y)		
  >    {
  >     this->sum = sum;
  >     this->x = x;
  >     this->y = y;
  >     cout << sum << " " << x << " " << y << endl;
  >    }
  >    ```
  >
  >    


- 멤버 함수의 정의

  ```c++
  void num1()
  {
      
  }
  //반환타입 멤버함수이름(매개변수목록) { 함수의 몸체; }
  ```

  > 만약 멤버 함수가 클래스의 선언 안에서 정의되면, 이 함수는 인라인 함수로 처리되어 위와 같이 범위 지정 연산자를 사용하여 소속 클래스를 명시할 필요가 없게 된다.
  >
  > 클래스 선언 밖에서 정의된 멤버 함수도 inline 키워드를 사용하여 인라인 함수로 처리할 수 있다.

- `this->변수` : 현재 접근하는 객체의 주소값을 가지고 있음.

  > - tmp라는 객체가 만들어지고 해당 객체에서 this가 포함된 함수를 실행하면, 'this'는 tmp라는 객체의 주소가 된다. 따라서 tmp가 가지고 있는 맴버변수에 접근이 가능하다.
  > - class의 맴버 변수의 값을 새롭게 할당할때 사용

- 객체 선언

  ```c++
  Hibernation tmp;  	// 클래스이름 객체참조변수이름;
  ```

  > class 타입의 변수를 '객체' 라고 함

- 멤버 함수의 호출

  ```c++
  tmp.num2();			//객체이름.멤버함수이름();               
  // 매개변수가 없는 멤버 함수의 호출.   
  
  tmp.num2(30)		// 객체이름.멤버함수이름(전달할 인수 목록); 
  {					// 함수 안에서 수행 할 박스{}가 있으면 ';' 안해도 됨
  }
// 매개변수가 있는 멤버 함수의 호출
  ```
  
  > 멤버 함수는 멤버 참조 연산자(.)를 사용하여 호출할 수 있다.



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

