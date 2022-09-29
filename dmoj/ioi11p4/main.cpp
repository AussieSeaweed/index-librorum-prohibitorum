#include <bits/stdc++.h>
#include <bits/extc++.h>
struct pair_hash { template <typename T1, typename T2> std::size_t operator()(const std::pair<T1, T2> &p) const { auto h1 = std::hash<T1>{}(p.first); auto h2 = std::hash<T2>{}(p.second); return h1 ^ h2; } };
template<typename T1, typename T2, typename T3> struct triple { T1 first; T2 second; T3 third; triple() : first{}, second{}, third{} {} triple(const T1 &first, const T2 &second, const T3 &third) : first{ first }, second{ second }, third{ third } {} triple(T1 &&first, T2 &&second, T3 &&third) : first{ first }, second{ second }, third{ third } {} };
template<typename T1, typename T2, typename T3, typename T4> struct quad { T1 first; T2 second; T3 third; T4 fourth; quad() : first{}, second{}, third{}, fourth{} {} quad(const T1 &first, const T2 &second, const T3 &third, const T4 &fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} quad(T1 &&first, T2 &&second, T3 &&third, T4 &&fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} };
template<typename T> using min_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template<typename T> using max_priority_queue = std::priority_queue<T>;
inline int ffs(int x) { return __builtin_ffs(x); }
inline int ctz(int x) { return __builtin_ctz(x); }
inline int clz(int x) { return __builtin_clz(x); }
inline int popcount(int x) { return __builtin_popcount(x); }
inline int ffs(long long x) { return __builtin_ffsll(x); }
inline int ctz(long long x) { return __builtin_ctzll(x); }
inline int clz(long long x) { return __builtin_clzll(x); }
inline int popcount(long long x) { return __builtin_popcountll(x); }
template<typename T> inline T gcd(const T &x, const T &y) { return std::__gcd(x, y); }
template<typename T, typename ...Ts> inline T gcd(const T &x, const Ts &...xs) { return std::__gcd(x, gcd(xs...)); }
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x : y; }
template<typename T, typename ...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename ...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
template<typename T> inline void scan(T &x) { char c; bool sign; while ((x = getchar()) < '-'); sign = x == '-'; if (sign) while ((x = getchar()) < '0'); for(x -= '0'; '0' <= (c = getchar()); x = (x << 3) + (x << 1) + c - '0'); x = sign ? -x : x; }
template<typename T, typename ...Ts> inline void scan(T &x, Ts &...xs) { scan(x), scan(xs...); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
using namespace std;

struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) : u{ u }, v{ v }, w{ w } {}
    int other(int node) { return node == u ? v : u; }
};

int N;
long long dist[100000], delay[100000];
bool is_exit[100000], visited[100000];
vector<Edge *> graph[100000];

void dijkstra() {
    fill(dist, dist + N, inf);
    fill(delay, delay + N, inf);

    min_priority_queue<pair<long long, int>> pq;

    for (int i = 0; i < N; i++)
        if (is_exit[i])
            dist[i] = 0, delay[i] = 0, pq.emplace(0, i);

    while (!pq.empty()) {
        long long cur_dist;
        int node;

        tie(cur_dist, node) = pq.top(), pq.pop();

        if (visited[node])
            continue;

        visited[node] = true;

        for (Edge *adj_edge : graph[node]) {
            int adj_node = adj_edge->other(node);

            if (dist[adj_node] > dist[node] + adj_edge->w + delay[node]) {
                delay[adj_node] = dist[adj_node] - (dist[node] + adj_edge->w + delay[node]);
                dist[adj_node] = dist[node] + adj_edge->w + delay[node];

                pq.emplace(dist[adj_node] + delay[adj_node], adj_node);
            } else if (dist[adj_node] + delay[adj_node] > dist[node] + adj_edge->w + delay[node]) {
                delay[adj_node] = (dist[node] + adj_edge->w + delay[node]) - dist[adj_node];

                pq.emplace(dist[adj_node] + delay[adj_node], adj_node);
            }
        }
    }
}

int travel_plan(int N, int M, int R[][2], int L[], int K, int P[]) {
    ::N = N;

    for (int i = 0; i < M; i++) {
        Edge *edge = new Edge(R[i][0], R[i][1], L[i]);
        graph[R[i][0]].push_back(edge);
        graph[R[i][1]].push_back(edge);
    }

    for (int i = 0; i < K; i++)
        is_exit[P[i]] = true;

    dijkstra();

    return dist[0] + delay[0];
}