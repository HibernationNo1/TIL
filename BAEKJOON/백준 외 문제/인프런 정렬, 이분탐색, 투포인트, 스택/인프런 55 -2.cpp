#include<iostream>
#include<stack>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

#define endl '\n'

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, count = 1;
	cin >> n;
	stack<int> tre;
	vector<int> arr(n);
	string str = "";

	for (int i = 0; i < n; i++) {
		cin >> arr[i];

		if (!(tre.empty()) && tre.top() < arr[i]) {
			cout << "impossible" << endl;
			return 0;
		}

		tre.push(arr[i]);
		str += "P";
		while (1) {
			if (tre.empty()) break;

			if (tre.top() == count) {
				tre.pop();
				str += "O";
				count++;
			}
			else break;

		}
	}

	cout << str << endl;

	return 0;
}