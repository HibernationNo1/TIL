num_s, mean_i  = map(int, input().split())

re_mel = num_s * (mean_i)

re_mel = re_mel - num_s + 1
print(re_mel)