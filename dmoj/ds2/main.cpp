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

int cnt = 0;

struct Edge {
    int u, v;
    long long w;
    Edge(int u, int v, long long w) : u{ u }, v{ v }, w{ w } {}
    int other(int node) { return node == u ? v : u; }
};

template<typename Compare>
long long prim(int num_nodes, Compare compare, vector<Edge *> graph[], Edge *output[]) {
    long long ptr = 0, ret = 0;
    Edge *edge_to[num_nodes];
    bool visited[num_nodes];
    multiset<Edge *, Compare> pq;
    fill(edge_to, edge_to + num_nodes, nullptr);
    fill(visited, visited + num_nodes, false);

    visited[0] = true;
    for (Edge *adj_edge : graph[0]) {
        edge_to[adj_edge->other(0)] = adj_edge;
        pq.insert(adj_edge);
    }

    while (!pq.empty()) {
        assert(pq.size());
        Edge *edge = *pq.begin();
        pq.erase(pq.begin());
        int node = visited[edge->u] ? edge->v : edge->u;
        visited[node] = true;
        output[ptr++] = edge;
        ret += edge->w;
        cnt++;

        for (Edge *adj_edge : graph[node]) {
            int other = adj_edge->other(node);
            if (!visited[other] && (edge_to[other] == nullptr || compare(adj_edge, edge_to[other]))) {
                if (edge_to[other]) pq.erase(edge_to[other]);
                edge_to[other] = adj_edge;
                pq.insert(edge_to[other]);
            }
        }
    }

    return ret;
}

struct Compare {
    bool operator()(const Edge *a, const Edge *b) const {
        return a->w < b->w;
    }
};

Edge *output[100000];
vector<Edge *> graph[100000];
int N, M;

int main() {
    scan(N);
    scan(M);

    for (int i = 1; i <= M; i++) {
        int u, v;
        scan(u);
        scan(v);
        u--;
        v--;
        Edge *edge = new Edge(u, v, i);
        graph[u].push_back(edge);
        graph[v].push_back(edge);
    }

    long long solve = prim(N, Compare(), graph, output), cur = 0;

    if (cnt == N - 1) {
        for (int i = 0; i < N - 1; i++) {
            printf("%lld\n", output[i]->w);
            cur += output[i]->w;
        }

        assert(solve == cur);
    } else {
        printf("Disconnected Graph\n");
    }

    return 0;
}