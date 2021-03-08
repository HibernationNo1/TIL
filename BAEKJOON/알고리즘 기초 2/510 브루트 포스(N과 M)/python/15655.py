import sys
from itertools import permutations
input = sys.stdin.readline
print = sys.stdout.write

n, m = map(int, input().split())
arr = list(map(int, input().split()))
arr.sort()

res = [0 for _ in range(m)]
stc = [False for _ in range(n)]

def foo(k, num):
    if(k == m):
        for i in range(m):
            print(f"{res[i]} ")
        print("\n")
        return

    for i in range(num, n):
        if stc[i]:
            continue
        res[k] = arr[i]
        stc[i] = True
        foo(k+1, i)
        stc[i] = False

foo(0, 0)