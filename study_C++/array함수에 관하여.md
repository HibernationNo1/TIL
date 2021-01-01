# array 배열에 대해서

### 1. 선언 및 입력

- **형태** :  array<자료형, 배열의 크기> 배열이름;

  ```c++
  #include<array>   //헤더파일 포함 필수
  
  array<int, 4> arr1 = {};      // 각 index값이 0 4개의 index를 가진 int형 배열 
  array<int, 4> arr1 = {1, 2, 3};  // 4번째 index값은 0
  array<char, 10> arr= {'a', 'b' ,'c'}; // 4번째부터 indexr값은 공백(띄어쓰기)
  ```

  >- 배열의 크기가 고정형이면 array함수를, 배열의 크기가 가변이면 vector함수를 활용하자.
  >
  >관련 내용: [vector함수에 관하여](https://github.com/HibernationNo1/TIL/blob/master/study_C%2B%2B/new%2C%20vector%EC%97%90%20%EA%B4%80%ED%95%98%EC%97%AC.md)

- 입력

  ```c++
  array<char, 10> arr= {};
  
  	for (int i = 0; i < 10; i++)
  	{
  		cin >> arr[i];
  	}
  ```

  > - `cin>>arr;` 또는 `getline`은 사용 불가. 
  >
  > 위 처럼 반복문을 사용해서 하나의 index마다 값을 할당해야 한다.



### 2. 관련 함수

```c++
#include<array>   //헤더파일 포함 필수

array<int, 10> arr = {}; 일 때
```

- `arr.begin()`: 배열의 시작 index를 가리킨다.

- `arr.end()`: 배열 마지막의 "다음" index를 가리킨다.

- `arr.fill(m)`: 배열의 모든 index값을 m으로 바꾼다.

- `arr.swap(tmp)`: 배열 tmp의 index를 arr배열과 스왑(교환)합니다.

  > arr배열과 tmp배열의 길이와 타입이 같아야 함.

- `arr.at(n)`: n번째 index값을 반환 (`arr[n]`) 과 같음

- `arr.empty()`: 배열 arr의 모든 index가 비어있으면 1을, 아니면 0을 반환.

- `arr.size()`: 배열 arr의 사이즈를 반환



### 3. 왜 사용해야 하는가?

- 객체이기 때문에 사이즈를 알 수 있다.

  > 기존의 배열(`char arr[n]`)의 사이즈는 #define 을 사용해서 매크로를 이용해 저장했지만, array배열은 `size()` 멤버 함수를 이용해 쉽게 알 수 있다.

- 배열 원소를 바꿔줄 때

  > 기존의 배열은 index값을 바꾸기 위해선 반복문으로 일일히 바꿔야 했지만, array배열은 `fill()` 멤버함수를 사용해서 동일한 인자로 한 번에 다 바꿀 수 있다.
  >
  > 단, 모두 다른 인자로 바꿀때는 반복문을 사용해야 한다.

- 배열의 각각의 원소들에 대해 대입 연산자를 호출 할 수 있다.

  ```c++
  #include <array>
  
  array<int, 3> tmp1 = {1,2,3};
  array<int, 3> tmp2 = {4,5,6};
  
  tmp1 =tmp2;  // tmp1 의 배열에 {4, 5, 6} 할당
  ```

  

- 여러 유용한 함수들을 사용할 수 있다. (위에서 설명)