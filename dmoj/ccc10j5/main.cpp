#include <iostream>

int** board;

void hop(int** b, int r, int c, int step) {
    if (0 <= r && r < 8 && 0 <= c && c < 8 && step < b[r][c]) {
        b[r][c] = step;
        step++;
        hop(b, r + 1, c + 2, step);
        hop(b, r + 1, c - 2, step);
        hop(b, r + 2, c + 1, step);
        hop(b, r + 2, c - 1, step);
        hop(b, r - 1, c + 2, step);
        hop(b, r - 1, c - 2, step);
        hop(b, r - 2, c + 1, step);
        hop(b, r - 2, c - 1, step);
    }
}

int main() {
    board = new int*[8];
    for (int i = 0; i < 8; i++) {
        board[i] = new int[8];
        for (int _ = 0; _ < 8; _++) {
            board[i][_] = 100000;
        }
    }

    int r, c;

    scanf("%d%d", &r, &c);
    r--; c--;
    hop(board, r, c, 0);

    scanf("%d%d", &r, &c);
    r--; c--;
    printf("%d", board[r][c]);

    return 0;
}