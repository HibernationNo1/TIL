#include <iostream>
#include<string>
using namespace std;

int main(void)
{
	string data;
	getline(cin, data, '\n');  // string함수 사용시 공백 포함 문자 입력받는 방법 
	cout << data << endl;

	return 0;
}