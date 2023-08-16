while 1:
    input_num = int(input())
    
    if input_num == -1:
        break
    
    factor_list = []
    factor_sum = 0
    for i in range(1, input_num):
        if input_num % i == 0:
            factor_list.append(i)
            factor_sum +=i
    
    if factor_sum == input_num:
        print(f"{input_num} = ", end='')
        for j, factor in enumerate(factor_list):
            if len(factor_list)-1 == j:
                print(f"{factor}")
                break
            print(f"{factor} + ", end = "")
    else:
        print(f"{input_num} is NOT perfect.")