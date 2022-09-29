from math import inf

T = int(input())

for _ in range(T):
    N, M = map(int, input().split())
    X, Y = -inf, -inf

    for _ in range(M):
        x, y = map(int, input().split())
        X = max(X, x)
        Y = max(Y, y)

    print(-1 if X + Y > N else 'a' * (N - Y) + 'b' * Y)