m = int(input())
n = int(input())

done = False

num = 1
sum = 0
min_num = n+1
while done==False:
    numnum = num*num
    if numnum < m:
        num +=1
        continue
    
    if numnum >n:
        done = True
        continue
    
    sum += numnum
    min_num = min(min_num, numnum)
    num +=1
    
if sum == 0:
    print(-1)
else:
    
        
    print(sum)
    print(min_num)
        