from functools import reduce
from operator import xor


def stoi(S):
    i = 0

    for s in S:
        i |= 1 << (s + 30)

    return i


def itos(i):
    S = []

    for j in range(-30, 31):
        if i & (1 << (j + 30)):
            S.append(j)

    return S


N, Q = map(int, input().split())
sets = [None] + [stoi(map(int, input().split()[1:])) for _ in range(N)]

for _ in range(Q):
    try:
        S = itos(reduce(xor, map(sets.__getitem__, map(int, input().split()[1:]))))
    except TypeError:
        S = []

    print(len(S), *S)