from collections import defaultdict
from functools import partial

n, m = map(int, input().split())
cereals = tuple(map(tuple, map(partial(map, int), map(str.split, (input() for _ in range(n))))))
takers = defaultdict(lambda: n)
counts = []

for i in range(n - 1, -1, -1):
    while i < n and i < takers[cereals[i][0]]:
        takers[cereals[i][0]], i = i, takers[cereals[i][0]]

    while i < n and i < takers[cereals[i][1]]:
        takers[cereals[i][1]], i = i, takers[cereals[i][1]]

    counts.append(len(takers))

print('\n'.join(map(str, reversed(counts))))