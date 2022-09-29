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
#define MOD 1000000007
using namespace std;

char str[200001];
long long N, hash_value[200001], suffix_array[200000], power[200001], ans;

struct CMP1 {
    bool operator()(int i, int j, int iend = N - 1, int jend = N - 1) {
        int sz = min(iend - i + 1, jend - j + 1);
        int lo = 0, hi = sz - 1;
        if ((hash_value[i + sz] - hash_value[i] + MOD) * power[N - i] % MOD == (hash_value[j + sz] - hash_value[j] + MOD) * power[N - j] % MOD)
            return (iend - i) < (jend - j);
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if ((hash_value[i + mid] - hash_value[i] + MOD) * power[N - i] % MOD == (hash_value[j + mid] - hash_value[j] + MOD) * power[N - j] % MOD) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return str[i + lo - 1] < str[j + lo - 1];
    }
} compare;

int lower(int sz) {
    int lo = 0, hi = N - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (compare(suffix_array[mid], 0, N - 1, sz - 1)) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return lo;
}

int upper(int start_index, int sz) {
    int lo = start_index, hi = N - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (suffix_array[mid] <= N - sz && (hash_value[sz] - hash_value[0] + MOD) * power[N] % MOD == (hash_value[suffix_array[mid] + sz] - hash_value[suffix_array[mid]] + MOD) * power[N - suffix_array[mid]] % MOD) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return lo;
}

int num_occurence(int sz) {
    int l = lower(sz);
    return upper(l, sz) - l;
}

int main() {
    scan(N);
    scanf("%s", str);
    power[0] = 1;
    for (int i = 0; i < N; i++) {
        power[i + 1] = 31 * power[i] % MOD;
        hash_value[i + 1] = (hash_value[i] + (str[i] - 'a' + 1) * power[i] % MOD) % MOD;
        suffix_array[i] = i;
    }
    sort(suffix_array, suffix_array + N, compare);
    for (int sz = 1; sz <= N; sz++) { // 0..sz-1, N-sz..N-1
        if ((hash_value[sz] - hash_value[0] + MOD) * power[N] % MOD == (hash_value[N] - hash_value[N - sz] + MOD) * power[sz] % MOD) {
            ans += num_occurence(sz);
        }
    }
    printf("%lld\n", ans);
    return 0;
}