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
#define MOD 1000000009
using namespace std;

inline int one_index(int N, int seq[]) {
    for (int i = 0; i < N; i++)
        if (seq[i] <= N)
            return (i - seq[i] + 1 + N) % N;
    return -1;
}

int valid(int N, int seq[]) {
    unordered_set<int> nums;

    int lim = max(0, one_index(N, seq)), i = lim, elem = 1;

    do {
        if (nums.count(seq[i]))
            return 0;
        if (seq[i] != elem++ && seq[i] <= N)
            return 0;

        nums.insert(seq[i]);
        ++i, i %= N;
    } while (i != lim);

    return 1;
}

int replacement(int N, int seq[], int ans[]) {
    min_priority_queue<pair<int, int>> pq;
    int lim = max(0, one_index(N, seq)), i = lim, p = 1;

    do {
        if (seq[i] > N)
            pq.push(make_pair(seq[i], p));
        ++i, i %= N, ++p;
    } while (i != lim);

    p = N, i = 0;

    while (!pq.empty()) {
        pair<int, int> cur = pq.top();

        ans[i++] = cur.second;

        for (int k = p + 1; k < cur.first; k++)
            ans[i++] = k;

        p = cur.first;
        pq.pop();
    }

    return i;
}

inline long long bin_exp(long long base, long long exp) {
    long long pow = 1;

    while (exp) {
        if (exp & 1)
            pow *= base, pow %= MOD;

        base *= base, base %= MOD;
        exp >>= 1;
    }

    return pow;
}

int countReplacement(int N, int seq[]) {
    if (!valid(N, seq))
        return 0;

    min_priority_queue<int> pq;

    for (int i = 0; i < N; i++)
        if (seq[i] > N)
            pq.push(seq[i]);

    int p = N;
    long long ret = 1;

    while (!pq.empty()) {
        ret *= bin_exp(pq.size(), pq.top() - p - 1), ret %= MOD;
        p = pq.top(), pq.pop();
    }

    if (one_index(N, seq) == -1)
        ret *= N, ret %= MOD;

    return ret;
}