#include <iostream>
//#include "add.h"
// 헤더파일 만들기
// 소스파일>헤더파일(이름:add) 추가
// 해더파일에 int add(int a, int b);  전방선언과 정의를 넣는다. >> 헤더파일로 가져와서 사용 가능
// 헤더파일을 하위폴더 또는 다른 폴더로 옮겨놓았을 경우  #include "헤더파일이 위치한 폴더 이름/add.h"
using namespace std;

int add(int a, int b); // 전방선언. forward declaration


int main(void)
{
	cout << add(1, 2) << endl;

	return 0;
}

int add(int a, int b)  // 함수의 정의 definition
{
	return a + b;
}

// 파일의 분류
// 같은 프로젝트 안에서 소스파일 추가, definition부분만 가져다 쓰고 
// 여기에선 전방선언만 해도 빌드 가능.
