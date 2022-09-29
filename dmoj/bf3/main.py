from itertools import count
import math

for x in count(input()):
  if x < 2:
    continue
  for i in xrange(2, int(math.sqrt(x))+1):
    if x % i == 0:
      break
  else:
    print x
    break