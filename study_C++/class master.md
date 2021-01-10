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

