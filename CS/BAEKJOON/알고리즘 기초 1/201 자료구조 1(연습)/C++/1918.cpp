#include<iostream>
#include<stack>
#include<deque>
#include<string>

using namespace std;

#define endl '\n'

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string str;
	deque<char> res;
	stack<char> tmp;
	getline(cin, str);

	for (int i = 0; i<int(str.size()); i++) {
		if ('A' <= str[i] && str[i] <= 'Z') {
			res.push_back(str[i]);
		}
		else if (str[i] == '(') {
			tmp.push(str[i]);
		}
		else if (str[i] == ')') {
			while (tmp.top() != '(') {
				res.push_back(tmp.top());
				tmp.pop();
			}
			tmp.pop();
		}
		else {
			if (str[i] == '+' || str[i] == '-') {
				while (!tmp.empty() && (tmp.top() == '/' || tmp.top() == '*' || tmp.top() == '-' || tmp.top() == '+')) {
					res.push_back(tmp.top());
					tmp.pop();
				}
				tmp.push(str[i]);
			}
			else {
				while (!tmp.empty() && (tmp.top() == '/' || tmp.top() == '*')) {
					res.push_back(tmp.top());
					tmp.pop();
				}
				tmp.push(str[i]);
			}
		}
	}

	while (!tmp.empty()) {
		res.push_back(tmp.top());
		tmp.pop();
	}

	int m = int(res.size());
	for (int i = 0; i<m; i++) {
		cout << res.front();
		res.pop_front();
	}

	return 0;

}