#include<iostream>
#include<string>
#include<stack>

using namespace std;

#define endl '\n'

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	cin.ignore();
	

	for (int i = 0; i < n; i++) {
		string word;
		getline(cin, word);  // 띄어쓰기 포함, 문장 단위로 입력
		stack<char> alph;

		for (int j = 0; j < int(word.size()); j++) {
			if (word[j] != ' ') {
				alph.push(word[j]);
				if (j == word.size() - 1) {
					int tmp = alph.size();
					for (int k = 0; k < tmp; k++) {
						cout << alph.top();
						alph.pop();
					}
				}
			}
			else {
				int tmp = alph.size();
				for (int k = 0; k < tmp; k++) {
					cout << alph.top();
					alph.pop();
				}
				cout << " ";
			}
		}
		cout << endl;
	}
	
	return 0;
}