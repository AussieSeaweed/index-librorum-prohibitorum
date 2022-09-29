from itertools import combinations_with_replacement
from math import factorial, prod


def solve(s):
    return factorial(len(s)) // prod(map(factorial, map(s.count, set(s))))


N, K = map(int, input().split())
s = input()
count = 0

for replacements in map(list, combinations_with_replacement(map(chr, range(ord('a'), ord('z') + 1)), s.count('*'))):
    count += solve(''.join(replacements.pop() if c == '*' else c for c in s))

print(count)