n, k = map(int, input().split())
counts = [[0] * 1001 for _ in range(1001)]

for _ in range(n):
    x1, y1, x2, y2 = map(int, input().split())

    counts[x1][y1] += 1
    counts[x1][y2] -= 1
    counts[x2][y1] -= 1
    counts[x2][y2] += 1

area = 0

for i in range(1000):
    counts[0][i + 1] += counts[0][i]
    counts[i + 1][0] += counts[i][0]

for r in range(1000):
    for c in range(1000):
        counts[r + 1][c + 1] += counts[r + 1][c] + counts[r][c + 1] - counts[r][c]

        if counts[r][c] == k:
            area += 1

print(area)