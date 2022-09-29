W, H, N = map(int, input().split())
# W -> number of columns
# H -> number of rows

psa2d = [[0 for i in range(W + 1)]]

for r in range(1, H + 1):
    psa2d.append([0] + list(map(int, input().split())))

for r in range(1, H + 1):
    for c in range(1, W + 1):
        psa2d[r][c] += psa2d[r - 1][c] + psa2d[r][c - 1] - psa2d[r - 1][c - 1]

def get_rectangle_sum(r1, c1, r2, c2):
    return psa2d[r2][c2] - psa2d[r2][c1 - 1] - psa2d[r1 - 1][c2] + psa2d[r1 - 1][c1 - 1]

ans = 0

for h in range(1, H + 1):
    # r is now the height of the current rectangle
    w = min(W, int(N / h))  # largest width possible with area <= N
    if w > 0:
        for r in range(h, H + 1):
            for c in range(w, W + 1):
                ans = max(ans, get_rectangle_sum(r - h + 1, c - w + 1, r, c))

print(ans)