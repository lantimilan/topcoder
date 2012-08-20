#!/usr/bin/python
# COOLNUM.py
#

def solve():
    snum=raw_input()
    N=int(snum)
    L=len(snum)
    for x in range(9*L):
        for y in range(1000):
            if x>=y:
                if pow(x-y, y, N)==0:
                    print x,y,N
    
T=int(raw_input())
for t in range(T):
    solve()
