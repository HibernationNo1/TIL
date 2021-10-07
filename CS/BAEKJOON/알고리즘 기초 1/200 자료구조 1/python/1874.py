import sys
input = sys.stdin.readline

n = int(input())
stc = [0]
front = stc[0]
top = 0
res = ""
for i in range(n):
    x =  int(input())
    if top+1 < x:
        for j in range(top+1, x+1):
            stc.append(j)
            res += "+\n"
        top = x
        
        res += "-\n"
        stc.pop()
        front = stc[len(stc)-1]
    elif top + 1 == x:
        res += "+\n"
        top = x
        res += "-\n"
    elif top > x:
        if x == front:
            res += "-\n"
            stc.pop()
            front = stc[len(stc)-1]
        else: 
            print("NO")
            sys.exit()

print(res[:len(res)-1])
