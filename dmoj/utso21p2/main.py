from itertools import repeat
from math import ceil, sqrt


def count(a, b):
    return (a + b) * (a + b + 1) // 2 - b * (b + 1) // 2


k = int(input())
n = max(1, ceil((-1 + sqrt(1 + 8 * k)) / 2))
A = []

while n:
    lo, hi = 0, n + 1

    while lo < hi:
        mid = (lo + hi) // 2

        if count(n - mid, mid) >= k:
            lo = mid + 1
        else:
            hi = mid

    m = lo - 1

    if m == n:
        n -= m
        A.extend(repeat(2, m))
    else:
        k -= (m + 1) * (n - m)
        n -= m + 1
        A.extend(repeat(2, m))
        A.append(1)

print(len(A))
print(' '.join(map(str, A)))