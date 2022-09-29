N = int(input())
D = tuple(map(int, input().split()))
d_prev = 0
count = 0

for d in D:
    if d_prev < d:
        count += d - d_prev
    d_prev = d

print(count)