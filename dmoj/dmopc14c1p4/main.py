import datetime

c = map(int, raw_input().split())
d = map(int ,raw_input().split())

dist = abs(c[0]-d[0]) + abs(c[1]-d[1])

y, m, d, h, min, s = map(int, raw_input().split(":"))

date = datetime.datetime(year=y, month=m, day=d, hour=h, minute=min, second=s) + datetime.timedelta(seconds=dist)

print(str(date).replace("-", ":").replace(" ", ":"))