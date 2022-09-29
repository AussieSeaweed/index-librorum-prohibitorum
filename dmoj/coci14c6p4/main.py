N, K = map(int, input().split())

if N // K + bool(N % K) > K:
    print(-1)
else:
    for i in range(1, N + 1, K):
        for j in range(min(N, i + K - 1), i - 1, -1):
            print(j, end=' ')