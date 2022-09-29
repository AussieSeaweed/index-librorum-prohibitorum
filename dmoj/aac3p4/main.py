from collections import Counter

n, m = map(int, input().split())
A = Counter(a - r for r, a in enumerate(map(int, input().split())) if a != -1)
B = Counter(b - c for c, b in enumerate(map(int, input().split())) if b != -1)

print(sum(min(A[key], B[key]) for key in set(A) & set(B)))