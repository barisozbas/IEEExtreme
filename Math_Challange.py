def p( a, b ):
    if b == 0:
        return 1
    if b == 1:
        return a
    r = p( a, b / 2 )
    if( b % 2 == 0 ):
        return ( r * r ) % 1000000007
    else:
        return ( r * r * a ) % 1000000007

def factorial(number):
    prime = [True]*(number + 1)
    result = 1
    for i in xrange (2, number+1):
        if prime[i]:
            j = i+i
            while j <= number:
                prime[j] = False
                j += i
            sum = 0
            t = i
            while t <= number:
                sum += number/t
                t *= i
            result *= i**sum
    return result
      
      
i = int(raw_input())

for j in xrange (1,i+1):
    x,y,z= map(int, raw_input().split())
    binomial = factorial(y)/(factorial(z)*factorial(y-z))% 1000000006
    print (p(x,binomial))