

# -- 입, 출력 --
# print 출력, input 입력  기본적인 input의 입력값은 문자열(str)임

# 실수 값 하나를 입력받아서 실수로 출력
tmp = input()
print(f"{tmp}")

# 정수 두 개를 입력받아서 출력
a, b = map(int, input().split())    # split(n)은 n을 기준으로 문자열을 나눈다.
print(f"{a} {b}")
# split()은 공백이므로, 입력받을때 공백을 기준으로 입력값을 나눈다.
# 여러 개의 데이터를 한 번에 다른 형태로 변환 map(변환 함수, 순회 가능한 데이터)
print(a, b, sep='\n', end='\n')
#sep: 각 출력값 사이사이마다 적용
#end: 모든 출력값을 출력 후 마지막에 적용

print("["+"0"*(4) + "]")  #출력문 안에서 연산 가능 [0000] 출력

a, b = map(str, input().split())   #문자열은 str

a = input()           
print('%.2f' % float(a))    # print("%자료형" % 자료형())
# .2f == 소수점 이하 셋째자리에서 반올림

y, m, d =map(int, input().split('.'))
print("%d.%02d.%02d" % (y, m, d))   # 02d == 2자리 int형, 빈 자리는 0으로 채움 
# %d: 정수  %f: 실수   %s: 문자   
# %o: 8진수  %x 16진수  (%X 처럼 대문자로 표현하면 알파뱃이 대문자로 출력)

# --타입 변환--
print( 10 + int(22.5))  # 자연수끼리 덧셈. 32출력
print(10 + int(float("22.5")))  # 문자열은 형 변환, 변환해서 덧셈
print(ord('a'))  # 문자를 int형으로
print(chr(98))  # int형을 문자로 (ASCII 코드값)으로 변환

# --bool 함수 --
a= 5
b= a ==5     # == 왼쪽 값이 참인지 아닌지 진위를 알려줌 (true, false 두 가지 값만 가짐)
print(type(b))       #b의 타입을 알려줌
print(b)     

bool(None) # false로 해석
bool(0)    # false로 해석
bool(" ")  # false로 해석
bool([])   # false로 해석
bool(())   # false로 해석 외 전부 true

# -- 연산자 -- 
# 대입 연산자
#파이썬에서는 형 변환이 자유롭기 때문에 3/2 == 1.5 가 된다.
print(8/2)  #4.0출력 
print(3//2) #몫만 출력, 1출력.
print(3**3)  # 27출력   **는 제곱
print(2%1) # 나머지 출력
print(1 and 0)      # and 연산자  비트단위: &
print(1 or 0)       # or 연산자  비트단위: |
print(1 not 0)      # not 연산자  
print(1 ^ 0)        # 비트단위 XOR연산자
print(~1)           # 비트단위 bitwise 연산자. 비트 단위로 0을 1로, 1을 0으로


 # 복합 대입 연산자
a += 1     # C언어의 a++와 같다. python 에선 a++ 이런 연산자 없다.
a *= 2     # a = a*2와 같다 

# -- 반복문 --
#while문
'''
while 조건:
    명령 블록
'''
student = 1
while student <=5:  #참일때만 수행
    print(student, "번 학생의 성적을 처리합니다.")
    student += 1   # while문에 사용되는 변수가 업데이트 되어야 한다. 안되면 무한루프
    break  # 반복문 종료         // 내의 실수로 프로그램을 종료시켜야 할때 ctrl + c

#for문
for i in range(1,10):     # i를 1부터 10까지 (10은 포함 안됨)  (1  10]

a = list(input())
for i in range(len(a)):     #len(a): a의 길이
    print("'%s'" % a[i])

for student in [1, 2, 3, 4, 5]  # 1부터 차례로 할당
print(student, "번 학생의 성적을 처리한다.")

total = 0
for num in range(1, 101):  #1에서부터 100까지 
    total +=num
    print("total =", total)

for num in range(2, 101, 2):    #시작, 끝 증가값

for a in range(5):  #for문 5번 반복
    break  #빠져나옴
    continue  # 해당 루프 계속

# -- 조건문 --

if b == 5:       #   b가 5라면      // : 이 나타나면 그 다음부터 들여쓰기의 길이가 각각의 코드 블럭을 이룸
    print('b는 5입니다.')
elif a == 5:      # else if = elif 
    print('a는 5입니다')   
else 

age = int(input("나이를 입력하세요"))  # 입력받을땐 입력받고자 하는 타입을 명시해야 한다.

if age < 19:
    print("애들은 가라")




