#include <stdio.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

int val[1000];
int dp[2][1000][1000];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int cnt = 0;

    while (++cnt) {
        int N;
        scan(N);

        if (!N) break;

        int total = 0;

        for (int i = 0; i < N; i++) {
            scan(val[i]);
            total += val[i];
            dp[0][i][i] = val[i];
        }

        for (int delta = 1; delta < N; delta++)
            for (int i = 0, j = delta; j < N; i++, j++) {
                dp[1][i][j] = val[i] >= val[j] ? dp[0][i + 1][j] : dp[0][i][j - 1];
                dp[0][i][j] = max(dp[1][i + 1][j] + val[i], dp[1][i][j - 1] + val[j]);
            }

        printf("In game %d, the greedy strategy might lose by as many as %d points.\n", cnt, dp[0][0][N - 1] - total + dp[0][0][N - 1]);
    }

    return 0;
}