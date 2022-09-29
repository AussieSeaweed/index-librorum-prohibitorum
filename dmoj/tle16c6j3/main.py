from math import ceil, inf


def solve(x1, x2, K, L):
    n1 = ceil(abs(x1 - x2) / (K - L))
    n2 = ceil(abs(x1 - x2) / (L - 1)) if L > 1 else inf

    return min(n1, n2)

x1, y1, K = map(int, input().split())
x2, y2, L = map(int, input().split())

print(solve(x1, x2, K, L) + solve(y1, y2, K, L))