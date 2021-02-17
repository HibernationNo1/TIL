#include <iostream>

using namespace std;

int main(void)
{
	int num, sum = 0;
	cin >> num;

	for (int i=0; i <= num; i++) 
	// for(반복 전 실행/ 준비내용 ; 조건 검사 내용(true에서 실행); 한 번 실행한 후 처리할 작업)
	{
		if ((i % 2) == 0)
		{
			sum = sum + i;
		}

	}
	cout << sum << endl;

	return 0;
}