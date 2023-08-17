s_num = int(input())



for i in range((s_num*2)):
    if i < s_num -1:
        star = '*' * (s_num - (i+1))
        space = ' ' * (i)
        ans = space + star + "*" + star
    elif i == s_num -1:
        continue
    else:
        star = '*' * (i - s_num)
        space = ' ' * (2*s_num - i -1)
        ans = space + star + "*" + star
        
    print(ans)