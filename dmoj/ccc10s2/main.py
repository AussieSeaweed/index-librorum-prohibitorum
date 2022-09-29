import sys
raw_input = sys.stdin.readline

bins = dict()

for x in xrange(int(raw_input())):
    alpha, bin_num = raw_input().split()
    bins[bin_num] = alpha

before = raw_input().rstrip()
after = ""

length = 1
while before:
    if before[:length] in bins.keys():
        after += bins[before[:length]]
        before = before[length:]
        length = 1
    else:
        length += 1

print after