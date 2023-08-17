fi_num = int(input())

fi_list = []
for i, _ in enumerate(range(fi_num +1)):
    if i == 0:
        fi_list.append(0)
        continue
    elif i == 1:
        fi_list.append(1)
        continue
    
    fi_list.append(fi_list[i-2] + fi_list[i-1])

print(fi_list[-1])