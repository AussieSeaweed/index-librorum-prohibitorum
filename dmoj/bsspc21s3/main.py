from itertools import accumulate
from sys import stdin

n, k = map(int, stdin.readline().split())
A = tuple(map(int, stdin.readline().split()))
S = tuple(accumulate((0,) + A))
dp = [0] * (n + 1)

for i in range(k, n + 1):
    dp[i] = max(0, dp[i - k] + S[i] - S[i - k])

print(max(dp))