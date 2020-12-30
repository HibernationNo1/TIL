#include <iostream>

using namespace std;

int main(void)
{
	char ASCII[7] = { 'a', 'A','0',' ','z','Z'};
	for (int i = 0; i < 6; i ++ )
	{
		int ASCII_num = ASCII[i] - 1;
		cout << ASCII_num + 1 << " ";      //각 문자의 아스키코드
		/*
		'a' = 97 
		'A' = 65 
		'0' = 48 
		' ' 공백 = 32
		'z' = 122 
		'Z' = 90  
		*/
	}
	cout << endl;

	return 0;
}