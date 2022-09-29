N = int(input())
queries = [0] + list(map(int, (input(f'? {1} {i + 1}\n') for i in range(1, N))))
indices = [0]

for i in range(1, N):
    indices.insert(len(indices) - queries[i] + queries[i - 1], i)

recipe = [0] * N

for i in range(N):
    recipe[indices[i]] = i + 1

print('!', ' '.join(map(str, recipe)))