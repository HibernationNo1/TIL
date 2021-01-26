#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int main(void)
{
	string str;
	int c = 0, h = 0, pos, i;
	cin >> str;

	if (str[1] == 'H') {
		c = 1;
		pos = 1;
	}
	else {
		for (i = 1; str[i] != 'H'; i++) {
			c = c * 10 + (str[i] - 48);
		}
		pos = i;
		
	}

	if (str[pos + 1] == '\0') {
		h = 1;
	}
	else {
		for (i = pos + 1; str[i] != '\0'; i++) {

			h = h * 10 + (str[i] - 48);
			
		}
		
	}
	
	cout << c * 12 + h << endl;

	return 0;
}