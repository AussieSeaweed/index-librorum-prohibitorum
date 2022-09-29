N, M, K, X = map(int, input().split())
word = input()
pools = tuple(map(sorted, (input() for _ in range(M))))
letters = list(reversed(word))

X -= 1

for i in range(M):
    letters[letters.index('#')] = pools[-1 - i][X % K]
    X //= K

print(''.join(reversed(letters)))