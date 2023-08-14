a, b, c = map(int, input().split())

tmp_list = []
same_num = 0

for i in [a, b, c]:
    if i not in tmp_list:
        tmp_list.append(i)
    else:
        same_num = i
        

if len(tmp_list) == 1:
    print(10000 + (same_num*1000))
elif len(tmp_list) == 2:
    print(1000 + (same_num*100))
else:
    def quicksort(input_list):
        if len(input_list) <=1:
            return input_list
        pivot = input_list[len(input_list)//2]
        left, right, equal = [], [], []
        
        for input_ele in input_list:
            if input_ele < pivot : 
                left.append(input_ele)
            elif input_ele > pivot:
                right.append(input_ele)
            else:
                equal.append(input_ele)
        return quicksort(left) + equal + quicksort(right)
    
    tmp_list = quicksort(tmp_list)
        
    print(tmp_list[-1]*100)
    
