#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define INFINITY 99999999
using namespace std;

int N, M, P;
vector<int> pairN(50001, 0);
vector<int> pairM(50001, 0);
vector<int> level(50001, INFINITY);
vector<vector<int>> adj(50001);

bool bfs() {
    fill(level.begin(), level.end(), INFINITY);
    queue<int> q;

    for (int i = 1; i <= N; i++)
        if (!pairN[i]) {
            level[i] = 0;
            q.push(i);
        }

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        if (level[node] < level[0]) {
            for (int m : adj[node]) {
                if (level[pairM[m]] == INFINITY) {
                    level[pairM[m]] = level[node] + 1;
                    q.push(pairM[m]);
                }
            }
        }
    }

    return level[0] != INFINITY;
}

bool dfs(int node) {
    if (node == 0) return true;

    for (int m : adj[node]) {
        if (level[node] + 1 == level[pairM[m]] && dfs(pairM[m])) {
            pairN[node] = m;
            pairM[m] = node;
            return true;
        }
    }

    level[node] = INFINITY;
    return false;
}

int main() {
    scanf("%d%d%d", &N, &M, &P);

    while (P--) {
        int n, m;
        scanf("%d%d", &n, &m);
        adj[n].push_back(m);
    }

    int ans = 0;

    while (bfs())
        for (int i = 1; i <= N; i++)
            if (level[i] == 0)
                ans += dfs(i);

    printf("%d", ans);

    return 0;
}