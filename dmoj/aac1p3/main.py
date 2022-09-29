N, X = map(int, input().split())

if (N - X) & 1:
    happiness = [-1]
else:
    happiness = [0] * X + [0, 1] * ((N - X) // 2)

print(' '.join(map(str, happiness)))