import sys

raw_input = sys.stdin.readline

for x in xrange(input()):
  a = list(raw_input())
  i = 0
  for _ in xrange(len(a)):
    if a[_].isalpha():
      if i % 2 == 0:
        a[_] = a[_].lower()
      else:
        a[_] = a[_].upper()
      i+=1
  print "".join(a)