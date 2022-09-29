from math import inf, isinf
from queue import Queue


def solve(grid):
    def neighbors_aux(r, c, dr, dc):
        while 0 <= r + dr < 10 and 0 <= c + dc < 10 \
                and grid[r + dr][c + dc] != '#':
            r += dr
            c += dc

        return r, c

    def neighbors(r, c):
        for dr, dc in ((0, -1), (0, 1), (-1, 0), (1, 0)):
            yield neighbors_aux(r, c, dr, dc)

    ar, ac, br, bc = None, None, None, None

    for r in range(10):
        for c in range(10):
            if grid[r][c] == 'A':
                ar, ac = r, c
            elif grid[r][c] == 'B':
                br, bc = r, c

    distances = [[inf] * 10 for _ in range(10)]
    queue = Queue()

    distances[ar][ac] = 0
    queue.put((ar, ac))

    while not queue.empty():
        r, c = queue.get()

        for nr, nc in neighbors(r, c):
            if isinf(distances[nr][nc]):
                distances[nr][nc] = distances[r][c] + 1
                queue.put((nr, nc))

    return distances[br][bc]


for _ in range(5):
    print(solve([input() for _ in range(10)]))
    input()