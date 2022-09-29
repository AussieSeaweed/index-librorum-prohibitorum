input()
vote = raw_input()
a = vote.count("A")
b = vote.count("B")

if a == b:
  print "Tie"
elif a > b:
  print "A"
else:
  print "B"