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



int par[100000], cc[100000], up[100000], down1[100000], down2[100000], down_node[100000], cc_len[100000], C;
bool visited[100000];
vector<pair<int, int>> graph[100000];

void dfs(int node, int parent, int cc_id) {
    visited[node] = true;
    par[node] = parent;
    cc[node] = cc_id;

    for (pair<int, int> &edge : graph[node]) {
        int adj, w;
        tie(adj, w) = edge;

        if (adj == parent) continue;

        dfs(adj, node, cc_id);

        int cur = down1[adj] + edge.second;

        if (cur > down1[node])
            down2[node] = down1[node], down1[node] = cur, down_node[node] = adj;
        else if (cur > down2[node])
            down2[node] = cur;
    }
}

void dfs2(int node, int parent) {
    visited[node] = true;
    cc_len[cc[node]] = min(cc_len[cc[node]], max(up[node], down1[node]));

    for (pair<int, int> &edge : graph[node]) {
        int adj, w;
        tie(adj, w) = edge;

        if (adj == parent) continue;

        up[adj] = edge.second + max(up[node], (down_node[node] == adj ? down2[node] : down1[node]));

        dfs2(adj, node);
    }
}

int travelTime(int N, int M, int L, int A[], int B[], int T[]) {
    for (int i = 0; i < M; i++) {
        graph[A[i]].emplace_back(B[i], T[i]);
        graph[B[i]].emplace_back(A[i], T[i]);
    }

    for (int i = 0; i < N; i++)
        if (!visited[i])
            dfs(i, -1, C++);

    fill(visited, visited + N, false);
    fill(cc_len, cc_len + C, inf);

    for (int i = 0; i < N; i++)
        if (!visited[i])
            dfs2(i, -1);

    int ans = 0;

    for (int i = 0; i < N; i++)
        ans = max(ans, down1[i] + down2[i], down1[i] + up[i]);

    sort(cc_len, cc_len + C, greater<int>());

    if (C == 2)
        ans = max(ans, cc_len[0] + L + cc_len[1]);
    else if (C >= 3)
        ans = max(ans, cc_len[0] + L + cc_len[1], cc_len[1] + L + L + cc_len[2]);

    return ans;
}