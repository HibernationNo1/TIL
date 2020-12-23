#include <iostream>
using namespace std;

#define MY_NUMBER "Hello, World" // 전처리기(매크로) 사용. #define은 걍 문서편집 기능
// MY_NUMBER가 보이면 자동으로 "Hello World" 로 대체된다.  
// #define은 여기 소스파일 안에서만 정의가 된다.
int main()
{
	cout << MY_NUMBER << endl;
	// 전처리기 #ifdef, #ifndef, #endef
	// 빌드가 들어가기 전에 결정이 된다는 것.
	// 즉, "OS가 무엇인지 확인하고 빌드하자" 와 같이 쓰일 수 있다
	// 멀티플랫폼 SW를 개발할때 많이 사용
#ifdef MY_NUMBER			// 만약 MY_NUMBER이 정의되어 있다면
	cout << "Apple" << endl;
#endif						// ifdef를 닫아주는 역할
	// #else 로 대체 사용 가능
#ifndef MY_NUMBER			// 만약 MY_NUMBER이 정의되어 있지 않다면
	cout << "Orage" << endl;
#endif						// ifndef를 닫아주는 역할

	return 0;