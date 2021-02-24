#include<iostream>

using namespace std;

int tmp[1001];

int main(void)
{
	int n1, n2, num1, num2 = 0;
	cin >> n1;

	for (int i = 1; i <= n1; i++) {
		cin >> num1;
		if (num1 <= num2) {
			break;
		}
		else {
			for (int j = num2 + 1; j <= num1; j++) {
				tmp[j] = tmp[j-1]+j;
				}
		}
		num2 = num1;

		cin >> n2;
		if (n2 == tmp[num1]) {
			cout << tmp[num1] << endl;
			cout << "YES" << endl;
		}
		else {
			cout << tmp[num1] << endl;
			cout << "NO" << endl;
		}

	}
	
	return 0;
}