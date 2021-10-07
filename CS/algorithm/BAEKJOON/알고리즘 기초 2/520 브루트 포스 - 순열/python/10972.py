import sys
from itertools import permutations
input = sys.stdin.readline
print = sys.stdout.write

def next_permutations(arr):
    i = len(arr)-1
    while i>0 and arr[i-1] >= arr[i]:
        i -=1
    if i == 0:
        return False

    j = len(arr)-1
    while arr[i-1]>=arr[j]:
        j-=1
    
    arr[i-1] , arr[j] = arr[j], arr[i-1]
     
    j = len(arr)-1
    while i<j:
        arr[i], arr[j] = arr[j], arr[i]
        i +=1
        j -=1
    return True

    
n = int(input())
arr = list(map(int, input().split()))

if next_permutations(arr) == True:
    for i in range(len(arr)):
        if i == len(arr)-1:
            print(f"{arr[i]}")
            break
        print(f"{arr[i]} ")
else : print("-1")