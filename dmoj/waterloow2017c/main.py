n, k = map(int, input().split())

if n <= k * 2:
    P = [None] * n
    count = 0

    for i in range(k):
        indices = range(i, n, k)
        count += len(indices)

        for j, index in enumerate(indices):
            P[index] = count - j

    print(' '.join(map(str, P)))
else:
    print(0)