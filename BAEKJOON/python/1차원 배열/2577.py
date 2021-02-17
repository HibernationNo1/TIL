a = int(input())
b = int(input())
c = int(input())
x = str(a*b*c)

y = list()
for i in range(10):
    y.append(0)

for i in range(len(x)):
    y[int(x[i])] +=1

for i in range(10):
    print(y[i])