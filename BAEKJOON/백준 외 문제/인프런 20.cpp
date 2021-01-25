#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

int dp[101];

int main(void)
{
	int n;
	int A[101], B[101];   //가위 = 1, 바위 = 2, 보 = 3;
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		cin >> A[i];
	}
	for (int i = 0; i < n; i++) {
		cin >>B[i];
		switch (A[i] - B[i]) {
		case -2:
			cout << "A" << endl;
			break;
		case -1:
			cout << "B" << endl;
			break;
		case 1:
			cout << "A" << endl;
			break;
		case 2:
			cout << "B" << endl;
			break;
		case 0:
			cout << "D" << endl;
			break;
		}
		
	}
	
	
	return 0;
}