import sys

input = sys.stdin.readline

a = int(input())

for i in range(1, a+1):
    x, y = map(int, input().split())
    print(x+y)
