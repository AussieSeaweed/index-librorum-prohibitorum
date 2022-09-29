#include <iostream>
#include <vector>
#include <unordered_set>

struct Edge {
    int v, w;

    int other(int node) {
        if (node == w) return v;
        else return w;
    }
};

std::vector<Edge *> edgeList;
std::vector<std::vector<Edge *>> graph(1001);
std::unordered_set<Edge *> bridges;
std::vector<int> parent(1001, -1);
std::vector<int> low(1001);
std::vector<bool> visited(1001, false);
std::vector<int> depth(1001);
std::vector<int> ids(1001);
int numID = 0;
int N, M;

void dfs(int node, int d) {
    visited[node] = true;
    depth[node] = low[node] = d;

    for (Edge *adjEdge : graph[node]) {
        int other = adjEdge->other(node);

        if (!visited[other]) {
            parent[other] = node;
            dfs(other, d + 1);

            low[node] = std::min(low[node], low[other]);

            if (low[other] > depth[node])
                bridges.insert(adjEdge);
        } else if (other != parent[node]) {
            low[node] = std::min(low[node], depth[other]);
        }
    }
}

void setID(int node, int id) {
    visited[node] = true;
    ids[node] = id;

    for (Edge *adjEdge : graph[node]) {
        if (!bridges.count(adjEdge)) {
            int other = adjEdge->other(node);
            if (!visited[other]) {
                setID(other, id);
            }
        }
    }
}

int main() {
    scanf("%d%d", &N, &M);

    while (M--) {
        int a, b;
        scanf("%d%d", &a, &b);
        Edge *e = new Edge {a, b};
        graph[a].push_back(e);
        graph[b].push_back(e);
    }

    dfs(1, 0);

    std::fill(visited.begin(), visited.end(), false);

    for (int i = 1; i <= N; i++)
        if (!visited[i])
            setID(i, numID++);

    std::vector<int> degree(numID, 0);

    for (int i = 1; i <= N; i++)
        for (Edge *adjEdge : graph[i])
            if (ids[i] != ids[adjEdge->other(i)])
                degree[ids[i]]++;

    int count = 0;

    for (int deg : degree)
        if (deg == 1) count++;

    printf("%d", count / 2 + count % 2);

    for (Edge *e : edgeList) delete e;
    return 0;
}