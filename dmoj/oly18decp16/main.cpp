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
#define P 29
#define MOD 1000000007
using namespace std;

int N;
long long str_hash[4000001], power[4000001] {1};
char S[2000001];

struct HASH_ORDER {
    inline bool operator()(const int &a, const int &b) {
        if (S[a] != S[b]) return S[a] > S[b];
        if (a < b) {
            if ((str_hash[a + N] - str_hash[a] + MOD) * power[b - a] % MOD == (str_hash[b + N] - str_hash[b] + MOD) % MOD) return false;
            int lo = 1, hi = N - 1;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if ((str_hash[a + mid] - str_hash[a] + MOD) * power[b - a] % MOD == (str_hash[b + mid] - str_hash[b] + MOD) % MOD) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            return S[(a + hi) % N] > S[(b + hi) % N];
        } else {
            if ((str_hash[b + N] - str_hash[b] + MOD) * power[a - b] % MOD == (str_hash[a + N] - str_hash[a] + MOD) % MOD) return true;
            int lo = 1, hi = N - 1;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if ((str_hash[b + mid] - str_hash[b] + MOD) * power[a - b] % MOD == (str_hash[a + mid] - str_hash[a] + MOD) % MOD) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            return S[(a + hi) % N] > S[(b + hi) % N];
        }
    }
} compare;

int main() {
    cin >> N >> S;
    for (int i = 0; i < N; i++) {
        power[i + 1] = power[i] * P % MOD;
        str_hash[i + 1] = (str_hash[i] + (S[i] - 'A' + 1) * power[i] % MOD) % MOD;
    }
    for (int i = N; i < 2 * N; i++) {
        power[i + 1] = power[i] * P % MOD;
        str_hash[i + 1] = (str_hash[i] + (S[i - N] - 'A' + 1) * power[i] % MOD) % MOD;
    }
    int ans = 0;
    for (int i = 1; i < N; i++)
        if (compare(ans, i))
            ans = i;
    printf("%d\n", ans + 1);
    return 0;
}