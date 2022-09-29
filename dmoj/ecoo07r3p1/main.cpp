#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
struct pair_hash { template <typename T1, typename T2> std::size_t operator()(const std::pair<T1, T2> &p) const { auto h1 = std::hash<T1>{}(p.first); auto h2 = std::hash<T2>{}(p.second); return h1 ^ h2; } };
template<typename T1, typename T2, typename T3> struct triple { T1 first; T2 second; T3 third; triple() : first{}, second{}, third{} {} triple(const T1 &first, const T2 &second, const T3 &third) : first{ first }, second{ second }, third{ third } {} triple(T1 &&first, T2 &&second, T3 &&third) : first{ first }, second{ second }, third{ third } {} };
template<typename T1, typename T2, typename T3, typename T4> struct quad { T1 first; T2 second; T3 third; T4 fourth; quad() : first{}, second{}, third{}, fourth{} {} quad(const T1 &first, const T2 &second, const T3 &third, const T4 &fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} quad(T1 &&first, T2 &&second, T3 &&third, T4 &&fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} };
template<typename T> inline constexpr const T &_min(const T &x,const T &y) { return x < y ? x: y; }
template<typename T> inline constexpr const T &_max(const T &x,const T &y) { return x < y ? y : x; }
template<typename T, typename...Ts> inline constexpr const T &_min(const T &x,const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename...Ts> inline constexpr const T &_max(const T &x,const Ts &...xs) { return _max(x, _max(xs...)); }
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

bitset<10000001> sieve;
deque<long long> primes;

void sieve_of_eratosthenes() {
    sieve.set();
    sieve[0] = sieve[1] = false;
    for (long long i = 2; i <= 10000000; i++) {
        if (sieve[i]) {
            primes.push_back(i);
            for (long long j = i * i; j <= 10000000; j += i) {
                sieve[j] = false;
            }
        }
    }
    primes.pop_front();
    sieve[2] = false;
}

void solve(int num) {
    if (sieve[num]) {
        printf("%d = %d\n", num, num);
        return;
    }

    for (int i = --upper_bound(primes.begin(), primes.end(), num / 2) - primes.begin(); i >= 0; i--) {
        if (sieve[num - primes[i]]) {
            printf("%d = %lld + %lld\n", num, primes[i], num - primes[i]);
            return;
        }
    }

    for (int i = --upper_bound(primes.begin(), primes.end(), num / 3) - primes.begin(); i >= 0; i--) {
        for (int j = --upper_bound(primes.begin(), primes.end(), (num - primes[i]) / 2) - primes.begin(); j >= i; j--) {
            if (sieve[num - primes[i] - primes[j]]) {
                printf("%d = %lld + %lld + %lld\n", num, primes[i], primes[j], num - primes[i] - primes[j]);
                return;
            }
        }
    }
}

int main() {
    sieve_of_eratosthenes();
    int T = 5;
    while (T--) {
        int num;
        scan(num);
        solve(num);
    }
    return 0;
}