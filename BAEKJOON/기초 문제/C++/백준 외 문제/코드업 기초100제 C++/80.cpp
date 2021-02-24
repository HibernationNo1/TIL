#include <iostream>

using namespace std;

int main(void)
{
	int sum = 0;
	int num, i;
	cin >> num;

	for (i = 1; sum < num; i++)  // sum이 num과 같을 때 한번 더 하면 안되기때문에 sum<=num 은 안됨
	{
		sum = sum + i;
	}
	cout << i - 1 << endl;  // 최종 i가 더해질땐 이미 num보다 높은 수이기 때문에 i-1


	return 0;
}