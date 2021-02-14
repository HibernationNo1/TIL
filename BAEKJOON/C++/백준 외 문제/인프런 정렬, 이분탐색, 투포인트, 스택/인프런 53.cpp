#include<iostream>
#include<stack>
#include<algorithm>

using namespace std;

#define endl '\n'

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	stack<char> sta;
	int n, k;
	char str;
	cin >> n >> k;
	

	
	while (n) {
		if (n % k >= 10) {
			str = (n % k) + 55;
		}
		else {
			str = (n % k) + 48;
		}
		sta.push(str);
		n = n / k;
	}
	
	int tmp = int(sta.size());
	for (int i = 0; i<tmp; i++) {
		if (sta.top() - 48 < 10) {
			cout << int(sta.top() - 48);
		}
		else {
			cout << sta.top();
		}
		
		sta.pop();
	}


	return 0;
}