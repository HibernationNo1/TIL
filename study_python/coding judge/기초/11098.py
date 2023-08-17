num = int(input())

for _ in range(num):
    case = int(input())
    max_price = -1
    max_price_name = None
    for _ in range(case):
        price, name = map(str, input().split())
        price = int(price)
        
        if price == max(price, max_price):
            max_price_name = name
            max_price = price
    
    print(max_price_name)
