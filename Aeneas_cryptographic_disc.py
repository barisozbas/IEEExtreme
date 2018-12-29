import math

r = float(raw_input())

gap = lambda (a1,b1), (a2,b2) : math.sqrt( (a1 - a2) * (a1 - a2) + (b1- b2) * (b1-b2) )
polar = lambda r , angle : ( math.cos( angle ) * r, math.sin( angle ) * r)
coord = {0 : (0,0)}

for i in xrange (0,26):
    letter, angle = raw_input().split()
    angle = math.radians(float(angle))
    a,b = polar ( r,angle )
    coord[letter] = (a,b)

tup={}

for firstL in coord.keys():
    for secL in coord.keys():
        tup[firstL,secL] = gap(coord[firstL] , coord[secL])
        
ans=0
prev=0
string= raw_input().strip().upper()
for letter in string:
    if letter.isalpha():
        ans = ans + tup[prev,letter]
        prev= letter
        
print (int(math.ceil(ans)))

