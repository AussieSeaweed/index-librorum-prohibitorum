N, K = map(int, input().split())
keys = [int(input()) - 1 for _ in range(N)]
indices = {key: i for i, key in enumerate(keys)}

init = 0
prev = 0

for door in range((K - 1) % N + 1):
    init += (indices[door] - prev) % N
    prev = indices[door]

cycle = 0
prev = indices[N - 1]

for door in range(N):
    cycle += (indices[door] - prev) % N
    prev = indices[door]

print(init + cycle * ((K - 1) // N))