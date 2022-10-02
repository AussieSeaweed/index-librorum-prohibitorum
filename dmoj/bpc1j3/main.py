from itertools import starmap
from operator import sub

N = int(input())
q = sorted(map(int, input().split()), reverse=True)
X = starmap(sub, zip(q[::2], q[1::2]))

print(sum(X))

