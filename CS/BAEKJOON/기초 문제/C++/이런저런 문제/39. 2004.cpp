#include<iostream>

using namespace std;

#define endl '\n'

int count_five(long long x) {
	long long countf = 0;
	for (long long i = 5; i <= x; i = i * 5) {
		countf += (x / i);
	}
	return countf;
}

int count_two(long long x) {
	long long countt = 0;

	for (long long i = 2; i <= x; i = i * 2) {
		countt += (x / i);
	
	}
	return countt;
}

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);


	long long n[3], m[3], x[3];
	cin >> n[0] >> m[0];
	x[0] = n[0] - m[0];

	

	n[1] = count_five(n[0]);
	m[1] = count_five(m[0]);
	x[1] = count_five(x[0]);

	n[2] = count_two(n[0]);
	m[2] = count_two(m[0]);
	x[2] = count_two(x[0]);

	if (n[1] - m[1] - x[1] >= n[2] - m[2] - x[2])
	{
		cout << n[2] - m[2] - x[2] << endl;
	}
	else {
		cout << n[1] - m[1] - x[1] << endl;
	}

	return 0;
}