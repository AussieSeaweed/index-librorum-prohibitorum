for _ in range(5):
    R, C, Ro = map(int, input().split())
    rooks = [tuple(map(int, input().split())) for _ in range(Ro)]
    X, Y = map(set, zip(*rooks))

    print((R - len(X)) * (C - len(Y)))