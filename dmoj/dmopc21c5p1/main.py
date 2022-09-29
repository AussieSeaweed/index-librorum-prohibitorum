N = int(input())

if N == 1:
    print(1)
elif N < 5:
    print(-1)
else:
    evens = range(6, N + 1, 2)
    odds = range(7, N + 1, 2)

    values = tuple(evens) + (2, 4, 5, 1, 3) + tuple(odds)

    print(' '.join(map(str, values)))