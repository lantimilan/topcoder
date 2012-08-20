#!/usr/bin/env python
import sys

def solve():
    def match(u):
        assert(len(u)==2)
        if u[0][0]==u[1][0]: return True
        if u[0][0]==u[1][1]: return True
        if u[0][1]==u[1][0]: return True
        if u[0][1]==u[1][1]: return True
        return False
    line=sys.stdin.readline()
    lst=line.split()
    N=int(lst[0])
    C=float(lst[1])
    M=int(lst[2])
    u=[]
    for i in range(M):
        line=sys.stdin.readline()
        lst=line.split()
        a=int(lst[0]); b=int(lst[1])
        u.append((a,b))
    ans=0.0
    if C<=2:
        ans = 1.0*N*(N-1) + C*(1.0*N*(N-1)/2 - M);
    else:
        if M<=1 or (M==2 and match(u)):
            ans = 2.0*N*(N-1) - 2*1.0*(N-1) + (N-1 - M)*C;
        else:
            ans = (1.0*(N-2) + 2.0*1);
            ans += 2.0*(N-2)*(N-3) + 1.0*(N-2) + 1.0*1 + 3.0*(N-3);
            ans += (1.0+2.0+3.0*(N-3));
            ans += (N-1-M)*C;
            if C<2.0*(N-2): ans -= (2.0*(N-2)-C);
    print '%.9f' % ans
        
T=int(raw_input())
for x in range(T): 
    solve()
