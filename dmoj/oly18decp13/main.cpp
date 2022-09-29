#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
struct pair_hash { template <typename T1, typename T2> std::size_t operator()(const std::pair<T1, T2> &p) const { auto h1 = std::hash<T1>{}(p.first); auto h2 = std::hash<T2>{}(p.second); return h1 ^ h2; } };
template<typename T1, typename T2, typename T3> struct triple { T1 first; T2 second; T3 third; triple() : first{}, second{}, third{} {} triple(const T1 &first, const T2 &second, const T3 &third) : first{ first }, second{ second }, third{ third } {} triple(T1 &&first, T2 &&second, T3 &&third) : first{ first }, second{ second }, third{ third } {} };
template<typename T1, typename T2, typename T3, typename T4> struct quad { T1 first; T2 second; T3 third; T4 fourth; quad() : first{}, second{}, third{}, fourth{} {} quad(const T1 &first, const T2 &second, const T3 &third, const T4 &fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} quad(T1 &&first, T2 &&second, T3 &&third, T4 &&fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} };
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x: y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
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
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
using namespace std;

struct Event {
    int x, y1, y2, v;
    bool operator<(const Event &that) const {
        return x == that.x ? v > that.v : x < that.x;
    }
};

int N, seg_tree[4096], cnt[4096], segy[2000];
unordered_map<int, int> comp;
Event events[2000];
long long ans = 0;

void update(int node, int lo, int hi, int left, int right, int value) {
    if (right < lo || hi < left) return;
    if (left <= lo && hi <= right) {
        cnt[node] += value;
    } else {
        int mid = (lo + hi) / 2;
        update(node * 2, lo, mid, left, right, value);
        update(node * 2 + 1, mid + 1, hi, left, right, value);
        seg_tree[node] = (cnt[node * 2] ? segy[mid + 1] - segy[lo] : seg_tree[node * 2]) + (cnt[node * 2 + 1] ? segy[hi + 1] - segy[mid + 1] : seg_tree[node * 2 + 1]);
    }
}

long long query() {
    return cnt[1] ? segy[2 * N + 1] - segy[0] : seg_tree[1];
}

int main() {
    scan(N);

    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        scan(x1);
        scan(y1);
        scan(x2);
        scan(y2);
        swap(y1, y2);
        events[i * 2].x = x1;
        events[i * 2 + 1].x = x2;
        events[i * 2].y1 = events[i * 2 + 1].y1 = y1;
        events[i * 2].y2 = events[i * 2 + 1].y2 = y2;
        events[i * 2].v = 1;
        events[i * 2 + 1].v = -1;
        segy[i * 2] = y1;
        segy[i * 2 + 1] = y2;
    }

    sort(segy, segy + N * 2);
    sort(events, events + N * 2);
    for (int i = 0; i < N * 2; i++)
        comp[segy[i]] = i;

    long long px {}, x {};

    for (int i = 0; i < 2 * N; i++) {
        x = events[i].x;
        ans += (x - px) * query();
        update(1, 0, 2 * N - 1, comp[events[i].y1], comp[events[i].y2] - 1, events[i].v);
        px = events[i].x;
    }

    printf("%lld\n", ans);

    return 0;
}