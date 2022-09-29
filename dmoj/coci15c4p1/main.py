from itertools import zip_longest

N, M = input(), input()
A, B = [], []

for n, m in zip_longest(reversed(N), reversed(M)):
    if not n:
        B.append(m)
    elif not m:
        A.append(n)
    elif ord(n) < ord(m):
        B.append(m)
    elif ord(n) > ord(m):
        A.append(n)
    else:
        B.append(m)
        A.append(n)

A = int(''.join(reversed(A))) if A else 'YODA'
B = int(''.join(reversed(B))) if B else 'YODA'

print(A)
print(B)