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

int N, p[1000000], ans;

int solve() {
    int cur = inf;

    deque<int> l, r;
    int ld = 0, rd = 0;

    for (int i = 0; i < N; i++) {
        int ldist, rdist;

        if (i < p[i]) {
            ldist = i + N - p[i];
            rdist = p[i] - i;
        } else {
            ldist = i - p[i];
            rdist = N - i + p[i];
        }

        if (ldist < rdist)
            l.push_back(ldist);
        else
            r.push_back(rdist);
    }

    sort(l.begin(), l.end()), sort(r.begin(), r.end());
    int ll = unique(l.begin(), l.end()) - l.begin(), rl = unique(r.begin(), r.end()) - r.begin();
    l.resize(ll), r.resize(rl);

    for (int i = 0; i < N; i++) {
        cur = min(cur, max(l.empty() ? 0 : l.back() + ld, r.empty() ? 0 : r.back() + rd));

        rd++, ld--;

        if (!r.empty() && r.back() + rd == N / 2 + 1) {
            r.pop_back();
            l.push_back((N - 1) / 2 - ld);
        }

        if (!l.empty() && l.front() + ld == -1) {
            l.pop_front();
            r.push_front(1 - rd);
        }
    }

    return cur;
}

int main() {
    scan(N);

    for (int i = 0; i < N; i++) {
        int c;
        scan(c);
        p[c - 1] = i;
    }

    ans = solve();

    reverse(p, p + N);

    ans = min(ans, solve());

    printf("%d\n", ans);

    return 0;
}