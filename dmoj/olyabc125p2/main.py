N = int(input())
V = list(map(int, input().split()))
C = list(map(int, input().split()))

print(sum(max(0, v - c) for v, c in zip(V, C)))