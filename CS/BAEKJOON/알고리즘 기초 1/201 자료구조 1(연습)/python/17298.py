import sys
import collections
input = sys.stdin.readline
print = sys.stdout.write


n = int(input())
lis = list(map(int, input().split()))
res = [-1 for _ in range(n)]
stack = collections.deque()
for i in range(n):
    try:
        while lis[stack[-1]] < lis[i]:
            res[stack.pop()] = lis[i]
    except:
        pass

    stack.append(i)

for i in range(n):
    print(f"{res[i]} ")