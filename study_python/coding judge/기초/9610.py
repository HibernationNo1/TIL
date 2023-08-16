num = int(input())

Q1, Q2, Q3, Q4, AXIS = 0, 0, 0, 0, 0
for i in range(num):
    x_p, y_p = map(int, input().split())
    if x_p * y_p == 0:
        AXIS +=1
    elif x_p * y_p > 0:
        if x_p > 0:
            Q1 +=1
        else:
            Q3 +=1
    else:
        if x_p > 0:
            Q4 +=1
        else:
            Q2 +=1

print(f"Q1: {Q1}")
print(f"Q2: {Q2}")
print(f"Q3: {Q3}")
print(f"Q4: {Q4}")
print(f"AXIS: {AXIS}")        
    