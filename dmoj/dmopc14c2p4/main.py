raw_input = __import__("sys").stdin.readline

N = int(raw_input())
lst = [int(raw_input()) for i in range(N)]

for i in range(1, len(lst)):
    lst[i] += lst[i - 1]

Q = int(raw_input())

for q in range(Q):
    a, b = map(int, raw_input().split())
    print(lst[b] - (0 if a == 0 else lst[a - 1]))