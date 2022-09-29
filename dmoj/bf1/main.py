import sys
raw_input = sys.stdin.readline

l = [None] * int(raw_input())
for x in xrange(len(l)):
    l[x] = int(raw_input())
    
l = sorted(l)
print "\n".join(map(lambda x: str(x), l))