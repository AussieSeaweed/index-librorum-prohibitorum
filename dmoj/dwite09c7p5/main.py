for _ in range(5):
    n, k = map(int, input().split())

    print('ON' if k >> (n - 1) & 1 else 'OFF')