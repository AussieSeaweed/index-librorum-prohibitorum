import sys
raw_input = sys.stdin.readline

N = input()
N2 = N * 2

land = [None for x in xrange(N2)]

for x in xrange(N2):
    land[x] = raw_input()

count = [0, 0, 0, 0]

for y in xrange(N2):
    for x in xrange(N2):
        if land[y][x] == "g":
            if x < N:
                if y < N:
                    count[1] += 1
                else:
                    count[2] += 1
            else:
                if y < N:
                    count[0] += 1
                else:
                    count[3] += 1

most_gold = max(count)

print count.index(most_gold) + 1