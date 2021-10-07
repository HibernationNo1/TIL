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
        if not stc[i]:
            res[k] = i+1
            for j in range(i):
                stc[j] = True
            func(k+1)
            for j in range(i):
                stc[j] = False

func(0)