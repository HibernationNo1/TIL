#include<iostream>
#include<vector>


using namespace std;

#define endl '\n'

int main(void) {
	
	int a, b, tmp = 0;
	cin >> a >> b;

	vector<int> arr(a);
	vector<int> brr(b);

	for (int i = a; i >= 1; i--) {
		if (!(a % i)) {
			arr[tmp++] = i;
		}
	}

	int c = tmp - 1;
	tmp = 0;
	
	for (int i = b; i >= 1; i--) {
		if (!(b % i)) {
			brr[tmp] = i;

			for (int j = 0; j <= c; j++) {
				if (brr[tmp] == arr[j]) {
					cout << brr[tmp] << endl;
					i = 0; 
					break;
				}
			}

			tmp++;
		}
	}

	for (int i = 1; i <= b; i++) {
		brr[i - 1] = a * i;
	}

	for (int i = 1; i <= a; i++) {
		arr[i - 1] = b * i;
		for (int j = 0; j < b; j++) {
			if (arr[i - 1] == brr[j]) {
				cout << brr[j] << endl;
				return 0;
			}
		}
	}
	
	return 0;
}