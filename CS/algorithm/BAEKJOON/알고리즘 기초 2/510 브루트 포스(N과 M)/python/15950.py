import sys
input = sys.stdin.readline
print = sys.stdout.write

n, m = map(int, input().split())

res = [0 for _ in range(m)]
stc = [False for _ in range(n)]

def func(k):
    if m == k:
        for i in range(m):
            print(f"{res[i]} ")
        print('\n')
        return

    for i in range(n):
        if stc[i] == False:
            res[k] = i+1
            for j in range(i+1):
                stc[j] = True
            func(k+1)
            for j in range(i+1):
                stc[j] = False
        
func(0)