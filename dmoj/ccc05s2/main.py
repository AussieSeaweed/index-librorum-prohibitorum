import sys
raw_input = sys.stdin.readline

x = 0
y = 0

c, r = map(lambda _: int(_), raw_input().split())

while 1:
    newx, newy = map(lambda _: int(_), raw_input().split())
    if newx == 0 and newy == 0:
        break
    x += newx
    y += newy

    if x < 0:
        x = 0
    elif x > c:
        x = c
    if y < 0:
        y = 0
    elif y > r:
        y = r

    print str(x) + " " + str(y)