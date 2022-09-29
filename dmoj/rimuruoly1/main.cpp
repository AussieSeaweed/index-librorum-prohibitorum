#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scanu(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
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
template<typename _EuclideanRingElement> inline _EuclideanRingElement gcd(const _EuclideanRingElement &_m, const _EuclideanRingElement &_n) { return std::__gcd(_m, _n); }
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x : y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename ...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename ...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
using namespace std;

int N, D, dp[2001][2000], parents[2001], ans, sorted_arr[2000], p, tmp[2000];
vector<int> graph[2001];

void dfs(int node, int parent) {
    parents[node] = parent;

    for (int adj : graph[node]) {
        if (adj == parent) continue;
        dfs(adj, node);
    }

    sorted_arr[p++] = node;
}

int main() {
    scan(N);
    scan(D);

    for (int i = 1; i < N; i++) {
        int a, b;
        scan(a);
        scan(b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(1, 0);

    for (int i = 0; i < N; i++) {
        int node = sorted_arr[i];
        fill(dp[node], dp[node] + D + 1, 1);

        for (int adj : graph[node]) {
            if (adj == parents[node]) continue;
            for (int j = 1; j <= D; j++)
                dp[node][j] += dp[adj][j - 1];
        }
    }

    for (int i = N - 1; i >= 0; i--) {
        int node = sorted_arr[i];

        if (parents[node]) {
            int prev = 0;

            for (int j = 1; j <= D; j++) {
                tmp[j] = dp[parents[node]][j - 1] - prev;
                prev = dp[node][j - 1];
            }

            for (int j = 0; j <= D; j++)
                dp[node][j] += tmp[j];
        }

        int cur = dp[node][D / 2];

        if (D % 2) {
            cur = max(cur, dp[node][D / 2] - (D / 2 == 0 ? 0 : tmp[D / 2]) + tmp[D / 2 + 1]);
            for (int adj : graph[node]) {
                if (adj == parents[node]) continue;
                cur = max(cur, dp[node][D / 2] - (D / 2 == 0 ? 0 : dp[adj][D / 2 - 1]) + dp[adj][D / 2]);
            }
        }

        ans = max(ans, cur);
    }

    printf("%d\n", N - ans);

    return 0;
}