#include <iostream>
using namespace std;

int main(void)
{
	string s;
	cin >> s;
	int num = 0;
	
	for (int i = 0; i < s.size(); i++)
	{
		if ((s[i] == 'c')||(s[i] == 'z')||(s[i] == 's'))    // s, z, c 중 하나하면
		{
			if (s[i + 1] == '=')    // s, z, c 중 하나 뒤에 =가 붙는다면 's=' 'z=' 'c='
			{
				i++;		// 2글자 크기 c= 알파벳 = > for 1회 건너뛰기
				num++;		// 알파벳 갯수 1추가
			}
			else if ((s[i] == 'c') && (s[i + 1] == '-')) // 'c-'라면
			{
				i++;
				num++;
			}
			else
			{
				num++;		// 단순 알파벳 1개 c z s 라면
			}
		}
		else if (s[i] == 'd')
		{
			if (s[i + 1] == 'z')   // 'dz'라면
			{
			
				if (s[i + 2] == '=') //  'dz='라면
				{
					
					i = i+2;  // for 2회 건너뛰기     
					num++;	 // 알파벳 갯수 1추가
				}
				else
				{
					num++; // 단순 dz라면 == 단순 d라면
					continue;
				}
			}
			else if (s[i + 1] == '-')  //'d-' 하면
			{
				i++;
				num++;
			}
			else
			{
				num++; // 단순 d라면
			}
		}
		else if ((s[i] == 'l') && (s[i + 1] == 'j'))   // li일때 
		{
			i++; 
			num++;
		}
		else if ((s[i] == 'n') && (s[i + 1] == 'j'))  // nj일때
		{
			i++;
			num++;
		}
		else
		{
			num++;
		}
	
	}
	
	cout << num << endl;  
	return 0;
}