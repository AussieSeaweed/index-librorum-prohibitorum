from collections import defaultdict
raw_input = __import__("sys").stdin.readline

N = int(raw_input())
summation = 0.
for x in xrange(N):
    summation += int(raw_input())

for x in xrange(int(raw_input())):
    N += 1
    summation += int(raw_input())
    print round(summation / N, 3)