#include <iostream>


using namespace std;

int main(void)
{
	int num, sum = 0;
	cin >> num;

	for (int i = 1; sum < num; i++)
	{
		sum = sum + i;
		
	}
	cout << sum << endl;

	return 0;
}