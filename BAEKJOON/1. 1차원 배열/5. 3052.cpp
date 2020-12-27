#include <iostream>
#include <string>  

using namespace std;

int main(void)
{ 
	int arr[11];
	int arr2[11];
	int n = 10;
	for (int i = 1; i <= 10; i++)
	{
		cin >> arr[i];
		arr2[i] = arr[i] % 42;

	}
	for (int i = 1; i <= 10; i++)
	{ 
		if (arr2[i] < 42)
		{
			for (int j = i+1; j <= 10; j++)
			{
				if (arr2[i] == arr2[j])
				{
					n--;
					arr2[j] = 42;
				}
			}
		}
		else
		{
			continue;
		}
	}
	cout << n << endl;

	return 0;
}