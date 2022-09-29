n = int(input())
d = tuple(map(int, input().split()))

print(sum(d) + (n - 2) * min(d))