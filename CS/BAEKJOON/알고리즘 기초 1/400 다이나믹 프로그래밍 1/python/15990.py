import sys
input = sys.stdin.readline
print = sys.stdout.write

num = 1000000009

t = int(input())

dp = [[0]*3 for _ in range(100001)]
dp[1][0] = 1
dp[2][1] = 1
dp[3][0] = dp[3][1] = dp[3][2] = 1

for j in range(4, 100001):
        dp[j][0] = (dp[j-1][1] + dp[j-1][2])%num
        dp[j][1] = (dp[j-2][0] + dp[j-2][2])%num
        dp[j][2] = (dp[j-3][0] + dp[j-3][1])%num


for i in range(t):
    n = int(input())       
    print(f"{sum(dp[n])%num}\n")
