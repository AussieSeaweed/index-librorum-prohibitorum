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
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x : y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename ...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename ...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
using namespace std;

const int BLOCK_SIZE = 316;
int N, Q, block_size = 316, a[100000], values[100000], cnt[100001];
long long ans[100000];
unordered_map<int, int> comp;

inline void update(int i, int delta) {
    while (i <= N) {
        cnt[i] += delta;
        i += i & -i;
    }
}

inline int query(int i) {
    int ret = 0;
    while (i) {
        ret += cnt[i];
        i -= i & -i;
    }
    return ret;
}

struct Query {
    int l, r, b, i;
    Query(int l, int r, int i) : l{ l }, r{ r }, b{ l / BLOCK_SIZE }, i{ i } {}
    bool operator<(const Query &that) const { return b == that.b ? (b & 1 ? r > that.r : r < that.r) : b < that.b; }
} *queries[100000];

void add_left(int l, int r, long long &cur) {
    update(a[l], 1);
    cur += query(a[l] - 1);
}

void remove_left(int l, int r, long long &cur) {
    cur -= query(a[l] - 1);
    update(a[l], -1);
}

void add_right(int l, int r, long long &cur) {
    update(a[r], 1);
    cur += (r - l + 1) - query(a[r]);
}

void remove_right(int l, int r, long long &cur) {
    cur -= (r - l + 1) - query(a[r]);
    update(a[r], -1);
}

void add_tmp(Query *query, long long &cur) {

}

void remove_tmp(Query *query, long long &cur) {

}

void mo(int num_queries, Query *queries[], long long ans[]) {
    sort(queries, queries + num_queries, [] (const Query *a, const Query *b) -> bool { return *a < *b; });
    int l = 0, r = -1;
    long long cur = 0;
    for (int i = 0; i < num_queries; i++) {
        int ql = queries[i]->l, qr = queries[i]->r;

        while (l < ql) {
            remove_left(l++, r, cur);
        }

        while (l > ql) {
            add_left(--l, r, cur);
        }

        while (r < qr) {
            add_right(l, ++r, cur);
        }

        while (r > qr) {
            remove_right(l, r--, cur);
        }

        add_tmp(queries[i], cur);
        ans[queries[i]->i] = cur;
        remove_tmp(queries[i], cur);
    }
}

int main() {
    pscan(N);
    for (int i = 0; i < N; i++) pscan(a[i]);
    copy(a, a + N, values);
    sort(values, values + N);
    for (int i = 0; i < N; i++) comp[values[i]] = i + 1;
    for (int i = 0; i < N; i++) a[i] = comp[a[i]];
    pscan(Q);
    for (int i = 0; i < Q; i++) {
        int l, r;
        pscan(l);
        pscan(r);
        l--, r--;
        queries[i] = new Query(l, r, i);
    }
    mo(Q, queries, ans);
    for (int i = 0; i < Q; i++) printf("%lld\n", ans[i]);
    return 0;
}