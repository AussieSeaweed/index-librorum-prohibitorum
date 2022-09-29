def solve(N, L, R, U, D):
    blocks = []

    for i, (l, r, u, d) in enumerate(zip(L, R, U, D)):
        if (l == -1) ^ (r == -1):
            return False
        if (u == -1) ^ (d == -1):
            return False
        if l != -1 and l + r >= N:
            return False
        if u != -1 and u + d >= N:
            return False

        if l != -1:
            blocks.append((i, l))
            blocks.append((i, N - 1 - r))
        if u != -1:
            blocks.append((u, i))
            blocks.append((N - 1 - d, i))

    for r, c in blocks:
        if L[r] == -1 or c < L[r] or c > N - 1 - R[r]:
            return False
        if U[c] == -1 or r < U[c] or r > N - 1 - D[c]:
            return False

    return True


N = int(input())
L = list(map(int, input().split()))
R = list(map(int, input().split()))
U = list(map(int, input().split()))
D = list(map(int, input().split()))

if solve(N, L, R, U, D):
    print('DA')
else:
    print('NE')