#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

int gNum(string &str)
{
	int s, n, j, num = 0;
	cin >> str;
	s = str.size();
	reverse(str.begin(), str.end());
	for (j = 0; str[j] != '\0'; j++) {
		if (str[0] == 48) {
			str.erase(str.begin());
			j--;
			s--;
		}
		else {
			n = (str[j] - 48);
			num = num + n * int(pow(10, s - j - 1));
		}
	}
	return num;
}

int gPrime(int x)
{
	int i = 2;
	if (x <= 1) return -1;
	else if (x == 2) return x;

	while (i<x) {
		if (x % i == 0) {
			break;
		}
		else {
			i ++ ;
		}

		if (i == x) {
			return x;
		}
	}

	return -1;
}

int main(void)
{
	int t, i;
	cin >> t;

	for (i = 1; i <= t; i++) {
		string str;
		int num = gNum(str);
		if (gPrime(num) != -1) {
			cout << num << endl;
		}
		else
			continue;
	}

	

	return 0;
}