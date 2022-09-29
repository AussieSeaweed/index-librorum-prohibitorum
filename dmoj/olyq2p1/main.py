def solve(distance_min):
    Q = [P[0]]

    for p in P[1:]:
        if Q[-1] + distance_min <= p:
            Q.append(p)

    return len(Q) >= m


n, m = map(int, input().split())
P = sorted(int(input()) for _ in range(n))

lo, hi = 0, 1000000001

while lo < hi:
    mid = (lo + hi) // 2

    if solve(mid):
        lo = mid + 1
    else:
        hi = mid

print(lo - 1)