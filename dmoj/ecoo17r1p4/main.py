from sys import setrecursionlimit

setrecursionlimit(10 ** 9)


def convert(names):
    indices = {}

    for i, name in enumerate(sorted(names)):
        indices[name] = i

    return list(map(indices.__getitem__, names))


def calculate(names):
    values = convert(names)
    indices = dict(map(tuple, map(reversed, enumerate(values))))
    count = 0

    for i in range(len(values)):
        if i != values[i]:
            j = indices[i]
            indices[i], indices[values[i]] = i, j
            values[i], values[j] = values[j], values[i]
            count += 1

    return count


for _ in range(10):
    N = int(input())
    names = [input() for _ in range(N)]

    print(min(calculate(names[:i] + names[i + 1:]) for i in range(N)))