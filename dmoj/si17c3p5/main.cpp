#include <bits/stdc++.h>
#define BASE 100000
using namespace std;

struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) : u{ u }, v{ v }, w{ w } {}
    int other(int node) { return node == u ? v : u; }
};

int N, val[200001], val_id[200001], id, centroid, min_max_subtree_sz, sz[100001];
long long ans;
bool marked[100001];
vector<Edge *> graph[100001];

void find_sz(int node, int parent) {
    sz[node] = 1;

    for (Edge *&edge : graph[node]) {
        int other = edge->other(node);
        if (marked[other] || other == parent) continue;
        find_sz(other, node);
        sz[node] += sz[other];
    }
}

void find_centroid(int node, int parent, int total) {
    int max_subtree_sz = total - sz[node];

    for (Edge *&edge : graph[node]) {
        int other = edge->other(node);
        if (marked[other] || other == parent) continue;
        find_centroid(other, node, total);
        max_subtree_sz = max(max_subtree_sz, sz[other]);
    }

    if (max_subtree_sz < min_max_subtree_sz) {
        min_max_subtree_sz = max_subtree_sz;
        centroid = node;
    }
}

void dfs_update(int node, int parent, int weight) {
    if (val_id[weight + BASE] != id) {
        val_id[weight + BASE] = id;
        val[weight + BASE] = 0;
    }

    val[weight + BASE]++;

    for (Edge *&edge : graph[node]) {
        int other = edge->other(node);
        if (marked[other] || parent == other) continue;
        dfs_update(other, node, weight + edge->w);
    }
}

void dfs_query(int node, int parent, int weight) {
    if (val_id[(1 - weight) + BASE] == id) {
        ans += val[(1 - weight) + BASE];
    }

    if (val_id[(-1 - weight) + BASE] == id) {
        ans += val[(-1 - weight) + BASE];
    }

    for (Edge *&edge : graph[node]) {
        int other = edge->other(node);
        if (marked[other] || parent == other) continue;
        dfs_query(other, node, weight + edge->w);
    }
}

void solve(int node) {
    find_sz(node, -1);
    min_max_subtree_sz = 0x3f3f3f3f;
    find_centroid(node, -1, sz[node]);

    val_id[BASE] = ++id, val[BASE] = 1;
    for (Edge *&edge : graph[centroid]) {
        int other = edge->other(centroid);
        if (marked[other]) continue;
        dfs_query(other, centroid, edge->w);
        dfs_update(other, centroid, edge->w);
    }

    int local_centroid = centroid;
    marked[local_centroid] = true;

    for (Edge *&edge : graph[local_centroid]) {
        int other = edge->other(local_centroid);
        if (marked[other]) continue;
        solve(other);
    }
}

int main() {
    scanf("%d", &N);

    for (int i = 1; i < N; i++) {
        char c;
        int u, v;
        scanf("%d%d %c", &u, &v, &c);
        Edge *edge = new Edge(u, v, c == 'r' ? 1 : -1);
        graph[u].push_back(edge);
        graph[v].push_back(edge);
    }

    solve(1);

    printf("%lld\n", ans - N + 1);

    return 0;
}