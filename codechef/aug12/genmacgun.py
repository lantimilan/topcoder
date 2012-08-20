m=int(raw_input("row: "))
n=int(raw_input("col: "))
f=open('large.in', 'w')
f.write('%d %d\n' % (m, n))
for i in range(m):
    f.write('F'*n + '\n')
f.write('0 0\n');
