#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

int dp[101];

int main(void)
{
	int A[11], B[11], sumA = 0, sumB = 0;   
		
	for (int i = 0; i < 10; i++) {
		cin >> A[i];
	}
	for (int i = 0; i < 10; i++) {
		cin >>B[i];
		if (A[i] > B[i]) {
			A[i] = 3;
			B[i] = 0;
		}
		else if (A[i] == B[i]) {
			A[i] = 1;
			B[i] = 1;
		}
		else {
			A[i] = 0;
			B[i] = 3;
		}
		sumA += A[i];

		sumB += B[i];

	}
	
	if (sumA > sumB) {
		cout << sumA << " " << sumB << endl;
		cout << "A" << endl;
	}
	else if (sumA == sumB) {
		for (int i = 9; i >= 0; i--) {
			if (A[i] == 3) {
				cout << sumA << " " << sumB << endl;
				cout << "A" << endl;
				break;
			}
			else if (A[i] == 0) {
				cout << sumA << " " << sumB << endl;
				cout << "B" << endl;
				break;
			}
			
			if (i == 0 && A[i] == 1) {
				cout << sumA << " " << sumB << endl;
				cout << "D" << endl;
				break;
			}
		}
	}
	else {
		cout << sumA << " " << sumB << endl;
		cout << "B" << endl;
	}
	
	return 0;
}