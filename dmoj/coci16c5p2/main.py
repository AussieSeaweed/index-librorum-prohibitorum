n = int(input())
values = sorted(map(int, input().split()), reverse=True)
sum_ = sum(values)
subsum = 0
A, B = 0, 0

for i, value in enumerate(values):
    subsum += value
    X, Y = (i + 1) / n, subsum / sum_

    if Y - X > B - A:
        A, B = X, Y

print(A * 100)
print(B * 100)