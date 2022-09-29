N, K = map(int, input().split())
A = list(map(int, input().split()))
counts = [1] + [0] * (K - 1)
count = 0
sum_ = 0

for a in A:
    sum_ = (sum_ + a) % K
    count += counts[(sum_ - K) % K]
    counts[sum_] += 1

print(count)