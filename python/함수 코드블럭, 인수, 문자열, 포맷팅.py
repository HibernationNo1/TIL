'''
-- 반복되는 코드  --   #C++에서 함수 코드블럭과 같음
def 함수명(변수)

def calcsum(n):
    total = 0
    for num in range(n+1):
        total += num
    return sum 

def calctotal():
    pass  #아무것도 안하고 넘어감
#함수는 반드시 코드 블럭이 있어야 함. 실제 구현을 나중으로 미루고자 할 때 pass지정


가변인수
def intsum(*ints)      #여기서 ints는 tuple이지만 *을 붙여서 가변인수로 받을 수 있음 
    total = 0           # (이 때 ints가 배열이면 *: 펼쳐서 전달해라.)
    for num in ints:
        total += num

print(intsum(1, 2, 3))       #ints = (1, 2, 3)
print(intsum(5, 7, 9, 11))   #ints = (5, 7, 9, 11)

def intsum(weight, abc, *int)  # 받는 인자가 여러개일 때, 가변인수는 뒤에 위치해야 한다.

인수의 기본 값
def calcstep(begin, end = 1, step = 1):       # 디폴트 갑 배정은 뒤에서부터 연속적으로 해야 한다.
    total = 0                                   # def calcstep(begin = 1, end, step = 1) 이건 안됨 
    for num i  range(begin, end + 1, step):
        total +=num

    return total ("1 ~ 10 =", calcstep(1, 10, 2))  # 25 출력

키워드 인수             #인수가 넘 많을때 사용
def calcstep(begin, end, step)        #순서에 상관 없이 이름에 따라서 값이 매칭이 된다.
    total = 0
    for num in range(begin, end + 1, step)
        total += num
    return total

print("3~ 5 =", calcstep(step = 1, end = 5, begin = 3))  # 12 출력

키워드 가변 인수 # **기호로 지정하여 타입은 사전(dictionary)이 됨
def 함수명(**인수명):
    명령 블럭

def calcstep(**args):
    begin = args['begin']
    end = args['end']
    step = args['step']

    total = 0
    for nu in range(begin, end + 1, step):
        total += num 

    return total

print("3 ~ 5 =", calcstep(begin = 3, end = 5 , step = 1))


price = 1000

def sale():
    global price     #지역변수처럼 호출했지만 global때문에 전역변수로 된다.
    price = 500

sale()
print(price)  # 500 출력


-- 문자열 --

s = "python"
print(s[2])
print(s[-2])     # -가 붙으면 2번째 index 안의 값 출력 

for c in s:
    print(c, end =" ,")  # p,y,t,h,o,n 출력

for i  in range(len(s)):        #len: 길이
    print(s[i], end = ",")    # p,y,t,h,o,n 출력

슬라이싱
문자열[begin:end:step]       #step이 음수면 뒤에서부터 진행. 범위는 (begin  end]

s = "0123456789"
print(s[2:5])       # 234출력
print(s[3:])        # 3456789출력
print(s[:4])        # 0123출력

dates = "월화수목금토일"
print(dates[::2])       # 월수금일 출력
print(dates[::-1])      # 일토금목수화월 출력

문자열 메서드
.find(str): str이라는 문자열을 찾아 index 반환, 없으면 -반환
.rfind(str):  뒤에서부터 찾음
.index(str): find()와 동일
.count(str): str문자열이 몇 번 등장하는지 리턴

s = "python programming"
print(len(s))           # 18 출력
print(s.find('o'))      # 4 출력     
print(s.count('n'))     # 2 출력
print(())
print(())

조사
print('a' in s)     # true 출력
print('w' in s)     # false 출력

name = "홍길동"

if name.startswith("홍")      # .starswith("m") 해당 문자가 m문자로 시작하는지
    print("시작단어 홍 마즘")
if name.endswith("동")
    print("마지막 단어 동 마즘")

분할
.slpit(구분자)     구분자를 기준으로 문자열을 분리아혀 리스트(배열)로 리턴, 디폴트는 공백
s = "가 나 다"
print(s.split())     # ['가','나','다'] 출력

s2 = "가->나->다->라"
tmp = s2.split("->")
print(tmp)    # ['가','나','다','라'] 출력
for asd in tmp:
    print(asd)        

s = "__"
print(s.join("대한민국"))      #join: 이어주는 메서드   

대체
.replace(기존문자열, 대체문자열)
s ="불편하면 자세를 바꿔"
print(s.replace("불편하", "아프"))      # 아프면 자세를 바꿔  로 출력


-- 포맷팅 -- 
%d  정수
%f  실수
%s  문자열
%c  문자 하나

m = 8
d = 15
a = "광복절"
print("%d월 %d일은 %s이다." %(m, d, a))    #8월 15일은 광복절이다.  이건 파이선2에서 쓰는 기법

파이썬3에서 쓰는 포맷팅. 선형 포맷팅

n = "태욱"
a = 28
w = 65.2
print("이름: {}, 나이: {}, 몸무게 {}", format(n, a, w)) 
print("이름: {:4s}, 나이: {:3d}, 몸무게 {:.2f}", format(n, a, w)) 
# 이름: 태욱, 나이: 27, 몸무게: 65.2
# 이름: 태욱  , 나이:  27, 몸무게: 65.20     이름엔 4칸, 나이엔 3칸, 몸무게엔 소수점 2자리까지

#python 3.7부터 지원하는 새로운 방법 (f-string)
print(f"이름: {n}, 나이: {a}, 몸무게 {w}")   요 방법이 제일 낫다
print(f"이름: {n:4s}, 나이: {a:3d}, 몸무게 {w:.2f}")
'''

# --------------------

