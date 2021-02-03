#include<iostream>
#include<string>
#include<vector>


using namespace std;

#define endl '\n'


int main(void)
{
	long long num1 = 0, num2 = 0;
	string str1, str2, str3, str4;
	cin >> str1 >> str2 >> str3 >> str4;

	str1 = str1 + str2;
	str3 = str3 + str4;

	for (int i = 0; i<int(str1.size()); i++) {
		num1 = num1 * 10;
		num1 = num1 + (str1[i] - 48);
	}

	for (int i = 0; i<int(str3.size()); i++) {
		num2 = num2 * 10;
		num2 = num2 + (str3[i] - 48);
	}

	cout << num1 + num2 << endl;

	return 0;
}