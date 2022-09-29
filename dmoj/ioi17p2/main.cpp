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

int N, lvl, lpos[200001], last[200001];
long long sumr[200001], sumb[200001], dp[200001];
pair<int, int> pts[200001];

long long nearist_dist(vector<int> &a, int x) {
    long long min_dist = INF;
    auto it = lower_bound(a.begin(), a.end(), x);
    if (it != a.end())
        min_dist = *it - x;
    if (it != a.begin())
        min_dist = min(min_dist, (long long) x - *--it);
    return min_dist;
}

long long min_total_length(vector<int> r, vector<int> b) {
    for (int x : r)
        pts[++N] = {x, -1};
    for (int x : b)
        pts[++N] = {x, 1};

    fill(last, last + N + 1, -1);
    sort(pts + 1, pts + N + 1);
    lvl = r.size();
    last[lvl] = 0;
    for (int i = 1; i <= N; i++) {
        sumr[i] = sumr[i - 1];
        sumb[i] = sumb[i - 1];
        (pts[i].second == -1 ? sumr[i] : sumb[i]) += pts[i].first;
        lvl += pts[i].second;
        lpos[i] = last[lvl];
        last[lvl] = i;
    }

    for (int i = 1; i <= N; i++) {
        dp[i] = dp[i - 1] + nearist_dist(pts[i].second == -1 ? b : r, pts[i].first);
        if (~lpos[i]) dp[i] = min(dp[i], dp[lpos[i]] + abs((sumr[i] - sumr[lpos[i]]) - (sumb[i] - sumb[lpos[i]])));
    }

    return dp[N];
}