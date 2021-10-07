#include <iostream>
using namespace std;


int main(void)
{
	int a, b;
	double c;
	long long int d;
	cin >> a >> b;
	d = (long long)a * b;// int형을 long long형에 할당하려면 앞에 (long long)표식 필요
	c = (double)a / b; //int형을 double형에 할당하려면 앞에 (double)표식 필요
	cout << a + b << "\n" << a-b << "\n" << d << "\n" << a / b << "\n" << a % b << endl;
	cout<<fixed;
	cout.precision(2);
	cout << c << endl;

		return 0;
}