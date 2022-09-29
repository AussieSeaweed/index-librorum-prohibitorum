import sys, math
input = sys.stdin.readline
sys.setrecursionlimit(1000000000)


def upper_bound(v, values):
    lo, hi = 0, len(values)

    while lo < hi:
        mid = (lo + hi) // 2

        if not v < values[mid]:
            lo = mid + 1
        else:
            hi = mid

    return lo


def main():
    N, P, M = map(int, input().split())

    units = [map(int, input().split()) for i in range(N)]
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))

    a.sort()
    b.sort()

    sa = a.copy()
    sb = b.copy()

    for i in range(P - 2, -1, -1):
        sa[i] += sa[i + 1]

    for i in range(M - 2, -1, -1):
        sb[i] += sb[i + 1]

    ans = -1
    min_value = math.inf

    for unit in range(N):
        u, v = units[unit]

        cur = 0

        i = upper_bound(u, a)

        if i != P:
            cur += sa[i] - u * (P - i)

        i = upper_bound(v, b)

        if i != M:
            cur += sb[i] - v * (M - i)

        if cur < min_value:
            min_value = cur
            ans = unit

    print(ans + 1)


if __name__ == "__main__":
    main()