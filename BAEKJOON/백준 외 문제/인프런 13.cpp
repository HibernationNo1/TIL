#include<iostream>
#include<cstring>

using namespace std;

int main(void)
{
	string str;
	int res[12] = {};
	memset(res, -1, sizeof(res));
	int n;
	cin >> str;

	for (int i = 0; str[i] != '\0'; i++) {
		res[str[i]-48]++;
	}

	for (int i = 1; i <= 9; i++) {
		if (res[i] >= res[11]) {
			n = i;
			res[11] = res[i];
		}
	}
	
	cout << n << endl;

	return 0;
}