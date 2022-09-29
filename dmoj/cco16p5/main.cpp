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
    Event(int x, int y1, int y2, int v) : x{ x }, y1{ y1 }, y2{ y2 }, v{ v } {}
    bool operator>(const Event &that) const {
        return x == that.x ? v < that.v : x > that.x;
    }
};

int N, M, K, Q, y_values[4000], sweep_line[4000];
pair<int, int> points[2000];
min_priority_queue<Event> pq;
unordered_map<int, int> comp;

long long solve(int q) {
    pq = min_priority_queue<Event>();
    for (int i = 0; i < K; i++) {
        int x = points[i].first, y = points[i].second;
        y_values[2 * i] = max(1, y - q);
        y_values[2 * i + 1] = min(M + 1, y + q + 1);
        pq.emplace(max(1, x - q), y_values[2 * i], y_values[2 * i + 1], 1);
        pq.emplace(min(N + 1, x + q + 1), y_values[2 * i], y_values[2 * i + 1], -1);
    }
    sort(y_values, y_values + 2 * K);
    comp.clear();
    for (int i = 0; i < 2 * K; i++) comp[y_values[i]] = i;
    long long area = 0, px = 0;
    fill(sweep_line, sweep_line + 2 * K, 0);
    while (!pq.empty()) {
        Event event = pq.top();
        pq.pop();
        for (int i = 0; i < 2 * K; i++)
            if (sweep_line[i])
                area += (event.x - px) * (y_values[i + 1] - y_values[i]);
        for (int i = comp[event.y1]; i < comp[event.y2]; i++)
            sweep_line[i] += event.v;
        px = event.x;
    }
    return area;
}

int main() {
    scan(N);
    scan(M);
    scan(K);
    for (int i = 0; i < K; i++) {
        scan(points[i].first);
        scan(points[i].second);
    }
    scan(Q);

    if (Q == 0) {
        printf("%d\n", K);
    } else {
        printf("%lld\n", solve(Q) - solve(Q - 1));
    }
    return 0;
}