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
long long dp[1 << 7][1 << 7], A[1000001], B[1000001];

int main() {
    scan(N);
    scan(K);

    if (N == 1) {
        printf("1\n");
        return 0;
    }

    for (int i = 0; i < min(7, K); i++) {
        int n;
        scan(n);
        while (n--) {
            int x;
            scan(x);
            A[x] |= 1 << i;
        }
    }

    for (int i = 7; i < min(14, K); i++) {
        int n;
        scan(n);
        while (n--) {
            int x;
            scan(x);
            B[x] |= 1 << (i - 7);
        }
    }

    for (int bm = 0; bm < (1 << max(0, min(7, K))); bm++)
        if (!(bm & A[N]))
            dp[bm][B[N]] = 1;

    for (int i = N - 1; i >= 2; i--) {
        long long cur = 0;
        for (int bm = 0; bm < (1 << max(0, min(7, K - 7))); bm++)
            if (!(bm & B[i]))
                cur = (cur + dp[A[i]][bm]) % MOD;

        for (int bm = 0; bm < (1 << max(0, min(7, K))); bm++)
            if (!(bm & A[i]))
                dp[bm][B[i]] = (dp[bm][B[i]] + cur) % MOD;
    }

    long long cur = 0;
    for (int bm = 0; bm < (1 << max(0, min(7, K - 7))); bm++)
        if (!(bm & B[1]))
            cur = (cur + dp[A[1]][bm]) % MOD;

    printf("%lld\n", cur);

    return 0;
}