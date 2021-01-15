# 문자열 관리 < sstream >

### 1. isstringstream

string을 입력 받아서 다른 형식으로 바꾸어 주는 기능을 지원

문자열 포맷을 parsing할 때 사용

문자열을 space 또는 tap으로 구분하여 추출해낸다. 

- ##### 예시

```c++
#include<sstream> // istringstream 을 사용하기 위하여 필요함.  
#include<iostream>  
#include<string>  
using namespace std;

int main()
{
    //string asd;      // cin으로 string을 입력받아 sitr에 적용하려면 
    //cin >> asd;			띄어쓰기까지 받는 getline을 사용해야 한다.
    istringstream istr("2345 asd 213 22as"); // istr에 string 저장, 띄어쓰기로 알아서 단어를 구분

    int a, b;
    string str1, str2;
    istr >> a >> str1 >> b >> str2; //istr에서 a,str1,b, str2로 순서대로 문자열 대입
    //입력을 할 때 타입에 따라 순서를 맞춰야 한다.

    cout << a << " " << str1  << " " << b <<" " << str2 <<endl;  
    istr.clear();   
    istr.str("");  // os 내용 삭제. 
    
    cout << istr.str() << endl<<endl;  // .str() == 객체에 저장된 문자열을 반환

    return 0;
}
```

> `istringstream istr("");`: istringstream 클래스의 객체 istr 생성.  istringstream 클래스는 헤더파일 <sstream> 에서 제공된다.
>
> istringstream 클래스는 `>>` 연산으로 문자열을 다른 타입에 맞게 대입할 수 있다.
>
> str()로 반환되는 문자열은 istringstream 클래스가 아니라 string 클래스다.
>
> `.clear()`, `.str("")` 함수를 제공함으로써 재사용이 용이하다. (두 함수를 위 코드처럼 같이 써줘야 안의 내용 삭제)



### 2. ostringstram

다른 타입을 string으로 변환한다. (isstringstream과 반대 기능으로 이해하면 됨)

숫자를 string으로 변환할 때 유용하다.

- **예시**

```c++
#include<sstream> // ostringstream 을 사용하기 위하여 필요함.  
#include<iostream>  
#include<string>  
using namespace std;

int main() 
{
    ostringstream os;

    int num = 34534;
    string val;
    os << num;    //os에 int형 num 대입
    // 이 때 <<는 연산자 오버로딩이 아님 
    os << "test";  //이런 식의 리터럴 문자열이나 상수도 대입 가능

    val = os.str(); //os을 val에 대입. 이 때 타입은 string이다.

    os.clear();   
    os.str("");  // os 내용 삭제. 
    
    return 0;
}
```

>os는 ostringstream클래스 타입이다.
>
>ostringstream클래스 객체는 다른 타입을 `<<` 연산자로 입력받을 수 있다.
>
>`.clear()`, `.str("")` 함수를 제공함으로써 재사용이 용이하다. (두 함수를 위 코드처럼 같이 써줘야 안의 내용 삭제)

### 3. stringstram

주어진 문자열에서 필요한 정보를 때낼 때 유용하게 사용된다.

- **예시**

```c++
#include<sstream> // istringstream 을 사용하기 위하여 필요함.  
#include<iostream>  
#include<string>  
using namespace std;

int main()
{
    int num;
    string str;
    stringstream foo; 

    string bar = "1 2 3 number sum";    // 문자열에 공백(띄어쓰기)까지 포함하여 대입해야 한다.

    foo.str(bar); //매개변수로 쓰인 문자열을 공백(띄어쓰기)으로 각 단어를 구분하여 foo에 대입한다.

    while (foo >> num)  //  foo를  문자열에 num의 타입보다 큰 타입의 정보를 만나면 종료
                       //  num << char  
    {
        cout << num << endl;
    }

    foo.clear();
    foo.str("");  // foo 내용 삭제

    cout << foo.str() << endl;

    return 0;
}
```

> foo는 stringstream클래스 타입이다. 