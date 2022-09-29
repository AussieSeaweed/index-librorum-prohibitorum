N = int(input())
A = sorted(map(int, input().split()))

permutation = []
actions = []

for i in range(N // 2):
    permutation.append(A[i])
    permutation.append(A[N - 1 - i])
    actions.append('B')
    actions.append('S')
else:
    if N % 2 == 1:
        permutation.append(A[N // 2])
        actions.append('E')

print(' '.join(map(str, permutation)))
print(''.join(actions))