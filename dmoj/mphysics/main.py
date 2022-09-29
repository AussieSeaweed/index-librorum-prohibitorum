from itertools import repeat


def merge(sc1, sc2):
    (s1, e1), (s2, e2) = sc1, sc2

    s = s1 * s2
    e = e1 + e2

    while round(s, 2) >= 10:
        s /= 10
        e += 1

    return s, e


def solve(n, k):
    if k == 0:
        return 1, 0

    sc = merge(*repeat(solve(n, k // 2), 2))

    if k & 1:
        sc = merge(sc, (n, 0))

    return sc


significand, exponent = solve(*map(int, input().split()))

print(f'{significand:1.2f}\n{exponent}')