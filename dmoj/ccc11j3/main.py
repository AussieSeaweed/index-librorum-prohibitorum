prev = input()
now = input()

count = 2
while 1:
  new = prev - now
  if new < 0:
    break
  count += 1
  prev = now
  now = new

print count