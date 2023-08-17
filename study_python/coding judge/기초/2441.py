s_num = int(input())

star = '*'*s_num
for i in range(s_num):
    star_ans = star[1*i:]
    star_ans = ' '*i + star_ans
    print(star_ans)
