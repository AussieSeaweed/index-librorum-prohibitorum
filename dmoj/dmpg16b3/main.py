art = []
for i in range(3):
  row = input()
  art.append(row)
  
v, h, w = map(int, input().split())
v = str(v)

times = h - 1

newart = []
for i in art:
  row = "|" + " " * (w)  + i + " " * (w) + "|" 
  newart.append(row)
  
top = "=" * len(row)

print (top)
print ("|" + v + " " * (len(row) - len(v) - 2) + "|")

for i in range(times):
  print ("|" + " " * (len(row) - 2) + "|")
  
for i in newart:
  print (i)
  
for i in range(times):
  print ("|" + " " * (len(row) - 2) + "|")
  
print ("|" + " " * (len(row) - len(v) - 2) + v + "|")

print (top)