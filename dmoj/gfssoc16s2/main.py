def ace(n):
    lookup = [10, 12, 14]
    base = 1
    i = 0

    while n >= 0:
        i += lookup[n % 3] * base
        n = n // 3 - 1
        base *= 16

    return i


def lower_bound(x):
    lo, hi = 0, 1

    while ace(hi) < x:
        hi *= 2

    while lo < hi:
        mid = (lo + hi) // 2

        if ace(mid) < x:
            lo = mid + 1
        else:
            hi = mid

    return lo


def upper_bound(x):
    lo, hi = 0, 1

    while not x < ace(hi):
        hi *= 2

    while lo < hi:
        mid = (lo + hi) // 2

        if not x < ace(mid):
            lo = mid + 1
        else:
            hi = mid

    return lo


a = int(input())
b = int(input())

print(upper_bound(b) - lower_bound(a))