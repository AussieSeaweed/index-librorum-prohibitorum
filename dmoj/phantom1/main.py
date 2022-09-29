import sys, math
raw_input = sys.stdin.readline

for x in xrange(input()):
  I, F = map(int, raw_input().split())
  count = 0
  for i in xrange(I, F):
    if i < 2:
      continue
    for _ in xrange(2, int(math.sqrt(i))+1):
      if i % _ == 0:
        break
    else:
      count += 1
  print count