# A와 B의 최소공배수 == A*B//최대공약수

# 최대공약수 == (작은 수)와 (큰수와 작은수를 나눈 나머지와)의 최대공약수


num_que = int(input())

for _ in range(num_que):
    a, b = map(int, input().split())
    
    org_a, org_b = a, b
    
    while a !=0:
        b = b%a			# 특정 한 수를 다른 한 수로 나눈다
        a, b = b, a		# 두 수의 자리 교로
						# 자리 교체를 반복함으로써 a, b중 작은수가 어떤 것인지 반복해가며 자동으로 판별
    gcm = b
    print(org_a * org_b // gcm)
    