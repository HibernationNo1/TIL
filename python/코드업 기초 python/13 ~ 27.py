'''
#13번
a, b = map(int, input().split())
print(a, b)


#14번
a, b = map(str, input().split())
print(b, a)

#15
a = input()
print('%.2f' % float(a))

#17
a = input()
print(a, a, a)

#18
a = input()
print(a)

#19
y, m, d =map(int, input().split('.'))
print("%d.%02d.%02d" % (y, m, d)) 

#20
f, d = map(str, input().split('-'))
print(f+d)

#21, 22
a = input()
print(a)

#23
d, f = map(str, input().split('.'))
print(d, f, sep='\n', end='\n')     
  
#24
a = list(input())
for i in range(len(a)):
    print("'%s'" % a[i])

# 25
a = list(input())
for i in range(len(a)):
    print("["+ a[i] + "0"*(len(a)-1-i) + "]")

# 26 
a, b, c = map(int, input().split(':'))
print(b)

# 27
a, b, c = map(str, input().split('.'))
if len(b) < 2 : "0"+b
if len(c) < 2 : "0"+c
while (len(a)<4): "0" + a

print(c, b, a, sep = '-')
'''