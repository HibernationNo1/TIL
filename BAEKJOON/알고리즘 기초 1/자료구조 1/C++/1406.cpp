#include<iostream>
#include<string>
#include<list>

using namespace std;

#define endl '\n'

int main(void) {
	string s;
	int m;
	cin >> s >> m;
	list<char> str(s.begin(), s.end());
	list<char>::iterator c = str.end();

	while (m--)
	{
		char a;
		cin >> a;
		if (a == 'L') {
			if (c != str.begin()) {
				c--;
			}
		}
		else if (a == 'D') {
			if (c != str.end()) {
				c++;
			}
		}
		else if (a == 'B') {
			if (c != str.begin()) {
				c--;
				c = str.erase(c);
			}
		}
		else if (a == 'P') {
			
				char t;
				cin >> t;
				str.insert(c, t);
			
			
		}
	}

	for (char x : str) {
		cout << x;
	}

	return 0;
}