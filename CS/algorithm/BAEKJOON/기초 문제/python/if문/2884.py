a, b = map(int, input().split())
if (b-45) <0:
    if (a-1)<0:
        a = 23
    else:
        a -= 1
    c = b + 60 - 45
else: c = b-45

print(a, c, sep = (' '))