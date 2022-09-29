a = input()
b = input()
count = 0

for x in xrange(0, 100):
    num = x**6
    if a <= num and num <= b:
        count += 1
    elif num > b:
        break

print count