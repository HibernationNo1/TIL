import sys
from collections import deque
from collections import Counter

input = sys.stdin.readline
print = sys.stdout.write

n = int(input())
arr = list(map(int, input().split()))
cnt = Counter(arr)
arr = [[cnt[num], num] for num in arr]
stack = deque()
res = list(-1 for _ in range(n))

for i in range(n):
    try:
        while arr[stack[-1]][0] < arr[i][0]:
            res[stack.pop()] = arr[i][1]
    except:
        pass

    stack.append(i)
    
for i in range(n):
    print(f"{res[i]} ")