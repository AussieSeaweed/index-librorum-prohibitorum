from itertools import count
from math import floor, ceil

N = int(input())
M = list(map(float, input().split()))
m_min = min(M)
X = [m / m_min for m in M]

for i in count(1):
    lo, hi = 0.99, 1.01

    for m, x in zip(M, X):
        jlo = ceil(0.99 / hi * i * x)
        jhi = floor(1.01 / lo * i * x)

        if jlo <= jhi:
            lo = max(lo, 0.99 * x * i / jhi)
            hi = min(hi, 1.01 * x * i / jlo)
        else:
            break
    else:
        if lo <= hi:
            gcd = hi * m_min / i
            print(f'{gcd:.4f}')
            break