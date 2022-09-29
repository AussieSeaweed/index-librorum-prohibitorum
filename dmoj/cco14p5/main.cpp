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
template<typename _EuclideanRingElement> inline _EuclideanRingElement euclidean(const _EuclideanRingElement &_m, const _EuclideanRingElement &_n) { return std::__gcd(_m, _n); }
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x : y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename ...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename ...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
using namespace std;

int N, M, bit[100001], aud[100001][6];
long long A, B, fmb[600001], sumb, ans = INF;

void update(int i, int delta) {
    while (i <= N) {
        bit[i] += delta;
        i += i & -i;
    }
}

int query(int i) {
    int ret = 0;
    while (i) {
        ret += bit[i];
        i -= i & -i;
    }
    return ret;
}

int main() {
    scan(N);
    scan(M);
    scan(A);
    scan(B);
    for (int i = 1; i <= M; i++) {
        int r;
        char c;
        scanf("%d%c", &r, &c);
        c -= 'A';
        aud[r][c] = 1;
        if (c == 2 || c == 3) update(r, 1);
        long long f = 2 * r - query(r), b = 2 * (N - r + 1) - (query(N) - query(r - 1));
        if (c == 0) f += !aud[r][1], b += !aud[r][1];
        else if (c == 5) f += !aud[r][4], b += !aud[r][4];
        sumb += b;
        fmb[i] = f - b;
    }
    sort(fmb + 1, fmb + M + 1);
    for (int i = 1; i <= M; i++) fmb[i] += fmb[i - 1];
    for (int i = 0; i <= M; i++) { // i = ppl at front
        long long x = sumb + fmb[i], y = i * (i - 1ll) / 2 + (M - i) * (M - i - 1ll) / 2;
        ans = min(ans, A * x + B * y);
    }
    printf("%lld\n", ans);
    return 0;
}