from collections import Counter

n, k = map(int, input().split())
A = input()
counter = Counter(A)
c = min(map(chr, range(ord('a'), ord('z') + 1)), key=counter.__getitem__)

if counter[c] <= k <= n:
    print(c * (n - k) + A[:k])
else:
    print('WRONGANSWER')