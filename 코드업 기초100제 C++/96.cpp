#include <iostream>
using namespace std;
int main(void)
{
	int num[20][20] = {};
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++)
	{
		int a, b;
		cin >> a >> b;
		num[a][b] = 1;
	}
	for (int i = 1; i <= 19; i++)
	{
		for (int j = 1; j <= 19; j++)
		{
			cout << num[i][j] << " ";
		}
		cout << endl;
	}
   

	return 0;
}