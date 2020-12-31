# 동적 할당

### 1. new와 delete 사용

**형태** >> `포인터 변수명 = new 타입;`

#### 선언

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

- `new`: HEAP에 메모리를 만들고 주소를 리턴

- `delete`: new가 가리키는 주소의 메모리를 해제

- new를 사용해서 할당된 배열은 동적으로 할당된 배열일 뿐 동적 배열이 아님



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

- 관련 함수
  - 



