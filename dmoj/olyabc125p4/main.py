n = int(input())
A = tuple(map(int, input().split()))
dp = [[0] * n, [0] * n]

dp[0][-1] = A[-1]
dp[1][-1] = -A[-1]

for i in range(n - 2, -1, -1):
    dp[0][i] = max(A[i] + dp[0][i + 1], -A[i] + dp[1][i + 1])
    dp[1][i] = max(-A[i] + dp[0][i + 1], A[i] + dp[1][i + 1])

print(dp[0][0])