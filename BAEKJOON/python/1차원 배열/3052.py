import sys
input = sys.stdin.readline

x = int(input())

a = [x%42]

for i in range(9):
    b = int(input())
    for j in range(len(a)):
        if a[j] == b%42:
            break
        
        if j == len(a) -1 : 
            a.append(b%42)        

print(len(a))