# string에 관하여

### 1. 선언 및 입력

- 선언

  ```c++
  #include <string>     
  string word ("hibernation");
  
  string word;
  word = "hibernation"
  ```

  > string 변수이름("입력하고자 하는 문자열")

- 입력

  ```c++
  string word;
  cin >> word;    // 단어 단위로 입력
  
  string word;
  getline(cin, word);  // 띄어쓰기 포함, 문장 단위로 입력
  
  string word = to_string(1234); // int형을 문자형으로 변환 후 입력
  //word[0] = 1, word[1] = 2...
  ```



### 2. 관련 함수

- `word.siez()`: word라는 문자열의 길이를 반환한다.

- `word.resize(n)`: 크기를(index 갯수를) n으로 변경한다

  > 더 커졌을 경우 index값을 default값인 ' '(띄어쓰기)로 초기화

- `word.resize(n,'m')`: 크기를 n으로 변경한다.

  > 더 커졌을 경우 index값을 'm'으로 초기화한다. 나머지 index값은 그대로

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

- `word.erase(word.begin() + n)0`:  1+n번째 자리 index삭제