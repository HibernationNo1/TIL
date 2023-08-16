num = int(input())

for i in range(num):
    ox_word = str(input())


    cumul_score = 0
    total_score = 0
    last_o_x = None
    for o_x in ox_word:
        if o_x == 'O':
            cumul_score +=1
            total_score += cumul_score
       
            if last_o_x == 'X':
                cumul_score = 1
        else:
            cumul_score = 0            

        last_o_x = o_x
    
    print(total_score)
    