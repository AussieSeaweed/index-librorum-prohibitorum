def count_words(cells):
    cells = [0] + cells + [0]
    count = 0

    for a, b, c in zip(cells, cells[1:], cells[2:]):
        if a != b and b and c:
            count += 1

    return count


for _ in range(5):
    H, W = map(int, input().split())
    grid = [[cell == '.' for cell in input()] for _ in range(H)]

    across_count = 0
    down_count = 0

    for h in range(H):
        across_count += count_words(grid[h])

    for w in range(W):
        down_count += count_words([grid[h][w] for h in range(H)])

    print(across_count, down_count)