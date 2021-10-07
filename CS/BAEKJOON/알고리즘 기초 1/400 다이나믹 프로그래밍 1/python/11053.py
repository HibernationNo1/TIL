import sys
input = sys.stdin.readline
print = sys.stdout.write


n = int(input())
arr = list(map(int, input().split()))
dp = [1 for _ in range(n)]

for i in range(1, n):
    for j in range(i-1, -1, -1):
        if arr[j]<arr[i]:
            dp[i] = max(dp[j]+1, dp[i])

res = 0  
for i in range(n):
    res = max(dp[i], res)

print(f"{res}")