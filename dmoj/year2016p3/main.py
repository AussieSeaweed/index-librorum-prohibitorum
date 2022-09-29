N, sizes = int(input()), sorted(map(int, input().split()))
max_size = 0

for i in range(N):
    remainders = set(sizes[i + 1:])

    for j in range(i):
        if sizes[i] + sizes[i] - sizes[j] in remainders:
            max_size = max(max_size, 3 * sizes[i])

print(max_size)