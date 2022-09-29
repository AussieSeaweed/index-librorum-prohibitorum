from collections import defaultdict


def solve(N, grid):
    boundaries = defaultdict(list)

    for r in range(N):
        for c in range(N):
            if grid[r][c] == '#':
                for dr in (-1, 0, 1):
                    for dc in (-1, 0, 1):
                        boundaries[r + dr, c + dc].append(0 in (dr, dc))

    for r in range(N):
        for c in range(N):
            if grid[r][c] == '#':
                del boundaries[r, c]

    for key, value in list(boundaries.items()):
        if value.count(True) >= 2:
            del boundaries[key]

    return len(boundaries)


for _ in range(5):
    N = int(input())
    grid = [input() for _ in range(N)]

    print(solve(N, grid))