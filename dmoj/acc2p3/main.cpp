#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
template<typename T>constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T>constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, Q, p[18][100001], d[100001];
vector<pair<int, int>> graph[100001];
pair<int, int> w[18][100001];

void dfs(int node, int parent, int depth) {
    d[node] = depth;

    for (pair<int, int> &edge : graph[node]) {
        int &adj = edge.first, &weight = edge.second;
        if (adj != parent) {
            p[0][adj] = node;
            w[0][adj].first = weight;
            dfs(adj, node, depth + 1);
        }
    }
}

pair<int, int> merge(pair<int, int> a, pair<int, int> b) {
    if (a.first < b.first) {
        a.second = a.first;
        a.first = b.first;
    } else if (a.second < b.first) {
        a.second = b.first;
    }

    if (a.second < b.second) {
        a.second = b.second;
    }

    return a;
}

void construct_sparse_tables() {
    for (int i = 1; i <= 17; i++) {
        for (int j = 1; j <= N; j++) {
            if (p[i - 1][j] != -1) {
                p[i][j] = p[i - 1][p[i - 1][j]];
                w[i][j] = merge(w[i - 1][p[i - 1][j]], w[i - 1][j]);
            }
        }
    }
}

int lca(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    for (int i = 17; i >= 0; i--) {
        if (p[i][u] != -1 && d[p[i][u]] >= d[v]) {
            u = p[i][u];
        }
        if (u == v) return u;
    }
    for (int i = 17; i >= 0; i--) {
        if (p[i][u] != -1 && p[i][v] != -1 && p[i][u] != p[i][v]) {
            u = p[i][u];
            v = p[i][v];
        }
    }
    return p[0][u];
}

pair<int, int> query(int u, int v) {
    pair<int, int> ret {-1, -1};

    for (int i = 17; i >= 0; i--) {
        if (p[i][u] != -1 && d[p[i][u]] >= d[v]) {
            ret = merge(ret, w[i][u]);
            u = p[i][u];
        }
    }

    return ret;
}

int main() {
    memset(p, -1, sizeof p);
    memset(w, -1, sizeof w);

    scan(N);

    for (int i = 1; i < N; i++) {
        int u, v, w;
        scan(u);
        scan(v);
        scan(w);
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    dfs(1, -1, 0);
    construct_sparse_tables();

    scan(Q);

    while (Q--) {
        int s, t;
        scan(s);
        scan(t);
        int pivot = lca(s, t);
        printf("%d\n", merge(query(s, pivot), query(t, pivot)).second);
    }

    return 0;
}