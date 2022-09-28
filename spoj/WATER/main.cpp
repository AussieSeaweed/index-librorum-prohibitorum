#include <iostream>
#include <vector>
#include <queue>
#define INFINITY 999999999

std::vector<std::vector<int>> grid(100, std::vector<int>(100));

struct Coord {
    int r, c;
    Coord(int r, int c) :r{r}, c{c} {}
};

std::vector<Coord> offsets = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int N, M;
int ans = 0;

bool bfs(int r, int c) {
    std::vector<std::vector<bool>> visited(N, std::vector<bool>(M, false));
    std::queue<Coord> q;
    int minVal = INFINITY;

    q.emplace(r, c);
    visited[r][c] = true;

    while (!q.empty()) {
        Coord coord = q.front(); q.pop();
        r = coord.r;
        c = coord.c;

        if (r == 0 || r == N - 1 || c == 0 || c == M - 1) return false;

        for (auto offset : offsets) {
            int i = r + offset.r;
            int j = c + offset.c;
            if (grid[r][c] == grid[i][j]) {
                if (!visited[i][j]) {
                    visited[i][j] = true;
                    q.emplace(i, j);
                }
            } else if (grid[r][c] > grid[i][j]) {
                return false;
            } else if (grid[r][c] < grid[i][j]) {
                minVal = std::min(minVal, grid[i][j] - grid[r][c]);
            }
        }
    }

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if (visited[r][c]) {
                grid[r][c] += minVal;
                ans += minVal;
            }
        }
    }

    return true;
}

int main() {
    int _;
    scanf("%d", &_);

    while (_--) {
        scanf("%d%d", &N, &M);
        ans = 0;

        for (int p = 0; p < N; p++) {
            for (int q = 0; q < M; q++) {
                scanf("%d", &grid[p][q]);
            }
        }

        while (true) {
            bool modified = false;

            for (int r = 1; r < N - 1; r++)
                for (int c = 1; c < M - 1; c++)
                    modified |= bfs(r, c);

            if (!modified) break;
        }

        printf("%d\n", ans);
    }

    return 0;
}