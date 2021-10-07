#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
	
	int num, sum = 0;
	cin >> num;
	for (int i = 1; i <= num; i++)
	{
		int n = 0, cp_n = 0;  // 단어가 바뀌는 순간의 횟수 저장할 메모리
		string word;
		cin >> word;
		char* cp_word = new char[word.size()+1];

		for (int j = 0; j < word.size(); j++)
		{
			cp_word[j] = word[j];   // 똑같은 원소의 다른 배열 만들고
			
		}
		sort(cp_word, cp_word + word.size(), less<char>());  // cp_word의 배열 오름차순 정렬

		for (int j = 0; j < word.size(); j++)
		{
			if (word[j] != word[j + 1])  // word배열의 j번째 배열 문자가 바로 뒤 배열의 문자가 다르다면
			{
				n++;  // 다음 단어로 넘어감
			}

			if (cp_word[j] != cp_word[j + 1])  // cp_word배열의 j번째 배열 문자가 바로 뒤 배열의 문자가 다르다면
			{
				cp_n++;  // 다음 단어로 넘어감
			}
		}
		
		if (n == cp_n)  // 기존에 입력받은 word와, word를 차순 정렬한 cp_word 의 알파벳 변화 갯수가 같으면 연속된 단어
		{
			sum++;
		}
	}
	cout << sum << endl;

	return 0;
}