import math
N, M = map(int, input().split())
edge = []

dist = {}
for i in range(N):
  s = input()
  dist[s] = 999999999

for i in range(M):
  f1, f2, w = map(str, input().split())
  w = -(math.log(float(w)))
  edge.append((f1,f2,w))

dist["APPLES"] = 0
for i in range(N):
  for m in edge:
    if dist[m[0]] + m[2] < dist[m[1]]:
      dist[m[1]] = dist[m[0]] + m[2]

if dist["APPLES"] < -0.01:
  print ("YA")
else:
  print ("NAW")