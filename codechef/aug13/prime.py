#!/usr/bin/python

p = [1] * 101
p[0] = p[1] = 0
primes = []
for i in range(2,101):
    if p[i]:
        primes.append(i)
        j = i + i
        while j <= 100:
            p[j] = 0
            j += i
print len(primes)
print primes
