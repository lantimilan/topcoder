#~/usr/bin/python
n=22; a=1; b=22;
print n,n*(n-1)/2,a,b
for i in xrange(n):
    for j in xrange(i):
        print (i+1),(j+1)

for i in xrange(n/2):
    print 0.5

for i in xrange(n/2):
    print 0.3
