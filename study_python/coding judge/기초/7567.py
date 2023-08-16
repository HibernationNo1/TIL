bowls = str(input())

last_bowl = None
height = 10
for i, bowl in enumerate(bowls):
    if i == 0:
        last_bowl = bowl
        continue
    
    if last_bowl == bowl:
        height +=5
    else:
        height += 10
        
    last_bowl = bowl
    
    
print(height)