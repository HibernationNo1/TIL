#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main(void)
{
	int num[26] = {};
	int num2[26] = {};
	string alphabet;
	cin >> alphabet;
	
	for (int i = 0; i < alphabet.size(); i++)
	{
		if (alphabet[i] >= 97)
		{
				alphabet[i] = alphabet[i] - 32;     // 소문자를 대문자로 만들기
		}										//  a == 97, A == 65  32차이
				
		for (int j = 0; j < 26; j++)    // 'A'부터 'Z' 까지
		{
			if (alphabet[i] == 'A' + j)   //alphabet[i] 안의 원소가 어떠한 알파벳이라면
			{
				num[j]++;          // num[알파벳 자리숫자] ++
				num2[j]++;  // 내림차순 사용해서 가장 큰 값 찾기위한 용도
			} 
		}
	}  // 가장 높은 알파벳 열

	sort(num2, num2 + 26, greater<int>());  // num2을 내림차순 정렬
	if (num2[0] == num2[1])		 // 가장 높은 값이 2개면
	{
			cout << "?" << endl;
	}
	else // 가장 높은 값이 1개면
	{
		for (int i = 0; i < 26; i++)
		{
			if (num[i] == num2[0])  // num2의 가장 높은 값과 같은 num[i] 라면
			{
				char R = 'A' + i;
				cout << R << endl;
			}
		}
	}
		return 0;
}