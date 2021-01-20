# memset

memset 함수는 어떤 메모리의 시작점부터 연속된 범위를 어떤 값으로(바이트 단위) 모두 지정하고 싶을 때 사용하는 함수다.

for문보다 더 빠른 속도가 나올 수 있다. (컴파일러, 컴퓨터 아키텍처에 따라 속도가 다르다.)



**형태**: `memset(foo, int myfoo, int num)`

`foo`: 채우고자 하는 메모리의 시작 주소

`myfoo`: 메모리에 할당하고자 하는 값. `int` 형이지만 내부에서는 `unsigned char`(1byte) 로 변환되어서 저장된다.

`num`: 채우고자 하는 바이트의 수 (채우고자 하는 메모리의 크기)

**ex) 배열에 적용**

```c++
#include <cstring>  //헤더파일 포함 안해도 컴파일은 되지만, 백준에선 컴파일에러
int main (){

    char a[20];

    // 1바이트마다 모두 65로 초기화
    // 배열을 채울 때는 sizeof()함수를 사용하면 된다.
    memset(a, 65, sizeof(a));

    // 출력을 통해 확인
    for(int i = 0; i < (sizeof(a)/sizeof(char)); i++){
        cout << a[i] <<endl;
    }

}
// A 가 20번 출력된다.
// 65는 unsigned char로 바뀌기 떄문에 65의 아스키코드 A 출력
```

> 만약 a배열의 타입이 char(1 byte)가 아닌 int(4 byte)라면, 각 배열에는 원치 않는 값이 할당되게 된다.   a배열의 타입은 char 또는 unsigned char로 하자.
>
> 2번째 인자가 unsigned char로 해석되기 때문에 0~255이외의 값을 넣는다면 제대로 된 초기화가 수행될 수 없다. 두 번째 인자는 0~255사이의 값을 넣자.