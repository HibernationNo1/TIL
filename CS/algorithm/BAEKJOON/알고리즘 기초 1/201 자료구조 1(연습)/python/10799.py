import sys
import collections
input = sys.stdin.readline
print = sys.stdout.write

tmp = input()
n = len(tmp)
stack = collections.deque()
cnt = 0

for i in range(n):
    if tmp[i] == '(':
        stack.append(tmp[i])
    elif tmp[i] == ')':
        if i > 0 and tmp[i-1] ==')':
            stack.pop()
            cnt += 1 
        else :
            stack.pop()
            cnt += len(stack) 

print(f"{cnt}\n")