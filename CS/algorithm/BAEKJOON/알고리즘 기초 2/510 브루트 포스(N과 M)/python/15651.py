import sys
input = sys.stdin.readline
print = sys.stdout.write

n, m = map(int, input().split())

res = [0 for _ in range(m)]

def func(k):
    if m == k:
        for i in range(m):
            print(f"{res[i]} ")
        print('\n')
        return

    for i in range(n):
        res[k] = i+1
        func(k+1)

        
func(0)