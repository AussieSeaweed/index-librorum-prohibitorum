#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) : u{ u }, v{ v }, w{ w } {}
    int other(int node) { return node == u ? v : u; }
};

int N, K, ans, sz[200000], centroid, min_max_subtree_sz, id, val_id[1000001], val[1000001];
bool marked[200000];
vector<Edge *> graph[200000];

void find_sz(int node, int parent) {
    sz[node] = 1;

    for (Edge *&edge : graph[node]) {
        int other = edge->other(node);
        if (other == parent || marked[other]) continue;
        find_sz(other, node);
        sz[node] += sz[other];
    }
}

void find_centroid(int node, int parent, int total_sz) {
    int max_subtree_sz = total_sz - sz[node];

    for (Edge *&edge : graph[node]) {
        int other = edge->other(node);
        if (other == parent || marked[other]) continue;
        max_subtree_sz = max(max_subtree_sz, sz[other]);
        find_centroid(other, node, total_sz);
    }

    if (max_subtree_sz < min_max_subtree_sz) {
        min_max_subtree_sz = max_subtree_sz;
        centroid = node;
    }
}

void dfs_solve(int node, int parent, int weight, int len, bool sol) {
    if (weight > K) return;

    if (sol) {
        if (val_id[K - weight] == id)
            ans = min(ans, val[K - weight] + len);
    } else {
        if (val_id[weight] != id || len < val[weight])
            val[weight] = len, val_id[weight ] = id;
    }

    for (Edge *&edge : graph[node]) {
        int other = edge->other(node);
        if (other == parent || marked[other]) continue;
        dfs_solve(other, node, weight + edge->w, len + 1, sol);
    }
}

void solve(int node) {
    find_sz(node, -1);
    min_max_subtree_sz = inf;
    find_centroid(node, -1, sz[node]);

    val_id[0] = ++id;

    for (Edge *&edge : graph[centroid]) {
        int other = edge->other(centroid);
        if (marked[other]) continue;
        dfs_solve(other, centroid, edge->w, 1, true);
        dfs_solve(other, centroid, edge->w, 1, false);
    }

    int local_centroid = centroid;
    marked[local_centroid] = true;

    for (Edge *&edge : graph[local_centroid]) {
        int other = edge->other(local_centroid);
        if (!marked[other]) {
            solve(other);
        }
    }
}

int solve() {
    ans = inf;
    solve(0);
    return ans == inf ? -1 : ans;
}

int best_path(int N, int K, int H[][2], int L[]) {
    ::N = N, ::K = K;

    for (int i = 0; i < N - 1; i++) {
        Edge *edge = new Edge(H[i][0], H[i][1], L[i]);
        graph[H[i][0]].push_back(edge);
        graph[H[i][1]].push_back(edge);
    }

    return solve();
}

int main() {
//    int N = 4,
//            K = 3,
//            H[][2] = {{0, 1}, {1, 2}, {1, 3}},
//            L[] = {1, 2, 4};
//    cout << best_path(N, K, H, L) << endl;
//    int N = 3,
//            K = 3,
//            H[][2] = {{0, 1}, {1, 2}},
//            L[] = {1, 1};
//    cout << best_path(N, K, H, L) << endl;
//    int N = 11,
//        K = 12,
//        H[][2] = {{0, 1}, {0, 2}, {2, 3}, {3, 4}, {4, 5}, {0, 6}, {6, 7}, {6, 8}, {8, 9}, {8, 10}},
//        L[] = {3, 4, 5, 4, 6, 3, 2, 5, 6, 7};
//    cout << best_path(N, K, H, L) << endl;
    return 0;
}