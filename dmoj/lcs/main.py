import sys
raw_input = sys.stdin.readline

LN, LM = map(int, raw_input().split())

N = [None] + raw_input().split()
M = [None] + raw_input().split()

matrix = [[0] * (LN+1) for x in xrange(LM + 1)]


def format_matrix(mat, n, m, ln, lm):
    for x in xrange(1, ln + 1):
        for y in xrange(1, lm + 1):
            if n[x] == m[y]:
                mat[y][x] = mat[y-1][x-1] + 1
            else:
                mat[y][x] = max(mat[y-1][x], mat[y][x-1])


format_matrix(matrix, N, M, LN, LM)

print matrix[LM][LN]