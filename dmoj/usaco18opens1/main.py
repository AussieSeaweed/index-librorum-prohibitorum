n = int(input())
A = tuple(int(input()) for _ in range(n))

indices = {a: i for i, a in enumerate(sorted(A))}
count = 0

for i, a in enumerate(A):
    count = max(count, i - indices[a])

print(count + 1)