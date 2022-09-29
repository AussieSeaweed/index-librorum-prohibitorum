from math import inf


def parse(s):
    return int(s[:-1]) - 1, ord(s[-1]) - ord('A')


def format_(r, c):
    return str(r + 1) + chr(c + ord('A'))


def status(tower):
    x, y, n = 0, 0, 0

    for r in range(len(tower) - 1, -1, -1):
        if r & 1:
            x, y = y, x

        hull = [inf, -inf]

        if tower[r][0]:
            hull[0] = min(hull[0], -0.5)
            hull[1] = max(hull[1], 0.5)
        if tower[r][1]:
            hull[0] = min(hull[0], 0.5)
            hull[1] = max(hull[1], 1.5)
        if tower[r][2]:
            hull[0] = min(hull[0], 1.5)
            hull[1] = max(hull[1], 2.5)

        if n:
            x_center = x / n

            if not hull[0] <= x_center <= hull[1]:
                return False

        for c in range(3):
            if tower[r][c]:
                n += 1
                x += c
                y += 1

        if r & 1:
            x, y = y, x

    return True


N = int(input())
moves = [map(parse, input().split()) for _ in range(N)]
tower = [[True] * 3 for _ in range(18)]

for (r_from, c_from), (r_to, c_to) in moves:
    tower[r_from][c_from] = False

    if not status(tower):
        print(f'The tower collapses after removing {format_(r_from, c_from)}')
        break

    while r_to >= len(tower):
        tower.append([False] * 3)

    tower[r_to][c_to] = True

    if not status(tower):
        print(f'The tower collapses after placing {format_(r_to, c_to)}')
        break
else:
    print('The tower never collapses')