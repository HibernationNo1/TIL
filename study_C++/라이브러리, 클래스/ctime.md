# ctime 

시간을 다루는 헤더파일로, time_t타입과 struct tm을 활용해서 현재 시간을 구현할 수 있다.



### time_t

time헤더에서 시간을 다루기 위해 만들어진 데이터 타입

time() 함수의 반환형이며, time()함수가 어떠한 기준애 의한 시간데이터를 반환하고 그 시간을 다루기 위해서 사용하는 데이터 타입이다.

**1970년 1월 1일 00시 00분(UTC) 부터 지금까지 초단위의 시간을 정수값**으로 표현하는 데이터다.

**예제)**

```c++
#include<iostream>
#include<ctime>  // 헤더파일 포함

using namespace std;

int main(void)
{
    time_t foo;  // time_t타입의 변수 foo 선언
    foo = time(nullptr); // time()함수를 통해서 현재까지 쌓인 초를 반환
    cout << foo << endl; 
}
```

> 위 foo를 출력해보면 어마어마하게 쌓인 시간을 초 단위로 출력됨을 볼 수 있다.
>
> tm구조체를 사용함으로써 우리가 원하는 시간 데이터를 얻을 수 있다.



### tm 구조체

tm구조체는 시간을 우리가 알아볼 수 있게 변수로 나누어서 만들어져 있는 구조체이다.

**tm구조체의 구조**

```c++
struct tm
{
    int tm_sec;   // seconds after the minute - [0, 60] including leap second
    int tm_min;   // minutes after the hour - [0, 59]
    int tm_hour;  // hours since midnight - [0, 23]
    int tm_mday;  // day of the month - [1, 31]
    int tm_mon;   // months since January - [0, 11]
    int tm_year;  // years since 1900
    int tm_wday;  // days since Sunday - [0, 6]
    int tm_yday;  // days since January 1 - [0, 365]
    int tm_isdst; // daylight savings time flag
};
```

> 이를 이용해서 우리가 원하는 데이터를 출력할 수 있다.



### 현재 시간 출력

**전체 코드**

```c++
#include<iostream>
#include<ctime>

using namespace std;

int main(void)
{
	struct tm tstruct;			// tm구조체의 포인터 객체 tstruct 생성
	time_t t= time(nullptr);	//초 단위로 된 현재 시간을 가져온다.  
	localtime_s(&tstruct , &t);	// localtime() 함수의 인자로 현재 시간에 대한 데이터 가져옴
	//localtime_s() 은struct tm의 결과 포인터를 반환한다. 
	//리눅스에서는 localtime_r()을 사용한다.

	int year = tstruct.tm_year + 1900;
	int month = tstruct.tm_mon + 1;
	int day = tstruct.tm_mday;
	int hour = tstruct.tm_hour;
	int minute = tstruct.tm_min;
	int second = tstruct.tm_sec;

	cout << year << endl;
	cout << month << endl;
	cout << day << endl;
	cout << hour << endl;
	cout << minute << endl;
	cout << second << endl;

	return 0;
}
```

> `localtime_s()` 은`struct tm`의 결과 포인터를 반환한다.  (리눅스에서는 localtime_r()을 사용한다.)