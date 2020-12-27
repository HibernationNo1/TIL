#include <iostream>
#include <cstring>
using namespace std;

int main(void)
{
	int num;
	char S[100] = {};
	int Alphabet[27] = {};
	cin >> S;
	// 배열 한 번에 같은 값으로 채우기
	fill_n(Alphabet, 27, -1);  // fill_n(배열이름, 배열길이, 채우고자 하는 값)
	
	//sizeof(S)를 한다면 실제로 차지하고 있는 메모리릐 크기를 구한다.
	for (int i = 0; i < strlen(S); i++)     //  strlen(배열이름) 문자열의 길이
	{
		num = S[i] - 'a';        // S[i] - 'a' 를 int형으로 받으면 숫자 출력. 
		// 'a' 는 아스키코드로 97

		if (Alphabet[num] == -1)   // 이미 i값이 할당된(중복된)경우는 제외
		{
				Alphabet[num] = i;      // S[i] 에서 i 는 ~번째 임을 의미
		}
		

	}

	for (int i = 0; i < 26; i++)
	{
		cout << Alphabet[i] << " ";
	}

	return 0;
}