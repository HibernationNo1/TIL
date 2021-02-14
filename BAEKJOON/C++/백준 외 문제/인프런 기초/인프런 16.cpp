#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

int main(void)
{
	char str1[101], str2[101];
	int r = 0;
	cin >> str1;
	cin >> str2;

	sort(begin(str1), end(str1), greater<char>());
	sort(begin(str2), end(str2), greater<char>());

	for (int i = 0; str1[i] != 0; i++) {
		if (str1[i] != str2[i]) {
			r = -1;
			break;
		}
	}

	if (r == -1) {
		cout << "NO" << endl;
	}
	else {
		cout << "YES" << endl;
	}
	

	return 0;
}