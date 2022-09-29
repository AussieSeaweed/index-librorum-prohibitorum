N = int(input())
puzzle = [list(map(int, input().split())) for _ in range(N)]

flag = False
row_flips = []
col_flips = []

for r in range(N):
    if puzzle[r][0]:
        puzzle[r] = [not a for a in puzzle[r]]
        row_flips.append(r)

for c in range(1, N):
    if any(puzzle[i][c] != puzzle[0][c] for i in range(N)):
        flag = True
        break

    if puzzle[0][c]:
        col_flips.append(c)

if flag:
    print(-1)
else:
    print(len(row_flips) + len(col_flips))

    for r in row_flips:
        print(f'R {r + 1}')
    for c in col_flips:
        print(f'C {c + 1}')