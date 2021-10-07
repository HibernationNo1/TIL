import sys
input = sys.stdin.readline
print = sys.stdout.write

n, m = map(int, input().split())

res = [i for i in range(1, m+1)]
stc = [False for _ in range(n)]

def func(k):
	if k == m:
		for i in range(m):
			print(f"{res[i]} ")
		print('\n')
		return
	
	for i in range(n):
		if stc[i] == False:
			res[k] = i+1
			stc[i] = True
			func(k+1)
			stc[i] = False


func(0)