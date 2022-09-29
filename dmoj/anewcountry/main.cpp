#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
struct pair_hash { template <typename T1, typename T2> std::size_t operator()(const std::pair<T1, T2> &p) const { auto h1 = std::hash<T1>{}(p.first); auto h2 = std::hash<T2>{}(p.second); return h1 ^ h2; } };
template<typename T1, typename T2, typename T3> struct triple { T1 first; T2 second; T3 third; triple() : first{}, second{}, third{} {} triple(const T1 &first, const T2 &second, const T3 &third) : first{ first }, second{ second }, third{ third } {} triple(T1 &&first, T2 &&second, T3 &&third) : first{ first }, second{ second }, third{ third } {} };
template<typename T1, typename T2, typename T3, typename T4> struct quad { T1 first; T2 second; T3 third; T4 fourth; quad() : first{}, second{}, third{}, fourth{} {} quad(const T1 &first, const T2 &second, const T3 &third, const T4 &fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} quad(T1 &&first, T2 &&second, T3 &&third, T4 &&fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} };
template<typename T> using min_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template<typename T> using max_priority_queue = std::priority_queue<T>;
inline int ffs(int x) { return __builtin_ffs(x) - 1; }
inline int ctz(int x) { return __builtin_ctz(x); }
inline int clz(int x) { return __builtin_clz(x); }
inline int popcount(int x) { return __builtin_popcount(x); }
inline int ffs(long long x) { return __builtin_ffsll(x) - 1; }
inline int ctz(long long x) { return __builtin_ctzll(x); }
inline int clz(long long x) { return __builtin_clzll(x); }
inline int popcount(long long x) { return __builtin_popcountll(x); }
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x: y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
using namespace std;

struct Edge {
    int u, v;
    long long w;
    Edge(int u, int v, long long w) : u{ u }, v{ v }, w{ w } {}
    int other(int node) { return node == u ? v : u; }
};

bool visited[10001];
int N, M, Q, id[10001], pid[10001], ccnt[1000], out[1000][1000], in[1000][1000], topo[10000], topo_i = 0, P;
long long pdist[1000][200][200], cdist[1000][1000];
vector<Edge *> graph[10001], igraph[10001], edge_list, pedge_list[1000], cgraph[1000];

void topological_sort(int node, vector<Edge *> graph[]) {
    visited[node] = true;

    for (Edge *adj_edge : graph[node]) {
        int other = adj_edge->v;
        if (!visited[other]) {
            topological_sort(other, graph);
        }
    }

    topo[topo_i++] = node;
}

void set_pid(int node, int i, vector<Edge *> graph[]) {
    pid[node] = i;
    id[node] = ccnt[i]++;

    for (Edge *adj_edge : graph[node]) {
        int other = adj_edge->v;
        if (pid[other] == -1) {
            set_pid(other, i, graph);
        }
    }
}

void kosaraju() {
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            topological_sort(i, igraph);
        }
    }

    fill(pid, pid + N + 1, -1);

    P = 0;

    for (int i = N - 1; i >= 0; i--) {
        if (pid[topo[i]] == -1) {
            set_pid(topo[i], P++, graph);
        }
    }

    for (Edge *e : edge_list) {
        if (pid[e->u] != pid[e->v]) {
            cgraph[pid[e->u]].push_back(new Edge(e->u, e->v, e->w));
            cgraph[pid[e->v]].push_back(new Edge(e->v, e->u, e->w));
        } else {
            pedge_list[pid[e->u]].push_back(new Edge(id[e->u], id[e->v], e->w));
        }
    }
}

void floyd_warshall() {
    for (int p = 0; p < P; p++) {
        for (int i = 0; i < ccnt[p]; i++) {
            fill(pdist[p][i], pdist[p][i] + ccnt[p], INF);
            pdist[p][i][i] = 0;
        }

        for (Edge *edge : pedge_list[p]) {
            pdist[p][edge->u][edge->v] = min(pdist[p][edge->u][edge->v], edge->w);
        }

        for (int k = 0; k < ccnt[p]; k++) {
            for (int i = 0; i < ccnt[p]; i++) {
                for (int j = 0; j < ccnt[p]; j++) {
                    if (pdist[p][i][j] > pdist[p][i][k] + pdist[p][k][j]) {
                        pdist[p][i][j] = pdist[p][i][k] + pdist[p][k][j];
                    }
                }
            }
        }
    }
}

void dfs(int curp, int source, int parent) {
    for (Edge *adj_edge : cgraph[curp]) {
        int otherp = pid[adj_edge->v];
        if (otherp != parent) {
            out[source][otherp] = curp == source ? adj_edge->u : out[source][curp];
            in[source][otherp] = adj_edge->v;
            cdist[source][otherp] = cdist[source][curp] + (curp != source ? pdist[curp][id[in[source][curp]]][id[adj_edge->u]] : 0) + adj_edge->w;
            dfs(otherp, source, curp);
        }
    }
}

void outer_dist() {
    for (int source = 0; source < P; source++) {
        dfs(source, source, -1);
    }
}

long long query(int a, int b) {
    if (pid[a] == pid[b]) {
        return pdist[pid[a]][id[a]][id[b]];
    } else {
        return pdist[pid[a]][id[a]][id[out[pid[a]][pid[b]]]] + cdist[pid[a]][pid[b]] + pdist[pid[b]][id[in[pid[a]][pid[b]]]][id[b]];
    }
}

int main() {
    pscan(N);
    pscan(M);
    pscan(Q);

    while (M--) {
        int a, b, d;
        pscan(a);
        pscan(b);
        pscan(d);
        Edge *e = new Edge(a, b, d);
        graph[a].push_back(e);
        igraph[b].push_back(new Edge(b, a, d));
        edge_list.push_back(e);
    }

    kosaraju();
    floyd_warshall();
    outer_dist();

    while (Q--) {
        int a, b;
        pscan(a);
        pscan(b);

        printf("%lld\n", query(a, b));
        fflush(stdout);
    }

    return 0;
}