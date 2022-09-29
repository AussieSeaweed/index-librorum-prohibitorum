N = int(input())
W = sorted(map(int, input().split()), reverse=True)

try:
    print(next(i for i in range(N) if i > W[i]))
except StopIteration:
    print(N)