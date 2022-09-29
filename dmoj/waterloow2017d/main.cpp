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

int N, K;
long long dp[31][901], fact[31], inv[31];

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

void get_factorials() {
    fact[0] = inv[0] = 1;

    for (int i = 1; i <= 30; i++) {
        fact[i] = fact[i - 1] * i % MOD;
        inv[i] = inverse(fact[i]);
    }
}

long long solve(int n, int k) {
    if (~dp[n][k]) return dp[n][k];
    if (n == 0) return dp[n][k] = k == 0;
    if (n == 1) return dp[n][k] = k == 1;

    dp[n][k] = 0;

    for (int i = 0; i < n; i++) {
        int lim = min(k - n, i * (i + 1) / 2);
        for (int j = i; j <= lim; j++) {
            dp[n][k] = (dp[n][k] + solve(i, j) * solve(n - i - 1, k - n - j) % MOD * fact[n - 1] % MOD * inv[i] % MOD * inv[n - i - 1] % MOD) % MOD;
        }
    }

    return dp[n][k];
}

int main() {
    get_factorials();

    scan(N);
    scan(K);

    memset(dp, -1, sizeof dp);
    printf("%lld\n", solve(N, K));
    return 0;
}