H, M = map(int, input().split())

m = (H * 60 + M - 45) % (24 * 60)

print(m // 60, m % 60)