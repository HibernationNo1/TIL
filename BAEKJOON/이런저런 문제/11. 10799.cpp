#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define endl '\n'

int main(void)
{
	int count = 0, p = 0;
	string str;
	cin >> str;

		for (int i = 1; i < int(str.size()); i++) {

			if (str[i] == ')' && str[i - 1] == '(') { //레이저
				if (p == 0) // 만들어진 막대기가 없으면
					continue;

				count += p;
			}
			else if (str[i] == '(' && str[i - 1] == '(') { //쇠 막대기 시작

				p++;  //막대기 개수 증가
				
			}
			else if (str[i] == ')' && str[i - 1] == ')') { //쇠 막대기 끝
				p--; // 막대기 개수 감소
				count++;
			}
		}

		cout << count << endl;
	
	return 0;
}