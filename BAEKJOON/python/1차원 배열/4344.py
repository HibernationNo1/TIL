import sys
input = sys.stdin.readline

t = int(input())

for i in range(t):
    avg = 0
    cnt = 0

    arr = list(map(int, input().split()))
    avg = sum(arr[1:])/arr[0]
    
    for j in range(1, arr[0]+1):
        if avg < arr[j]:
            cnt +=1
    
    print(f"{cnt/arr[0] * 100:.3f}%")
    