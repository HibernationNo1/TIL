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

	fill_n(alphabet, 26, -1);  // fill_n(배열이름, 배열길이, 채우고자 하는 값)

	  // 'a' = 97 + 26 - 1 == z = 122;
	for (int i = 0; i < int(s.size()); i++) {
		if (alphabet[s[i] - 97] != -1) continue;
		alphabet[s[i] - 97] = i;
	}

	for (int i = 0; i < 26; i++) {
		cout << alphabet[i] << endl;
	}

	return 0;
}