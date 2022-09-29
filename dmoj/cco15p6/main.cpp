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
#define MAX_NUM 400000
using namespace std;

int N, K, M, T, bit[MAX_NUM + 1], cnt[2502][2502], r[4], c[4], nc[2502][2502], nr[2502], total;

inline int get_root(int node, int ds[]) { return node == ds[node] ? node : ds[node] = get_root(ds[node], ds); }

inline void update(int i, int delta) {
    total += delta;
    while (i <= MAX_NUM) {
        bit[i] += delta;
        i += i & -i;
    }
}

inline int query(int i) {
    int ret = 0;
    while (i) {
        ret += bit[i];
        i -= i & -i;
    }
    return ret;
}

inline double get_ans(int v) {
    if (v > MAX_NUM) return 0;
    return (total - query(v - 1)) / ((double) (N - K + 1) * (N - K + 1));
}

int main() {
    scan(N);
    scan(K);
    scan(M);

    for (int i = 0; i < M; i++) {
        int s;
        scan(s);

        for (int j = 0; j < s; j++) { scan(r[j]); scan(c[j]); }

        for (int j = 1; j < (1 << s); j++) {
            int min_r = inf, max_r = -inf, min_c = inf, max_c = -inf;

            for (int k = 0; k < s; k++) {
                if (j & (1 << k)) {
                    min_r = min(min_r, r[k]);
                    max_r = max(max_r, r[k]);
                    min_c = min(min_c, c[k]);
                    max_c = max(max_c, c[k]);
                }
            }

            if (max_r - min_r + 1 <= K && max_c - min_c + 1 <= K) {
                int delta = popcount(j) & 1 ? 1 : -1, ri = max(1, max_r - K + 1), rj = min_r, ci = max(1, max_c - K + 1), cj = min_c;
                cnt[ri][ci] += delta;
                cnt[rj + 1][ci] -= delta;
                cnt[ri][cj + 1] -= delta;
                cnt[rj + 1][cj + 1] += delta;
            }
        }
    }

    for (int i = 1; i <= N + 1; i++) {
        nr[i] = i;
        for (int j = 1; j <= N + 1; j++) {
            nc[i][j] = j;
            cnt[i][j] += cnt[i][j - 1] + cnt[i - 1][j] - cnt[i - 1][j - 1];
        }
    }

    for (int i = 1; i <= N - K + 1; i++) {
        for (int j = 1; j <= N - K + 1; j++) {
            if (cnt[i][j]) {
                update(cnt[i][j], 1);
            }
        }
    }

    scan(T);

    while (T--) {
        int t;
        scan(t);

        if (t == 1) {
            int A, B;
            scan(A);
            scan(B);

            for (int i = get_root(max(1, A - K + 1), nr), lim1 = min(N - K + 1, A); i <= lim1; i = get_root(i + 1, nr)) {
                for (int j = get_root(max(1, B - K + 1), nc[i]), lim2 = min(N - K + 1, B); j <= lim2; j = get_root(j, nc[i]))
                    update(cnt[i][j], -1), nc[i][j] = j + 1;
                if (get_root(1, nc[i]) == N - K + 2)
                    nr[i] = i + 1;
            }

        } else {
            int V;
            scan(V);
            printf("%.6lf\n", get_ans(V));
        }
    }

    return 0;
}