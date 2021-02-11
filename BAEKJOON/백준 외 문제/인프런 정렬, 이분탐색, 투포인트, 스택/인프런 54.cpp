#include<iostream>
#include<stack>
#include<string>
#include<algorithm>

using namespace std;

#define endl '\n'

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	stack<char> staaa;
	string str;
	cin >> str;

	for (int i = 0; i<int(str.size()); i++) {
		if (str[i] == '(') {
			staaa.push(str[i]);
		}
		else if (str[i] == ')') {
			if (staaa.size() == 0) {
				cout << "NO" << endl;
				return 0;
			}
			staaa.pop();
		}
	}

	if (staaa.size() == 0) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}

	return 0;
}