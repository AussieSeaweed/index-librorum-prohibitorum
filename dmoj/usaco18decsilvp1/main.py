def check(k):
    buses = []

    for t in T:
        if not buses or len(buses[-1]) == c or t - buses[-1][0] > k:
            buses.append([t])
        else:
            buses[-1].append(t)

    return len(buses) <= m


n, m, c = map(int, input().split())
T = sorted(map(int, input().split()))

lo, hi = 0, T[-1] - T[0]

while lo < hi:
    mid = (lo + hi) // 2

    if not check(mid):
        lo = mid + 1
    else:
        hi = mid

print(lo)