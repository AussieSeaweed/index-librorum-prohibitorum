for _ in range(10):
    N = int(input())
    M = list(map(int, input().split()))

    count = 0

    for i in range(1, N):
        a = M.index(N - i)
        b = M.index(N - i + 1)

        if a > b:
            count += a
            M.insert(0, M.pop(a))

    print(count)