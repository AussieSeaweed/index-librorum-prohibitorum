/*
 * A C++ implementation of depth first search.
 *
 * Time Complexity: O(N + M)
 *
 * Written by Juho Kim
 */

#include <bits/stdc++.h>
#define inf 2000000000
using namespace std;

const int MAX_NODE = 2000; // your choice
int dist[MAX_NODE + 1], pred[MAX_NODE + 1];
bool visited[MAX_NODE + 1];
vector<int> graph[MAX_NODE + 1];

void dfs(int node, int parent, int depth) {
    dist[node] = depth;
    visited[node] = true;
    pred[node] = parent;

    for (int adj : graph[node]) {
        if (!visited[adj]) {
            dfs(adj, node, depth + 1);
        }
    }
}

vector<int> get_path(int node) {
    vector<int> path;

    while (node != -1) {
        path.push_back(node);
        node = pred[node];
    }

    return vector<int> {path.rbegin(), path.rend()};
}

int main() {
    // start by calling dfs(source_node, -1, 0)
    int N, M, A, B;
    scanf("%d%d%d%d", &N, &M, &A, &B);
    while (M--) {
        int u, v;
        scanf("%d%d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(A, -1, 0);
    printf(visited[B] ? "GO SHAHIR!" : "NO SHAHIR!");
    return 0;
}