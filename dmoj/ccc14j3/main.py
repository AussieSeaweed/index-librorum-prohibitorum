import sys
raw_input = sys.stdin.readline

pts = [100, 100]

for x in xrange(input()):
  cast = map(lambda x: int(x), raw_input().split())
  if cast[0] > cast[1]:
    pts[1] -= cast[0]
  elif cast[1] > cast[0]:
    pts[0] -= cast[1]
    
print "\n".join(map(lambda x: str(x), pts))