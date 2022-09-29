import sys
raw_input = sys.stdin.readline

R, C = map(int, raw_input().split())

arr = [[0]*(C+1) for x in xrange(R+1)]
state = [[False]*(C+1) for x in xrange(R+1)]

for x in xrange(int(raw_input())):
    cR, cC = map(int, raw_input().split())
    state[cR][cC] = True

arr[1][1] = 1
state[1][1] = True

for x in xrange(1, R + 1):
    for y in xrange(1, C + 1):
        if not state[x][y]:
            arr[x][y] = arr[x-1][y] + arr[x][y-1]

print arr[x][y]