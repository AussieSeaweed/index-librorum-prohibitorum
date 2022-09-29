from statistics import mean

for _ in range(5):
    N = int(input())
    counts = [int(input()) for _ in range(N)]
    avg = mean(counts)

    print(sum(abs(count - avg) for count in counts) // 2)