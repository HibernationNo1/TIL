s_num = int(input())

str_star = ' ' * s_num

for i in range((s_num*2)-1):
    if i < s_num-1:
        star_num = i+1
        left_st = '*'*(star_num) + str_star[star_num:]
        right_st = str_star[star_num:] + "*"*(star_num)
        ans = left_st + right_st
    elif i == s_num -1:
        ans = '**'*s_num
    else:
        star_num = s_num*2 - (i+1)
        
        left_st = '*'*(star_num) + str_star[star_num:]
        right_st = str_star[star_num:] + "*"*(star_num)
        ans = left_st + right_st
        
    print(ans)