#include <iostream>

using namespace std;

int main(void)
{
	int num[10]={};
	int max_num, tmp, i;
	cin >> num[1];
	tmp = num[1];

	for (i = 2; i <= 9; i++)
	{	
		cin >> num[i];
		if (tmp <= num[i])
		{
			tmp = num[i];
			max_num = i;
		}
		else
			continue;
	}
	if (num[1] == tmp)
	{
		max_num = 1;
	}

	cout << tmp << "\n" << max_num << endl;
	
	return 0;
}