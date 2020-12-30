#include <iostream>
using namespace std;

int add(int a, int b); 
// 입, 출력의 형태만 먼저 선언하는 것.
int subtrack(int a, int b);

int main(void)
{
	cout << add(1, 2) << endl;  // 마우스 커서를 add에 올리고 오른쪽클릭
	// go to declaration 누르면 전방선언으로, go to definition 누르면 정의로 이동
	// peek definition 누르면 정의를 보여준다. 다른 파일에 definition이 있을 때 사용하기 좋다.
	cout << subtrack(1, 2) << endl;
	return 0;
}

int add(int a, int b)  // 함수의 정의 definition
{
	return a + b;
}

int subtrack(int a, int b)
{
	return a - b;
}