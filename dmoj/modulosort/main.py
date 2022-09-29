N, K = int(input()), int(input())

print(' '.join(map(str, sorted(map(int, input().split()), key=lambda value: (value % K, value)))))