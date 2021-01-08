# const   

### 1. 특징

- 변경되면 안 될 대상을 선언할 때 사용한다.

- 컴파일러는 const로 지정한 대상을 변경하는 코드를 발견하면 에러를 발생시킨다.

- 최적화 할 때 const로 지정된 대상을 최적화하면 효율 높다.

- const를 적용할 수 있는 대상은 변수 또는 매개변수, 메서드다.

**기본 형태**

```c++
const int a = 4;

a = 5;  // 컴파일 에러
```

> 변수에 const를 붙이면 그 값이 변하지 않게 보호할 수 있다.



### 2. const 포인터

- 변수가 포인터로 선언됐을 때

  - `const를 앞에 붙인다.` = 포인터로 가리키는 값이 수정되지 않게 한다.

  ```c++
  const int* tmp;			
  //   초기화 이후 * tmp = 3;		 << 컴파일 에러   
  
  const int* ptrary[10];	
  // 초기화 이후 *ptrary[3] = 3;		<< 컴파일 에러
  
  const int* tmp = new int(3);  
  // 바로 초기화 하면 그 값 고정   *tmp = 3;		 << 컴파일 에러   
  
  const int* ptrary = new int[3];	
  // 초기화를 할 수 없으니 의미가 없음
  ```

  > 

  - `변수명 앞에 const를 붙인다.` : 변수 자체가 수정되지 않게 한다.

  > 이 때는 변수 자체를 변경할 수 없게 되기 때문에 변수를 선언과 동시에 초기화해햐 한다. (주소값 고정)

  ```c++
  int* const  tmp = &A;			
  //   tmp = &B << 컴파일 에러
  
  int* const ptrary[2] = { &A, &B };	
  // 	ptrary[0] = &B; << 컴파일 에러
  
  int* const tmp = new int(4);  		
  //    tmp = &A; 컴파일 에러   
  
  int* const ptrary = new int[3]; 	 
  // 	ptrary = &value2; 컴파일 에러 
  
  ptrary[1] = 3;      
  //하나씩 전체를 초기화 하기 위해서는 for문으로 초기화
  
  // 처음 초기화를 ptrary = &value2; 와 같이는 안됨
  
  ```

  > 

  - 변수와 변수 포인터가 가리키는 값을 모두 const로 지정도 가능

  ```c++
  const int* const tem =  &value1;   
  //  *tmp = 3, tmp = &value2  둘 다 불가능
  ```

  > >  참고 내용:  [Pointer에 관하여](https://github.com/HibernationNo1/TIL/blob/master/study_C%2B%2B/pointer%EC%97%90%20%EA%B4%80%ED%95%98%EC%97%AC.md)

### 3. const 레퍼런스

- 레퍼런스의 특징
  - 레퍼런스는 기본적으로 const속성을 가지고 있다. (가리키는 대상을 변경하지 않는다.)
  - 레퍼런스에 대한 레퍼런스를 만들 수 없기 때문에 참조가 한 단계뿐이다.

- const 레퍼런스 형태

  ```c++
  int z = 3;
  
  const int &tmp = z;  // tmp = 4; << 컴파일 에러
  
  					// 단, z = 4; 는 가능
  ```



### 4. const 메서드

- 어떤 함수가 데이터 멤버를 변경하지 않는다고 보장하고 싶을 때 const 키워드를 붙인다.

- 함수가 const로 선언되면, 해당 함수 안에서 객체의 내부 값을 변경하지 않겠다는 계약을 클라이언트 코드와 맺는 셈이다.

- 데이터 멤버를 수정하는 메서드를 const로 선언하면 컴파일 에러

  - `--main함수 안에서--`

  ```c++
  int main(void)
  {
  	const int num(int a, int b);
  	{
  		return 1;
  	}
  
  const int sum(int a, int b);    // 컴파일 에러
  	{
  	sum1 = a + b;
  	return 1;
  	}
  	
      return 0;
  }
  ```

  > 

  - `--class 안에서--`

  ```c++
  class tmp
  {
  	int sum1;
     	public:
  	int num(int a, int b) const  // 요건 가능
  	{
  		return 1;
  	}
  
  	int sum(int a, int b) const    // 요건 불가능
  	{
  		sum1 = a + b;
  	  	return 1;
  	}
  };
  ```

  > main 함수에서 클래스의 객체를 const로 선언한다면, 해당 클래스 안의 const메서드만 호출할 수 있다.
  >
  > 추가) static 메서드를 const로 선언해서는 안된다. (static 참고)
  >
  > >  참고내용: [class에 관하여](https://github.com/HibernationNo1/TIL/blob/master/study_C%2B%2B/class%EC%97%90%20%EA%B4%80%ED%95%98%EC%97%AC.md)

>  9장 calss부분 p. 380 참고

### 5. constexpr 키워드

- 배열을 정의할 때, 배열의 크기를 상수 표현식으로 지정해야 하는 것을 상수 표현식으로 다시 정의할 수 있게 해준다.

  ```c++
  int tmp() { return 10;}
  
  int main(void)
  {
  array<int, 10> arr = {};       
      // array<int, tmp()> arr = {}; 이런식으론 컴파일 에러
  
  return 0;
  
  } 
  ```

  > constexpr 키워드를 사용하면 위의  tmp() 함수를 상수 표현식으로 다시 정의할 수 있다.

  ```c++
  #include <iostream>
  #include <array>
  using namespace std;
  
  constexpr int tmp() { return 10; }
  
  int main(void)
  {
  
  array<int, tmp()> asd = {1};      // 에러 없음. tmp()+1 도 가능
  int asd[tmp()];
  
  return 0;
  
  } 
  ```





###### 참고. 

>  p. 509 부터













