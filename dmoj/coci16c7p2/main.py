from math import sqrt, floor

N = int(input())

for i in range(2, floor(sqrt(2 * N)) + 1):
    a = (2 * N // i - i + 1) // 2
    b = a + i - 1

    if 2 * N == (b - a + 1) * (a + b):
        print(a, b)