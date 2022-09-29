from functools import partial
from operator import truth, gt

n = int(input())
W = tuple(map(int, input().split()))
M = []

for i in range(n):
    c = sum(map(partial(gt, W[i]), W[:i]))
    M.append(-c)
    M.append(c + 1)
else:
    M.append(-n)

M = list(filter(truth, M))

print(len(M))
print('\n'.join(map(str, M)))