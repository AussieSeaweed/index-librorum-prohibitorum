#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

struct Edge {
    int u, v, w;
    Edge() : u{}, v{}, w{} {}
};

const int MAX_N = 100000;
int uf[MAX_N + 1], sz[MAX_N + 1], N, queries[MAX_N + 1], path_val[MAX_N + 1];
unordered_map<int, int> elems[MAX_N + 1];
vector<int> subtree_nodes[MAX_N + 1];
long long answers[MAX_N + 1], ans;
Edge edges[MAX_N + 1];

int id(int node) {
    return node == uf[node] ? node : uf[node] = id(uf[node]);
}

void connect(int u, int v, long long w) {
    int ru = id(u), rv = id(v);
    if (sz[rv] > sz[ru]) {
        swap(ru, rv);
        swap(u, v);
    }

    for (int node : subtree_nodes[rv]) {
        ans += elems[ru][path_val[u] ^ w ^ path_val[v] ^ path_val[node]];
    }

    int v_path_val = path_val[v];

    for (int node : subtree_nodes[rv]) {
        path_val[node] ^= path_val[u] ^ w ^ v_path_val;
        elems[ru][path_val[node]]++;
    }

    subtree_nodes[ru].insert(subtree_nodes[ru].end(), subtree_nodes[rv].begin(), subtree_nodes[rv].end());

    uf[rv] = ru;
    sz[ru] += sz[rv];
    elems[rv].clear();
    subtree_nodes[rv].clear();
}

void init_uf(int N) {
    for (int i = 0; i <= N; i++)
        uf[i] = i;
    fill(sz, sz + N + 1, 1);
}

int main() {
    scan(N);
    init_uf(N);

    for (int i = 1; i <= N; i++) {
        elems[i][0] = 1;
        subtree_nodes[i].push_back(i);
    }

    for (int i = 1; i < N; i++) {
        scan(edges[i].u);
        scan(edges[i].v);
        scan(edges[i].w);
    }

    for (int i = 0; i < N - 1; i++) {
        scan(queries[i]);
    }

    answers[N - 1] = ans = 0;

    for (int i = N - 2; i >= 0; i--) {
        connect(edges[queries[i]].u, edges[queries[i]].v, edges[queries[i]].w);
        answers[i] = ans;
    }

    for (int i = 0; i < N; i++)
        printf("%lld\n", answers[i]);

    return 0;
}