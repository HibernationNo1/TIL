# string에 관하여

### 1. 특징

1. string은 문자형 배열보다 사용하기 편리하며, 문자열을 하나의 타입처럼 표현할 수 있다.

2. 문자열 끝에 null이 들어가지 않는다.

3. index로 원하는 요소에 Direct Access가 가능하다.
4. char과 구분하기
   - 'A' 와 같이 ' ' 는 하나의 문자이며 ASCII Code와 대응되는 수치이다.
   - "ABCDE" 과 같이 " " 로 여러 문자를 나열한 것은 문자 리터럴이다.
   - char str1[5] { 'A', 'B', 'C', 'D', 'E' }; 에서 str1은 문자배열이며 각 배열 요소는 독립된 수치이며 문자로 표현할 수 있다.
   - char str2[] = "ABCDE"; 에서 str2는 문자열이며 str2의 마지막 요소로 '\0' 값이 포함된다. 즉 str2의 크기는 6이 된다.
   - string str3 = "ABCDE"; 에서 str3는 표준 라이브러리가 지원하는 자료형이며 string이다. string은 '\0'을 포함하지 않으며 문자열을 필요로 하는 경우와 호환하기 위해 c_str() 멤버함수(반환값이 const char* 자료형이며 마지막에 '\0'를 포함한다)를 제공한다.

### 2. 선언 및 입력

- 선언

  ```c++
  #include <string>     
  string word ("hibernation");
  
  string word;
  word = "hibernation"
      
  string month[8] = { "MON", "TUE" , "WED" , "TUE" , "FRI" , "SAT", "SUN" };
  // 한 글자가 하닌, 한 단어의 배열을 선언한다면 string을 사용해야 한다.
  //char month[8] = { "MON", "TUE" , "WED" , "TUE" , "FRI" , "SAT", "SUN" }; 이건 안됨
  ```

  > string 변수이름("입력하고자 하는 문자열")

- 입력

  ```c++
  #include<string>  // getline을 사용하기 위해선 string헤더파일 포함 필요
  string word;
  cin >> word;    // 단어 단위로 입력
  
  string word;
  getline(cin, word);  // 띄어쓰기 포함, 문장 단위로 입력
  
  ```



### 3. 관련 메서드

- ```c++
  #include <string>
  
  string word = to_string(12); // int형을 문자형으로 변환 후 입력
  //word[0] = 1, word[1] = 2
  int num1 = 10
  x += to_string(num1)      // string은 덧셈 연산자로 뒤에 원소 붙이기 가능
  //word[0] = 1, word[1] = 2, word[2] = 10
  ```

- `word.siez()`: word라는 문자열의 길이를 반환한다.

- `word.resize(n)`: 크기를(index 갯수를) n으로 변경한다

  > 더 커졌을 경우 추가된 index의 원소를 default값인 ' '(띄어쓰기)로 초기화

- `word.resize(n,'m')`: 크기를 n으로 변경한다.

  > 더 커졌을 경우 추가된 index의 원소를 'm'으로 초기화한다. 나머지 index값은 그대로

- `word.clear()`: 문자열 안의 index를 삭제 (size = 0)
- `word.empty()`: 문자열 index가 없으면 1을 반환(비어있는지 확인)

- `word.find("aa", n)`: n번째 index부터 aa라는 문자를 찾아 그 문자의 시작 index위치를 반환한다.

  > - `string word("hibernation")` 일 때 
  >
  > >  `word.find("hi")` == 0
  > >
  > > `word.find("n", 4)` == 5  (맨 처음 나온 n의 위치)
  > >
  > > `word.find("n", 6)` == 10
  > >
  > > `word.find("haa")` == 쓰레기값
  >
  > - algorithm 라이브러리 내의 find 함수화는 다른 함수임
  >
  >   > 관련 내용: 

- `word.push_back('m')`: 문자열 맨 뒤에 문자m을 추가

  > "hibernaition" >> "hibernationm"
  >
  > `word.push_back('md')` : 문자 d만 추가된다.

- `word.pop_back()`: 문자열 맨 뒤에 index를 삭제 (index갯수 1 감소)

- `word.begin()`: 문자열의 첫 번째 문자를 가리키는 반복자(포인터)를 반환

- `word.end()`: 문자열의 마지막 바로 다음을 가리키는 반복자(포인터)를 반환

- `swap(word1, word2)`: 문자열 word1과 word2를 스왑(교환)

  > `word2 = "hibernation"`, `word1 = "No.1"` 일 때
  >
  > `swap(word1, word2)` =>`word1 = "No.1"` ,  `word2 = "hibernation"`

- `word.insert(word.begin()+n, 'm')`: 1+n번째 자리에 'm'의 문자를 가진 index를 삽입

  > - 기존 1+n 자리의 index를 새롭게 할당하는 것이 아님. 즉, index갯수 늘어남
  > - `word.insert(2, 'm')` 처럼 `vec.bigin()+n` 자리에 int형 값을 넣으면 에러. 

- `word.erase(word.begin() + n)`:  1+n번째 자리 index삭제