import sys
input = sys.stdin.readline
print = sys.stdout.write

e, s, m = map(int, input().split())
res = 1
while True:
    if not(res-e)%15 and not(res-s)%28 and not(res - m)%19:
        print(f"{res}")
        exit()
    res+=1