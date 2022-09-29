from itertools import count

year = input() + 1

for y in count(year):
    str_y = str(y)
    for x in str_y:
        if str_y.count(x) > 1:
            break
    else:
        print str_y
        break