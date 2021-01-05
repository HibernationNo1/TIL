#include <iostream>
using namespace std;

int main(void)
{
	int num;
	cin >> num;
	cout << "[" << num / 10000 * 10000 << "]\n"; 
	// int는 정수이기 때문에 1만으로 나누면 실수부분인 소수점 아래가 없어진다. 이후 다시 곱하기 1만.
	cout << "[" << num%10000/1000*1000 << "]\n";  // %n은 n으로 나눈 후 나머지를 의미
	cout << "[" << num % 1000 / 100 * 100 << "]\n";
	cout << "[" << num % 100 / 10 * 10 << "]\n";
	cout << "[" << num % 10 << "]\n";
	return 0;
}