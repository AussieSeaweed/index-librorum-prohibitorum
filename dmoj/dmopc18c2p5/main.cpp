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

long long N, M, K;
int a[2500];

long long *solve(long long size) {
    if (size == 1) {
        long long *ret = new long long[M + 1];

        for (int i = 0; i <= M; i++)
            ret[i] = 0;

        for (int i = 0; i < K; i++)
            ret[a[i]] = 1;

        return ret;
    } else if (size & 1) {
        long long *dp = solve(size - 1);
        long long *ret = new long long[M + 1];

        for (int i = 0; i <= M; i++)
            ret[i] = 0;

        for (int i = 0; i < K; i++) {
            for (int j = a[i]; j <= M; j++) {
                ret[j] = (ret[j] + dp[j - a[i]]) % MOD;
            }
        }

        delete[] dp;
        return ret;
    } else {
        long long *dp = solve(size / 2);
        long long *ret = new long long[M + 1];

        for (int i = 0; i <= M; i++) {
            ret[i] = 0;
            for (int j = 0; j <= i; j++) {
                ret[i] = (ret[i] + dp[j] * dp[i - j]) % MOD;
            }
        }

        delete[] dp;
        return ret;
    }
}

int main() {
    scan(N);
    scan(M);
    scan(K);
    for (int i = 0; i < K; i++)
        scan(a[i]);
    long long *dp = solve(N);
    long long ans = 0;
    for (int i = 0; i <= M; i++)
        ans = (ans + dp[i]) % MOD;
    printf("%lld\n", ans);
    return 0;
}