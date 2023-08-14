h, m, s = map(int, input().split())
input_s = int(input())

added_s = input_s + s
re_s = (added_s % 60)

added_m = m + (added_s//60)
re_m = (added_m % 60)

added_h = h + (added_m//60)
re_h = (added_h % 24)

print(re_h, re_m, re_s)