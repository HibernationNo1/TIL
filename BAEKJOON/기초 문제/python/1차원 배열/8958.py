import sys
input = sys.stdin.readline

tmp = int(input())

for i in range(tmp):
    cnt = 0
    sum = 0
    a = input()
    for j in range(len(a)):
        if a[j] =='O':
            cnt +=1
            sum += cnt
        elif a[j] == 'X':
            cnt = 0
    print(sum)
