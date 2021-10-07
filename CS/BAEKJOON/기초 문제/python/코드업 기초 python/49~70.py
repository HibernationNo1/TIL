'''
# 49, 50, 51, 52
a, b = map(int, input().split())
if a>b: print(1)
if a<=b: print(0)

# 53
a = int(input())
if a==1: print(0)
if a==0: print(1)

# 54
a, b = map(int, input().split())
if (a and b): print(1)
else : print(0)

# 55
a, b = map(int, input().split())
if (a|b): print(1)
else: print(0)

# 56
a, b = map(int, input().split())
if (a ^ b): print(1)
else: print(0)

# 57
a, b = map(int, input().split())
if (a == b): print(1)
else: print(0)

# 58
a, b = map(int, input().split())
if (a | b) == 0: print(1)
else: print(0)

# 59
a = int(input())
print(~a)

# 60
a, b = map(int, input().split())
print(a&b)

# 61
a, b = map(int, input().split())
print(a|b)

# 62
a, b = map(int, input().split())
print(a^b)

# 63
a, b = map(int, input().split())
if(a>b): print(a)
else: print(b)

# 64
a, b, c = map(int, input().split())
if(a<b):
    if(a<c): print(a)
    else: print(c)
else:
    if(b<c): print(b)
    else: print(c) 

# 65
a, b, c = map(int, input().split())
if (a%2 ==0): print(a)
if (b%2 ==0): print(b)
if (c%2 ==0): print(c)

# 66
a, b, c = map(int, input().split())
if (a%2 ==0): print("even")
else: print("odd")
if (b%2 ==0): print("even")
else: print("odd")
if (c%2 ==0): print("even")
else: print("odd")

#67
a = int(input())
if ( a > 0):
    if(a%2==0): print("plus","even", sep = '\n')
    else: print("plus","odd", sep = '\n')
else:
    if(a%2==0): print("minus","even", sep = '\n')
    else: print("minus","odd", sep = '\n')

# 68
a = int(input())
if (90<=a)&(a<=100): print("A")
elif (70<=a)&(a<=89): print("B")
elif (40<=a)&(a<=69): print("C")
elif (0<=a)&(a<=39): print("D")

# 69
a = str(input())
if (a=='A'): print("best!!!")
elif (a=='B'): print("good!!")
elif (a=='C'): print("run!")
elif (a=='D'): print("slowly~")
else: print("what?")

# 70
a = int(input())
if (a==12)|(a==1)|(a==2): print("winter")
elif (a==3)|(a==4)|(a==5): print("spring")
elif (a==6)|(a==7)|(a==8): print("summer")
elif (a==9)|(a==10)|(a==11): print("fall")
'''