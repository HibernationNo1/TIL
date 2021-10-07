import sys
input = sys.stdin.readline
print = sys.stdout.write

t = int(input())
dp = [1 for _ in range(12)]
dp[1] = 1
dp[2] = 2

for i in range(t):
    n = int(input())
    for j in range(3, n+1):
        dp[j] = dp[j-1] + dp[j-2] + dp[j-3]
    print(f"{dp[n]}\n")