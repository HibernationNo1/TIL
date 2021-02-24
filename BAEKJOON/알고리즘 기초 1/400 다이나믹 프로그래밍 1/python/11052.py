import sys
input = sys.stdin.readline
print = sys.stdout.write

n = int(input())
dp = [0 for _ in range(n+1)]
arr = list(map(int, input().split()))

for i in range(1, n+1):
    for j in range(i):
        dp[i] = max(dp[i], dp[j] + arr[i-j-1] )

print(f"{dp[n]}")