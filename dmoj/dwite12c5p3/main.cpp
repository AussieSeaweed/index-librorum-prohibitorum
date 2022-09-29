#include <iostream>
#include <cstring>

std::string grid[256];
bool left[256][256][257], right[256][256][256]; int N;

int solve() {
    memset(left, false, sizeof left);
    memset(right, false, sizeof right);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            left[i][j][0] = true;
            right[i][j][0] = true;
        }

    for (int i = 0; i < N; i++)
        left[i][0][1] = grid[i][0] == '#';

    for (int j = 1; j < N; j++) {
        left[N - 1][j][1] = grid[N - 1][j] == '#';
        for (int i = N - 2, consec = grid[N - 1][j] == '#'; i >= 0; i--) {
            consec = grid[i][j] == '#' ? consec + 1 : 0;
            for (int k = 1; k <= consec; k++) {
                left[i][j][k] = left[i + 1][j - 1][k - 1];
            }
        }
    }

    for (int i = 0; i < N; i++)
        right[i][N - 1][1] = grid[i][N - 1] == '#';

    for (int j = N - 2; j >= 0; j--) {
        right[N - 1][j][1] = grid[N - 1][j] == '#';
        for (int i = N - 2, consec = grid[N - 1][j] == '#'; i >= 0; i--) {
            consec = grid[i][j] == '#' ? consec + 1 : 0;
            for (int k = 1; k <= consec; k++) {
                right[i][j][k] = right[i + 1][j + 1][k - 1];
            }
        }
    }

    int cnt = 0;

    for (int i = 0; i < N; i++)
        cnt += right[i][N - 1][1];

    for (int j = 0; j < N - 1; j++)
        cnt += left[N - 1][j][1];

    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1; j++) {
            for (int k = 1; k <= N; k++) {
                cnt += left[i][j][k] && right[i + 1][j + 1][k - 1];
            }
        }
    }

    return cnt;
}

int main() {
    for (int _ = 0; _ < 5; _++) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++)
            std::cin >> grid[i];
        printf("%d\n", solve());
    }
    return 0;
}