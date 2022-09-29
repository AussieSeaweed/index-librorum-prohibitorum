import sys
from collections import defaultdict
raw_input = sys.stdin.readline

N, M = map(int, raw_input().split())

graph = defaultdict(list)

for x in xrange(M):
    x, y = map(int, raw_input().split())
    graph[x].append(y)


def taller(a, b):
    visited = []
    queue = [a]
    while queue:
        person = queue.pop()
        visited.insert(0,person)

        if person == b:
            return True

        for p in graph[person]:
            if p not in visited:
                queue.append(p)

    return False


p, q = map(int, raw_input().split())

if taller(p, q):
    print "yes"
elif taller(q, p):
    print "no"
else:
    print "unknown"