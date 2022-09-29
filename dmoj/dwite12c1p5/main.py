from itertools import permutations, product
from math import inf
from queue import Queue


def solve(n, grid):
    def bfs(source, destination, count):
        distance = [[inf] * n for _ in range(n)]
        queue = Queue()

        distance[source[0]][source[1]] = 0
        queue.put(source)

        while not queue.empty():
            r, c = queue.get()

            for dr, dc in ((0, -1), (0, 1), (-1, 0), (1, 0)):
                nr, nc = r + dr, c + dc

                if 0 <= nr < n and 0 <= nc < n \
                        and (grid[nr][nc] in ('.', 'B', '*') + tuple(map(chr, range(ord('a'), ord('a') + min(6, count))))) \
                        and distance[nr][nc] == inf:
                    distance[nr][nc] = distance[r][c] + 1
                    queue.put((nr, nc))

        return distance[destination[0]][destination[1]]

    billy = None
    candies = []
    result = 0, 0

    for r, c in product(range(n), repeat=2):
        if grid[r][c] == '*':
            candies.append((r, c))
        elif grid[r][c] == 'B':
            billy = r, c

    for permutation in permutations(candies):
        permutation = (billy,) + permutation
        c, s = 0, 0

        for i, (source, destination) in enumerate(zip(permutation, permutation[1:])):
            distance = bfs(source, destination, i)

            if distance == inf:
                break

            c += 1
            s += distance

        if result[0] < c or result[0] == c and result[1] > s:
            result = c, s

    return result


for _ in range(5):
    n = int(input())
    grid = [input() for _ in range(n)]

    print(' '.join(map(str, solve(n, grid))))