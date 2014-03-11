N = 3000; M = N*(N-1)/2; K = 1000;
print N, M, K
for i in range(N):
    for j in range(N):
        if i != j:
            print i, j
