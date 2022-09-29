#include <iostream>
#include <vector>
#include <queue>
#define INFINITY 99999999

using namespace std;

vector<pair<int, int>> offsets {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
};
vector<vector<bool>> isDest(1000, vector<bool>(1000, false));
vector<string> grid(1000);
int R, C;

int minDist(int sr, int sc) {
    vector<vector<int>> dist(R, vector<int>(C, INFINITY));
    queue<pair<int, int>> q;
    q.emplace(sr, sc);
    dist[sr][sc] = 0;

    while (!q.empty()) {
        pair<int, int> coord = q.front();
        q.pop();

        int r = coord.first;
        int c = coord.second;

        if (isDest[r][c]) return dist[r][c];

        for (pair<int, int> offset : offsets) {
            int nr = offset.first + r;
            int nc = offset.second + c;
            if (0 <= nr && nr < R && 0 <= nc && nc < C && grid[nr][nc] != 'X' && dist[nr][nc] == INFINITY) {
                dist[nr][nc] = dist[r][c] + 1;
                q.emplace(nr, nc);
            }
        }
    }
}

int getThere(int sr, int sc, int tr, int tc) {
    vector<vector<int>> dist(R, vector<int>(C, INFINITY));
    queue<pair<int, int>> q;
    q.emplace(sr, sc);
    dist[sr][sc] = 0;

    while (!q.empty()) {
        pair<int, int> coord = q.front();
        q.pop();

        int r = coord.first;
        int c = coord.second;

        if (r == tr && c == tc) return dist[r][c];

        for (pair<int, int> offset : offsets) {
            int nr = offset.first + r;
            int nc = offset.second + c;
            if (0 <= nr && nr < R && 0 <= nc && nc < C && grid[nr][nc] != 'X' && dist[nr][nc] == INFINITY) {
                dist[nr][nc] = dist[r][c] + 1;
                q.emplace(nr, nc);
            }
        }
    }
}

int main() {
    scanf("%d%d", &R, &C);

    int sr, sc, tr, tc;
    scanf("%d%d%d%d", &sr, &sc, &tr, &tc);

    for (int i = 0; i < R; i++)
        cin >> grid[i];

    int T;
    scanf("%d", &T);

    while (T--) {
        int r, c;
        scanf("%d%d", &r, &c);
        isDest[r][c] = true;
    }

    int md = minDist(sr, sc);
    int normal = getThere(sr, sc, tr, tc);

    printf("%d", normal - md);

    return 0;
}