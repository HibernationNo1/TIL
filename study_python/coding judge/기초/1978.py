_ = int(input())

num_list = list(map(int, input().split()))

num_fac = 0
for num in num_list:
    if num == 1:
        continue
    
    fac_count = 0
    num_fac +=1
    for i in range(0, num//2):
        if num % (i+1) ==0:
            fac_count +=1
        if fac_count >=2: 
            num_fac -=1
            break
    
print(num_fac)