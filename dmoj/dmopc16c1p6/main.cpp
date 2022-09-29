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

bitset<500> endpoints[30][500], tmp[2];
int N, M, Q, a[500], min_a[30][500];

int main() {
    scan(N);
    scan(M);

    for (int i = 0; i < N; i++) {
        scan(a[i]);
        min_a[0][i] = inf;
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scan(u);
        scan(v);
        u--, v--;
        endpoints[0][u].set(v);
        min_a[0][u] = min(min_a[0][u], a[v]);
    }

    for (int i = 1; i < 30; i++) {
        for (int j = 0; j < N; j++) {
            min_a[i][j] = min_a[i - 1][j];

            for (int k = endpoints[i - 1][j]._Find_first(); k < N; k = endpoints[i - 1][j]._Find_next(k))
                endpoints[i][j] |= endpoints[i - 1][k], min_a[i][j] = min(min_a[i][j], min_a[i - 1][k]);
        }
    }

    scan(Q);

    while (Q--) {
        int c, k;
        scan(c);
        scan(k);
        c--;

        int qa = a[c];
        tmp[0].reset();
        tmp[0].set(c);

        for (int i = 29; i >= 0 && tmp[0].count(); i--) {
            if ((1 << i) <= k) {
                tmp[1].reset();
                for (int node = tmp[0]._Find_first(); node < N; node = tmp[0]._Find_next(node))
                    tmp[1] |= endpoints[i][node], qa = min(qa, min_a[i][node]);
                swap(tmp[0], tmp[1]);
                k -= (1 << i);
            }
        }

        printf("%d %d\n", qa, tmp[0].count());
    }

    return 0;
}