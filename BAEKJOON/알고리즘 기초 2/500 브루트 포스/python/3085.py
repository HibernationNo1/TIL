import sys
input = sys.stdin.readline
print = sys.stdout.write


def Width(arr2, i, n) :
	cnt = 1
	m = 0
	for j in range(n-1):
		if arr2[i][j] == arr2[i][j+1]:
			cnt +=1
			m = max(m, cnt)
		else : cnt = 1

	return m

def Lenth(arr1, i, n) :
	cnt = 1
	m = 0
	for j in range(n-1):
		if arr1[j][i] == arr1[j+1][i]:
			cnt +=1
			m = max(m, cnt)
		else : cnt = 1

	return m


n = int(input())
arr = [0 for _ in range(n)]
count = 0
for i in range(n):
	arr[i] = list(input())



for i in range(n):
	for j in range(n):
		if j < n-1 :
			tmp = arr[i][j]
			arr[i][j] = arr[i][j+1]
			arr[i][j+1] = tmp
			count = max(count , Width(arr, i, n))
			count = max(count ,Lenth(arr, j, n))
			count = max(count ,Lenth(arr, j+1, n))
			tmp = arr[i][j]
			arr[i][j] = arr[i][j+1]
			arr[i][j+1] = tmp
			
		if i< n-1 :
			tmp = arr[i][j]
			arr[i][j] = arr[i+1][j]
			arr[i+1][j] = tmp
			count = max(count , Width(arr, i, n))
			count = max(count ,Width(arr, i+1, n))
			count = max(count ,Lenth(arr, j, n))
			tmp = arr[i][j]
			arr[i][j] = arr[i+1][j]
			arr[i+1][j] = tmp
			

print(f"{count}\n")