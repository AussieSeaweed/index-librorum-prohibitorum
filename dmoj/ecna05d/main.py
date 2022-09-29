from itertools import count
from sys import setrecursionlimit

setrecursionlimit(10 ** 9)


def solve(R, C, queens, knights, pawns):
    blocks = set(queens + knights + pawns)
    marks = blocks.copy()

    def mark(r, c):
        if 0 < r <= R and 0 < c <= C and (r, c) not in blocks:
            marks.add((r, c))
            return True

        return False

    for r, c in queens:
        for k in range(1, max(R, C)):
            if not mark(r + k, c):
                break
        for k in range(1, max(R, C)):
            if not mark(r - k, c):
                break
        for k in range(1, max(R, C)):
            if not mark(r, c + k):
                break
        for k in range(1, max(R, C)):
            if not mark(r, c - k):
                break
        for k in range(1, max(R, C)):
            if not mark(r + k, c + k):
                break
        for k in range(1, max(R, C)):
            if not mark(r - k, c + k):
                break
        for k in range(1, max(R, C)):
            if not mark(r + k, c - k):
                break
        for k in range(1, max(R, C)):
            if not mark(r - k, c - k):
                break

    for r, c in knights:
        mark(r + 1, c + 2)
        mark(r - 1, c + 2)
        mark(r + 1, c - 2)
        mark(r - 1, c - 2)
        mark(r + 2, c + 1)
        mark(r - 2, c + 1)
        mark(r + 2, c - 1)
        mark(r - 2, c - 1)

    return R * C - len(marks)


try:
    for i in count(1):
        R, C = map(int, input().split())

        coords = list(map(int, input().split()))
        queens = [(coords[i], coords[i + 1]) for i in range(1, len(coords), 2)]

        coords = list(map(int, input().split()))
        knights = [(coords[i], coords[i + 1]) for i in range(1, len(coords), 2)]

        coords = list(map(int, input().split()))
        pawns = [(coords[i], coords[i + 1]) for i in range(1, len(coords), 2)]

        print(f'Board {i} has {solve(R, C, queens, knights, pawns)} safe squares.')
except EOFError:
    ...