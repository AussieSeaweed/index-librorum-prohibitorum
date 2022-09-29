from collections import defaultdict

N, K = map(int, input().split())
H, V = [0] * 100001, [0] * 100001
D, U = defaultdict(int), defaultdict(int)

if K > 100000:
    print(-1)
    exit()

for i, (X, Y) in enumerate(map(int, input().split()) for _ in range(N)):
    H[Y] += 1
    V[X] += 1
    D[Y + X] += 1
    U[Y - X] += 1

    if H[Y] == K or V[X] == K or D[Y + X] == K or U[Y - X] == K:
        print(i + 1)
        break
else:
    print(-1)