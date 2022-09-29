N = int(input())

neg = list()
pos = list()
haszero = False

for _ in range(N):
    n = int(input())
    if n < 0:
        neg.append(n)
    elif n > 0:
        pos.append(n)
    else:
        haszero = True

product = 1

for num in pos:
    product *= num

neg.sort()

for i in range(0, len(neg) - len(neg) % 2):
    product *= neg[i]

if len(pos) == 0 and len(neg) <= 1 and haszero:
    print(0)
elif len(neg) == 1:
    print(neg[0])
else:
    print(product)