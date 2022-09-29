from bisect import bisect_left, bisect_right

N, Q = map(int, input().split())
P = sorted(map(int, input().split()))

for _ in range(Q):
    L, R = map(int, input().split())

    print(bisect_right(P, R) - bisect_left(P, L))