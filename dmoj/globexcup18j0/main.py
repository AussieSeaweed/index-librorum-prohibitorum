N, M = map(int, raw_input().split())
a = map(int, raw_input().split())
a.sort()
print(sum(a[M:]))