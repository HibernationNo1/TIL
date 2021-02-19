import sys
input = sys.stdin.readline

res1 = list(input().rstrip())
res2 = list()
n = int(input())


for i in range(n):
    tmp = input().split()
    if tmp[0] == 'P':
        res1.append(tmp[1])
    elif tmp[0] == 'D':
        if len(res2) == 0:
            continue
        else : 
            res1.append(res2.pop())
    elif tmp[0] == 'L':
        if len(res1) == 0:
            continue
        else : 
            res2.append(res1.pop())

    elif tmp[0] == 'B':
        if len(res1) == 0:
            continue
        else: 
            res1.pop()

res2.reverse()

for i in range(len(res1)):
    print(res1[i], end = "")

for i in range(len(res2)):
    print(res2[i], end = "")