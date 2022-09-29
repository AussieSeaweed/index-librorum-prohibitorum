n = int(input())
M = tuple(map(int, input().split()))
bins = [[], [], []]

for m in M:
    bins[m % 3].append(m)

if len(bins[0]) <= len(bins[1]) + len(bins[2]) + 1 and (not bins[1] or not bins[2] or bins[0]):
    A = []
    B = []

    while bins[1]:
        if bins[0]:
            A.append(bins[0].pop())
        A.append(bins[1].pop())

    while bins[2]:
        if bins[0]:
            B.append(bins[0].pop())
        B.append(bins[2].pop())

    print(' '.join(map(str, B + A + bins[0])))
else:
    print('impossible')