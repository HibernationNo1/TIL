// n개의 정수를 입력받아 n개의 배열에 동적메모리 할당하여 내림차순으로 출력
#include <iostream>
#include <algorithm>
using namespace std;
int main(void)
{
	int n;
	cin >> n;

	int* num = new int[n];   // 동적 메모리 할당 >> 배열의 길이를 상수값이 아닌, 입력받을 값으로 할당 가능
	// 타입 *변수명 = new 타입;


	for (int i = 0; i < n; i++)
	{
		cin >> num[i];
	}

	sort(num, num + n, greater<int>());  // algorithm라이브러리에 있는 sort 함수
	// sort(배열의 시작 주소, 배열의 마지막 주소, 3번째 인자) 
	// >> 배열의 시작 주소는 포함하고, 마지막 주소는 포함하지 않음. 즉, num[0]부터 num[n-1]까지 적용
	// sort(num, num + n, less<자료형>()) >> num[0]부터 num[n-1]까지 오름차순으로 정렬 / 오름차순은 세 번째 인자 생략 가능
	// sort(num, num + n, greater<자료형>()) >> num[0]부터 num[n-1]까지 내림차순으로 정렬

	// 배열의 n번째 주소: 배열이름 + n 으로 표현 가능
	for (int i = 0; i < n; i++)
	{
		cout << num[i] << " ";
	}

	// 동적 메모리 해제 방법 :  delete 변수명;
	// 해제 안해도 오류는 안뜨지만 일반적으로 코드 마지막에 해제한다.
	delete num;

	return 0;
}