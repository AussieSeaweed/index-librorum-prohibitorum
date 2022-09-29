#include <iostream>

int T, N;
bool grid[55][55];

int rowCount(int r) {
    int count = 0;

    for (int c = 0; c < N; ++c)
        count += grid[r][c];

    return count;
}

int colCount(int c) {
    int count = 0;

    for (int r = 0; r < N; ++r)
        count += grid[r][c];

    return count;
}

void select(int r1, int r2, int c1, int c2) {
    if (r1 > r2) std::swap(r1, r2);
    if (c1 > c2) std::swap(c1, c2);

    N -= 2;

    for (int r = 0; r < N; ++r) {
        int dr = 0;

        if (r + dr >= r1) ++dr;
        if (r + dr >= r2) ++dr;

        for (int c = 0; c < N; ++c) {
            int dc = 0;

            if (c + dc >= c1) ++dc;
            if (c + dc >= c2) ++dc;

            grid[r][c] = grid[r + dr][c + dc];
        }
    }
}

bool solve() {
    if (N == 1) return grid[0][0];

    int rowCounts[N];
    int colCounts[N];

    for (int i = 0; i < N; ++i)
        rowCounts[i] = rowCount(i), colCounts[i] = colCount(i);

    for (int r1 = 0; r1 < N; ++r1) {
        if (rowCounts[r1] == 2) {
            for (int r2 = 0; r2 < r1; ++r2) {
                if (rowCounts[r2] == 2) {
                    for (int c1 = 0; c1 < N; ++c1) {
                        if (colCounts[c1] == 2) {
                            for (int c2 = 0; c2 < c1; ++c2) {
                                if (colCounts[c2] == 2) {
                                    if (grid[r1][c1] && grid[r1][c2] && grid[r2][c1] && grid[r2][c2]) {
                                        select(r1, r2, c1, c2);
                                        return solve();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

int main() {
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        std::cin >> N;

        for (int i = 0; i < N; ++i) {
            std::string line;
            std::cin >> line;

            for (int j = 0; j < N; ++j)
                grid[i][j] = line[j] == 'X';
        }

        std::cout << "Case #" << t << ": " << (solve() ? "POSSIBLE" : "IMPOSSIBLE") << std::endl;
    }

    return 0;
}