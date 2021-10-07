#include <iostream>
#include <string>  

using namespace std;

int main(void)
{ 
	int a, b, c;
	cin >> a >> b >> c;

	string str = to_string(a * b * c);

	int arr[10] = {};
	for (int i = 0; i <= str.size(); i++)
	{
		arr[str[i] - 48]++;	
	}
	for (int i = 0; i <= 9; i++)
	{
		cout << arr[i] << endl;
	}

	return 0;
}