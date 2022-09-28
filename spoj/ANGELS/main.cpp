#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define inf 999999999

using namespace std;

int pairR[90001], pairC[90001], R, C, row[300][300], col[300][300], level[90001];
vector<int> adj[90001];
char grid[300][300];

int bfs() {
    queue<int> q;

    for (int r = 1; r <= R; r++) {
        if (!pairR[r]) {
            level[r] = 0;
            q.push(r);
        } else {
            level[r] = inf;
        }
    }

    level[0] = inf;

    while (!q.empty()) {
        int r = q.front();
        q.pop();

        if (level[r] < level[0] - 1) {
            for (int c : adj[r]) {
                if (level[pairC[c]] == inf) {
                    level[pairC[c]] = level[r] + 1;
                    q.push(pairC[c]);
                }
            }
        }
    }

    return level[0] != inf;
}

bool dfs(int r) {
    if (r == 0) return true;

    for (int c : adj[r]) {
        if (level[pairC[c]] == level[r] + 1 && dfs(pairC[c])) {
            pairC[c] = r;
            pairR[r] = c;
            return true;
        }
    }

    level[r] = inf;
    return false;
}

int hopcroft_karp() {
    int matches = 0;

    while (bfs())
        for (int r = 1; r <= R; r++)
            if (!pairR[r])
                matches += dfs(r);

    return matches;
}

int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        fill(begin(pairR), end(pairR), 0);
        fill(begin(pairC), end(pairC), 0);
        for_each(begin(adj), end(adj), [] (vector<int>& vec) -> void {
            vec.clear();
        });
        R = 0, C = 0;

        int R_, C_;
        scanf("%d%d", &R_, &C_);

        for (int r = 0; r < R_; r++) {
            for (int c = 0; c < C_; c++) {
                scanf(" %c", &grid[r][c]);

                if (c == 0 || grid[r][c - 1] == 'A') {
                    row[r][c] = ++R;
                } else {
                    row[r][c] = row[r][c - 1];
                }

                if (r == 0 || grid[r - 1][c] == 'A') {
                    col[r][c] = ++C;
                } else {
                    col[r][c] = col[r - 1][c];
                }

                if (grid[r][c] == 'H') {
                    adj[row[r][c]].push_back(col[r][c]);
                }
            }
        }

        printf("%d\n", hopcroft_karp());
    }
    return 0;
}