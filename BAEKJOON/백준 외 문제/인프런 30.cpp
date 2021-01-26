#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

int main(void)
{
	int n;
	int ct, lt, rt, count = 0;
	cin >> n;

	for (int i = 1; i <= int(log10(n)) + 1; i++) {
		ct = n % int(pow(10, i)) / int(pow(10, i-1));
		lt = n / int(pow(10, i));
		if (i == 1) {
			rt = 0;
		}
		else {
			rt = n % int(pow(10, i - 1));
		}

		if (ct > 3) {
			count = count +  ((lt + 1) * int(pow(10, i - 1)));
		}
		else if (ct == 3) {
			count = count + ((lt) * int(pow(10, i - 1))) + rt;
		}
		else {
			count = count + ((lt) * int(pow(10, i - 1)));
		}
	}

	cout << count << endl;
	
	return 0;
}