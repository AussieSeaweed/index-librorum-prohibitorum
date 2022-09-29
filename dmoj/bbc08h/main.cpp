#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
template<typename T>constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T>constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
#define MOD 1000000007
using namespace std;

long long fact[2000002], ifact[2000002], N;

inline long long powmod(long long base, long long exponent) {
    long long result = 1;
    base %= MOD;
    while (exponent) {
        if (exponent & 1)
            result = result * base % MOD;
        exponent >>= 1;
        base = base * base % MOD;
    }
    return result;
}

inline long long inverse(long long a) {
    return powmod(a, MOD - 2);
}

int main() {
    fact[0] = ifact[0] = 1;
    scan(N);
    for (int i = 1; i <= 2 * N + 1; i++) {
        fact[i] = i * fact[i - 1] % MOD;
        ifact[i] = inverse(fact[i]);
    }

    long long ans = 2 * fact[2 * N + 1] % MOD * ifact[N + 1] % MOD * ifact[N] % MOD;

    printf("%lld\n", (ans - 1 + MOD) % MOD);

    return 0;
}