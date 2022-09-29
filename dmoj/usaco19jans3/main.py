from math import inf

n = int(input())
peaks = [tuple(map(int, input().split())) for _ in range(n)]
intervals = sorted(((x - y, x + y) for x, y in peaks), key=lambda interval: (interval[0], -interval[1]))
end = -inf
count = 0

for interval in intervals:
    if end < interval[1]:
        end = interval[1]
        count += 1

print(count)