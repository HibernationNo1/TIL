import sys
input = sys.stdin.readline
print = sys.stdout.write

tmp = [0 for _ in range(9)]
res = 0

for i in range(9):
    tmp[i] = int(input())

for i in range(8):
    for j in range(i+1, 9):
        res = sum(tmp) - tmp[i] - tmp[j]
        if res == 100:
            if i > j:
                del tmp[i-1], tmp[j]
            else:
                del tmp[i], tmp[j-1]
            
            tmp.sort()

            for x in range(7):
                print(f"{tmp[x]}\n") 
            break

    if res == 100:
        break
        