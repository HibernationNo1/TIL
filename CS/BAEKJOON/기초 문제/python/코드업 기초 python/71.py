'''
#71, 73
a = input().split()
for i in a:
    if(int(i) == 0): break
    else: print(i)

# 72
b = int(input())
a = input().split()

for i in a:
    print(i)

# 74, 75   
a = int(input())
for i in range(0, a):
    print(a-i)

# 76
a = str(input())
for i in range(ord('a'), ord(a)+1):
    print(chr(i))

# 77
a = int(input())
for i in range(0, a+1):
    print(i)

# 78
aa = 0
a = int(input())
for i in range(0, a+1):
    
    if (i%2 ==0):
        aa += i

print(aa)

# 79
a = input().split()

for i in list(a):
    if(i=='q'): 
        print(i)
        break
    else: print(i)

# 80
sum = 0
a = int(input())

for i in range(1, a):
    sum += i
    if(sum >= a): 
        
        print(i)
        break
'''
# 81
        
       
       

    
