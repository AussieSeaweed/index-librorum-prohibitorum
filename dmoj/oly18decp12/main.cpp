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
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
using namespace std;

int N, K, dp[100][100][6], next_i[100];
vector<int> color_indices[101];

int solve(int i, int lim, int consec) {
    if (~dp[i][lim][consec]) return dp[i][lim][consec];

    if (i == lim) {
        dp[i][lim][consec] = K - consec;
    } else if (next_i[i] != i + 1) {
        dp[i][lim][consec] = K - consec + solve(i + 1, lim, 1);
        int j = next_i[i];
        while (~j && j <= lim) { // there is another index with the same color after i before lim
            dp[i][lim][consec] = min(dp[i][lim][consec], solve(i + 1, j - 1, 1) + solve(j, lim, min(K, consec + 1)));
            j = next_i[j];
        }
    } else {
        dp[i][lim][consec] = solve(i + 1, lim, min(K, consec + 1));
    }

    return dp[i][lim][consec];
}

int main() {
    scan(N);
    scan(K);
    for (int i = 0; i < N; i++) {
        int c;
        scan(c);
        color_indices[c].push_back(i);
    }
    fill(next_i, next_i + N, -1);
    for (int i = 1; i <= 100; i++) {
        for (int j = 1; j < color_indices[i].size(); j++) {
            next_i[color_indices[i][j - 1]] = color_indices[i][j];
        }
    }
    memset(dp, -1, sizeof dp);
    printf("%d\n", solve(0, N - 1, 1));
    return 0;
}