import sys

raw_input = sys.stdin.readline

for x in xrange(input()):
  print sum(map(lambda x: int(x), raw_input().split()))