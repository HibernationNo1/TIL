#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define endl '\n'


int main(void)
{
	string s;
	int alphabet[26] = {};
	cin >> s;

	for (int i = 0; i < 26; i++) {
		alphabet[i] = 0;
	}

	  // 'a' = 97 + 26 - 1 == z = 122;
	for (int i = 0; i < int(s.size()); i++) {
		alphabet[s[i] - 97]++;
	}

	for (int i = 0; i < 26; i++) {
		cout << alphabet[i] << endl;
	}

	return 0;
}