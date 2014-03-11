n = 747474747
i = 2
print "%d = " % n,
while n > 1:
    while n % i != 0 and i * i < n:
        i += 1
    if i * i > n:
        print "%d^%d" % (n, 1),
        n = 1
    else:
        cnt = 0
        while n % i == 0:
            cnt += 1; n /= i
        print "%d^%d" % (i, cnt),
print
