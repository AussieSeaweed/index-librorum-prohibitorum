#include <bits/stdc++.h>

std::vector<std::vector<int>> cubes(20, std::vector<int>(20));

int M, N;
int ans = 0;

bool fillable(int r, int c) {
    int initial = cubes[r][c];

    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<bool>> visited(20, std::vector<bool>(20, false));

    q.emplace(r, c);
    visited[r][c] = true;

    while (!q.empty()) {
        auto p = q.front();
        q.pop();

        int i = p.first;
        int j = p.second;

        if (cubes[i][j] > initial) continue;
        if (cubes[i][j] < initial) return false;
        if (i == 0 || i == M - 1 || j == 0 || j == N - 1) return false;

        if (!visited[i + 1][j]) {
            q.emplace(i + 1, j);
            visited[i + 1][j] = true;
        }
        if (!visited[i - 1][j]) {
            q.emplace(i - 1, j);
            visited[i - 1][j] = true;
        }
        if (!visited[i][j + 1]) {
            q.emplace(i, j + 1);
            visited[i][j + 1] = true;
        }
        if (!visited[i][j - 1]) {
            q.emplace(i, j - 1);
            visited[i][j - 1] = true;
        }
    }

    return true;
}

void fill(int r, int c) {
    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<bool>> visited(20, std::vector<bool>(20, false));

    int initial = cubes[r][c];

    q.emplace(r, c);
    visited[r][c] = true;

    while (!q.empty()) {
        auto p = q.front();
        q.pop();

        int i = p.first;
        int j = p.second;

        if (cubes[i][j] != initial) continue;

        cubes[i][j]++;
        ans++;

        if (!visited[i + 1][j]) {
            q.emplace(i + 1, j);
            visited[i + 1][j] = true;
        }
        if (!visited[i - 1][j]) {
            q.emplace(i - 1, j);
            visited[i - 1][j] = true;
        }
        if (!visited[i][j + 1]) {
            q.emplace(i, j + 1);
            visited[i][j + 1] = true;
        }
        if (!visited[i][j - 1]) {
            q.emplace(i, j - 1);
            visited[i][j - 1] = true;
        }
    }
}

int main() {
    for (int i = 0; i < 5; i++) {
        scanf("%d%d", &M, &N);
        ans = 0;

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                int n;
                scanf("%d", &n);
                cubes[i][j] = n;
            }
        }

        bool modified = true;

        while (modified) {
            modified = false;

            for (int i = 1; i < M - 1; i++) {
                for (int j = 1; j < N - 1; j++) {
                    if (fillable(i, j)) {
                        fill(i, j);
                        modified = true;
                    }
                }
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}