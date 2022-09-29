from functools import cache
from math import floor, log2
from sys import setrecursionlimit

setrecursionlimit(1000000)


@cache
def get_count(m, n):
    if m > n:
        m, n = n, m

    if not m:
        return 0
    elif 1 << floor(log2(m)) == m:
        return n // m + get_count(n % m, m)

    size = 1 << floor(log2(m))

    return 1 + get_count(m - size, size) + get_count(m, n - size)


for _ in range(5):
    N, M = map(int, input().split())

    print(get_count(N, M))