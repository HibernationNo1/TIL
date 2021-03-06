# pointer에 관하여

### 1. 특징

> - 포인터(pointer)는 어떠한 값을 저장하는 것이 아니라, 메모리 주소를 저장하는 변수다.
>
> - 포인터는 단지 메모리 주소에 불과해서 타입을 엄격히 따지지 않는다.
>
> - 포인터를 역참조하면 응용 프로그램은 포인터에 저장된 메모리 위치로 이동하여 메모리 내용을 검색한다.
>
> - 포인터의 크기는 실행 파일이 컴파일된 아키텍처에 따라 달라진다. 즉 64bit 실행 파일에서 포인터의 크기는 64bit(8byte) 이다.
>
> - `*`연산자로 포인터를 역참조하면 메모리에서 한 단계 더 들어가 볼 수 있다.
>
> - **레퍼런스**`&`연산자를 사용하면 특정 지점의 주소를 얻을 수 있다.
>
>   > 추가 내용: [레퍼런스에 관하여](https://github.com/HibernationNo1/TIL/blob/master/study_C%2B%2B/Reference%EC%97%90%20%EA%B4%80%ED%95%98%EC%97%AC.md)
>
> - 힙에 할당된 배열은 첫 번째 원소를 가리키는 포인터로 참조한다.
>
> - 스택에 할당된 배열은 배열 문법`[]` 으로 참조한다.
>
>   > 스택 배열에 포인터로 접근
>   >
>   > ```c++
>   > itn arr[10] = {};
>   > int* ptr = arr;     // 포인터로 arr배열에 접근
>   > ptr[4] = 5
>   > ```
>   >
>   > 배열을 함수에 넘길 때 유용하다.
>   >
>   > ```c++
>   > void exmple(int* arr, size) //arr배열을 받아온다.
>   > {
>   >     for(int i = 0; i<size; i++)
>   >         arr[i] *=2           	//각 배열에 *2
>   > }
>   > ```
>   >
>   > >이 함수를 호출할 때 `arr`가 
>   > >
>   > >스택 배열이면: exmple 함수에 배열 변수를 전달하고 컴파일러가 이를 배열에 대한 포인터로 변환.
>   > >
>   > >힙 배열이면:  이미 포인터가 담겨 있어서 함수에 값으로 전달됨.



**추가로 알아둬야 할 것**

>  `int a = 10;`
>
>  위 문장처럼 변수 a에 값을 할당하면 해당 값이 들어간 메모리의 위치도 할당되고, 프로그램에서 변수 a에 접근할 떄마다 값을 얻으려면 메모리 위치를 찾아야 한다. 그리고 우리는 어떤 메모리 주소가 할당되었는지 모른다.   
>
>  주소를 알고자 한다면 주소 연산자(레퍼런스) `&`를 사용해서 할당된 메모리 주소를 확인할 수 있다. 
>
>  레퍼런스는 주로 매개변수에 적용한다. (인수를 효율적으로 전달하기 때문에)
>
>  특정 주소(다른 주소)에서 x의 값에 접근하기 위해서는 역참조 연산자`*`를 사용할 수 있다. `*x`

---



### 2. 선언

**형태** :`자료형* 포인터 이름`

```c++
int* tmp;		
int* tmp1, *tmp2;  // 두 개의 포인터 선언

int value = 10;
```

> - 포인터는 선언 시 초기화되지 않고 쓰레기값이 들어가 있다.
>
> - 항상 포인터 변수를 선언하자마자 nullptr나 적절한 포인터로 초기화해야 한다. 절대로 초기화 하지 않은 상태로 내버려두지 않는다.
>
> - 포인터는 메모리 주소만 저장한다. (보통 다른 변수의 주소를 저장)
>
>   > 포인터 초기화를 한다면,  `int *tmp = 10;`
>   >
>   > 정수 리터럴 10에는 메모리 주소가 없기 때문에 이건 오류
>
> - 다른 변수의 주소를 할당하는 법: `포인터 = &변수; `
>
>   ```c++
>   int *tmp = &value;     //*tmp 초기화
>   *tmp = 3;              //  value에 3이라는 값 할당
>   //*tmp에 이미 포인터가 담겨 있으므로 값으로 취급 
>
>   int (*ptrary)[n] = &arr; // ptrary라는 이름의 포인터, 길이가 n인 arr이라는 배열의 주소 할당 
>   arr[2] = 22;  	 // arr배열의 index 2에 해당하는 지점에 값을 할당
>   *(arr+3) = 33; 	 // 포인터 연산자 사용. arr[3] =33; 과 같다.
>
>   int *ptrary[3];	// ptrary라는 이름의 포인터형 배열
>   int* ptrary[3] = {&a, &b, &c};  // a,b,c 각각의 주소 할당 (ptrary 한 번에 초기화)
>    ptrary[1] = &value1; // 배열 하나씩 주소 할당
>
>   int (*arr)[n]; // 길이가 n인 arr의 배열의 주소 할당 
>   ```
>
>   > 이때, tmp에는 value의 주소값이 할당된다.  
>   >
>   > `cout << tmp;` : value의 주소 출력
>   >
>   > `cout << *tmp;` : value의 값 출력
>   >
>   > 여기서 `*tmp`는 `value`와 같게 취급되므로 변수값인 것 처럼 값을 할당할 수 있다.
>
> - 포인터 변수의 자료형은 가리키는 변수의 자료형과 같다
>
> - 포인터를 사용하여 class 원소에 접근할 때는 화살표 연산자`->` 를 사용
>
> - 포인터 연산
>
>   > C++은 포인터 연산을 수행할 때 포인터에 선언된 타입을 이용한다.

---



### 3. 포인터를 사용하는 경우

- 배열은 포인터를 사용하여 구현된다. 포인터는 배열을 반복할 때 사용할 수 있다. (배열 인덱스 대신 사용 가능)

- C++에서 동적으로 메모리를 할당할 수 있는 유일한 방법이다. (가장 흔한 사용 사례)

  > ex) [동적 할당](https://github.com/HibernationNo1/TIL/blob/master/study_C%2B%2B/new%2C%20vector%EC%97%90%20%EA%B4%80%ED%95%98%EC%97%AC.md)

- 데이터를 복사하지 않고도 많은 양의 데이터를 함수에 전달할 수 있다.

- 함수를 매개 변수로 다른 함수에 전달하는 데 사용할 수 있다.

- 상속을 다룰 때 다형성을 달성하기 위해 사용한다.

- 하나의 구조체/클래스 포인터를 다른 구조체/클래스에 두어 체인을 형성하는 데 사용할 수 있다. 이는 연결리스트 및 트리와 같은 고급 자료구조에서 유용하다.



