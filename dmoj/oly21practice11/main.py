N = int(input())
C = list(map(int, input().split()))
X = []
count = 1

for i in range(1, N):
    if C[i] != C[i - 1]:
        count += 1
    else:
        X.append(count)
        count = 1
else:
    X.append(count)

if len(X) < 3:
    print(sum(X))
else:
    print(max(i + j + k for i, j, k in zip(X, X[1:], X[2:])))