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

int N, R, C, values[1500][1500], dp[1500][1500], rows[1500][5], cols[1500][5], datas[2250000];

int get_dp(int r, int c) {
    if (~r && ~c) return dp[r][c];
    else return 0;
}

int get_highest_c(int r, int c) {
    for (int i = 0; i < 4; i++) if (rows[r][i] < c - 1 || c + 1 < rows[r][i]) return get_dp(r, rows[r][i]);
    return 0;
}

int get_highest_r(int r, int c) {
    for (int i = 0; i < 4; i++) if (cols[c][i] < r - 1 || r + 1 < cols[c][i]) return get_dp(cols[c][i], c);
    return 0;
}

void update(int r, int c) {
    rows[r][4] = c;
    cols[c][4] = r;
    sort(rows[r], rows[r] + 5, [&] (int a, int b) -> bool { return get_dp(r, a) > get_dp(r, b); });
    sort(cols[c], cols[c] + 5, [&] (int a, int b) -> bool { return get_dp(a, c) > get_dp(b, c); });
}

int get_highest(int r, int c) {
    int ret = 0;
    if (0 < r) ret = max(ret, get_highest_c(r - 1, c));
    if (r < N - 1) ret = max(ret, get_highest_c(r + 1, c));
    if (0 < c) ret = max(ret, get_highest_r(r, c - 1));
    if (c < N - 1) ret = max(ret, get_highest_r(r, c + 1));
    return ret;
}

int main() {
    scan(N);
    scan(R);
    scan(C);
    R--, C--;

    for (int i = 0; i < N * N; i++) datas[i] = i;

    for (int i = 0; i < N; i++) {
        fill(rows[i], rows[i] + 5, -1);
        fill(cols[i], cols[i] + 5, -1);
        for (int j = 0; j < N; j++) {
            scan(values[i][j]);
        }
    }

    sort(datas, datas + N * N, [&] (int a, int b) -> bool { return values[a / N][a % N] > values[b / N][b % N]; });
    int prev_index = 0, prev_value = inf;

    for (int i = 0; i < N * N; i++) {
        if (values[datas[i] / N][datas[i] % N] != prev_value) {
            while (prev_index < i) {
                update(datas[prev_index] / N, datas[prev_index] % N);
                prev_index++;
            }
        }

        dp[datas[i] / N][datas[i] % N] = 1 + get_highest(datas[i] / N, datas[i] % N);
        prev_value = values[datas[i] / N][datas[i] % N];
    }

    printf("%d\n", dp[R][C]);

    return 0;
}