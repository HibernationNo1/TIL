import sys
input = sys.stdin.readline

tmp = int(input())

lis = list()

for i in range(tmp):
    x = input().split()
    for j in range(len(x)):
        for k in range(len(x[j])):
            lis.append(x[j][k])
        for k in range(len(x[j])):
            print(lis.pop(), end = "")
        print(" ", end = "")
    print("")
        
    
    