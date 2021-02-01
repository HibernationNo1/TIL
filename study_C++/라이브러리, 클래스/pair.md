# pair 클래스

- 두 객체를 하나의 객체로 취급할 수 있게 묶어주는 클래스.

- STL에서 데이터 '쌍'을 표현할 때 사용한다.

- pair의 데이터에 접근하기 위해서는 `이름.first` 또는 `이름.second` 키워드를 사용해야 한다.

- sort 알고리즘에 의해 정렬이 가능하다.
  (대소 비교 및 sort에의한 정렬에서 : 첫번째 인자 기준, 첫번째가 같으면 두번째인자로 판단)



**pair 선언**

```c++
#include<utility> // pair 관련 함수를 사용한다면 헤더 포함 필수

//방법 1
pair<int, double> p1(1, 1.3);    
// first에는 1이라는 int형 데이터, second에는 1.3이라는 double형 데이터가 들어있다.
cout << p1.first << " " << p1.second << endl;  // 1 1.3 출력

//방법 2;
pair <int, double> p2;
  p2 = make_pair(2, 2.6);
// first에는 2이라는 int형 데이터, second에는 2.6이라는 double형 데이터가 들어있다.

방법 3;
pair<int, string> tmp;
cin >> tmp.first >> tmp.second;  // first에 int형 입력받고, second에 string형 입력받기
```

