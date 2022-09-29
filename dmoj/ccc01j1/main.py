N = input()

arr = [[" " for x in xrange(N*2)] for x in xrange(N)]

i = 0
for x in range(1,N+1,2) + list(reversed(range(1,N,2))):
    y = 1
    while y <= x:
        arr[i][y-1] = "*"
        arr[i][-y] = "*"
        y += 1
    i += 1
for x in arr:
    print "".join(x)