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

int N, ans, s, e;
char str[25002];
unsigned long long power[25001], fhash[25001], bhash[25002];

unsigned long long hash_forward(int i, int j) {
    return (fhash[j] - fhash[i - 1]) * power[N - i];
}

unsigned long long hash_backward(int i, int j) {
    return (bhash[i] - bhash[j + 1]) * power[j - 1];
}

int main() {
    scan(N);
    scanf("%s", str + 1);

    power[0] = 1;

    for (int i = 1; i <= N; i++) {
        power[i] = power[i - 1] * 29;
        fhash[i] = fhash[i - 1] + ((str[i] - 'A' + 1) * power[i - 1]);
    }

    for (int i = N; i >= 1; i--) {
        bhash[i] = bhash[i + 1] + ((str[i] - 'A' + 1) * power[N - i]);
    }

    for (int i = 1; i <= N; i++) {
        int lo = 0, hi = min(i + 1, N - i + 2);

        while (lo < hi) {
            int mid = (lo + hi) / 2;

            if (hash_forward(i, i + mid - 1) == hash_backward(i - mid + 1, i)) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }

        if (ans < lo * 2 - 3) {
            ans = lo * 2 - 3;
            s = i - lo + 2, e = i + lo - 2;
        }
    }

    for (int i = 1; i <= N - 1; i++) {
        int lo = 0, hi = min(i + 1, N - (i + 1) + 2);

        while (lo < hi) {
            int mid = (lo + hi) / 2;

            if (hash_forward(i + 1, i + mid) == hash_backward(i - mid + 1, i)) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }

        if (ans < lo * 2 - 2) {
            ans = lo * 2 - 2;
            s = i - lo + 2, e = i + 1 + lo - 2;
        }
    }

    for (int i = s; i <= e; i++)
        printf("%c", str[i]);
    printf("\n%d", ans);

    return 0;
}