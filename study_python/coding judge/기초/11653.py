num_input = int(input())

num_s = 2

done = False
while done == False:
    if num_input == 1:
        done = True
    
    if num_input % num_s == 0:
        num_input /=num_s
        print(num_s)
    else:
        num_s +=1