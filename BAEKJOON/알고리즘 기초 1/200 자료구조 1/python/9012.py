import sys
input = sys.stdin.readline

tmp = int(input())

for i in range(tmp):
    res = 1
    stc = list()
    x = input()
    for j in range(len(x)):
        if x[j] == '(':
            stc.append(1)
        elif x[j] == ')':
            if len(stc) == 0:
                res = -1
                break
            stc.pop()
           
    if res == -1:
        print("NO")
        continue

    if len(stc) == 0:
        print("YES")
    else : print("NO")

                