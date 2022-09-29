from math import sqrt, floor, ceil

xf, yf, r = map(int, input().split())
xw, yw, l = map(int, input().split())

sqr_r = r * r

count = 0

identical = xf == xw and yf == yw

for y in range(max(yf - r, yw - l), min(yf + r, yw + l) + 1):
    deltaxf = sqrt(sqr_r - (y - yf)**2)
    minxf = max(floor(xf - deltaxf), ceil(xf - deltaxf))
    maxxf = min(floor(xf + deltaxf), ceil(xf + deltaxf))

    deltaxw = l - abs(yw - y)
    minxw = xw - deltaxw
    maxxw = xw + deltaxw

    minx = max(minxf, minxw)
    maxx = min(maxxf, maxxw)

    if minx > min(maxxf, maxxw):
        continue
    if maxx < max(minxf, minxw):
        continue

    if minx <= xf <= maxx and y == yf:
        count -= 1

    if minx <= xw <= maxx and y == yw and not identical:
        count -= 1

    count += maxx - minx + 1

print(count)