import sys

input = sys.stdin.readline

a = int(input())

for i in range(1, a+1):
    for x in range(a - i, 0, -1):
        print(" ", end ='')

    for j in range(1, i+1):
        print("*", end = "")
    
    print()