s = ''
for i in range(3000):
    if i & 1:
        s += 'G'
    else:
        s += 'L'
print s
