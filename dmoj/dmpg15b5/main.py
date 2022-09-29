N, K, L = map(int, input().split())

fires = list()

def V(i):
    return max(abs(fires[i] - fires[i - 1]), abs(fires[i + 1] - fires[i]))

for _ in range(N):
    fires.append(int(input()))

fires.insert(0, fires[-1])
fires.append(fires[1])

count = 0

for i in range(1, len(fires) - 1):
    if (fires[i] >= K) != (V(i) <= L):
        count += 1

print(count)