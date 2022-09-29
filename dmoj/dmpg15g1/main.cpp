#include <iostream>

int N;
int col[500][500], row[500][500];
std::string grid[500];

int solve() {
    for (int j = 0; j < N; j++) {
        col[0][j] = grid[0][j] == '.';
        for (int i = 1; i < N; i++) {
            col[i][j] = grid[i][j] == '.' ? 1 + col[i - 1][j] : 0;
        }
    }

    for (int i = 0; i < N; i++) {
        row[i][0] = grid[i][0] == '.';
        for (int j = 1; j < N; j++) {
            row[i][j] = grid[i][j] == '.' ? 1 + row[i][j - 1] : 0;
        }
    }

    int X = -1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int limit = std::min(i, j);
            for (int k = 0; k <= limit; k++) {
                if (row[i][j] > k && col[i][j] > k &&
                    row[i - k][j] > k && col[i][j - k] > k)
                    X = std::max(X, k);
            }
        }
    }

    return X;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        std::cin >> grid[i];
    printf("%d", solve());
    return 0;
}