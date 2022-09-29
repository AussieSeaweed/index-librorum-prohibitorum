import sys
raw_input = sys.stdin.readline


def isPossible(trailers):
    branch = []
    req = 1
    while 1:
        if len(trailers) == 0 and len(branch) == 0:
            return "Y"

        if len(trailers) and req == trailers[-1]:
            req += 1
            trailers.pop()
        elif len(branch) and req == branch[-1]:
            req += 1
            branch.pop()
        elif len(trailers):
            branch.append(trailers.pop())
        else:
            return "N"


for x in xrange(int(raw_input())):
    N = int(raw_input())
    ts = [None] * N
    for y in xrange(N):
        ts[y] = int(raw_input())
    print isPossible(ts)