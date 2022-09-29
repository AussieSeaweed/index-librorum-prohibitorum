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
template<typename _EuclideanRingElement> inline _EuclideanRingElement gcd(const _EuclideanRingElement &_m, const _EuclideanRingElement &_n) { return std::__gcd(_m, _n); }
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x : y; }
template<typename T, typename ...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename ...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
template<typename T> inline void scan(T &x) { char c; bool sign; while ((x = getchar()) < '-'); sign = x == '-'; if (sign) while ((x = getchar()) < '0'); for(x -= '0'; '0' <= (c = getchar()); x = (x << 3) + (x << 1) + c - '0'); x = sign ? -x : x; }
template<typename T, typename ...Ts> inline void scan(const T &x, const Ts &...xs) { scan(x), scan(xs...); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
using namespace std;

unsigned long long power[1000000], maxn = 1000000, seed = 29;
char tmp[1000001];

void init() {
    power[0] = 1;
    for (int i = 1; i <= maxn; i++) power[i] = seed * power[i - 1];
}

struct Str {
    char *s;
    unsigned long long *hash;
    int N, base;

    Str(char *s, unsigned long long *hash, int N, int base = 0) : s{ s }, hash{ hash }, N{ N }, base{ base } {}

    int size() const { return N - base; }
    unsigned long long get_hash(int n) const { return (hash[n + base] - hash[base]) * power[maxn - base]; }
    const char &operator[](int i) const { return s[base + i]; }
};

bool operator<(const Str &a, const Str &b) {
    int lo = 0, hi = min(a.size(), b.size());

    while (lo < hi) {
        int mid = (lo + hi) / 2;

        if (a.get_hash(mid + 1) == b.get_hash(mid + 1))
            lo = mid + 1;
        else
            hi = mid;
    }

    return min(a.size(), b.size()) == lo ? a.size() < b.size() : a[lo] < b[lo];
}

void get_input(char *&s, unsigned long long *&hash, int &N) {
    scanf("%s", tmp);
    N = strlen(tmp);

    s = new char[N + 1];
    copy(tmp, tmp + N + 1, s);

    hash = new unsigned long long[N + 1];
    hash[0] = 0;
    for (int i = 0; i < N; i++)
        hash[i + 1] = hash[i] + (s[i] - 'a' + 1) * power[i];
}

char *str;
unsigned long long *hash_value;
int N, K;

int main() {
    init();
    get_input(str, hash_value, N);
    scan(K);

    Str min_value{ str, hash_value, N };

    for (int i = 1; i < N - K + 1; i++)
        min_value = min(min_value, Str{ str, hash_value, N, i });

    for (int i = 0; i < K; i++)
        printf("%c", str[min_value.base + i]);
    printf("\n");

    return 0;
}