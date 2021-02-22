import sys
input = sys.stdin.readline
print = sys.stdout.write

n = int(input())
dp = [0 for _ in range(1001)]
dp[1] = dp[0] = 1
for i in range(2, n+1):
    dp[i] = (dp[i-1] + dp[i-2]) % 10007

print(f"{dp[n]}")