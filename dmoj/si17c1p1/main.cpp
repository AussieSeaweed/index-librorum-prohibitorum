#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
struct pair_hash { template <typename T1, typename T2> std::size_t operator()(const std::pair<T1, T2> &p) const { auto h1 = std::hash<T1>{}(p.first); auto h2 = std::hash<T2>{}(p.second); return h1 ^ h2; } };
template<typename T1, typename T2, typename T3> struct triple { T1 first; T2 second; T3 third; triple() : first{}, second{}, third{} {} triple(const T1 &first, const T2 &second, const T3 &third) : first{ first }, second{ second }, third{ third } {} triple(T1 &&first, T2 &&second, T3 &&third) : first{ first }, second{ second }, third{ third } {} };
template<typename T1, typename T2, typename T3, typename T4> struct quad { T1 first; T2 second; T3 third; T4 fourth; quad() : first{}, second{}, third{}, fourth{} {} quad(const T1 &first, const T2 &second, const T3 &third, const T4 &fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} quad(T1 &&first, T2 &&second, T3 &&third, T4 &&fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} };
template<typename T> inline constexpr const T &_min(const T &x,const T &y) { return x < y ? x: y; }
template<typename T> inline constexpr const T &_max(const T &x,const T &y) { return x < y ? y : x; }
template<typename T, typename...Ts> inline constexpr const T &_min(const T &x,const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename...Ts> inline constexpr const T &_max(const T &x,const Ts &...xs) { return _max(x, _max(xs...)); }
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
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
using namespace std;

int N, M, K, B, weight_to[20], dp[1 << 20], mst_cost[1 << 20];
vector<pair<int, int>> graph[20];
vector<int> burrows[20];
bool visited[20];
min_priority_queue<pair<int, int>> pq;

void add_burrow(int bm) {
    fill(visited, visited + N, false);
    fill(weight_to, weight_to + N, inf);
    pq = min_priority_queue<pair<int, int>>();
    weight_to[ctz(bm)] = 0;
    pq.emplace(0, ctz(bm));

    while (!pq.empty()) {
        pair<int, int> event = pq.top();
        pq.pop();
        int node = event.second;

        if (visited[node]) continue;
        visited[node] = true;

        for (pair<int, int> &adj_edge : graph[node]) {
            int other = adj_edge.first, weight = adj_edge.second;
            if (bm & (1 << other) && !visited[other] && weight_to[other] > weight) {
                weight_to[other] = weight;
                pq.emplace(weight_to[other], other);
            }
        }
    }

    for (int i = 0; i < N; i++)
        if (bm & (1 << i))
            mst_cost[bm] = min(mst_cost[bm] + weight_to[i], inf);

    burrows[ctz(bm)].push_back(bm);
}

int solve(int bm) {
    if (~dp[bm]) return dp[bm];
    if (popcount(bm) == B) return dp[bm] = mst_cost[bm];
    dp[bm] = inf;
    int division = ctz(bm);
    for (int adj : burrows[division])
        if ((bm & adj) == adj)
            dp[bm] = min(dp[bm], mst_cost[adj] + solve(bm - adj));
    return dp[bm];
}

int main() {
    scan(N);
    scan(M);
    scan(K);
    if (N % K) {
        printf("-1\n");
        return 0;
    }
    B = N / K;
    while (M--) {
        int i, j, c;
        scan(i);
        scan(j);
        scan(c);
        i--, j--;
        graph[i].emplace_back(j, c);
        graph[j].emplace_back(i, c);
    }
    int lim = (1 << N);
    for (int i = 0; i < lim; i++)
        if (popcount(i) == B)
            add_burrow(i);
    memset(dp, -1, sizeof dp);
    printf("%d\n", solve((1 << N) - 1) == inf ? -1 : solve((1 << N) - 1));
    return 0;
}