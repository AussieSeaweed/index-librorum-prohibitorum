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

int N, K, S, A, B, *sq[12][3000], *tri[12][3000];
long long ans;

int flog2(int n) {
    return n == 1 ? 0 : 1 + flog2(n / 2);
}

long long query(int i, int j) {
    return max(sq[B][i][j], sq[B][i - S + (1 << B)][j], sq[B][i - S + (1 << B)][j + S - (1 << B)], sq[B][i][j + S - (1 << B)], tri[A][i - K + (1 << A)][j], tri[A][i][j + K - (1 << A)]);
}

int main() {
    scan(N);
    scan(K);
    A = flog2(K);
    B = flog2(S = K / 2 + K % 2);

    for (int l = 0; l < 12; l++)
        for (int i = 0; i < N; i++)
            sq[l][i] = new int[i + 1], tri[l][i] = new int[i + 1];


    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            int a; scan(a);
            sq[0][i][j] = tri[0][i][j] = a;
        }
    }

    for (int l = 1; l < 12; l++) {
        for (int i = (1 << l) - 1; i < N; i++) {
            for (int j = 0; j + (1 << l) - 1 <= i; j++) {
                tri[l][i][j] = max(sq[l - 1][i][j], tri[l - 1][i - (1 << (l - 1))][j], tri[l - 1][i][j + (1 << (l - 1))]);
                sq[l][i][j] = max(sq[l - 1][i][j], sq[l - 1][i - (1 << (l - 1))][j], sq[l - 1][i - (1 << (l - 1))][j + (1 << (l - 1))], sq[l - 1][i][j + (1 << (l - 1))]);
            }
        }
    }

    for (int i = K - 1; i < N; i++) {
        for (int j = 0; j + K - 1 <= i; j++) {
            ans += query(i, j);
        }
    }

    printf("%lld\n", ans);

    return 0;
}