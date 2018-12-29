# a simple parser for python. use get_number() and get_word() to read
def parser():
    while 1:
        data = list(input().split(' '))
        for number in data:
            if len(number) > 0:
                yield(number)   

input_parser = parser()

def get_word():
    global input_parser
    return next(input_parser)

def get_number():
    data = get_word()
    try:
        return int(data)
    except ValueError:
        return float(data)

def ans(length,arr):
    max1 , max2 = 0,0
    for x in range (length):
        if(arr[x] > max1):
            max1 = arr[x]
        if(max1 > max2):
            max2 = max1
            max1 = -1
    arr.remove(max1)
    arr.remove(max2)
    return arr
    
# numpy and scipy are available for use
import numpy
import scipy

a = get_number()

for i in range (a):
    b = get_number()
    arr = [0]*b
    dogwalker = get_number()
    for x in range (b):
        arr[x] = get_number()
        
    arr.sort()
    dif = []
    
    for x in range (b-1):
        dif.append(abs(arr[x]-arr[x+1]))
    dif.sort()
    
    bigdif = arr[-1] - arr[0]
    if dogwalker!=1:
        bigdif -= sum(dif[-(dogwalker-1):])
    print (bigdif)   