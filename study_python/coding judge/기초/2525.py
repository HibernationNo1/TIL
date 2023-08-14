h, m = map(int, input().split())
a_m = int(input())


r_m = m + a_m
if r_m >= 60:
    h += (r_m // 60)
    r_m = int(r_m % 60)
    
    h = int(h % 24)



print(h, r_m)
