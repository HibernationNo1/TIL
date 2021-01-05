
'''
print 출력, input 입력  기본적인 input의 입력값은 문자열(str)임


 print(ord('a'))  문자를 int형으로
 print(chr(98))   int형을 문자로 (ASCII 코드값)으로 변환

for i in range(1,10):     i를 1부터 10까지 (10은 포함 안됨)  (1  10]

for i in range(ord('a'), ord('z')+1):
 print(i,chr(i), end=' \n')   


a= 5
b= a ==5     # == 왼쪽 값이 참인지 아닌지 진위를 알려줌 (true, false 두 가지 값만 가짐)
print(type(b))       #b의 타입을 알려줌
print(b)     

bool(None)  false로 해석
bool(0)     false로 해석
bool(" ")   false로 해석
bool([])    false로 해석
bool(())   false로 해석 외 전부 true

member = ['a1','b2','c3','d4','e5','f6','g7']      # 문자 배열
print(type(member))     #타입: list
print(member)

member = ('a1','b2','c3','d4','e5','f6','g7')    
print(type(member))    # 타입: tuple 
print(member)            # list는 가변이고, tuple은 불변적이다


-- 연산자 -- 
# 대입 연산자
 파이썬에서는 형 변환이 자유롭기 때문에 3/2 == 1.5 가 된다.
print(8/2)  #4.0출력 
print(3//2) #몫만 출력, 1출력.
print(3**3)  # 27출력   **는 제곱
print(2%1) # 나머지 출력

 # 복합 대입 연산자
a += 1     # C언어의 a++와 같다. python 에선 a++ 이런 연산자 없다.
a *= 2     # a = a*2와 같다 

#문자열 연결
s1 = "대한민국"
s2 = "만세"
print(s1+s2) # 대한민국만세 출력
print("싫어" *3)  #싫어싫어싫어 출력   여기서 *n는 해당 문자를 n번 반복시켜라 라는 뜻
  
s = "asd" + str(2021)  # str(문자열)과 int형의 덧셈은 형 변환이 필요
print(s) # asd2021출력

# 타입 변환
print( 10 + int(22.5))  # 자연수끼리 덧셈. 32출력
print(10 + int(float("22.5")))  # 문자열은 형 변환, 변환해서 덧셈

-- 조건문 --

if b == 5:       #   b가 5라면      // : 이 나타나면 그 다음부터 들여쓰기의 길이가 각각의 코드 블럭을 이룸
    print('b는 5입니다.')
elif a == 5:      # else if = elif 
    print('a는 5입니다')   
else 

age = int(input("나이를 입력하세요"))  # 입력받을땐 입력받고자 하는 타입을 명시해야 한다.

if age < 19:
    print("애들은 가라")

-- 반복문 --
while 조건:
    명령 블록
    
student = 1
while student <=5:  #참일때만 수행
    print(student, "번 학생의 성적을 처리합니다.")
    student += 1   # while문에 사용되는 변수가 업데이트 되어야 한다. 안되면 무한루프
    break  # 반복문 종료         // 내의 실수로 프로그램을 종료시켜야 할때 ctrl + c


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

'''
#-------------------------------------


