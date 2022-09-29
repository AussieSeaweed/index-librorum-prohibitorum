N, M = map(int, input().split())

INFINITY = 99999999

matrix = []
visible = [[False] * M for _ in range(N)]
dist = [[INFINITY] * M for _ in range(N)]


def fill(r, c):
    for r_ in range(r, N):
        if matrix[r_][c] == "W": break
        elif matrix[r_][c] == "." or matrix[r_][c] == "S": visible[r_][c] = True

    for r_ in range(r, -1, -1):
        if matrix[r_][c] == "W": break
        elif matrix[r_][c] == "." or matrix[r_][c] == "S": visible[r_][c] = True

    for c_ in range(c, M):
        if matrix[r][c_] == "W": break
        elif matrix[r][c_] == "." or matrix[r][c_] == "S": visible[r][c_] = True

    for c_ in range(c, -1, -1):
        if matrix[r][c_] == "W": break
        elif matrix[r][c_] == "." or matrix[r][c_] == "S": visible[r][c_] = True


for r in range(N):
    line = input()
    matrix.append(line)

start = tuple()

for r in range(N):
    for c in range(M):
        if matrix[r][c] == "C":
            fill(r, c)
        elif matrix[r][c] == "S":
            start = r, c

from collections import deque
queue = deque()
if not visible[start[0]][start[1]]:
    queue.append(start)
    dist[start[0]][start[1]] = 0

while queue:
    pos = queue.popleft()
    r = pos[0]
    c = pos[1]

    up, down, left, right = False, False, False, False
    nextDist = dist[r][c]

    if matrix[r][c] == "." or matrix[r][c] == "S": up = True; down = True; left = True; right = True; nextDist += 1
    elif matrix[r][c] == "U": up = True
    elif matrix[r][c] == "D": down = True
    elif matrix[r][c] == "L": left = True
    elif matrix[r][c] == "R": right = True

    if up:
        if dist[r-1][c] > nextDist and not visible[r-1][c]:
            dist[r-1][c] = nextDist
            queue.append((r-1, c))
    if down:
        if dist[r+1][c] > nextDist and not visible[r+1][c]:
            dist[r+1][c] = nextDist
            queue.append((r+1, c))
    if left:
        if dist[r][c-1] > nextDist and not visible[r][c-1]:
            dist[r][c-1] = nextDist
            queue.append((r, c-1))
    if right:
        if dist[r][c+1] > nextDist and not visible[r][c+1]:
            dist[r][c+1] = nextDist
            queue.append((r, c+1))

for r in range(N):
    for c in range(M):
        if matrix[r][c] == ".":
            print(dist[r][c] if dist[r][c] < INFINITY else -1)