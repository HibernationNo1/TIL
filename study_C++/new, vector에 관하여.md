# 동적 할당

### 1. new와 delete 사용

#### -  선언

**형태** >> `포인터 변수명 = new 타입;`

```c++
int* num = new num(10);   // 10으로 num을 초기화
delete num;
    
char* arr = new char[10];     // 10개의 배열
delete [] arr;  // 1차원 배열의 delete

auto tmp = new char[10][5];   // 2차원 배열
for(int i = i; i <10; i++)     // 2차원 배열 delete 방법
{
    delete [] tmp[i];
}
delete [] tmp;
```

> - `new`: HEAP에 메모리를 만들고 주소를 리턴
> - `delete`: new가 가리키는 주소의 메모리를 해제
> - new를 사용해서 할당된 배열은 동적으로 할당된 배열일 뿐 동적 배열이 아님

#### -  입력

```c++
char* arr = new char[10];     // 10개의 배열
cin >> arr;        // 단어 단위로 입력
delete [] arr;  

char* arr = new char[10];      // 입력되는 문장(띄어쓰기 포함) 단위로 받기
cin.getline(arr, 10);
delete [] arr; 
```

> - 선언 후 따로 index를 초기화 해야함



### 2. vector 사용

**형태** : vector<타입> 변수명 = {};

#### 선언

```c++
#include <vector>     // 헤더파일 추가 필수

vector<char> vec(5); //  vec이라는 cahr형 배열에 5개의 index를 0으로 초기화
vector<int> vec(5,3); // 5개의 index를 3으로 초기화
vector<char> vec = {'a','b','c'};  // 3개의 index를 각 문자로 초기화

int arr[3] = {1, 2, 3};
vector<int> vec(arr);     // arr을 그대로 vec배열로 복사

vector<vector<int>> vec(2, vector<int>(4, 0)); //  2행 4열이며 각 열의 index는 0으로 초기화 된 2차원 벡터
```

- 메모리 HEAP에 동적할당
- 따로 `delete`를 하지 않아도 됨

- cin으로 index의 갯수를 받는 방법

  ```c++
  int a;
  cin >> a;
  vector<int> vec(a);    // 입력받은 a만큼의 index를 가진 1차원 배열
  
  int a, b;
  cin >> a >> b;
  vector<vector<int>> vec(a, vector<int>(b)); // a갯수의 행, b 갯수의 열 intdex를 가진 2차원 배열 
  // 초기화는 for문 활용
  ```

- 입력

  ```c++
  vector<int> vec(10);
  for (int i = 0; i<10; i++)  //for문 활용
  {
      cin >> vec[i];
  }
  ```

  > - `cin>>arr;` 또는 `getline`은 사용 불가. 
  >
  > 위 처럼 반복문을 사용해서 하나의 index마다 값을 할당해야 한다.




- 관련 메서드

  - `vec.assign(n, m)`: m의 값으로 n개의 index할당

    > 원소값이 할당이 안 된 상태에서  n을 index갯수와 다르게 입력시 오류 

  - `vec.push_back(m)`: 마지막 index 뒤에 m의 값을 할당

    > index 갯수가 늘어나는 것임

  - `vec.resize(n)`: 크기를(index 갯수를) n으로 변경한다

    > 더 커졌을 경우 추가된 index의 원소값을 default값인 0으로 초기화

  - `vec.resize(n,m)`: 크기를 n으로 변경한다.

    > 더 커졌을 경우 추가된 index의 원소값을 m으로 초기화한다. 나머지 index값은 그대로

  - `vec.size()`: index의 갯수 리턴

  - `vec.insert(vec.begin()+n,m)`: 1+n번째 자리에 m의 값을 가진 index를 삽입

    >- `vec.insert(vec.begin()+n, m, s)`: 1+n번째 자리에 m의 값을 가진 index를 s개 삽입
    >
    >- 기존 1+n 자리의 원소값을 새롭게 할당하는 것이 아님. 즉, index갯수 늘어남
    >
    >- `vec.insert(2, m, s)` 처럼 `vec.bigin()+n` 자리에 int형 값을 넣으면 에러.  m, s자리에는 int형 값 가능

  - `vec.erase(vec.begin()+n)`: 1+n번째 자리 index삭제

    > - `vec.degin()` 대신 int형 정수를 넣으면 에러
    >
    > - 원소값만 삭제하는 것이 아니라 1+n번째 자리를 삭제하는 것이기 때문에 index갯수가 줄어듦
    > - `vec.erase(vec.begin()+n, vec.begin()+m)`: 1+n, 1+m번째 자리 삭제

  - `vec.clear()`: 전체 index 삭제
  
  - `vec.empty()`: 배열 vec의 모든 index가 비어있으면 1을, 아니면 0을 반환.
  
  - `swap(vec1, vec2)`: 두 배열 vec1, vec2을 스왑(교환)
  
    > ```c++
    > vector<char> vec1 = { 'a' ,'b' ,'c' ,'d' };
    > vector<char> vec2 = { 'e' ,'f' ,'g' ,'h' , 'i' };
    > 
    > swap(vec1, vec2);
    > 
    > vec1 == { 'e' ,'f' ,'g' ,'h' , 'i' };
    > vec2 == { 'a' ,'b' ,'c' ,'d' };
    > ```



- 추가 내용

  - 고정된 사이즈의 배열을 사용할 것이라면 C++ array 배열을 사용하자.

    > 관련 내용
    >
    > [array함수에 관하여](https://github.com/HibernationNo1/TIL/blob/master/study_C%2B%2B/array%ED%95%A8%EC%88%98%EC%97%90%20%EA%B4%80%ED%95%98%EC%97%AC.md)

  - 사이즈가 변하는 배열읠 사용해야 한다면 C++ vector 배열을 사용하자.

