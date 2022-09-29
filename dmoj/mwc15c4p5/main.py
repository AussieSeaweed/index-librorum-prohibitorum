from bisect import bisect_right
from collections import defaultdict

n, x, y = map(int, input().split())
V = {x}
H = defaultdict(int)

for _ in range(n):
    line = input()

    if line[0] == 'h':
        s, d = map(int, line.split()[1:])
        H[s] = max(H[s], d)
    elif line[0] == 'v':
        s = int(line.split()[1])
        V.add(s)

V = sorted(V)
count = len(V)

for d in H.values():
    count += bisect_right(V, d)

print(count)