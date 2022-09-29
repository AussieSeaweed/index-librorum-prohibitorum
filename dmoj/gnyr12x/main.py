for _ in range(int(input())):
    D = int(input())
    chars = input()
    N = int(input())
    indices = list(map(int, input().split()))

    indices[0] %= len(chars)

    for i in range(1, N):
        indices[i] = (indices[i - 1] + indices[i]) % len(chars)

    print(D, ''.join(map(chars.__getitem__, indices)))