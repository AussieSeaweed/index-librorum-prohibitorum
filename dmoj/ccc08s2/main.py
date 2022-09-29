import math

radius = input()
while radius:
    pennies = 0
    r2 = radius**2
    for x in xrange(1, radius+1):
        pennies += int(math.sqrt(r2 - x**2) + 1)
    pennies = 4 * pennies + 1
    print(int(pennies))
    radius = input()