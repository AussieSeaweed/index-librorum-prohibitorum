#include <iostream>
#include <queue>
#define INFINITY 99999999
using namespace std;

int dist[8][8];
pair<int, int> adj[8] {
        {-2, -1},
        {-2, 1},
        {-1, -2},
        {-1, 2},
        {1, -2},
        {1, 2},
        {2, -1},
        {2, 1}
};

bool valid(int r, int c) {
    return 0 <= r && r < 8 && 0 <= c && c < 8;
}

int main() {
    int N;
    scanf("%d", &N);

    while (N--) {
        for (int r = 0; r < 8; r++)
            for (int c = 0; c < 8; c++)
                dist[r][c] = INFINITY;

        string s1, s2;
        cin >> s1 >> s2;

        pair<int, int> start(s1[0] - 'a', s1[1] - '1');
        pair<int, int> end(s2[0] - 'a', s2[1] - '1');

        queue<pair<int, int>> q;
        q.push(start);
        dist[start.first][start.second] = 0;

        while (!q.empty()) {
            pair<int, int> p = q.front();
            q.pop();

            int r = p.first;
            int c = p.second;

            if (end.first == r && end.second == c) break;

            for (pair<int, int> ap : adj) {
                int nr = ap.first + r;
                int nc = ap.second + c;
                if (valid(nr, nc) && dist[nr][nc] == INFINITY) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.emplace(nr, nc);
                }
            }
        }

        printf("%d\n", dist[end.first][end.second]);
    }

    return 0;
}