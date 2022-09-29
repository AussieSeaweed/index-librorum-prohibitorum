from math import ceil

N, M = int(input()), int(input())

Q = 0

while N > (1 << Q):
    Q += 1

print(ceil(Q / M))