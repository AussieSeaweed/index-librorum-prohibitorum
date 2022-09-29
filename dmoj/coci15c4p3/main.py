from functools import reduce
from operator import or_

N = int(input())
M = [list(map(int, input().split())) for _ in range(N)]

print(*(reduce(or_, row) for row in M))