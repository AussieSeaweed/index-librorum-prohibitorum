from itertools import combinations

N, T = map(int, input().split())
H = [int(input()) for _ in range(N)]

try:
    print(min(sum(combo) - T for n in range(N + 1) for combo in combinations(H, n) if sum(combo) >= T))
except StopIteration:
    print(-1)