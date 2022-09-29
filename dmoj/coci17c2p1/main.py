K = int(input())

for _ in range(K):
    print((min(map(int, input().split())) - 1) * 2)