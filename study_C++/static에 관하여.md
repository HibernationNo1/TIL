# static

### static 키워드가 사용되는 경우

1. static mamber function
2. static mamber variable
3. static variable in a function

---



### 1. static mamber function

```c++
class Foo
{
    public:
    void printA()
    {
        cout << "A" << endl;
    }
    static void PrintB()  //스태틱 메서드 정의
    {
        cout << "B" << endl;
    }
    private:
    int mValue = 0;
};
int main(void)
{
    Foo myfoo;  //static을 사용하기 위해선 항상 객체를 생성해야 한다.
    Foo::PrintB();  //스태틱 메서드는 객체 선언 없이 호출이 가능하다.
    myfoo.PrintB();  //이것도 가능
}
```

> 스태틱 멤버함수는 this 포인터와 연결이 되어있지 않기 때문에 객체와 연관이 없다. 
>
> static 메서드에서는 멤버 변수, 멤버 함수도 호출할 수 없다.

```c++
    static void PrintB()  //스태틱 메서드 
    {
        cout << "B" << endl;
        cout << mValue <<endl; //this가 작동을 안하기 때문에 컴파일 에러
        PrintB(); //멤버 함수도 호출 불가능
    }
```

---



### 2. static mamber variable

```c++
class Foo
{
    public:
    void printA()
    {
        count++;
        cout << count << "A" << endl;
    }
    static int count;  // 스태틱 멤버변수 선언
    private:
    int mValue = 0;
};

int Foo::count = 0; // 스태틱 멤버변수는 프로그램이 작동되기 전에(int main 전에) 반드시 초기화가 되어야 한다.

int main(void)
{
    Foo myfoo; 
    Foo mybar;
    myfoo.printA();  //각각의 객체에서 count가 호출되는 멤버함수 호출
    mybar.printA();
}
/* 실행결과
1A
2A   // 서로 다른 객체 myfoo, mybar가 static멤버 변수를 공유하고 있음을 알 수 있다.
```

> static 메모리는 heap 메모리 안에 자신만의 공간을 가지고 있으며, 위 코드의 count는 Foo::count = 0; 으로 static 메모리 안에 할당 되어있다.
>
> static 메모리 안의 Foo클래스 static변수는 모든 Foo클래스 변수가 공유한다.
>
> 위 코드처럼 static을 public에서 선언하면, 인터페이스에서 static값에 접근할 수 있다.

```c++
class Foo
{
    public:
    void printA()
    {
         static int count1 =0;  // 메서드 안에 스태틱 멤버변수 선언
        count++;
        cout << count << "A" << endl;
    }
    
    private:
    static int count2;  // private 영역에 스태틱 멤버변수 선언
    int mValue = 0;
};

int Foo::count2 = 0;

int main(void)
{
    Foo myfoo; 
    Foo mybar;
    myfoo.printA(); 
    mybar.printA();
}
```

> static 멤버변수 count1, count2 둘 다 값에 접근이 불가능하다.
>
> 위 코드에서 count1 처럼 메서드 안에 위치하여도 count1는 static메모리에 위치하고 있고, 값은 모든 객체와 공유한다. 단, 해당 함수가 호출이 되어야만 초기화가 진행된다.



### 3. static variable in a function