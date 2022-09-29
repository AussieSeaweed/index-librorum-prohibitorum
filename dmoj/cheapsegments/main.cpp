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

int E, N, Q, M, v[100000], len[100000], l[100000], r[100000], x[200000], ans[100000];
pair<int, int> segs[100000];
unordered_map<int, int> comp;

struct VALUE_ORDER {
    bool operator()(const int &a, const int &b) const { return v[a] == v[b] ? (l[a] == l[b] ? a < b : l[a] < l[b]) : v[a] < v[b]; }
} compare;

set<int, VALUE_ORDER> bit[200001];

struct Event {
    int t, l, r, i;
    Event(int t, int l, int r, int i) : t{ t }, l{ l }, r{ r }, i{ i } {}
    bool operator<(const Event &that) const { return l == that.l ? t < that.t : l < that.l; }
} *events[200000];

void insert(int i, int k) {
    i = M - i;

    while (i <= M) {
        bit[i].insert(k);
        if (bit[i].size() > 3) bit[i].erase(--bit[i].end());
        i += i & -i;
    }
}

void erase(int i, int k) {
    i = M - i;

    while (i <= M) {
        bit[i].erase(k);
        i += i & -i;
    }
}

int query(int i) {
    i = M - i;
    int ret = -1;

    while (i) {
        if (ret == -1)
            ret = bit[i].empty() ? -1 : *bit[i].begin();
        else if (!bit[i].empty())
            ret = compare(ret, *bit[i].begin()) ? ret : *bit[i].begin();

        i -= i & -i;
    }

    return ret;
}

int main() {
    scan(N);

    for (int i = 0; i < N; i++) {
        scan(l[i], r[i], v[i]);
        len[i] = r[i] - l[i] + 1;
        x[M++] = l[i], x[M++] = r[i];
    }

    sort(x, x + M);
    M = unique(x, x + M) - x;

    for (int i = 0; i < M; i++)
        comp[x[i]] = i;

    for (int i = 0; i < N; i++) {
        l[i] = comp[l[i]], r[i] = comp[r[i]];
        events[E++] = new Event(0, l[i], r[i], i);
    }

    scan(Q);

    for (int i = 0; i < Q; i++) {
        scan(segs[i].first, segs[i].second);
        segs[i].first--, segs[i].second--;
        events[E++] = new Event(1, min(l[segs[i].first], l[segs[i].second]), max(r[segs[i].first], r[segs[i].second]), i);
    }

    sort(events, events + E, [] (Event *a, Event *b) -> bool { return *a < *b; });

    for (int i = 0; i < E; i++) {
        Event &e = *events[i];

        if (e.t == 0) {
            insert(e.r, e.i);
        } else {
            if (l[segs[e.i].first] <= e.l) erase(r[segs[e.i].first], segs[e.i].first);
            if (l[segs[e.i].second] <= e.l) erase(r[segs[e.i].second], segs[e.i].second);
            ans[e.i] = query(e.r);
            if (l[segs[e.i].first] <= e.l) insert(r[segs[e.i].first], segs[e.i].first);
            if (l[segs[e.i].second] <= e.l) insert(r[segs[e.i].second], segs[e.i].second);
        }
    }

    for (int i = 0; i < Q; i++)
        printf("%d\n", ans[i] == -1 ? -1 : ans[i] + 1);

    return 0;
}