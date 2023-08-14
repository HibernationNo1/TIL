num_input = int(input())

ans = 0
sum_num = 0
for i in range(1, num_input+1):
    ans +=1
    sum_num += i

    if sum_num > num_input:
        ans -=1
        break

print(ans)