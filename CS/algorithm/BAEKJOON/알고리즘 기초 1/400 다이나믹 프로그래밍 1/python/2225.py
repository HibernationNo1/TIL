import sys
input = sys.stdin.readline
print = sys.stdout.write

m = 1000000000

n, k = map(int, input().split())
dp = [[0 for _ in range(201)] for _ in range(201)]

for i in range(n+1):
    dp[1][i] = 1
    dp[2][i] = i+1


for i in range(3, k+1):
    for j in range(n+1):
        for t in range(j+1):
            dp[i][j] = (dp[i][j] + dp[i-1][t])%m

print(f"{dp[k][n]}")