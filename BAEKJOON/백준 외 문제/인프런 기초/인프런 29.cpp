#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int main(void)
{
	int count = 0;
	int n, tmp;
	cin >> n;

	for (int i = 1; i <=n; i++) {
		tmp = i;
		while (tmp > 0) {
			if (tmp % 10 == 3) {
				count++;
			}
			tmp = tmp/10;
		}
	
	}
	cout << count <<endl;	
	
	return 0;
}