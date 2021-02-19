import sys

input = sys.stdin.readline

tmp = int(input())

stc = list()

for i in range(tmp):
    x = input().split()
    if x[0] == "push":
        stc.append(x[1])
    elif x[0] == "pop":
        if len(stc) == 0:
            print(-1)
        else: print(stc.pop())
    elif x[0] == "size":
        print(len(stc))
    elif x[0] == "empty":
        if len(stc) == 0:
            print(1)
        else: print(0)
    elif x[0] =="top":
        if len(stc) == 0:
            print(-1)
        else : print(stc[len(stc)-1])


        