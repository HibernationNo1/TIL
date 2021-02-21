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



### 3. copy함수

**형태**: `copy(배열의 시작 주소, 배열의 마지막 주소, 복사한 원소들을 저장할 곳의 시작점을 나타내는 반복자)`

> - 인자로 넣는 배열의 범위 index를 복사 후 마제막 인자로 들어간 주소에 붙여넣음
> - 배열의 시작주소 부터 마지막-1번째 주소까지 복사 // [begin, end)범위

```c++
#include <algorithm>
array<int 5> arr1 = {1, 2, 3, 4, 5};
array<int 5> arr2 = {6, 6, 6, 6, 6};

copy(arr1.begin(), arr1.begin()+3, arr2.begin()+1);  //범위 0~3까지
// arr2의 배열이 {6,1,2,3,6} 이 됨
```









## 원소를 수정하는 작업들

### 1. Sort함수

##### 1. sort()

**형태**:  `sort(배열의 시작 주소, 배열의 마지막 주소, 올림내림 구분<자료형>());`

> - 인자로 넣는 배열의 범위 index들을 오름차순(또는 내림차순)으로 재정렬한다.
> - sort함수의 1, 2번째 인자는 배열의 포인터나 반복자 객체를 인수로 줘야함
> - 배열의 시작주소 부터 마지막-1번째 주소까지 정렬 // [begin, end)범위

```c++
#include <algorithm>     //헤더파일 포함 필수
array<int, 5> arr = { 1,5,2,8,3 };

sort(arr.begin(),arr.end());    // arr배열을 오름차순으로 정렬 {1,2,3,5,8}
sort(arr.begin(),arr.end(), less<int>()); // 위와 동일
sort(arr.begin(),arr.end(), greater<int>()); // arr배열을 내림차순으로 정렬 {8, 5, 3, 2, 1}

sort(arr.begin(), arr.begin()+4); // arr배열의 첫 번째 index부터 4번째 인덱스까지 오름차순으로 정렬
```



**2차원 배열 정렬**

```c++
	int n;
	cin >> n;

	vector<vector<int>> arr(n, vector<int>(2));  // 2중 백터 배열

	for (int i = 0; i < n; i++) {
		cin >> arr[i][0]; 
		cin >> arr[i][1];
	}

	sort(arr.begin(), arr.end());   
```

> `sort(arr.begin(), arr.end()); ` 는 다중배열에 적용하면, 가장 하위 배열의 첫 번째 인자끼리만 정렬한다. 
>
> 첫 번째 인자의 값이 같을 때, 해당 인자들의 두 번째 배열끼리 비교 후 정렬된다.  
>
> 결과적으로 아래의 **비교함수 이용하기** 의 예시와 같은 원리이다.



**pair을 활용한 sort 정렬**

```c++
#include<iostream>
#include<vector>
#include<utility>  // pair 사용
#include<algorithm>

using namespace std;

#define endl '\n'

int main(void)
{
	int n;
	cin >> n;

	vector< pair<int, int>> arr(n);  // pair형 vector를 선언 ([n][2] 와 비슷한 2차원 배열과 같음)

	for (int i = 0; i < n; i++) {
		cin >> arr[i].first >> arr[i].second;
	}

	stable_sort(arr.begin(), arr.end());
	

	for (int i = 0; i < n; i++) {
		cout << arr[i].first << " " << arr[i].second << endl;
	}

	return 0;
}
```

>위의 **2차원 배열 정렬** 과 같은 방식으로 정렬된다.
>
>예시: [백준 11650번 문제](boj.kr/11650)



**비교함수 이용하기** 

**형태**:  `sort(배열의 시작 주소, 배열의 마지막 주소, 함수호출);`

```c++
#include <iostream>
#include <algorithm>

using namespace std;

struct Point{ // 구조체 선언
    int x;
    int y;
};

// const와  &를 통해서 레퍼런스로 받아오는걸 잊지말자!
// x순으로 정렬하고 x값이 같으면 y순으로 각각 오른차순으로 정렬
bool cmp(const Point &p1, const Point &p2){
    if(p1.x < p2.x){
        return true;  // true면 첫 번째 인자가 앞에 정렬됨
    }
    else if(p1.x == p2.x){  
        return p1.y < p2.y;
    }
    else{
        return false; // false이면 두 번째 인자가 앞에 정렬됨
    }
}

int main (){
    Point a[100];

    // 초기화를 했다고 가정

    // 정렬
    // 첫번째 인자는 시작지점 = 배열의 포인터
    // 두번째 인자는 끝나는지점 + 1 = a(배열의 포인터) + 배열의 크기
    sort(a, a+100, cmp);  //cmp함수 호출
}
```





##### 2. stable_sort()

**형태**:  `stable_sort(배열의 시작 주소, 배열의 마지막 주소, 함수호출);`

- stable_sort()는 구조체처럼 여러 값들이 묶여 있을 때 하나의 요소로 정렬을 했을 때 다른 요소들의 정렬 순서는 정렬 전과 같이 그대로 유지 될 수 있도록 하는 정렬이다.
- 여러 요소를 한 번에 정렬하는 과정에서, 그 중 특정 요소만 정렬이 적용되도록 할 때 사용한다.

```c++
#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>

using namespace std;

#define endl '\n'

bool cmd(const pair<int, string> &x, const pair<int, string> &y)
{
	return x.first < y.first;
}

int main(void)
{
	int n;
	cin >> n;

	vector< pair<int, int>> arr(n);

	for (int i = 0; i < n; i++) {
		cin >> arr[i].first >> arr[i].second;
	}

	stable_sort(arr.begin(), arr.end());
	

	for (int i = 0; i < n; i++) {
		cout << arr[i].first << " " << arr[i].second << endl;
	}

	return 0;
}
```

> pair의 first부분만 정렬되고, second부분은 first 정렬 된 상태 안에서,  입력 된 순서대로 정렬이 유지된다.
>
> 예시 문제: [백준 10814번 문제](boj.kr/10814)



### 2. reverse 함수

**형태**: `reverse(배열의 시작 주소, 배열의 마지막 주소)`

>- begin 부터 end 전 까지의 원소들의 순서를 역순으로 뒤집는다.  [begin, end)범위
>- 인자는 배열의 포인터나 반복자 객체를 인수로 줘야함

```c++
#include <algorithm>     //헤더파일 포함 필수

string alphabet;
cin >> alphabet;    // abcd라고 가정

reverse(alphabet.begin(), alphabet.end())

cout << alphabet;      // dcba 출력
```



###  3. max, min 함수

##### 1. max(), min()

**형태**: `max(a, b)`

>- min: 매개변수 a와 b의 값을 비교해서 최소 값을 반환한다.
>- max: 매개변수 a와 b의 값을 비교해서 최대 값을 반환한다.

```c++
#include <algorithm>     //헤더파일 포함 필수

min(1, 2); //1반환
max(1234.231, 1235.111) // 1234.231반환
    
max({1, 2, 3})  // 인자 3개 이상을 받을땐 배열형태로 넣자   
```



##### 2. max_element(), min_element()

**형태**: `max_element()(배열의 시작 주소, 배열의 마지막 주소)`

> - 배열의 요소 중 가장 큰(또는 작은) 값의 주소를 반환한다.

```c++
vector<int> arr(10) = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
cout << "max값: " << *max_element(arr.begin(), arr.end())<<endl;
cout << "min값: " << *min_element(arr.begin(), arr.end())<<endl;
```

> 주소를 반환한다는 점 기억하자.

