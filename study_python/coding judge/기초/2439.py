s_num = int(input())

star = ' '*s_num
for i in range(s_num):
    star = star[1:]
    star += '*'
    print(f"{star}")