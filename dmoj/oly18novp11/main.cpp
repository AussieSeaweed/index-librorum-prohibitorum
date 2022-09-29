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
inline int ffs(int x) { return __builtin_ffs(x); }
inline int ctz(int x) { return __builtin_ctz(x); }
inline int clz(int x) { return __builtin_clz(x); }
inline int popcount(int x) { return __builtin_popcount(x); }
inline int ffs(long long x) { return __builtin_ffsll(x); }
inline int ctz(long long x) { return __builtin_ctzll(x); }
inline int clz(long long x) { return __builtin_clzll(x); }
inline int popcount(long long x) { return __builtin_popcountll(x); }
template<typename _EuclideanRingElement> inline _EuclideanRingElement euclidean(_EuclideanRingElement _m, _EuclideanRingElement _n) { return std::__gcd(_m, _n); }
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x : y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename ...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename ...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
#define RECT_BEGIN 0
#define POINT 1
#define RECT_END 2
using namespace std;

struct Event {
    int i, t, x, a, b;
    inline Event(int i, int t, int x, int a, int b=0) : i{ i }, t{ t }, x{ x }, a{ a }, b{ b } {}
    inline bool operator<(const Event &that) const { return x == that.x ? t < that.t : x < that.x; }
};

int N, M, T, ans[400000], l[400001], r[400001], e = 1, anc[19][400001], depths[400001], bit[800001], visited[800001], cur, E;
Event *events[2000000], *tmp[2000000];
vector<int> graph[400001];

void dfs(int node, int parent, int depth) {
    anc[0][node] = parent;
    depths[node] = depth;
    l[node] = e++;

    for (int adj : graph[node]) {
        if (adj == parent) continue;
        dfs(adj, node, depth + 1);
    }

    r[node] = e++;
}

inline void build_sparse_table() {
    for (int i = 1; i < 19; i++)
        for (int j = 1; j <= N; j++)
            if (anc[i - 1][j])
                anc[i][j] = anc[i - 1][anc[i - 1][j]];
}

inline void update(int i, int delta) {
    while (i < e) {
        if (visited[i] != cur) { visited[i] = cur, bit[i] = 0; }
        bit[i] += delta;
        i += i & -i;
    }
}

inline int query(int i) {
    int ret = 0;
    while (i) {
        if (visited[i] != cur) { visited[i] = cur, bit[i] = 0; }
        ret += bit[i];
        i -= i & -i;
    }
    return ret;
}

inline int get_first_child(int u, int v) {
    for (int i = 18; i >= 0; i--)
        if (depths[u] - (1 << i) > depths[v])
            u = anc[i][u];
    return u;
}

struct Weapon_Data {
    int a, b, c;
    inline Weapon_Data(int a, int b, int c) : a{ a }, b{ b }, c{ c } {}
    inline bool operator<(const Weapon_Data &that) const { return c < that.c; }
} *weapon_datas[400000];

struct Weapon {
    int a, b, c, i;
    vector<Event *> events;
    inline Weapon(int a, int b, int c, int i) : a{ a }, b{ b }, c{ c }, i{ i } {
        if (l[a] > l[b]) swap(a, b); // a discovered before
        if (l[a] <= l[b] && l[b] <= r[a]) { // b is in subtree of a
            int first_child = get_first_child(b, a);
            events.push_back(new Event(i, RECT_BEGIN, 1, l[b], r[b]));
            events.push_back(new Event(i, RECT_END, l[first_child] - 1, l[b], r[b]));
            events.push_back(new Event(i, RECT_BEGIN, l[b], r[first_child] + 1, e - 1));
            events.push_back(new Event(i, RECT_END, r[b], r[first_child] + 1, e - 1));
        } else {
            events.push_back(new Event(i, RECT_BEGIN, l[a], l[b], r[b]));
            events.push_back(new Event(i, RECT_END, r[a], l[b], r[b]));
        }
    }
    inline bool operator<(const Weapon &that) const { return c < that.c; }
} *weapons[400000];

struct Path {
    int a, b, k, i;
    Event *event;
    inline Path(int a, int b, int k, int i) : a{ a }, b{ b }, k{ k }, i{ i } {
        if (l[a] > l[b]) swap(a, b); // a discovered before
        event = new Event(i, POINT, l[a], l[b]);
    }
} *paths[400000];

inline void line_sweep(int ei, int ej) {
    cur++;

    for (int i = ei; i <= ej; i++) {
        Event *event = tmp[i];

        if (event->t == RECT_BEGIN) {
            update(event->a, 1);
            update(event->b + 1, -1);
        } else if (event->t == RECT_END) {
            update(event->a, -1);
            update(event->b + 1, 1);
        } else {
            ans[event->i] = query(event->a);
        }
    }
}

void solve(int wi, int wj, int pi, int pj, int ei, int ej) {
    if (pj - pi + 1 == 0) return;
    if (wi == wj) {
        for (int i = pi; i <= pj; i++)
            ans[paths[i]->i] = weapons[wi]->c;
    } else {
        int wmid = (wi + wj) / 2, pmid = pi, ti = ei, tj = ej;

        for (int i = ei; i <= ej; i++)
            if (events[i]->t == POINT || events[i]->i <= wmid)
                tmp[ti++] = events[i];

        line_sweep(ei, ti - 1);

        for (int i = pi; i <= pj; i++) {
            if (ans[paths[i]->i] >= paths[i]->k) {
                paths[i]->event->b = 1;
                swap(paths[pmid++], paths[i]);
            } else {
                paths[i]->k -= ans[paths[i]->i];
                paths[i]->event->b = 0;
            }
        }

        ti = ei;

        for (int i = ei; i <= ej; i++) {
            if (events[i]->t == RECT_BEGIN || events[i]->t == RECT_END) {
                if (events[i]->i > wmid) {
                    tmp[tj--] = events[i];
                } else {
                    tmp[ti++] = events[i];
                }
            } else {
                if (events[i]->b) {
                    tmp[ti++] = events[i];
                } else {
                    tmp[tj--] = events[i];
                }
            }
        }

        reverse(tmp + ti, tmp + ej + 1);
        copy(tmp + ei, tmp + ej + 1, events + ei);

        solve(wi, wmid, pi, pmid - 1, ei, ti - 1);
        solve(wmid + 1, wj, pmid, pj, ti, ej);
    }
}

int main() {
    scan(N);
    scan(M);
    scan(T);

    for (int i = 1; i < N; i++) {
        int a, b;
        scan(a);
        scan(b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(1, 0, 0);
    build_sparse_table();

    for (int i = 0; i < M; i++) {
        int a, b, c;
        scan(a);
        scan(b);
        scan(c);
        weapon_datas[i] = new Weapon_Data(a, b, c);
    }

    sort(weapon_datas, weapon_datas + M, [] (Weapon_Data *a, Weapon_Data *b) -> bool { return *a < *b; });

    for (int i = 0; i < M; i++) {
        weapons[i] = new Weapon(weapon_datas[i]->a, weapon_datas[i]->b, weapon_datas[i]->c, i);
        for (Event *event : weapons[i]->events)
            events[E++] = event;
    }

    for (int i = 0; i < T; i++) {
        int a, b, k;
        scan(a);
        scan(b);
        scan(k);
        paths[i] = new Path(a, b, k, i);
        events[E++] = paths[i]->event;
    }

    sort(events, events + E, [] (Event *a, Event *b) -> bool { return *a < *b; });
    solve(0, M - 1, 0, T - 1, 0, E - 1);

    for (int i = 0; i < T; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}