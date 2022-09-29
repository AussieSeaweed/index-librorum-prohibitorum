R, S = map(int, input().split())
apples = [[i for i, c in enumerate(input()) if c == 'J'] for _ in range(R)]

count = 0
prev_end = 0
o = 1

for indices in reversed(apples):
    if indices:
        if o == 1:
            start, end = indices[0], indices[-1]
        else:
            start, end = indices[-1], indices[0]

        count += abs(start - prev_end) + abs(end - start)
        prev_end = end

    o = -o

try:
    count += R - next(i for i in range(R) if apples[i]) - 1
except StopIteration:
    ...

print(count)