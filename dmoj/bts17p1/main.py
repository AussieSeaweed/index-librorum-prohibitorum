i = raw_input().split()
for x in xrange(1, len(i)):
    if i[x][0].isupper():
        i[x-1] += "."

if i[len(i)-1] != ".":
    i[len(i) - 1] += "."

print " ".join(i)