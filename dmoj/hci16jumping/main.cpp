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

deque<long long> M, B;
int N, C;
long long dp[2000][2];
bool grid[2000][2000];
char str[2001];

void init() {
    M.clear(), B.clear();
}

void insert(long long m, long long b) {
    while (M.size() >= 2 && (b - B[B.size() - 2]) / ((double) M[M.size() - 2] - m) < (B[B.size() - 1] - B[B.size() - 2]) / ((double) M[M.size() - 2] - M[M.size() - 1]))
        M.pop_back(), B.pop_back();

    M.push_back(m);
    B.push_back(b);
}

long long calculate(long long x) {
    while (M.size() >= 2 && M[0] * x + B[0] > M[1] * x + B[1])
        M.pop_front(), B.pop_front();
    return M[0] * x + B[0];
}

int main() {
    scan(N);
    scan(C);

    for (int i = 0; i < C; i++) {
        scanf("%s", str);
        for (int j = 0; j < N; j++) {
            grid[i][j] = str[j] - '0';
        }
    }

    for (int i = 0; i < C; i++)
        dp[i][0] = grid[i][0] ? 0 : INF;

    for (int j = 1; j < N; j++) {
        init();

        for (int i = 0; i < C; i++) {
            if (grid[i][j - 1]) insert(-2 * i, dp[i][(j - 1) & 1] + i * i);
        }

        for (int i = 0; i < C; i++) {
            if (grid[i][j]) dp[i][j & 1] = calculate(i) + i * i;
        }
    }

    long long ans = INF;

    for (int i = 0; i < C; i++) {
        if (grid[i][N - 1]) {
            ans = min(ans, dp[i][(C - 1) & 1]);
        }
    }

    printf("%lld\n", ans);

    return 0;
}