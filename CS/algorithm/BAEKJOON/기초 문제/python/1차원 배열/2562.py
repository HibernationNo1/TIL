import sys
input = sys.stdin.readline

b = 0
for i in range(9):
    a = int(input())
    b = max(a, b)
    if a == b:
        cnt = i+1

print(b)
print(cnt)