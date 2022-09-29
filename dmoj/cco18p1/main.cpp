#include <iostream>
#include <cstring>

using namespace std;

bool geese[1000], hawks[1000];
int gscore[1000], hscore[1000], N, dp[1000][1000];

int solve(int i, int j) {
    if (i < 0 || j < 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    if ((geese[i] && !hawks[j] && gscore[i] > hscore[j]) || (!geese[i] && hawks[j] && gscore[i] < hscore[j])) {
        dp[i][j] = gscore[i] + hscore[j] + solve(i - 1, j - 1);
    } else {
        dp[i][j] = 0;
    }

    dp[i][j] = max(dp[i][j], max(solve(i - 1, j), solve(i, j - 1)));

    return dp[i][j];
}

int main() {
    scanf("%d", &N);
    string str;
    cin >> str;
    for (int i = 0; i < N; i++) {
        geese[i] = str[i] == 'W';
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", gscore + i);
    }
    cin >> str;
    for (int i = 0; i < N; i++) {
        hawks[i] = str[i] == 'W';
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", hscore + i);
    }
    memset(dp, -1, sizeof dp);
    printf("%d", solve(N - 1, N - 1));
    return 0;
}