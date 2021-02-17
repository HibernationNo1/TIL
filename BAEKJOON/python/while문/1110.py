import sys
input = sys.stdin.readline

a = int(input())
b = a
i = 0
while(1):
    c = (b//10) + (b%10)
    d = (b%10)*10 + (c%10)
    if d == a:
        break
    else: 
        i += 1
        b = d

print(i+1)