#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
template<typename T> inline constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T> inline constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> inline constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> inline constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
#define MOD 1000000007
using namespace std;

struct Edge {
    int u, v, o, cnt;
    Edge(int u, int v, int o) : u{ u }, v{ v }, o{ o }, cnt{ 0 } {}
    int other(int node) { return node == u ? v : u; }
};

vector<Edge *> graph[100001];
Edge *edges[99999];
int N, K, b[100001], e[100001], p2[1000001], inward[200001], outward[200001], dfsnum = 1;
vector<int> from[100001], to[100001];

inline void update(int i, int bit[]) {
    while (i < dfsnum) {
        bit[i]++;
        i += i & -i;
    }
}

inline int query(int i, int bit[]) {
    int ret = 0;
    while (i) {
        ret += bit[i];
        i -= i & -i;
    }
    return ret;
}

inline int query(int i, int j, int bit[]) {
    return query(j, bit) - query(i - 1, bit);
}

void setup(int node, int parent) {
    b[node] = dfsnum++;

    for (Edge *adj_edge : graph[node]) {
        int other = adj_edge->other(node);
        if (other == parent) continue;
        setup(other, node);
    }

    e[node] = dfsnum++;
}

void dfs(int node, int parent) {

    for (Edge *adj_edge : graph[node]) {
        int other = adj_edge->other(node);
        if (other == parent) continue;

        if (adj_edge->o) {
            if (adj_edge->v == other) { // downward edge
                int prev_query = query(b[other] - 1, outward) + query(e[other] + 1, dfsnum - 1, outward);
                dfs(other, node);
                adj_edge->cnt = query(b[other] - 1, outward) + query(e[other] + 1, dfsnum - 1, outward) - prev_query;
            } else { // upward edge
                int prev_query = query(b[other] - 1, inward) + query(e[other] + 1, dfsnum - 1, inward);
                dfs(other, node);
                adj_edge->cnt = query(b[other] - 1, inward) + query(e[other] + 1, dfsnum - 1, inward) - prev_query;
            }
        } else {
            dfs(other, node);
        }
    }

    for (int f : from[node]) {
        update(b[f], outward);
    }

    for (int t : to[node]) {
        update(b[t], inward);
    }
}

int main() {
    srand(time(nullptr));
    scan(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v, o;
        scan(u);
        scan(v);
        scan(o);
        edges[i] = new Edge(u, v, o);
        graph[u].push_back(edges[i]);
        graph[v].push_back(edges[i]);
    }

    scan(K);

    p2[0] = 1;

    for (int i = 1, p = 1; i <= K; i++) {
        p2[i] = p2[i - 1] * 2 % MOD;
        int s;
        scan(s);
        from[p].push_back(s);
        to[s].push_back(p);
        p = s;
    }

    setup(1, -1);
    dfs(1, -1);

    long long ans = 0;

    for (int i = 0; i < N - 1; i++) {
        ans = (ans + p2[edges[i]->cnt] - 1) % MOD;
    }

    printf("%lld\n", ans);

    return 0;
}