n, m, k, v = map(int, input().split())
count = [0, 0]

for i in range(k):
    count[bool(v & (1 << i))] += 1

print(pow(2, k * (n - 1), m))
print(pow(pow(2, n, m) - 1, count[1], m))
print(pow(pow(2, n, m) - 1, count[0], m))