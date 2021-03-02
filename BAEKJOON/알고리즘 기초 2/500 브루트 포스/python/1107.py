import sys
input = sys.stdin.readline
print = sys.stdout.write

num = int(input())
n = int(input())
arr = list()
if n != 0:
    arr = list(input().split())

ans = 9999999
length = 0
for i in range(1000000):
    tmp = False
    for j in str(i):
        if j in arr:
            tmp =True
    if tmp:
        pass
    else :
        if ans > abs(num-i):
            ans = abs(num-i)
            length = len(str(i))

ans = min(ans + length, abs(num-100))

print(f"{ans}")
