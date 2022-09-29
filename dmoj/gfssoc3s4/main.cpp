#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
#define MOD 1000000007
using namespace std;

int R, C, dp[100][3000];
vector<int> bitmasks;
vector<int> graph[3000];

int surround(int b) {
    for (int i = 1; i < C;) {
        if (b & (1 << i)) {
            b |= (1 << (i - 1));
            b |= (1 << (i + 1));
            i += 2;
        }
        i++;
    }

    return b;
}

bool compatible(int b1, int b2) {
    return !(surround(b1) & b2);
}

long long solve() {
    dp[R - 1][0] = 1;
    for (int i = 1; i < bitmasks.size(); i++)
        dp[R - 1][i] = 0;

    for (int r = R - 2; r >= 0; r--) {
        for (int i = 0; i < bitmasks.size(); i++) {
            for (int adj : graph[i]) {
                dp[r][i] = (dp[r][i] + dp[r + 1][adj]) % MOD;
            }
        }
    }

    long long total = 0;

    for (int i = 0; i < bitmasks.size(); i++) {
        total = (total + dp[0][i]) % MOD;
    }

    return total - 1;
}

int main() {
    scan(R);
    scan(C);

    for (int i = 0; i < (1 << C); i++)
        if (!(i & (i << 1)) && !(i & (i << 2)) && !(i & 1) && !(i & (1 << (C - 1))))
            bitmasks.push_back(i);

    for (int i = 0; i < bitmasks.size(); i++)
        for (int j = 0; j < bitmasks.size(); j++)
            if (compatible(bitmasks[i], bitmasks[j]))
                graph[i].push_back(j);

    printf("%lld\n", solve());

    return 0;
}