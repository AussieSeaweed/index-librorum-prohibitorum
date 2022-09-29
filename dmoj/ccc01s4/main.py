import math
raw_input = __import__("sys").stdin.readline

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

def dist(a, b):
    dx = a.x - b.x
    dy = a.y - b.y
    return math.sqrt(dx**2 + dy**2)

pts = list()

N = int(raw_input())

for i in xrange(N):
    pts.append(Point(*map(int, raw_input().split())))

ans = 0
for i in xrange(N):
    for j in xrange(i+1, N):
        for k in xrange(j+1, N):
            a = dist(pts[i], pts[j])
            b = dist(pts[j], pts[k])
            c = dist(pts[k], pts[i])
            s = (a+b+c)/2.
            if s == 0 or (a*a + b*b - c*c < 0) or (a*a + c*c - b*b < 0) or (c*c + b*b - a*a < 0):
                d = max(a, b, c)
            else:
                d = 2 * (a * b * c) / (4 * math.sqrt(s * (s - a) * (s - b) * (s - c)))
            ans = max(ans, d)

print(round(ans,2))