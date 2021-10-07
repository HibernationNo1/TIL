#include <iostream>
#include <string>
using namespace std;

int main(void)
{ 
	int c = 0;
	cin >> c;
	double* test_case = new double[c+1];
	
	for (int i = 1; i <= c; i++)
	{
		int s = 0;
		double sum = 0, num = 0;
		cin >> s;
		int* each_case = new int[s + 1];

		for (int j = 1; j <= s; j++)
		{
			cin >> each_case[j];
			sum = sum + each_case[j];	
		}
		sum = sum / s;

		for (int j = 1; j <= s; j++)
		{
			if (each_case[j] > sum)
			{
				num++;
			}
			else
			{
				continue;
			}
		}
		num = num / s;
		test_case[i] = num;

		delete each_case;
	}

	for (int i = 1; i <= c; i++)
	{
		cout << fixed;
		cout.precision(3);
		cout << test_case[i] * 100 << "%" << endl;
	}	
	delete test_case;

	return 0;
}