from collections import Counter
from functools import partial
from operator import eq


def normalize(grid):
    for r in range(len(grid) - 1):
        for c in range(len(grid[r]) - 1):
            if grid[r][c]:
                grid[r][c] = not grid[r][c]
                grid[r + 1][c] = not grid[r + 1][c]
                grid[r][c + 1] = not grid[r][c + 1]
                grid[r + 1][c + 1] = not grid[r + 1][c + 1]


def reduce(grid):
    state = 0

    for i in range(len(grid)):
        state = state << 2 | grid[-1][i] << 1 | grid[i][-1]

    return state


n = int(input())
g = int(input())
counter = Counter()

for _ in range(g):
    grid = list(list(map(partial(eq, 'R'), input())) for _ in range(n))
    normalize(grid)
    state = reduce(grid)
    counter[state] += 1

count = sum(m * (m - 1) // 2 for m in counter.values())

print(count)