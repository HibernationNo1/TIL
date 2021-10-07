#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>

using namespace std;


int main(void)
{
	int n, now, pre, count = 1, m = numeric_limits<int>::min();
	cin >> n;

	cin >> pre;
	for (int i = 1; i < n; i++) {
		cin >> now;
		
		if (now>= pre) {
			count++;
			m = max(m, count);
		}
		else {
			count = 1;
		}
		pre = now;
		
	}

	cout << m << endl;

	return 0;
}