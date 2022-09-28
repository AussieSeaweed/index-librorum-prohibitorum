#include <iostream>
#define inf 2000000000
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
using namespace std;

int dp[4001][4001];
int cost[4001][4001];
int N, K;

int get(int i, int j) {
    return (cost[j][j] + cost[i - 1][i - 1] - cost[i - 1][j] - cost[j][i - 1]) / 2;
}

void solve(int k, int lo, int hi, int predleft, int predright) {
    if (lo > hi) return;

    int mid = lo + (hi - lo) / 2, lim = min(mid - 1, predright), pred = predleft;
    dp[k][mid] = dp[k - 1][predleft] + get(predleft + 1, mid);

    for (int i = predleft + 1; i <= lim; i++) {
        if (dp[k - 1][i] + get(i + 1, mid) < dp[k][mid]) {
            dp[k][mid] = dp[k - 1][i] + get(i + 1, mid);
            pred = i;
        }
    }

    solve(k, lo, mid - 1, predleft, pred);
    solve(k, mid + 1, hi, pred, predright);
}

int main() {
    scan(N);
    scan(K);

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++) {
            scan(cost[i][j]);
            cost[i][j] += cost[i - 1][j];
            cost[i][j] += cost[i][j - 1];
            cost[i][j] -= cost[i - 1][j - 1];
        }

    fill(begin(dp[0]), end(dp[0]), inf);
        dp[0][0] = 0;

    for (int i = 1; i <= K; i++)
        solve(i, 1, N, 0, N - 1);

    cout << dp[K][N] << '\n';

    return 0;
}
