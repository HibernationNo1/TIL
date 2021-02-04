#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

#define endl '\n'


int main(void) {
	
	int n, b, tmp = 0;
	cin >> n >> b;

	for (int i = 1; i <= n; i++) {
		if (pow(b, i) > n) {
			tmp = i;
			break;
		}
	}

	vector<int> arr(tmp);

	for (int i = tmp-1; i >=0; i--) {
		arr[tmp-1 -i] = (n / int(pow(b, i)))%b;
	}

	vector<char> str(tmp);
	for (int i = 0; i < tmp; i++) {
		if (arr[i] >= 10) {
			for (int j = 10; j <= 35; j++) {
				str[i] = arr[i] + 55;
			}
		}
		else {
			str[i] = arr[i] + 48;
		}
		cout << str[i];
	}
	
	return 0;
}