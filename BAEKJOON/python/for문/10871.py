import sys

input = sys.stdin.readline

a, b = map(int, input().split())

x = list(map(int,input().split()))

for i in range(a):
    if x[i] < b:
        print(x[i], end = ' ')