import sys
raw_input = sys.stdin.readline

k = int(raw_input())
u = [0] * 1000001
i = map(int, raw_input().split())

for x in i:
    u[x] = 1

for x in xrange(1, 1000001):
    u[x] = u[x-1] + u[x]

for x in xrange(int(raw_input())):
    n = int(raw_input())
    print n - u[n]