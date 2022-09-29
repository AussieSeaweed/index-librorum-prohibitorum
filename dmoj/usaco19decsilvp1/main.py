def index_of(value):
    return value - (value // 3 + value // 5 - value // 15) - 1


n = int(input()) - 1

lo, hi = 1, 1

while index_of(hi) < n:
    hi *= 2

while lo < hi:
    mid = (lo + hi) // 2

    if index_of(mid) < n:
        lo = mid + 1
    else:
        hi = mid

print(lo)