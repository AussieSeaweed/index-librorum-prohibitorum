from sys import stdin
from math import hypot
from bisect import bisect_right

N, Q = map(int, stdin.readline().split())
houses = sorted(hypot(*map(int, stdin.readline().split())) for _ in range(N))

for _ in range(Q):
    r = int(stdin.readline())
    print(bisect_right(houses, r))