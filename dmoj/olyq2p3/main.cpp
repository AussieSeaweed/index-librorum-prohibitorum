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
using namespace std;

int N, K;
long long cnt[1 << 10], dp[2][101][1 << 10];
vector<int> valid, bitmasks[11], graph[1 << 10];

int main() {
    scan(N);
    scan(K);

    for (int i = 0; i < (1 << N); i++) {
        cnt[i] = __builtin_popcount(i);
        if (!(i & (i << 1)) && !(i & (i >> 1))) {
            valid.push_back(i);
            bitmasks[cnt[i]].push_back(i);
        }
    }

    for (int bm1 : valid)
        for (int bm2 : valid)
            if (!(bm1 & bm2) && !(bm1 & (bm2 << 1)) && !(bm1 & (bm2 >> 1)))
                graph[bm1].push_back(bm2);

    for (int bm : valid)
        dp[0][cnt[bm]][bm] = 1;

    for (int n = 1, h = 1; n < N; n++, h = !h) {
        for (int i = 0; i <= K; i++) {
            for (int bm : valid) {
                dp[h][i][bm] = 0;
                if (cnt[bm] <= i) {
                    for (int adj : graph[bm]) {
                        dp[h][i][bm] += dp[!h][i - cnt[bm]][adj];
                    }
                }
            }
        }
    }

    long long ans = 0;

    for (int i = 0; i < (1 << N); i++)
        ans += dp[(N - 1) & 1][K][i];

    printf("%lld\n", ans);

    return 0;
}