#!/usr/bin/env python
N=100; M=10000
print N, M
for i in range(1,N+1):
    for j in range(1,N+1):
        d = 0
        if i==j: d = 10000000
        elif j == i+1: d = 1
        else: d = 100000
        print i, j, d
