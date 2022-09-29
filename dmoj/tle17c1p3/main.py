def solve():
    return 1 if mirrors[0] else N + 2 * count


N, T = map(int, input().split())
mirrors = [c == '|' for c in input()]
count = sum(mirrors)

for _ in range(T):
    m = int(input()) - 1
    mirrors[m] = not mirrors[m]
    count += 1 if mirrors[m] else -1

    print(solve())