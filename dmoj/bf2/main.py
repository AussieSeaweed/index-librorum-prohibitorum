import sys
raw_input = sys.stdin.readline

s = raw_input().rstrip()
k = int(raw_input())

least = s[:k]
for x in xrange(1, len(s)-k):
    if s[x:x+k] < least:
        least = s[x:x+k]

print least