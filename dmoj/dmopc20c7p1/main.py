n = int(input())
M = tuple(map(int, input().split()))
indices = sorted(range(2 * n), key=M.__getitem__)

m = sum(M[indices[i]] != M[indices[i + n]] for i in range(n))

print(m)

for i in range(n):
    print(indices[i] + 1, indices[i + n] + 1)