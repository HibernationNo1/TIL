word = str(input())

pel = True
for i in range(len(word)):
    if word[i] != word[len(word)-1-i]:
        pel = False
        break

if pel:
    print(1)
else:
    print(0)
    