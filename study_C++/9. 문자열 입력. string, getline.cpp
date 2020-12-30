// 문자열 입력
// 문자열은 그 끝을 나타내기 위해 끝에 \0을 붙인다. 
// 문자열 저장 목적으로 char 배열 선언 시 특수문자 \0이 저장될 것을 고려해서 배열의 길이 결정해야함
#include <iostream>
#include <string>  

using namespace std;

int main(void)
{ 
	//string 함수, cin으로 받기
	string str;     // string 헤더파일의 string함수
	cout << "입력1: ";
	cin >> str;    
	cout <<"출력1: " << str << endl;  // cin으로 입력받으면 띄어쓰기는 인식하지 못한다

	str = "Hellow world";
	cout << str << endl << endl;   // string으로 할당받을때는 띄어쓰기까지 인식한다. 
	
	//string함수, getline으로 받기
	string s;
	getline(cin, s);  // cin으로 입력받는 방식과 동일하게 적용. 단, 띄어쓰기까지 다 인식해서 입력
	cout << "getline(cin.s)출력: " << s << endl<<endl;  // 앞부분에 cin이 있는데 뒤에 getline이 있으면 한 번에 str과 s에 전부 입력됨

	
	//char배열, cin으로 입력받기
	char a[10];
	cout << "입력2: ";   // 입력된 문자열의 크기가 10보다 작으면 나머지 공간은 NULL
	cin >> a;            // 문자열의 마지막은 \0으로 자동 저장됨 
	cout << "출력2: " << a << endl;   // 띄어쓰기는 입력 안됨

    sizeof(a);   //sizeof(배열이름) 실제로 차지하고 있는 메모리dml 크기를 구한다.
	strlen(a);   //  strlen(배열이름) 문자열의 길이

	//char배열, getline으로 입력받기
	char c[10];
	cout << "입력3: ";
	cin.getline(c, 10);  // char 배열로 문자열 입력받을 때 cin.getline(문자열이름, 배열크기)
	cout << "출력3: " << c << endl;    // 띄어쓰기까지 입력 됨


    // 정수형을 문자열로 변환할 때
	int a1 = 3, b1 = 5, c1 = 6;
	string str2 = to_string(a1 * b1 * c1);  // to_string 사용
    string str2 = to_string(123456); // str2[0] = 1 , str[5] = 5
    // str2[6]부터는 아예 정의되지 않은 것.
    cout << str2.size() << endl; // str의 배열이 몇개까지 정의되어있는지
   
	return 0;
}