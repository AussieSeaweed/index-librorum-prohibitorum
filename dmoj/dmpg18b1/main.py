p, c, v = map(int,input().split())
pr = p%3
p = p//3
cr = c%3
c = c//3
vr = v%3
v = v//3
if pr:
    p +=1
if cr:
    c+=1
if vr:
    v+=1
sum = v+c+p
print (sum)