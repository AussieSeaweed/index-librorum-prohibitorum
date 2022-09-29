#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
#define MOD 1000000001
using namespace std;

int N;
vector<int> bitmasks;
long long dp[2][1 << 11];

long long solve(int num) {
    int h = 0, ph = 1, i = num, last = 0;
    dp[ph][0] = 1;

    for (; i <= N; i *= 2, h = !h, ph = !ph) {
        memset(dp[h], 0, sizeof dp[h]);
        int j = 0;
        for (int k = i; k <= N; k *= 3) j++;
        for (int mask1 : bitmasks) {
            if (mask1 >= (1 << j)) break;
            for (int mask2 : bitmasks) {
                if (mask2 >= (1 << last)) break;
                if (!(mask1 & mask2))
                    dp[h][mask1] = (dp[h][mask1] + dp[ph][mask2]) % MOD;
            }
        }
        last = j;
    }

    long long ans = 0;

    for (int mask : bitmasks)
        ans = (ans + dp[ph][mask]) % MOD;

    return ans;
}

int main() {
    scan(N);

    for (int i = 0; i < (1 << 11); i++)
        if (!(i & (i << 1)) && !(i & (i >> 1)))
            bitmasks.push_back(i);

    long long ans = 1;

    for (int i = 1; i <= N; i++) {
        if (i % 2 && i % 3) {
            ans = ans * solve(i) % MOD;
        }
    }

    printf("%lld\n", ans);

    return 0;
}