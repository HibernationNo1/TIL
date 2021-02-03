#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

#define endl '\n'


int main(void)
{
	while (1)
	{
		string s;
		int arr[4];  // 소 대 숫 공
		fill_n(arr, 4, 0);

		getline(cin, s);

		if (s.size() == 0) break;

		for (int i = 0; i<int(s.size()); i++) {
			if (s[i] == ' ') arr[3]++;
			else if (48 <= s[i] && s[i] <= 57) arr[2]++;
			else if (97 <= s[i] && s[i] <= 122) arr[0]++;
			else if (65 <= s[i] && s[i] <= 90) arr[1]++;

		}

		for (int i = 0; i < 4; i++) {
			cout << arr[i] << " ";
		}
	}

	return 0;
}