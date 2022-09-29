#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
#define MOD 1000000007
using namespace std;

int N, M;
long long X[4001], F[4001], reluct[4001][4001], weight[4001][4001], dp[21][4001];

int main() {
    int t = 10;
    while (t--) {
        scan(N);
        scan(M);

        for (int i = 1; i <= N; i++) {
            scan(X[i]);
            scan(F[i]);
        }

        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                reluct[i][j] = abs(X[i] - X[j]) * F[j];
                reluct[i][j] += reluct[i][j - 1];
            }
        }

        for (int i = 1; i <= N; i++) {
            for (int j = i; j <= N; j++) {
                int lo = i, hi = j;
                while (lo < hi) {
                    int ml = lo + (hi - lo) / 3, mr = hi - (hi - lo) / 3;
                    long long mlw = reluct[ml][j] - reluct[ml][i - 1], mrw = reluct[mr][j] - reluct[mr][i - 1];

                    if (mlw > mrw) {
                        lo = ml + 1;
                    } else {
                        hi = mr - 1;
                    }
                }
                weight[i][j] = min(reluct[hi][j] - reluct[hi][i - 1], reluct[lo][j] - reluct[lo][i - 1]);
            }
        }

        for (int m = 0; m <= M; m++) {
            for (int n = 0; n <= N; n++) {
                dp[m][n] = INF;
            }
        }

        dp[0][0] = 0;

        for (int m = 1; m <= M; m++) {
            for (int i = 1; i <= N; i++) {
                for (int j = 0; j < i; j++) {
                    dp[m][i] = min(dp[m][i], dp[m - 1][j] + weight[j + 1][i]);
                }
            }
        }

        printf("%lld\n", dp[M][N] % MOD);
    }

    return 0;
}