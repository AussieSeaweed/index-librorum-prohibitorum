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
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define MOD 1000000007
using namespace std;

pair<long long, long long> get_fib_pair(unsigned long long N) { // returns {fib(N) + fib(N + 1)}
    if (!N) return {0, 1};
    pair<long long, long long> query = get_fib_pair(N / 2);
    long long a = query.first * ((2 * query.second - query.first) % MOD) % MOD,
                        b = ((query.first * query.first) % MOD + (query.second * query.second) % MOD) % MOD;
    if (N & 1) {
        return {b, (a + b) % MOD};
    } else {
        return {a, b};
    }
}

long long fib(unsigned long long N) {
    return (get_fib_pair(N).first + MOD) % MOD;
}

int main() {
    unsigned long long N;
    scan(N);
    printf("%lld\n", fib(N));
    return 0;
}