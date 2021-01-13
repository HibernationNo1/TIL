# template에 관하여

보통은 인자로 **값** 또는 **객체**를 전달했지만, 템플릿은 **타입** 그 자체를 매개변수화 해서 전달한다. 

int, double 같은 기본 타입뿐만 아니라 사용자가 정의한 클래스에 대해서도 매개변수화 할 수 있다.

함수나 클래스를 개별적으로 다시 작성하지 않아도, 여러 자료 형으로 사용할 수 있도록 하게 만들어놓은 틀

템플릿은 클래스 템플릿과 함수 템플릿으로 나뉜다.



### 선언

```c++
template <typename T>
// template <타입매개변수 매개변수이름>
// 템플릿에 적용할 타입을 템플릿이 매개변수 이름(T)으로 표현한 것.
```

> 아래에 나올 클래스 또는 함수의 정의가 특정한 타입에 적용할 수 있는 템플릿이라고 선언
>
> 이는 '템플릿 지정자'이며 템플릿 지정자는 문장 전체에 적용된다.
>
> 아래 나오는 것이 클래스면 클래스 템플릿, 함수가 나온다면 함수 템플릿.
>
> 템플릿은 바로 아래 나오는 클래스 또는 함수 하나에만 적용된다.



### 예시

#### 1. 클래스 템플릿

클래스 템플릿은 멤버 변수 타입, 메서드의 매개변수 또는 리턴 타입을 매개변수로 받아서 클래스를 만든다. (매개변수화)

주로 객체를 저장하는 컨테이너나 데이터 구조에서 많이 사용한다.

```c++
//템플릿을 사용하지 않았을 때.  
class Foo
{
   private:
    int mValue1;
    int mValue2;
    int sum;
    
   public:
    Foo(int mValue1, int mValue2)
    {
        this->mValue1 = mValue1;
        this->mValue2 = mValue2;
        this->sum = mValue1 + mValue2;
    }
	
    void printSum(int mValue1, int mValue2)
    {
        sum =  mValue1 + mValue2
            cout << sum << endl;
    }
   
};
// --------- 템플릿을 사용할 때 --------- //
template <typename T>
class Foo
{
   private:
    T mValue1;
    T mValue2;
    T sum;
    
   public:
    Foo(T mValue1, T mValue2)
    {
        this->mValue1 = mValue1;
        this->mValue2 = mValue2;
        this->sum = mValue1 + mValue2;
    }
	
    void printSum(T mValue1, T mValue2)
    {
        sum =  mValue1 + mValue2
            cout << sum << endl;
    }
   
};

int main(void)
{
    Foo<int> myfoo(1, 2);  //클래스이름<타입> 객체명(인수1,인수2)
    myfoo.printSum(3, 4);  //객체로 함수를 호출할 땐 타입을 명시하지 않아도 됨      
    
}
```





#### 2. 함수 템플릿

```c++
//템플릿을 사용하지 않았을 때.                    
int sum(int a, int b)  		//int형을 인수로 받는 sum
{
    return a+b;
}
double sum(int a, int b)	//double형을 인수로 받는 sum
{
	return a+b;
}   		// 함수 오버로딩

// --------- 템플릿을 사용할 때 --------- //
template <typename T>  
T sum1(T a, T b)        // T라는 타입 하나로 적용할 수 있다.
{
    return a+b;
}

//템플릿을 다시 적용한다고 가정하고
template <typename T1, typename T2>    //두 개의 템플릿을 사용할 때
T1 sum2(T1 a, T2 b)    // T1에 적용된 타입으로 리턴하는 함수
{
    return a+b;
}

//템플릿이 적용된 위 함수를 호출할 때
int main(void)
{
    int x1 = 1, y1 = 2;
    double x2 = 1.1, y2 = 2.2;
    string x3 = "a", y3 = "b";
    sum1<int>(x1, y1);		 //함수명<사용할 타입>(인수1, 인수2)
    sum1<double>(x2, y2);
    sum1<string>(x3, y3);    
    // 같은 함수에 타입에 상관 없이 인수 적용 가능. 타입만 명시해주면 됨
    
    //template로 사용하는 변수가 2개 이상일 경우 함수이름 뒤에 <>로 명시 안함
    sum2(x1, x2);		// 두 개의 타입을 각각 T1, T2에 적용하여 전달
    sum2(y2, y3);
}
```



