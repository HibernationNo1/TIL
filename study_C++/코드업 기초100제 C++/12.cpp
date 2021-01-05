#include <iostream>

using namespace std;

int main(void)
{
	float x;
	cin >> x;
	cout.setf(ios::fixed);  // 코드업 제출 전용 코딩
	//이 문장은 고정소수점으로0까지 나올 수 있도록 한 것
	cout << x << endl;

	return 0;
}