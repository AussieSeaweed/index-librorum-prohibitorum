#include <iostream>
#include <vector>
#include <queue>
#define INFINITY 999999999
using namespace std;

vector<string> grid(1000);
vector<vector<int>> dist(1000, vector<int>(1000, INFINITY));
vector<pair<int, int>> offsets {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}
};
int n, m;

bool is_valid(int r, int c) {
    return 0 <= r && r < n && 0 <= c && c < m && grid[r][c] != 'X' && dist[r][c] == INFINITY;
}

void bfs(int sr, int sc) {
    queue<pair<int, int>> q;
    dist[sr][sc] = 0;
    q.emplace(sr, sc);
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        int r = p.first;
        int c = p.second;
        for (auto offset : offsets) {
            int nr = offset.first + r;
            int nc = offset.second + c;
            if (is_valid(nr, nc)) {
                dist[nr][nc] = dist[r][c] + 1;
                q.emplace(nr, nc);
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        cin >> grid[i];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 's') bfs(i, j);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 'e')
                printf("%d", dist[i][j] == INFINITY ? -1 : dist[i][j] - 1);
    return 0;
}