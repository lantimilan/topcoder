#!/usr/bin/env python
def bitcount(n):
    cnt=0
    while n:
        n&=n-1
        cnt+=1
    return cnt

n=int(raw_input())
l=[n]
while n>1:
    if n%2!=0: 
        half=n/2; b1=bitcount(half)
        less=n-1; b2=bitcount(less)
        if b1<=b2:
            l.append(half+1)
            l.append(half)
            n=half
        else:
            l.append(less)
            n=less
    else:
        l.append(n/2)
        n=n/2
print l
print len(l)
l.reverse()

for i in range(1,len(l)):
    if l[i]%2==0: print i-1, i-1
    else: 
        if l[i-1]==l[i]/2: print i-1, i-2
        else: print i-1, 0

# the nearest 2^n-1 to 10^100
# uses 665 numbers
