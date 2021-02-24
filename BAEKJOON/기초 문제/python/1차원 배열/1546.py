import sys
input = sys.stdin.readline

tmp = int(input())
arr = list(map(int, input().split()))

m = max(arr)
sum =0
for i in range(tmp):
    arr[i]= arr[i]/m*100
    sum = sum + arr[i]

print(sum/tmp)