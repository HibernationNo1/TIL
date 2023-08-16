num = int(input())

max_price = -1
for i in range(num):
    f, s, t = map(int, input().split())
    
    unduple_dice = []
    duple_dice = []
    for dice in [f, s, t]:
        if dice not in unduple_dice:
            unduple_dice.append(dice)
        else: 
            duple_dice.append(dice)
            
            
    if len(unduple_dice) == 1:
        price = 10000 + unduple_dice[0]*1000
    elif len(unduple_dice) == 2:
        price = 1000 + duple_dice[0]*100
    else:
        def sort_list(input_list):
            if len(input_list) <= 1:
                return input_list
            
            mid_ele = input_list[len(input_list)//2]
            left_list, equel, right_list = [], [], []
            
            for ele in input_list:
                if ele < mid_ele:
                    right_list.append(ele)
                elif ele > mid_ele:
                    left_list.append(ele)
                else:
                    equel.append(ele)
            
            return sort_list(left_list) + equel + sort_list(right_list)
        
        max_dice = sort_list(unduple_dice)[0]
        price = max_dice*100
        
    max_price = max(max_price, price)

print(max_price)