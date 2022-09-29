from itertools import product
from math import inf
from sys import stdin


def solve(aliens, depth=0):
    if not aliens:
        return depth
    elif depth >= n - 2:
        return inf

    count = inf

    for dr, dc in cardinal_directions:
        coordinates = {(r + dr, c + dc) for r, c in aliens if grid[r + dr][c + dc] != 'W'}
        count = min(count, solve(coordinates, depth + 1))

    return count


cardinal_directions = ((0, -1), (0, 1), (-1, 0), (1, 0))

n = int(stdin.readline())
grid = tuple(stdin.readline() for _ in range(n))

print(solve({(r, c) for r, c in product(range(n), repeat=2) if grid[r][c] == 'A'}))