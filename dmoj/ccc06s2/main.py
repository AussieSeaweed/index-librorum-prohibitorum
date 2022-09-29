from collections import defaultdict

chars = defaultdict(lambda: ".")

initial = raw_input().rstrip()
encoded = raw_input().rstrip()

for x in xrange(len(initial)):
  chars[encoded[x]] = initial[x]
  
build = ""  
for x in raw_input().rstrip():
  build += chars[x]

print build