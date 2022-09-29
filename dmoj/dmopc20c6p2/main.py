def solve(N, A, B):
    X = [i for i in range(N) if A[i]]
    Y = [i for i in range(N) if B[i]]
    strokes = []

    while Y:
        n = 0

        while n < len(Y) and Y[-n - 1] == Y[-1] - n:
            n += 1

        if len(X) < n:
            return None

        L = []
        R = []

        for i in range(n):
            L.append(X.pop())
            R.append(Y.pop())

        if any(l > r for l, r in zip(L, R)):
            return None
        elif L != R:
            strokes.append((L[-1], R[0]))

    if X:
        return None

    return strokes


N = int(input())
A = list(map(int, input().split()))
B = list(map(int, input().split()))

strokes = solve(N, A, B)

if strokes is None:
    print(-1)
else:
    print(len(strokes))

    for stroke in strokes:
        print(stroke[0] + 1, stroke[1] + 1)