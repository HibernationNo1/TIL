import sys
from collections import deque
input = sys.stdin.readline
print = sys.stdout.write

alp = input().rstrip()
res = deque()
stack = list()
oper = {'+': 1, '-': 1, '*': 2, '/': 2, '(':0}

for i in alp:
    if 'A'<=i <= 'Z':
        res.append(i)
    elif i =='(':
        stack.append(i)
    elif i == ')':
        try:
            while stack[-1] != '(':
                res.append(stack.pop())
            stack.pop()
        except:
            pass
    else: 
        try:
            while oper[i] <= oper[stack[-1]]:
                res.append(stack.pop())
            else: stack.append(i)
        except:
            stack.append(i)

while stack:
    res.append(stack.pop())

for i in res:
    print(f"{i}")