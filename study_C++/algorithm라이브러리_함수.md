# algorithm라이브러리_함수

C++ 표준 라이브러리의 라이브러리에는 원소들에 대해 작업할 수 있는 여러가지 함수(검색, 정렬, 원소들 수정하기, 개수 세기 등등) 들을 정의하고 있습니다.

이 때 작업할 원소들은 반복자 혹은 포인터를 통해 가리킬 수 있으며, 아래 함수들의 경우 작업을 시작할 원소와, 작업을 끝낼 원소 **바로 뒤**를 인자로 받게 됩니다. 식으로 표현하자면 `[first, last)` 의 형태로 보시면 됩니다.

정의 출처: [모두의 코드 algorithm](https://modoocode.com/256)

## 원소를 수정하지 않는 작업들

### 1. find함수

**형태**:  `find(배열의 시작 주소, 배열의 마지막 주소, 찾고자 하는 값);`

> - 배열에서 찾고자 하는 값을 찾았을 때 해당 index의 반복자 값을 리턴한다.
>
> - find함수의 1, 2번째 인자는 배열의 포인터나 반복자 객체를 인수로, 마지막 인자는 찾고자 하는 값(숫자 또는 문자)을 인수로 줘야함
>
> - string 배열의 관련 함수 find과는 다른 함수임
>
>   > 관련 내용: [string에 관하여](https://github.com/HibernationNo1/TIL/blob/master/study_C%2B%2B/string%EC%97%90%20%EA%B4%80%ED%95%98%EC%97%AC.md)

```c++
#include <algorithm>  // 헤더파일 포함 안해도 visual studio에서 빌드 됨
#include <vector> 


array<int, 5> arr = { 1,5,2,8,3 };
vector<char> vec = { 'e' ,'f' ,'g' ,'h' , 'i' };
string word("hibernation");

find(arr.begin(), arr.end(), 8); // arr배열의 시작부터 마지막 다음 주소까지 8의 값을 찾으면 해당index의 반복자 값을 리턴

find(arr.begin(), arr.end(), 8) - arr.begin(); 
//반복자 값을 리턴하면 int형에 담거나 cout을 할 수 없기 때문에 같은 반복자 타입의 값을 연산해서 int형을 변환.


int a;
a = find(arr.begin(), arr.end(), 8) - arr.begin(); 
	cout << a << endl;  // arr의 4번째 index값이 8이므로 3출력

a = find(vec.begin(), vec.end(), 'e') - vec2.begin();
	cout << a << endl;  // 0출력

a = find(word.begin(), word.end(), 'i') - word.begin();
	cout << a << endl;  // 1출력
```

컴파일 에러가 나는 경우

>```c++
>int *a;
>a = find(vec.begin(), vec.end(), 'e') - vec2.begin();
>```



### 2. count함수

**형태**:  `count(배열의 시작 주소, 배열의 마지막 주소, 세고자 하는 값);`

> - 배열에서 특정 값의 갯수를 반환한다.
> - find함수의 1, 2번째 인자는 배열의 포인터나 반복자 객체를 인수로, 마지막 인자는 세고자 하는 값(숫자 또는 문자)을 인수로 줘야함

```c++
#include <algorithm>  //헤더파일 포함 필수

string word("hibernation");
vector<char> vec = { 'e' ,'f' ,'g' ,'e' , 'i' };
array<int, 8> arr = { 1,5,3,8,5,5,2,5 };
	
cout << count(word.begin(), word.end(), 'i') << endl; // 2 출력
cout << count(vec.begin(), vec.end(), 'i') << endl;  // 1 출력
cout << count(arr.begin(), arr.end(), 5) << endl;  // 4 출력

```











## 원소를 수정하는 작업들









### 1. Sort함수에 관하여

**형태**:  `sort(배열의 시작 주소, 배열의 마지막 주소, 올림내림 구분<자료형>());`

> - 인자로 넣는 함수의 index들을 오름차순(또는 내림차순)으로 재정렬한다.
> - sort함수의 1, 2번째 인자는 배열의 포인터나 반복자 객체를 인수로 줘야함
> - 배열의 시작주소 부터 마지막-1번째 주소까지 정렬 // [start, end)범위

```c++
#include <algorithm>     //헤더파일 포함 필수
array<int, 5> arr = { 1,5,2,8,3 };

sort(arr.begin(),arr.end());    // arr배열을 오름차순으로 정렬 {1,2,3,5,8}
sort(arr.begin(),arr.end(), less<int>()); // 위와 동일
sort(arr.begin(),arr.end(), greater<int>()); // arr배열을 내림차순으로 정렬 {8, 5, 3, 2, 1}

sort(arr.begin(), arr.begin()+4); // arr배열의 첫 번째 index부터 4번째 인덱스까지 오름차순으로 정렬
```