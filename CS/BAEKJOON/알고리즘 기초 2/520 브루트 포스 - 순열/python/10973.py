import sys
input = sys.stdin.readline
print = sys.stdout.write

def prev_permutation(arr, n):
    i = n-1
    while i>0 and arr[i-1]<arr[i]:
        i -=1
    if not(i):
        return False

    j = n-1
    while arr[i-1] < arr[j]:
        j -=1

    arr[i-1], arr[j] = arr[j], arr[i-1]

    j = n-1
    while i < j:
        arr[j], arr[i] = arr[i], arr[j]
        i +=1
        j -=1
    return True

n = int(input())
arr = list(map(int, input().split()))

if prev_permutation(arr, n):
    for i in arr:
        if i == arr[-1]:
            print(f"{i}")
            break
        print(f"{i} ")
else : print("-1")