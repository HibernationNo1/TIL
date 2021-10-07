import sys
import collections
input = sys.stdin.readline

foo = input().rstrip()
tmp = collections.deque()

n = len(foo)
i = 0
while i < n:
    if foo[i] == '<':
        print(foo[i], end = "")
        for j in range(i+1, n):
            print(foo[j], end = "")
            if foo[j] == '>':
                i = j
                break
    elif foo[i] == ' ':
        print(' ', end = "")
        i +=1
        continue
    else :
        for j in range(i, n):
            if foo[j] == ' ' or foo[j] == '<':
                for k in range(len(tmp)):
                    print(tmp.pop(), end = "")
                i = j-1
                break
            elif j == n-1:
                tmp.append(foo[j])
                for k in range(len(tmp)):
                    print(tmp.pop(), end = "")
                i = n
                break
            else: tmp.append(foo[j])
    
    i +=1
    
            

            