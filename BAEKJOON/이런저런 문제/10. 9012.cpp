#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define endl '\n'

int main(void)
{
	int p = 0, t;
	string str;
	cin >> t;
	
	for (int i = 0; i < t; i++) {
		cin >> str;
		

		for (int j = 0; j < str.size(); j++) {

			if (str[j] == '(') {
				p++;
			}
			else if (str[j] == ')') {
				p--;
			}

			if (p < 0) {
				break;
			}

		}

		if (p == 0) cout << "YES" << endl;
		else  cout << "NO" << endl;
		p = 0;
	}
	
	return 0;
}