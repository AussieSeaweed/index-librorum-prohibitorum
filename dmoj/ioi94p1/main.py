from math import inf

n = int(input())
dp = [int(input())]

for _ in range(n - 1):
    values = list(map(int, input().split()))

    for i, value in enumerate(values):
        values[i] = value + max(dp[i] if i < len(dp) else -inf, dp[i - 1] if i else -inf)

    dp = values

print(max(dp))