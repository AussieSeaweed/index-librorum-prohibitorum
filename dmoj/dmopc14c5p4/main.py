from sys import stdin

n, m = map(int, stdin.readline().split())
bads = []
goods = []

for _ in range(n):
    s, p = map(int, stdin.readline().split())

    (goods if p == 2 else bads).append(s)

bads.sort(reverse=True)
goods.sort()

m -= sum(goods)
protection = 2 * len(goods)
protection_max = 0

while True:
    while bads and bads[-1] <= m:
        m -= bads.pop()
        protection += 1

    if m >= 0:
        protection_max = max(protection_max, protection)

    if goods:
        m += goods.pop()
        protection -= 2
    else:
        break

print(protection_max)