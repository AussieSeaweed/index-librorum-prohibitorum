#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int pies[3000];
int extra[100];
int dp[3001][101][101][2];
int N, M;

int solve(int p, int i, int j, bool takable) {
    if (dp[p][i][j][takable] != -1) return dp[p][i][j][takable];

    dp[p][i][j][takable] = 0;

    if (p == N) {
        if (i < j) {
            if (takable) {
                dp[p][i][j][takable] = extra[j - 1] + solve(p, i, j - 1, false);
            } else {
                dp[p][i][j][takable] = solve(p, i + 1, j, true);
            }
        }
    } else {
        if (takable) {
            dp[p][i][j][takable] = max(
                    (i < j ? extra[j - 1] + solve(p, i, j - 1, false) : 0),
                    max(pies[p] + solve(p + 1, i, j, false), solve(p, i, j, false))
                    );
        } else {
            dp[p][i][j][takable] = max(
                    (i < j ? solve(p, i + 1, j, true) : 0),
                    solve(p + 1, i, j, true)
                    );
        }
    }

    return dp[p][i][j][takable];
}

int main() {
    memset(dp, -1, sizeof dp);

    scanf("%d", &N);

    for (int i = 0; i < N; i++)
        scanf("%d", pies + i);

    scanf("%d", &M);

    for (int i = 0; i < M; i++)
        scanf("%d", extra + i);

    sort(extra, extra + M);

    printf("%d", solve(0, 0, M, true));

    return 0;
}