#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, K, colors[1000001], pred[1000001];
long long dp[2][1000001], values[1000001];
vector<int> indices[1000001];

int main() {
    scan(N);
    scan(K);

    for (int i = 1; i <= N; i++) {
        scan(colors[i]);
    }

    for (int i = 1; i <= N; i++) {
        scan(values[i]);
        values[i] += values[i - 1];
    }

    for (int i = 1; i <= N; i++) {
        for (int j = pred[colors[i]]; j < indices[colors[i]].size(); j++) {
            int index = indices[colors[i]][j];
            long long cur = dp[0][index - 1] + values[i] - values[index - 1];

            if (dp[1][i] <= cur) {
                dp[1][i] = cur;
                pred[colors[i]] = j;
            }
        }

        dp[0][i] = max(dp[0][i - 1], dp[1][i]);

        indices[colors[i]].push_back(i);
    }

    printf("%lld\n", dp[0][N]);

    return 0;
}