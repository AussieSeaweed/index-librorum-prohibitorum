#include <bits/stdc++.h>

int solve(std::vector<std::vector<int>> grid, int R, int C) {
    std::vector<std::vector<int>> money(R, std::vector<int>(C, -1));

    money[R-1][0] = grid[R-1][0];
    for (int i = R-2; i >= 0; i--) {
        if (grid[i][0] == -1) break;
        money[i][0] = money[i+1][0] + grid[i][0];
    }

    for (int j = 1; j < C; j++) {
        for (int i = 0; i < R; i++) {
            if (money[i][j - 1] != -1) {
                int last = money[i][j - 1];

                for (int k = i; k >= 0; k--) {
                    if (grid[k][j] == -1) break;
                    last += grid[k][j];
                    money[k][j] = std::max(money[k][j], last);
                }

                last = money[i][j - 1];

                for (int k = i; k < R; k++) {
                    if (grid[k][j] == -1) break;
                    last += grid[k][j];
                    money[k][j] = std::max(money[k][j], last);
                }
            }
        }
    }

    return money[R-1][C-1];
}

int main() {
    while (true) {
        int R, C;
        scanf("%d%d", &R, &C);
        if (!R && !C) break;

        std::vector<std::vector<int>> grid(R, std::vector<int>(C));
        std::string str;
        for (int i = 0; i < R; i++) {
            std::cin >> str;
            for (int j = 0; j < C; j++) {
                char c = str[j];
                if (c == '.') {
                    grid[i][j] = 0;
                } else if (c == '*') {
                    grid[i][j] = -1;
                } else {
                    grid[i][j] = c - '0';
                }
            }
        }

        printf("%d\n", solve(grid, R, C));
    }

    return 0;
}