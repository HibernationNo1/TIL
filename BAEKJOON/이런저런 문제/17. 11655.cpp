#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

#define endl '\n'


int main(void)
{
	
	string s;
	getline(cin, s);

	for (int i = 0; i<int(s.size()); i++) {
		if (65 + 13 <= s[i] && s[i] <= 90) {
			s[i] = s[i] - 13;
		}
		else if (65 <= s[i] && s[i] < 65 + 13) {
			s[i] = s[i] + 13;
		}
		else if (97+13 <= s[i] && s[i] <= 122) {
			s[i] = s[i] - 13;
		}
		else if (97 <= s[i] && s[i] < 97 + 13) {
			s[i] = s[i] + 13;
		}
	
	}
		
	for (int i = 0; i<int(s.size()); i++) {
		cout << s[i];
	}

	return 0;
}