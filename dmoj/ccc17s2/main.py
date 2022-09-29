import sys
raw_input = sys.stdin.readline

N = int(raw_input())

tides = map(int, raw_input().split())
tides.sort()

output = []

if N % 2 == 0:
    low = list(reversed(tides[:N/2]))
    high = tides[N/2:]
else:
    low = list(reversed(tides[:N/2+1]))
    high = tides[N/2+1:]

i = 0
while 1:
    if len(low) > 0:
        output.append(low[i])
        del low[i]
    if len(high) > 0:
        output.append(high[i])
        del high[i]

    if len(high) == 0 and len(low) == 0:
        break

print " ".join(map(str, output))