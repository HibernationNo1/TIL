num_que = int(input())

for i in range(num_que):
    input_list = list(map(str, input().split()))
    
    first_num = 0
    for j, num_oper in enumerate(input_list):
        if j == 0:
            first_num = float(num_oper)
            continue
            
        if num_oper == "@" : 
            first_num *=3
        elif num_oper == "%" :
            first_num +=5
        elif num_oper == "#":
            first_num -=7
    
    print(f"{first_num:.2f}")
