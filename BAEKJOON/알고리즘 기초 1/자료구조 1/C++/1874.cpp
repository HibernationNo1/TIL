#include<iostream>
#include<string>
#include<stack>
#include<vector>

using namespace std;

#define endl '\n'

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, top = 0;
	cin >> n;
	stack<int> tmp;
	tmp.push(0);
	vector<char> res;
	
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		if (x > top) {
			for (int j = top + 1; j <= x; j++) {
				tmp.push(j);
				res.push_back('+');
				
			}
			tmp.pop();
			res.push_back('-');
			
			top = x;
		}
		else if (x < top) {
			if (x == tmp.top()) {
				tmp.pop();
				res.push_back('-');
				
			}
			else {
				cout << "NO";
				return 0;
			}
		}
	}

	int k = int(res.size());
	for (int i = 0; i<k; i++) {
		if (i == k - 1) {
			cout << res[i];
			break;
		}
		cout << res[i] << endl;
	}
	return 0;
}