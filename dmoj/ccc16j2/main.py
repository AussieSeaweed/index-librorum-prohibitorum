mat = [map(int, raw_input().split()) for x in xrange(4)]


def isMagic(matrix):
  init = sum(matrix[0])
  for x in matrix:
    if sum(x) != init:
      return False
  
  for x in xrange(4):
    summing = 0
    for y in xrange(4):
      summing += matrix[y][x]
    if summing != init:
      return False
      
  return True
  

if isMagic(mat):
  print "magic"
else:
  print "not magic"