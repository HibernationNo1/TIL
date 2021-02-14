#include <iostream>
#include <string>
using namespace std;

int main(void)
{ 
	int n, s = 0;
	int num = 0;
	cin >> n;
	int* sum = new int[n+1];

	string ox;
	for (int i = 1; i <= n; i++)
	{
		int score = 0;
		cin >> ox;

		for (int j = 0; j < ox.size(); j++)
		{
			if (ox[j] == 'O')
			{
				num++;
				s = score;
				score = s + num;
			}
			else if (ox[j] == 'X')
			{
				num = 0;
			}	
		}
		num = 0;
		sum[i]= score;
	}
	for (int i = 1; i <= n; i++)
	{
		cout << sum[i] << endl;
	}

	delete sum;

	return 0;
}