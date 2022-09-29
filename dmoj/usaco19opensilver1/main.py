from functools import partial
from operator import eq
from sys import stdin

n = int(stdin.readline())
grid = [list(map(partial(eq, 'R'), stdin.readline()[:-1])) for _ in range(n)]

for i in range(n):
    if grid[i][0]:
        for j in range(n):
            grid[i][j] = not grid[i][j]
    if grid[0][i]:
        for j in range(n):
            grid[j][i] = not grid[j][i]

count = sum(map(sum, grid))
row_count = tuple(map(sum, grid))
column_count = tuple(sum(grid[r][c] for r in range(n)) for c in range(n))

if count == (n - 1) ** 2:
    coordinates = 0, 0
elif count == n - 1 and row_count.count(n - 1) == 1:
    coordinates = row_count.index(n - 1), 0
elif count == n - 1 and column_count.count(n - 1) == 1:
    coordinates = 0, column_count.index(n - 1)
elif count == 1:
    coordinates = row_count.index(1), column_count.index(1)
else:
    coordinates = None

if coordinates is None:
    print(-1)
else:
    print(coordinates[0] + 1, coordinates[1] + 1)