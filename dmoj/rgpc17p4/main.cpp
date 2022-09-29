#include <iostream>
#include <vector>

using namespace std;

vector<bool> visited(1001, false);
vector<long long> maxDist(1001, -1);
vector<int> pred(1001, -1);
vector<int> topo;
vector<vector<int>> graph(1001);
vector<vector<int>> igraph(1001);
vector<vector<int>> dist(1001, vector<int>(1001));
int N, M;

void top_sort(int node) {
    visited[node] = true;

    for (int adj : graph[node]) {
        if (!visited[adj]) {
            top_sort(adj);
        }
    }

    topo.push_back(node);
}

void dfs(int node) {
    visited[node] = true;

    for (int adj : igraph[node])
        if (!visited[adj])
            dfs(adj);
}

bool isDAG() {
    top_sort(1);

    if (!visited[N]) return false;

    fill(visited.begin(), visited.end(), false);

    int id = 0;
    for (int i : vector<int>{topo.rbegin(), topo.rend()}) {
        if (!visited[i]) {
            id++;
            dfs(i);
        }
    }

    return id == N;
}

int main() {
    scanf("%d%d", &N, &M);

    while (M--) {
        int v, w, d;
        scanf("%d%d%d", &v, &w, &d);
        graph[v].push_back(w);
        igraph[w].push_back(v);
        dist[v][w] = max(dist[v][w], d);
    }

    if (!isDAG()) {
        printf("-1");
        return 0;
    }

    maxDist[1] = 0;
    pred[1] = 1;

    for (int node : vector<int>{topo.rbegin(), topo.rend()}) {
        for (int adj : graph[node]) {
            if (maxDist[adj] < maxDist[node] + dist[node][adj]) {
                maxDist[adj] = maxDist[node] + dist[node][adj];
                pred[adj] = pred[node] + 1;
            } else if (maxDist[adj] == maxDist[node] + dist[node][adj] && pred[adj] < pred[node] + 1) {
                pred[adj] = pred[node] + 1;
            }
        }
    }

    printf("%lld %d", maxDist[N], pred[N]);

    return 0;
}