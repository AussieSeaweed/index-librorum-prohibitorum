from math import factorial, prod
from collections import Counter

sub = input()
base = input()

pool = list(base)

try:
    for c in sub:
        pool.remove(c)
except ValueError:
    print(0)
else:
    counter = Counter(pool)

    n = factorial(len(pool)) // prod(map(factorial, counter.values()))

    print(n * (len(pool) + 1) % 1000000007)