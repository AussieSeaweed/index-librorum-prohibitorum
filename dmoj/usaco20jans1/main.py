from functools import cache
from sys import stdin


@cache
def solve(m):
    baskets = []

    for b in B:
        while b:
            berries = min(b, m)
            b -= berries
            baskets.append(berries)

    baskets.sort()

    return sum(baskets[-k:-k // 2])


n, k = map(int, stdin.readline().split())
B = tuple(map(int, stdin.readline().split()))

for i in range(2, 1001):
    if solve(i - 1) > solve(i):
        print(solve(i - 1))
        break
else:
    print(solve(1000))