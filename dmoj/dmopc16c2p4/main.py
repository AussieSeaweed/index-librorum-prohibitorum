def ftzc(n):
    count = 0
    i = 1

    while 5 ** i <= n:
        factor_count = n // (5 ** i)
        count += factor_count
        i += 1

    return count


def solve_lower_bound(m):
    lo, hi = 1, 1

    while ftzc(hi) < m:
        hi *= 2

    while lo < hi:
        mid = (lo + hi) // 2

        if ftzc(mid) < m:
            lo = mid + 1
        else:
            hi = mid

    return lo


def solve_upper_bound(m):
    lo, hi = 1, 1

    while not m < ftzc(hi):
        hi *= 2

    while lo < hi:
        mid = (lo + hi) // 2

        if not m < ftzc(mid):
            lo = mid + 1
        else:
            hi = mid

    return lo


a, b = map(int, input().split())

print(solve_upper_bound(b) - solve_lower_bound(a))