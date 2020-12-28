#include <iostream>
#include <string>

using namespace std;

int main(void)
{
	
	string word;
	getline(cin, word);
	int* word_num = new int[word.size()]; //word와 word_num의 길이를 같게 한다.
	fill_n(word_num, word.size(), 0);		// 배열 한 번에 같은 값(0)으로 채우기
	int sum = 0;   // 단어의 갯수 새는 정수형 선언

	for (int i = 0; i < word.size(); i++)
	{
		
		if (word[i] == 32)   // 한 단어가 끝나는 지점(공백이 나타나는 지점) 파악 (공백의 아스키 코드 32)
		{
			if (i >= 1)     // i가 1보다 클 때. 
			{
				if (i == (word.size() - 1)) // 문장의 마지막에 공백이 나타난다면
				{
					continue;
				}
				word_num[i]++;  // 한 단어가 끝나는 지점의 word_num에 1 저장 (나머진 0임)
			}
			else if (i == 0) // i가 1이라면. 즉, 첫 단어가 공백이라면
			{
				if (word.size() == 1)  // cin에서 공백 하나만 입력됐다면
				{
					sum = -1;
					break;
				}
				else
				continue;
			}
			
		}
		sum = sum + word_num[i];
	}
	
	cout << sum + 1 << endl;

	delete word_num;

		return 0;
}