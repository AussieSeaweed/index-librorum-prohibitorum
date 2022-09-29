#include <iostream>
#include <vector>
using namespace std;

struct Beacon {
    int x, r, y, r_sqr;
};

vector<Beacon> beacons(501);
vector<vector<int>> graph(501);
vector<vector<bool>> visited(501, vector<bool>(501, false));
int N, Q;

void dfs(int node, int s) {
    visited[s][node] = true;

    for (int adj : graph[node])
        if (!visited[s][adj])
            dfs(adj, s);
}

bool can_reach(Beacon a, Beacon b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    int sqr_dist = dx * dx + dy * dy;
    return sqr_dist <= a.r_sqr;
}

int main() {
    scanf("%d%d", &N, &Q);

    for (int i = 1; i <= N; i++) {
        int x, y, r;
        scanf("%d%d%d", &x, &y, &r);
        beacons[i].x = x;
        beacons[i].y = y;
        beacons[i].r = r;
        beacons[i].r_sqr = r * r;
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i == j) continue;
            if (can_reach(beacons[i], beacons[j]))
                graph[i].push_back(j);
        }
    }

    for (int i = 1; i <= N; i++) dfs(i, i);

    while (Q--) {
        int v, w;
        scanf("%d%d", &v, &w);
        printf(visited[v][w] ? "YES\n" : "NO\n");
    }

    return 0;
}