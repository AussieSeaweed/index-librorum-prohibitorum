import sys
raw_input = sys.stdin.readline

for x in xrange(input()):
    s = raw_input().rstrip().split()
    for _ in xrange(len(s)):
        if len(s[_]) == 4:
            s[_] = "****"

    print " ".join(s)