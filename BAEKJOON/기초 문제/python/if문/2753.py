a = int(input())

if not(a%4):
    if not(a%100):
        if not(a%400):
            print("1")
        else: print ("0")   
    else: print("1")
else: print("0")   