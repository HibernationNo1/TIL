#include<iostream>
#include<string>
#include<stack>

using namespace std;

#define endl '\n'

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string str;
	getline(cin, str);

	int n = str.size();

	for (int i = 0; i < n; i++) {
		if (str[i] == '<') {
			for (int j = i; j < n; j++) {
				cout << str[j];
				if (str[j] == '>') {
					i = j;
					break;
				}
			}
		}
		else if (str[i] == ' ') {
			cout << str[i];
			continue;
		}
		else {
			stack<char> tmp;
			for (int j = i; j < n; j++) {
				if (str[j] == '<' || str[j] == ' ') {
					int m = tmp.size();
					for (int k = 0; k < m; k++) {
						cout << tmp.top();
						tmp.pop();
					}
					i = j - 1;
					break;
				}
				else if (j == n - 1) {
					tmp.push(str[j]);
					int m = tmp.size();
					for (int k = 0; k < m; k++) {
						cout << tmp.top();
						tmp.pop();
					}
					return 0;
				}
				tmp.push(str[j]);
			}
			
		}
	}
	
	return 0;
}