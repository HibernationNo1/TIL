now = str(input())
now_str = now.split(":")
now_h, now_m, now_s = int(now_str[0]), int(now_str[1]), int(now_str[2])

pur = str(input())
pur_str = pur.split(":")
pur_h, pur_m, pur_s = int(pur_str[0]), int(pur_str[1]), int(pur_str[2])

def check_minas(now, pur):
    if pur - now < 0: return False
    else:
        return True

if check_minas(now_s, pur_s):
    sec = pur_s - now_s
else:
    sec = 60 + pur_s - now_s
    now_m +=1

if check_minas(now_m, pur_m):
    minu = pur_m - now_m
else:
    minu = 60 + pur_m - now_m
    now_h +=1
    
if check_minas(now_h, pur_h):
    hour = pur_h - now_h
else:
    hour = 24 + pur_h - now_h     

if minu < 10:
    minu = f"0{minu}"
if sec < 10:
    sec = f"0{sec}"
if hour < 10:
    hour = f"0{hour}"
        
print(f"{hour}:{minu}:{sec}")   