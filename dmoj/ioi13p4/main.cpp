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

int N, S[5000], D[5000], combinations[5000];
bool solved[5000];

void reset() {
    for (int i = 0; i < N; i++) {
        combinations[i] = solved[i] ? S[i] : 0;
    }
}

void invert_interval(int lo, int hi) {
    for (int i = lo; i <= hi; i++) {
        combinations[i] = solved[i] ? S[i] : !combinations[i];
    }
}

void solve(int lo, int hi, int cur) {
    if (lo == hi) {
        solved[lo] = true;
        D[lo] = cur;
        S[lo] = !combinations[lo];
    } else {
        int mid = (lo + hi) / 2;
        invert_interval(lo, mid);
        int q = tryCombination(combinations);
        q = ~q ? q : N;
        if (q == cur) {
            solve(mid + 1, hi, cur);
        } else if (q > cur) {
            invert_interval(lo, mid);
            solve(lo, mid, cur);
        } else {
            solve(lo, mid, q);
        }
    }
}

void exploreCave(int N) {
    ::N = N;

    while (true) {
        reset();
        int q = tryCombination(combinations);
        if (!~q) break;
        solve(0, N - 1, q);
    }

    for (int i = 0; i < N; i++) {
        if (!solved[i]) {
            S[i] = combinations[i];
            combinations[i] = !combinations[i];
            D[i] = tryCombination(combinations);
            combinations[i] = !combinations[i];
        }
    }

    answer(S, D);
}