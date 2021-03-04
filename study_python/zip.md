# zip

파이썬 에서는 zip이라는 내장함수가 있다. zip() 은 동일한 개수로 이루어진 자료형을 묶어 주는 역할을 하는 함수이다.

**문법** : zip(자료형 1, 자료형 2)

```python
# list끼리 zip
Number = [1,2,3,4]
Name = ['hong','gil','dong','nim']

res = list(zip(Number,name))
print(res) # [(1 ,'hong'), (2 ,'gil'), (3 ,'dong'), (4 ,'nim')] 출력
#각 원소는 튜플로 만들어짐

# 사전과 list의 zip
Number = [1,2,3,4]
Name = ['hong','gil','dong','nim']
dic = {}
for number , name in zip(Number,Name): 
    dic[number] = name
print(dic) # {1 : 'hong' , 2 : 'gil' , 3 : 'dong' , 4 : 'nim'} 출력
```

