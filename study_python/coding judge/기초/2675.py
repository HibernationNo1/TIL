num_que = int(input())

for i in range(num_que):
    num_re, str_a = map(str, input().split())

    str_result = ""
    for str_ in str_a:
        for _ in range(int(num_re)): 
            str_result += str_
        
    print(str_result)