#include <iostream>
#include <vector>
using namespace std;

int N;
vector<vector<int>> graph(10001);
vector<int> depth(10001, -1);

void dfs(int node, int d) {
    depth[node] = d;

    for (int adj : graph[node])
        if (depth[adj] == -1)
            dfs(adj, d + 1);
}

int main() {
    scanf("%d", &N);

    for (int i = 0; i < N - 1; i++) {
        int v, w;
        scanf("%d%d", &v, &w);
        graph[v].push_back(w);
        graph[w].push_back(v);
    }

    dfs(1, 0);

    int node, mdist = -9999999;

    for (int i = 1; i <= N; i++)
        if (mdist < depth[i]) {
            node =  i;
            mdist = depth[i];
        }

    fill(depth.begin(), depth.end(), -1);

    dfs(node, 0);

    mdist = -9999999;

    for (int i = 1; i <= N; i++)
        mdist = max(mdist, depth[i]);

    printf("%d", mdist);

    return 0;
}