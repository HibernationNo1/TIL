k, n, m = map(int, input().split())

total = k*n
ans = m - total

if ans < 0:   
	print(abs(ans))
else:
    print(0)