#include <iostream>
#define inf 2000000000
using namespace std;

int bcount[50][1001], N, B;
int brk[1001][1001];
int dp[50][1001][1001];
char str[1001][52];

int count(bool bit, int index, int i, int j) {
    if (i > j) return 0;
    return bit ? (bcount[index][j] - bcount[index][i - 1]) :
           (j - i + 1 - bcount[index][j] + bcount[index][i - 1]);
}

int main() {
    scanf("%d%d", &N, &B);

    for (int i = 0; i < N; i++)
        scanf("%s", str[i]);

    for (int b = 0; b < B; b++) {
        bcount[b][1] = str[0][b] - '0';

        for (int i = 2; i <= N; i++) {
            bcount[b][i] = bcount[b][i - 1] + (str[i - 1][b] - '0');
        }
    }

    // zero starts at i and ends at k, and one starts at k + 1 and ends at j

    for (int i = 1; i <= N; i++) {
        dp[B - 1][i][i] = 0;

        if (str[i - 1][B - 1] - '0') {
            brk[i][i] = i - 1;
        } else {
            brk[i][i] = i;
        }
    }

    for (int offset = 1; offset < N; offset++) {
        for (int i = 1, j = offset + 1; j <= N; i++, j++) {
            dp[B - 1][i][j] = inf;
            for (int k = brk[i][j - 1]; k <= brk[i + 1][j]; k++) {
                int cur = count(true, B - 1, i, k) + count(false, B - 1, k + 1, j);
                if (cur < dp[B - 1][i][j]) {
                    dp[B - 1][i][j] = cur;
                    brk[i][j] = k;
                }
            }
        }
    }

    for (int b = B - 2; b >= 0; b--) {
        for (int i = 1; i <= N; i++) {
            dp[b][i][i] = 0;

            if (str[i - 1][b] - '0') {
                brk[i][i] = i - 1;
            } else {
                brk[i][i] = i;
            }
        }

        for (int offset = 1; offset < N; offset++) {
            for (int i = 1, j = offset + 1; j <= N; i++, j++) {
                dp[b][i][j] = inf;
                for (int k = brk[i][j - 1]; k <= brk[i + 1][j]; k++) {
                    int cur = count(true, b, i, k) + count(false, b, k + 1, j) + dp[b + 1][i][k] + dp[b + 1][k + 1][j];
                    if (cur < dp[b][i][j]) {
                        dp[b][i][j] = cur;
                        brk[i][j] = k;
                    }
                }
            }
        }
    }

    printf("%d\n", dp[0][1][N]);

    return 0;
}