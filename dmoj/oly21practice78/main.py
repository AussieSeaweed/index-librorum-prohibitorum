from math import inf

N = int(input())
H = list(map(int, input().split()))
h_min = min(H)
h_max = max(H)

opt = inf

for t in range(h_min, h_max + 1):
    cost = 0

    for h in H:
        cost += (h - t) ** 2

    opt = min(opt, cost)

print(opt)